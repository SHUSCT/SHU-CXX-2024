---
marp: true
---

# Introduce to Concept

---

## What is Concept

就像Rust的trait，Concept是一种对泛型的约束，通过定义不同的Concept，可以限制泛型的使用
并大大提高代码的可读性和可维护性。

---

## A Simple Example

假设我们有一个 `add` 函数，这个函数可以对两个任意相同类型值进行相加，

```cpp
struct Point2d
{
    double x;
    double y;
};

// @brief: add two values with the same type
template <typename T>
T add(T a, T b)
{
    return a + b;
}
```

---

但是对于 `Point2d` 来说，我们显然没有定义 `+` 操作符。然而有意思的是，在使用 `clang++` 编译前，我们的 `clangd` 并没有给出
报错。当然，编译的时候会报错告诉我们 `+` 不合法。

```cpp
namespace shucxx2024::concept_crtp_test
{
void want_to_add()
{

    Point2d p1{1.0, 2.0};
    Point2d p2{3.0, 4.0};
    auto p3 = add(p1, p2);

    std::println("{},{}", p3.x, p3.y);
}
```

---

## Using Concept

### Define Concept

我们可以通过定义一个Concept来限制 `add` 函数的使用，只有当 `T` 满足这个Concept的时候， `add` 函数才能被调用。
例如我们要求 `T` 必须有 `+` 操作符，并且返回值类型必须是 `T` 。

```cpp
template <typename T>
concept must_have_add = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

template <must_have_add T>
T add_ensure(T a, T b)
{
    return a + b;
}
```

---

现在，我们的 `add_ensure` 函数就只能接受满足 `must_have_add` 的类型了。并且会立刻报错。

```cpp
Point2d p1{1.0, 2.0};
Point2d p2{3.0, 4.0};
auto p3 = add(p1, p2);

/// error: no matching function
auto p4 = add_ensure(p1, p2); 
```

---

### how to use Concept?

`Concept` 的使用十分直观，只是在我们的模板参数上写一些语句加以限制。再看 `must_have_add`

```cpp

template <typename T>
concept must_have_add = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};
```

我们对模板参数 `T` 给出了一个要求 `requires` ，并且像函数一样给出了一个函数体，这个函数体就是我们的限制条件。
在里面我们可以写任意的表达式， `requires` 的唯一要求就是这些表达式必须是成立的。

---

例如我们想定义一个 `Concept` 来限制某个泛型必须有迭代器，我们可以这样写：

```cpp
template < typename T >
concept is_iterable = requires(T t) {
    t.begin() != t.end();
    ++t.begin();
    *t.begin();
};
```

对于 `T` ，我们要求它必须有 `begin` 和 `end` 方法，并且 `begin` 返回的类型必须支持 `++` 和 `*` 操作符。

---

我们可以对这样具有迭代器的类型写一个打印方法。只要在定义模板函数时加上 `is_iterable` 的限制即可。
以下三种形式都是可以的。

```cpp
template < typename T >
    requires is_iterable< T >
void print(T t) {
    for (auto i : t) {
        std::cout << i << std::endl;
    }
}

template < is_iterable T >
void print(T t) {
    for (auto i : t) {
        std::cout << i << std::endl;
    }
}

template <typename T>
auto print_3(const T& t) -> void
    requires is_iterable<T>
{
    for (auto i : t) {
        std::print("{} ", i);
    }
    std::println();
}
```

---

个人不太喜欢的写法，本质还是第三种，但可读性可能有点不高？👾

```cpp
template <typename T>
auto print_3(const T& t) -> void requires is_iterable<T>
{
    for (auto i : t) {
        std::print("{} ", i);
    }
    std::println();
}
```

---

### requires of requires

我们可以在 `requires` 语句内部再使用 `requires` 语句，这样我们可以更加灵活的定义 `Concept` 。

```cpp
template < typename T >
concept is_iterable = requires(T t) {
    t.begin() != t.end();
    ++t.begin();
    *t.begin();
    requires requires(T t) { // requires of requires
        t.size();
    };
};
```

本质上来说，一个 `requires` 块组成一个 `Concept` ，然后再使用一个 `requires` 对其进行限制。

---

### A More Complex Example

我们需要限制一个模板参数是模板类的函数，其模板参数中的模板类型必须有 `+` 操作符，并且该模板类必须有 `size` 方法且可迭代。

```cpp
template < typename T >
concept IntOrFloat = std::is_integral_v< T > || std::is_floating_point_v< T >;

template < template < typename ...> class _ClassT, typename U >
concept is_intger_iterable = requires(_ClassT< U > t) {

    requires is_iterable< _ClassT< U > >;
    requires IntOrFloat< U >;
    requires requires(_ClassT< U > c) {
        c.size();
    };

    requires must_have_add< U > ;
    
};
```

