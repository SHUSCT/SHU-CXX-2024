#include "01-introduction-to-cxx/HelloWorld.hpp"
#include "01-introduction-to-cxx/IntroConcept.hpp"

int main()
{
    shucxx2024::sayHello();
    shucxx2024::concept_crtp_test::want_to_add();
    shucxx2024::concept_crtp_test::want_to_print();
    shucxx2024::concept_crtp_test::crtp_test();
    return 0;
}
