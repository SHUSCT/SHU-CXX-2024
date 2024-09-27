#include "shucxx2024/utils.hpp"

struct Foo
{
    Foo();
    Foo(const Foo&);
    ~Foo();
};
extern Foo* first;
extern Foo* last;
extern Foo& foo;

void test2()
{
    shucxx2024::unitialized_fill_v2(first, last, foo);
}