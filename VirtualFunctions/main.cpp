#include <iostream>
#include "Virtuality.h"

VIRTUAL_CLASS(base)
END_CLASS(base)

DECLARE_METHOD(base, both)
    std::cout << "base::both\n";
END_METHOD(base, both)

DECLARE_METHOD(base, only_base)
    std::cout << "base::only_base\n";
END_METHOD(base, only_base)

VIRTUAL_CLASS_DERIVED(derived, base)
END_CLASS_DERIVED(derived, base)

DECLARE_METHOD(derived, both)
    std::cout << "derived::both\n";
END_METHOD(derived, both)

DECLARE_METHOD(derived, only_derived)
    std::cout << "derived::only_derived\n";
END_METHOD(derived, only_derived)



int main() {
    base s;
    derived d;
    std::cout << "base* to base call for both: ";
    VIRTUAL_INVOKE(&s, both)
    std::cout << "derived* to derived call for both: ";
    VIRTUAL_INVOKE(&d, both)
    std::cout << "base* to base call for only_base: ";
    VIRTUAL_INVOKE(&s, only_base)
    std::cout << "derived* to base call for only_derived: ";
    VIRTUAL_INVOKE(&d, only_derived)
    base * pm = reinterpret_cast<base *>(&d);
    std::cout << "base* to derived call for both: ";
    VIRTUAL_INVOKE(pm, both)
    std::cout << "base* to derived call for only_base: ";
    VIRTUAL_INVOKE(pm, only_base)
    try{
        std::cout << "base* to derived call for only_derived: \n";
        VIRTUAL_INVOKE(pm, only_derived)
    } catch(std::runtime_error &e) {
        std::cout << "### invocation error\n";
        std::cout << "### problem: " <<  e.what() << "\n";
    }
}