#pragma once

#include <concepts>
#include <iostream>

/// @brief: test the concept and crtp part
namespace shucxx2024::concept_crtp
{

struct Point2d
{
    double x;
    double y;
};

/// @brief: add two values with the same type
template <typename T>
T add(T a, T b)
{
    return a + b;
}

/// @brief: require the type T must have valid operator+
template <typename T>
concept must_have_add = requires(T a, T b) {
    { a + b } -> std::same_as<T>;  // std::same_as defined in <concepts>
};

/// @brief: add two values with the same type, and ensure the type T must have
/// valid operator+
template <must_have_add T>
T add_ensure(T a, T b)
{
    return a + b;
}

/// @brief: add two values with the type T is integral or floating point
template <typename T>
    requires std::is_integral_v<T> || std::is_floating_point_v<T>
T add_int_float(T a, T b)
{
    return a + b;
}

/// @brief: judge the type T is iterable or not
template <typename T>
concept is_iterable = requires(T t) {
    t.begin() != t.end();
    ++t.begin();
    *t.begin();
};

template <typename T>
    requires is_iterable<T>
void print_1(const T& t)
{
    for (auto i : t) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

template <is_iterable T>
void print_2(const T& t)
{
    for (auto i : t) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

template <typename T>
auto print_3(const T& t) -> void
    requires is_iterable<T>
{
    for (auto i : t) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

template <typename T>
concept is_iterable_with_size = requires(T t) {
    t.begin() != t.end();
    ++t.begin();
    *t.begin();
    requires requires(T t) {  // requires' requires
        t.size();
    };
};

template <typename T>
concept IntOrFloat = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <template <typename...> class TemplClassT, typename InnerT>
concept is_intger_iterable = requires(TemplClassT<InnerT> t) {
    requires is_iterable<TemplClassT<InnerT>>;
    requires IntOrFloat<InnerT>;
    requires requires(TemplClassT<InnerT> c) { c.size(); };

    requires must_have_add<InnerT>;
};

template <template <typename...> class TemplClassT, typename InnerT>
    requires is_intger_iterable<TemplClassT, InnerT>
void print_vec(const TemplClassT<InnerT>& t)
{
    for (auto i : t) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

/// @brief: A simple example of CRTP
template <typename DerivedT>
class BaseSimple
{
public:
    void interface()
    {
        /// @note: the complier just think this is a function,
        /// even don't kown the detail of implementation
        /// But, when you call the interface function,
        /// the complier will find the implementation function
        static_cast<DerivedT*>(this)->implementation();
    }
};

class DerivedSimple : public BaseSimple<DerivedSimple>
{
    template <typename Any>
    friend class BaseSimple;

    void implementation()
    {
        std::cout << "Derived implementation\n";
    }
};

template <typename>
struct get_raw;

/// @brief: get_raw< std::vector< std::byte > > -> std::byte
template <template <typename...> class TemplateClass, typename InnerType>
struct get_raw<TemplateClass<InnerType>>
{
    using type = InnerType;
};

template <typename T>
using get_raw_t = typename get_raw<T>::type;

template <typename DerivedT>
class BaseComplex
{
public:
    /// @note: bad practice, THIS is not CRTP
    // using RawT = typename DerivedT::RawT;

    using RawT = get_raw_t<DerivedT>;

    void interface(this auto&& self)
    {
        std::cout << "RawT: " << typeid(RawT).name() << std::endl;
        self.implementation();
    };
};

template <typename RawT>
class DerivedComplex;

template <>
class DerivedComplex<int> : public BaseComplex<DerivedComplex<int>>
{
    template <typename Any>
    friend class BaseComplex;

public:
    using RawT = int;

protected:
    void implementation()
    {
        std::cout << "DerivedComplex<int> implementation" << std::endl;
    }
};

void want_to_add();    /// you want to add ?
void want_to_print();  /// print some iterable container
void crtp_test();      /// crtp test

}  // namespace shucxx2024::concept_crtp
