
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cstdlib>
#include <iostream>
#include <tuple>

#include <boost/context/continuation.hpp>

namespace ctx = boost::context;

ctx::continuation f1( ctx::continuation && c) {
    std::cout << "f1: entered first time"  << std::endl;
    c = ctx::callcc( std::move( c) );
    std::cout << "f1: entered second time" << std::endl;
    c = ctx::callcc( std::move( c) );
    std::cout << "f1: entered third time" << std::endl;
    return std::move( c);
}

void f2( ctx::continuation & c) {
    std::cout << "f2: entered" << std::endl;
}

int main() {
    ctx::continuation c = ctx::callcc( f1);
    std::cout << "f1: returned first time" << std::endl;
    c = ctx::callcc( std::move( c) );
    std::cout << "f1: returned second time" << std::endl;
    c = ctx::callcc( std::move( c), ctx::exec_ontop_arg, f2);
    std::cout << "f1: returned third time" << std::endl;

    std::cout << "main: done" << std::endl;

    return EXIT_SUCCESS;
}