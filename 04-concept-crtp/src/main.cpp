#include "04-concept-crtp/IntroConcept.hpp"
#include <vector>

namespace shucxx2024::concept_crtp
{

void want_to_add()
{

    Point2d p1{1.0, 2.0};
    Point2d p2{3.0, 4.0};
    // auto p3 = add(p1, p2);

    // auto p4 = add_ensure(p1, p2);

    add_int_float(1.22, 2.);
    add_int_float(0, 1);
    add_int_float('a', 'b');  /// char is int8_t

    // std::println("{},{}", p3.x, p3.y);
}

void want_to_print()
{
    std::vector<int> v{1, 2, 3, 4, 5};
    print_1(v);
    print_2(v);
    print_3(v);
    print_vec(v);
}

void crtp_test()
{
    DerivedSimple d_simple;
    d_simple.interface();

    DerivedComplex<int> d_complex_int;
    d_complex_int.interface();
}

}  // namespace shucxx2024::concept_crtp

int main(int argc, char* argv[])
{
    shucxx2024::concept_crtp::want_to_add();
    shucxx2024::concept_crtp::want_to_print();
    shucxx2024::concept_crtp::crtp_test();
    return 0;
}
