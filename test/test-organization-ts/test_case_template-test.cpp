//  (C) Copyright Gennadiy Rozental 2001.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
/// @file
/// @brief tests function template test case
// ***************************************************************************

// Boost.Test
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/results_collector.hpp>
#include <boost/test/utils/nullstream.hpp>
typedef boost::onullstream onullstream_type;

// BOOST
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/list_c.hpp>
#include <boost/scoped_ptr.hpp>

namespace ut = boost::unit_test;
namespace mpl = boost::mpl;

// STL
#include <iostream>

//____________________________________________________________________________//

BOOST_TEST_CASE_TEMPLATE_FUNCTION( test0, Number )
{
    BOOST_TEST( 2 == (int)Number::value );
}

//____________________________________________________________________________//

BOOST_TEST_CASE_TEMPLATE_FUNCTION( test1, Number )
{
    BOOST_TEST( 6 == (int)Number::value );
    BOOST_TEST_REQUIRE( 2 <= (int)Number::value );
    BOOST_TEST( 3 == (int)Number::value );
}

//____________________________________________________________________________//

BOOST_TEST_CASE_TEMPLATE_FUNCTION( test2, Number )
{
    throw Number();
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE( test0_only_2 )
{
    onullstream_type    null_output;

    typedef boost::mpl::list_c<int,2,2,2,2,2,2,2> only_2;
    ut::unit_test_log.set_stream( null_output );

    ut::test_suite* test = BOOST_TEST_SUITE( "" );

    test->add( BOOST_TEST_CASE_TEMPLATE( test0, only_2 ) );

    test->p_default_status.value = ut::test_unit::RS_ENABLED;
    ut::framework::finalize_setup_phase( test->p_id );
    ut::framework::run( test );
    ut::test_results const& tr = ut::results_collector.results( test->p_id );

    ut::unit_test_log.set_stream( std::cout );
    BOOST_TEST( tr.p_assertions_failed == 0U );
    BOOST_TEST( !tr.p_aborted );
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE( test0_one_to_ten )
{
    onullstream_type    null_output;
    ut::test_suite* test = BOOST_TEST_SUITE( "" );

    typedef boost::mpl::range_c<int,0,10> one_to_ten;
    ut::unit_test_log.set_stream( null_output );

    test->add( BOOST_TEST_CASE_TEMPLATE( test0, one_to_ten ) );

    test->p_default_status.value = ut::test_unit::RS_ENABLED;
    ut::framework::finalize_setup_phase( test->p_id );
    ut::framework::run( test );
    ut::test_results const& tr = ut::results_collector.results( test->p_id );

    ut::unit_test_log.set_stream( std::cout );
    BOOST_TEST( tr.p_assertions_failed == 9U );
    BOOST_TEST( !tr.p_aborted );

}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE( test1_one_to_five )
{
    onullstream_type    null_output;
    ut::test_suite* test = BOOST_TEST_SUITE( "" );

    typedef boost::mpl::range_c<int,1,5> one_to_five;
    ut::unit_test_log.set_stream( null_output );
    test->add( BOOST_TEST_CASE_TEMPLATE( test1, one_to_five ) );

    test->p_default_status.value = ut::test_unit::RS_ENABLED;
    ut::framework::finalize_setup_phase( test->p_id );
    ut::framework::run( test );
    ut::test_results const& tr = ut::results_collector.results( test->p_id );

    ut::unit_test_log.set_stream( std::cout );
    BOOST_TEST( tr.p_assertions_failed == 7U );
    BOOST_TEST( !tr.p_aborted );
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE( test2_one_to_three )
{
    onullstream_type    null_output;
    ut::test_suite* test = BOOST_TEST_SUITE( "" );

    typedef boost::mpl::range_c<int,1,3> one_to_three;
    ut::unit_test_log.set_stream( null_output );
    test->add( BOOST_TEST_CASE_TEMPLATE( test2, one_to_three ) );

    test->p_default_status.value = ut::test_unit::RS_ENABLED;
    ut::framework::finalize_setup_phase( test->p_id );
    ut::framework::run( test );
    ut::test_results const& tr = ut::results_collector.results( test->p_id );

    ut::unit_test_log.set_stream( std::cout );
    BOOST_TEST( tr.p_assertions_failed == 2U );
    BOOST_TEST( !tr.p_aborted );
    BOOST_TEST( !tr.passed() );
}

//____________________________________________________________________________//

// EOF
