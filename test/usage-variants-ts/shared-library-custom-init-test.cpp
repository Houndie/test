//  (C) Copyright Gennadiy Rozental 2001.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
/// @file
/// @brief shared library usage variant with custom init test
// ***************************************************************************

// Boost.Test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test )
{
    int i = 1;
    BOOST_TEST( i*i == 1 );
}

//____________________________________________________________________________//

bool init_unit_test() {
    boost::unit_test::framework::master_test_suite().p_name.value = "Custom init func";

    return true;
}

//____________________________________________________________________________//

int main(int argc, char* argv[])
{
  return boost::unit_test::unit_test_main( &init_unit_test, argc, argv );
}

//____________________________________________________________________________//

// EOF