---

## CRTP
 
大家可以看看这篇博客，[C++ CRTP基类接口获取子类定义的类型?](https://www.blog.lap-lace.top/post/cpp-crtp/#more)https://www.blog.lap-lace.top/post/cpp-crtp/#more

--- 

### A Simple Example

CRTP是一种模板技术，通过模板继承的方式，可以在编译期间实现多态。我们可以通过CRTP来实现Concept。
下面是一个简单的例子。

```cpp
template <typename DerivedT>
class Base {
public:
    void interface() {
        static_cast<DerivedT*>(this)->implementation();
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() {
        std::cout << "Derived implementation" << std::endl;
    }
};
```

---

### Why CRTP works

CRTP 能够工作的关键在于 C++ 编译器的两阶段名称查找（two-phase name lookup）机制：

1. 第一阶段：在模板定义时，编译器会检查语法和非依赖名称。 
2. 第二阶段：在模板实例化时，编译器会检查依赖名称。
3. 延迟绑定：当基类模板中使用 Derived 类的成员时，这些名称被视为依赖名称。编译器会延迟这些名称的解析，直到模板实例化时。

当编译器首次遇到 `Base` 类模板时，它不会报错说找不到 `implementation()` 。
编译器知道 `Derived` 是一个模板参数，因此假设 `implementation()` 将在 `Derived` 中定义。
当 `Derived` 类实例化 `Base<Derived>` 时，编译器检查 `Derived` 是否真的有 `implementation()` 方法。

--- 

### Why RawT not work

这是一个更复杂的例子，我们想要在基类中获取到模板子类的模板参数，并为其定义一个别名。
但是这报错了，告诉我们找不到 `RawT` 的定义，即使我们加上 `typename` 告诉编译器这是一个类型。

```cpp
template <typename DerivedT>
class BaseComplex
{
public:
    using RawT = typename DerivedT::RawT;

    void interface()
    {
        static_cast<DerivedT*>(this)->implementation();
    };
};
```

---

```cpp
template <typename RawT>
class DerivedComplex;

template <>
class DerivedComplex<int> : public BaseComplex<DerivedComplex<int>>
{
    template <typename Any>
    friend class Base;

public:
    using RawT = int;

protected:
    void implementation()
    {
        std::println("DerivedComplex<int> implementation");
    }
};
```

---

直观理解，当解析 `DerivedComplex<int>` 时，编译器先实例化 `BaseComplex<DerivedComplex<int>>` ，此时还没有得到 `DerivedComplex<int>` 的完整定义，
所以编译器无法找到 `RawT` 的定义。这其实也好理解，因为暂时不知道 `DerivedComplex<int>` 的 `RawT` 到底是什么，编译器还不知道该分配多少内存给 `RawT` 。
因为你很有可能在 `BaseComplex` 类中使用了 `RawT` 。

---

然而这和 `CRTP` 是不一样的，因为 `CRTP` 对函数具有延迟解析，但是对于类型而言，不能进行延迟解析，否则我们依然无法知道到底该分配多少内存。
所以我们无法在 `BaseComplex` 中使用模板参数 `DerivedT` 来获取子类的模板参数。

---

### How to solve

既然无法通过 `DerivedT` 来间接获取，那么我们就直接获取。我们可以利用模板特化的方式获取一个模板类的模板参数。

```cpp
template < typename >
struct get_raw;

/*
 * @brief: get_raw< std::vector< std::byte > > -> std::byte
 */
template < template < typename... > class TemplateClass, typename InnerType >
struct get_raw< TemplateClass< InnerType > > {
    using type = InnerType;
};

template < typename T >
using get_raw_t = typename get_raw< T >::type;

/// @note: use in BaseComplex 
using RawT = get_raw_t<DerivedT>;
```

--- 

我们通过 `get_raw` 的实例化，使得模板类会自动匹配该实例化版本，从而直接获取到模板类的模板参数。

```cpp
get_raw< vector< int > > :: type -> int

template < vector, int >
get_raw< vector< int > > -> int 
```

---

## CRTP in C++23

---

在 `C++23` 之后，我们支持在类中使用显式的 `this` 。例如在上述 `BaseComplex` 中，
我们可以这样改变 `interface` 函数，函数内我们不再需要使用类型转换，
而是通过类的第一关参数就是 `this` 来调用 `implementation` 函数。
当我们使用子类调用的时候， `this` 使得 `self` 被推导为子类的类型。

```cpp
template <typename DerivedT>
class BaseComplex
{
public:

    using RawT = get_raw_t<DerivedT>;

    void interface(this auto&& self)
    {
        std::println("RawT: {}", typeid(RawT).name());
        self.implementation();
    };
};
```
