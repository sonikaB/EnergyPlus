// ObjexxFCL::Array1 Unit Tests
//
// Project: Objexx Fortran Compatibility Library (ObjexxFCL)
//
// Version: 4.0.0
//
// Language: C++
//
// Copyright (c) 2000-2015 Objexx Engineering, Inc. All Rights Reserved.
// Use of this source code or any derivative of it is restricted by license.
// Licensing is available from Objexx Engineering, Inc.:  http://objexx.com

// Google Test Headers
#include <gtest/gtest.h>

// ObjexxFCL Headers
#include <ObjexxFCL/Array1.all.hh>
#include <ObjexxFCL/Array2.all.hh>
#include <ObjexxFCL/Array.functions.hh>
#include <ObjexxFCL/Vector2.hh>
#include <ObjexxFCL/Vector3.hh>
#include "ObjexxFCL.unit.hh"

// C++ Headers
#include <array>
#include <string>
#include <vector>

using namespace ObjexxFCL;
typedef  IndexRange  IR;

TEST( Array1Test, ConstructionEmpty )
{
	Array1D_int v;
	EXPECT_EQ( 0u, v.size() );
	EXPECT_EQ( 0u, v.size1() );
	EXPECT_EQ( 1, v.l() );
	EXPECT_EQ( 1, v.l1() );
	EXPECT_EQ( 0, v.u() );
	EXPECT_EQ( 0, v.u1() );
	EXPECT_EQ( Array1D_int::IR(), v.I() );
	EXPECT_EQ( Array1D_int::IR(), v.I1() );
}

TEST( Array1Test, AllocateZero )
{
	Array1D_int i;
	EXPECT_FALSE( i.allocated() );
	EXPECT_FALSE( allocated( i ) );
	i.allocate( 0 );
	EXPECT_TRUE( i.allocated() );
	EXPECT_TRUE( allocated( i ) );
	EXPECT_EQ( 0u, i.size() );
	EXPECT_EQ( 0u, size( i ) );
}

TEST( Array1Test, ConstructionCopyEmpty )
{
	Array1D_int v;
	Array1D_int c( v );
	EXPECT_EQ( v.size(), c.size() );
	EXPECT_EQ( v.size1(), c.size1() );
	EXPECT_EQ( v.l(),  c.l() );
	EXPECT_EQ( v.l1(), c.l1() );
	EXPECT_EQ( v.u(),  c.u() );
	EXPECT_EQ( v.u1(), c.u1() );
	EXPECT_EQ( v.I(),  c.I() );
	EXPECT_EQ( v.I1(), c.I1() );
}

TEST( Array1Test, ConstructionUninitialized )
{
	Array1D_int v( 22 );
	EXPECT_EQ( 22u, v.size() );
	EXPECT_EQ( 1, v.l() );
	EXPECT_EQ( 1, lbound( v, 1 ) );
	EXPECT_EQ( 22, v.u() );
	EXPECT_EQ( 22, ubound( v, 1 ) );
}

TEST( Array1Test, ConstructionValueInitialized )
{
	Array1D_int v( 22, 33 );
	EXPECT_EQ( 22u, v.size() );
	EXPECT_EQ( 1, v.l() );
	EXPECT_EQ( 22, v.u() );
	for ( int i = 1; i <= 22; ++i ) {
		EXPECT_EQ( 33, v( i ) );
	}
}

TEST( Array1Test, ConstructionInitializerListIndexRange )
{
//	Array1D_double r( Array1D_double::IR( { 1, 3 } ) ); // Unambiguous
	Array1D_double r{ 1, 3 }; // Calls the initializer_list constructor but special code in that treats it as an IndexRange
	EXPECT_EQ( 1, r.l1() );
	EXPECT_EQ( 3, r.u1() );
}

TEST( Array1Test, ConstructionInitializerListOnlyInt )
{
	Array1D_double r{ 1, 2, 3 };
	EXPECT_EQ( 1, r.l1() );
	EXPECT_EQ( 3, r.u1() );
	EXPECT_EQ( 1.0, r( 1 ) );
	EXPECT_EQ( 2.0, r( 2 ) );
	EXPECT_EQ( 3.0, r( 3 ) );
	int v( 0 );
	for ( auto const e : r ) {
		EXPECT_EQ( ++v, e );
	}
}

TEST( Array1Test, ConstructionInitializerListOnlyUnsigned )
{
	Array1D_double r{ 1u, 2u, 3u };
	EXPECT_EQ( 1, r.l1() );
	EXPECT_EQ( 3, r.u1() );
	EXPECT_EQ( 1.0, r( 1 ) );
	EXPECT_EQ( 2.0, r( 2 ) );
	EXPECT_EQ( 3.0, r( 3 ) );
}

TEST( Array1Test, ConstructionInitializerListOnlyDouble )
{
	Array1D_double r{ 1.0, 2.0, 3.0 };
	EXPECT_EQ( 1, r.l1() );
	EXPECT_EQ( 3, r.u1() );
	EXPECT_EQ( 1.0, r( 1 ) );
	EXPECT_EQ( 2.0, r( 2 ) );
	EXPECT_EQ( 3.0, r( 3 ) );
}

TEST( Array1Test, ConstructionInitializerListOnlyString )
{
	Array1D_string r{ "Food", "Hat", "Eggs" };
	EXPECT_EQ( 1, r.l1() );
	EXPECT_EQ( 3, r.u1() );
	EXPECT_EQ( 4u, r( 1 ).length() );
	EXPECT_EQ( 3u, r( 2 ).length() );
	EXPECT_EQ( 4u, r( 3 ).length() );
	EXPECT_EQ( "Food", r( 1 ) );
	EXPECT_EQ( "Hat", r( 2 ) );
	EXPECT_EQ( "Eggs", r( 3 ) );
}

TEST( Array1Test, ConstructionStdArray )
{
	Array1D_int v( std::array< int, 3 >{ { 11, 22, 33 } } );
	EXPECT_EQ( 3u, v.size() );
	EXPECT_EQ( 3u, v.size1() );
	EXPECT_EQ( 1, v.l() );
	EXPECT_EQ( 1, v.l1() );
	EXPECT_EQ( 3, v.u() );
	EXPECT_EQ( 3, v.u1() );
	EXPECT_EQ( 11, v( 1 ) );
	EXPECT_EQ( 22, v( 2 ) );
	EXPECT_EQ( 33, v( 3 ) );
}

TEST( Array1Test, ConstructionStdVector )
{
	Array1D_int v( std::vector< int >{ 11, 22, 33 } );
	EXPECT_EQ( 3u, v.size() );
	EXPECT_EQ( 3u, v.size1() );
	EXPECT_EQ( 1, v.l() );
	EXPECT_EQ( 1, v.l1() );
	EXPECT_EQ( 3, v.u() );
	EXPECT_EQ( 3, v.u1() );
	EXPECT_EQ( Array1D_int::IR( 1, 3 ), v.I() );
	EXPECT_EQ( Array1D_int::IR( 1, 3 ), v.I1() );
	EXPECT_EQ( 11, v( 1 ) );
	EXPECT_EQ( 22, v( 2 ) );
	EXPECT_EQ( 33, v( 3 ) );
}

TEST( Array1Test, ConstructionVector2 )
{
	Array1D_int v( Vector2_int{ { 11, 22 } } );
	EXPECT_EQ( 2u, v.size() );
	EXPECT_EQ( 2u, v.size1() );
	EXPECT_EQ( 1, v.l() );
	EXPECT_EQ( 1, v.l1() );
	EXPECT_EQ( 2, v.u() );
	EXPECT_EQ( 2, v.u1() );
	EXPECT_EQ( 11, v( 1 ) );
	EXPECT_EQ( 22, v( 2 ) );
}

TEST( Array1Test, ConstructionVector3 )
{
	Array1D_int v( Vector3_int{ { 11, 22, 33 } } );
	EXPECT_EQ( 3u, v.size() );
	EXPECT_EQ( 3u, v.size1() );
	EXPECT_EQ( 1, v.l() );
	EXPECT_EQ( 1, v.l1() );
	EXPECT_EQ( 3, v.u() );
	EXPECT_EQ( 3, v.u1() );
	EXPECT_EQ( 11, v( 1 ) );
	EXPECT_EQ( 22, v( 2 ) );
	EXPECT_EQ( 33, v( 3 ) );
}

static void initializer_function( Array1D_string & a )
{
	a( 1 ) = "This";
	a( 2 ) = "is";
	a( 3 ) = "a";
	a( 4 ) = "string";
}

template< typename T >
static void initializer_function_template( Array1D< T > & a )
{
	a( 1 ) = T( 1 );
	a( 2 ) = T( 2 );
	a( 3 ) = T( 3 );
	a( 4 ) = T( 4 );
}

TEST( Array1Test, ConstructionInitializerFunction )
{
	Array1D_string r( 4, { "This", "is", "a", "stub" } );
	initializer_function( r );
	EXPECT_EQ( "This", r( 1 ) );
	EXPECT_EQ( "is", r( 2 ) );
	EXPECT_EQ( "a", r( 3 ) );
	EXPECT_EQ( "string", r( 4 ) );

	Array1D_string const cr( 4, initializer_function );
	EXPECT_EQ( "This", cr( 1 ) );
	EXPECT_EQ( "is", cr( 2 ) );
	EXPECT_EQ( "a", cr( 3 ) );
	EXPECT_EQ( "string", cr( 4 ) );

	Array1D_double const tr( 4, initializer_function_template< double > );
	EXPECT_EQ( 1.0, tr( 1 ) );
	EXPECT_EQ( 2.0, tr( 2 ) );
	EXPECT_EQ( 3.0, tr( 3 ) );
	EXPECT_EQ( 4.0, tr( 4 ) );
}

TEST( Array1Test, ConstructionIndexRange )
{
	Array1D_int r( IR( 1, 5 ), 33 );
	EXPECT_EQ( 1, r.l() );
	EXPECT_EQ( 5, r.u() );
	for ( int i = 1; i <= 5; ++i ) {
		EXPECT_EQ( 33, r( i ) );
		EXPECT_EQ( 33, r[ i - 1 ] );
	}
	Array1A_int a( r, IR( 1, 3 ) );
	EXPECT_EQ( 1, a.l() );
	EXPECT_EQ( 3, a.u() );
	EXPECT_EQ( 33, a[ 0 ] );
	EXPECT_EQ( 33, a[ 2 ] );
}

TEST( Array1Test, ConstructionIndexRangeList )
{
	Array1D_int r( {1,5}, 33 );
	EXPECT_EQ( 1, r.l() );
	EXPECT_EQ( 5, r.u() );
	for ( int i = 1; i <= 5; ++i ) {
		EXPECT_EQ( 33, r( i ) );
		EXPECT_EQ( 33, r[ i - 1 ] );
	}
}

TEST( Array1Test, ConstructionString )
{
	Array1D_string r( 3, std::string( 3, ' ' ) );
	EXPECT_EQ( 1, r.l1() );
	EXPECT_EQ( 3, r.u1() );
	EXPECT_EQ( "   ", r( 1 ) );
}

TEST( Array1Test, ConstructionStringSticky )
{
	Array1D_string r( 3, Sticky_string( std::string( 3, ' ' ) ) );
	EXPECT_EQ( 1, r.l1() );
	EXPECT_EQ( 3, r.u1() );
	EXPECT_EQ( "   ", r( 1 ) );
	EXPECT_EQ( "   ", r( 2 ) );
	EXPECT_EQ( "   ", r( 3 ) );
}

TEST( Array1Test, ConstructionStringMakeSticky )
{
	Array1D_string r( 3, sticky( std::string( 3, ' ' ) ) );
	EXPECT_EQ( 1, r.l1() );
	EXPECT_EQ( 3, r.u1() );
	EXPECT_EQ( "   ", r( 1 ) );
	EXPECT_EQ( "   ", r( 2 ) );
	EXPECT_EQ( "   ", r( 3 ) );
}

TEST( Array1Test, ConstructionStringStickyScalar )
{
	Array1D_string r( 3, make_Sticky( std::string( 2, ' ' ) ), "Map" ); // Initializer overrides sticky string size
	EXPECT_EQ( 1, r.l1() );
	EXPECT_EQ( 3, r.u1() );
	EXPECT_EQ( 3u, r( 1 ).length() );
	EXPECT_EQ( 3u, r( 2 ).length() );
	EXPECT_EQ( 3u, r( 3 ).length() );
	EXPECT_EQ( "Map", r( 1 ) );
	EXPECT_EQ( "Map", r( 2 ) );
	EXPECT_EQ( "Map", r( 3 ) );
	r.allocate( 2 ); // Reallocation uses sticky initialization
	EXPECT_EQ( 1, r.l1() );
	EXPECT_EQ( 2, r.u1() );
	EXPECT_EQ( 2u, r.size() );
	EXPECT_EQ( 2u, r( 1 ).length() );
	EXPECT_EQ( 2u, r( 2 ).length() );
	EXPECT_EQ( std::string( "  " ), r( 1 ) );
	EXPECT_EQ( std::string( "  " ), r( 2 ) );
}

TEST( Array1Test, ConstructionStringInitializerList )
{
	Array1D_string r( 3, { "Food", "Hat", "Eggs" } );
	EXPECT_EQ( 1, r.l1() );
	EXPECT_EQ( 3, r.u1() );
	EXPECT_EQ( 4u, r( 1 ).length() );
	EXPECT_EQ( 3u, r( 2 ).length() );
	EXPECT_EQ( 4u, r( 3 ).length() );
	EXPECT_EQ( "Food", r( 1 ) );
	EXPECT_EQ( "Hat", r( 2 ) );
	EXPECT_EQ( "Eggs", r( 3 ) );
}

TEST( Array1Test, ConstructionStringMakeStickyInitializerList )
{
	Array1D_string r( 3, sticky( std::string( 2, ' ' ) ), { "Food", "Hat", "Eggs" } ); // Strings of different lengths
	EXPECT_EQ( 1, r.l1() );
	EXPECT_EQ( 3, r.u1() );
	EXPECT_EQ( 4u, r( 1 ).length() );
	EXPECT_EQ( 3u, r( 2 ).length() );
	EXPECT_EQ( 4u, r( 3 ).length() );
	EXPECT_EQ( "Food", r( 1 ) );
	EXPECT_EQ( "Hat", r( 2 ) );
	EXPECT_EQ( "Eggs", r( 3 ) );
	r.allocate( 2 ); // Reallocation uses sticky initialization
	EXPECT_EQ( 1, r.l1() );
	EXPECT_EQ( 2, r.u1() );
	EXPECT_EQ( 2u, r.size() );
	EXPECT_EQ( 2u, r( 1 ).length() );
	EXPECT_EQ( 2u, r( 2 ).length() );
	EXPECT_EQ( std::string( "  " ), r( 1 ) );
	EXPECT_EQ( std::string( "  " ), r( 2 ) );
}

TEST( Array1Test, ConstructionIndexRangeInitializerList )
{
	Array1D_int r( IR( -1, 1 ), { 1, 2, 3 } );
	EXPECT_EQ( -1, r.l() );
	EXPECT_EQ( 1, r.u() );
	for ( int i = -1; i <= 1; ++i ) {
		EXPECT_EQ( i + 2, r( i ) );
	}
}

TEST( Array1Test, ConstructionIndexRangeInitializerArray )
{
	Array1D_int r( {-1,1}, Array1D_int( 3, 33 ) );
	EXPECT_EQ( -1, r.l() );
	EXPECT_EQ( 1, r.u() );
	EXPECT_EQ( 33, r( -1 ) );
	EXPECT_EQ( 33, r( 0 ) );
	EXPECT_EQ( 33, r( 1 ) );
}

TEST( Array1Test, ConstructionRange )
{
	Array1D_int c( 3 );
	c( 1 ) = 11;
	c( 2 ) = 22;
	c( 3 ) = 33;
	Array1D_int r1( Array1D_int::range( c ) );
	EXPECT_EQ( 3u, r1.size() );
	EXPECT_EQ( 3u, r1.size1() );
	EXPECT_EQ( 1, r1.l() );
	EXPECT_EQ( 1, r1.l1() );
	EXPECT_EQ( 3, r1.u() );
	EXPECT_EQ( 3, r1.u1() );
	// Values remain uninitialized
	Array1D_int r2( Array1D_int::range( c, 17 ) );
	EXPECT_EQ( 3u, r2.size() );
	EXPECT_EQ( 3u, r2.size1() );
	EXPECT_EQ( 1, r2.l() );
	EXPECT_EQ( 1, r2.l1() );
	EXPECT_EQ( 3, r2.u() );
	EXPECT_EQ( 3, r2.u1() );
	EXPECT_EQ( 17, r2( 1 ) );
	EXPECT_EQ( 17, r2( 2 ) );
	EXPECT_EQ( 17, r2( 3 ) );
}

TEST( Array1Test, ConstructionShape )
{
	Array1D_int c( 3 );
	c( 1 ) = 11;
	c( 2 ) = 22;
	c( 3 ) = 33;
	Array1D_int r1( Array1D_int::shape( c ) );
	EXPECT_EQ( 3u, r1.size() );
	EXPECT_EQ( 3u, r1.size1() );
	EXPECT_EQ( 1, r1.l() );
	EXPECT_EQ( 1, r1.l1() );
	EXPECT_EQ( 3, r1.u() );
	EXPECT_EQ( 3, r1.u1() );
	// Values remain uninitialized
	Array1D_int r2( Array1D_int::shape( c, 17 ) );
	EXPECT_EQ( 3u, r2.size() );
	EXPECT_EQ( 3u, r2.size1() );
	EXPECT_EQ( 1, r2.l() );
	EXPECT_EQ( 1, r2.l1() );
	EXPECT_EQ( 3, r2.u() );
	EXPECT_EQ( 3, r2.u1() );
	EXPECT_EQ( 17, r2( 1 ) );
	EXPECT_EQ( 17, r2( 2 ) );
	EXPECT_EQ( 17, r2( 3 ) );
}

TEST( Array1Test, ConstructionOneBased )
{
	Array1D_int c( 3 );
	c( 1 ) = 11;
	c( 2 ) = 22;
	c( 3 ) = 33;
	Array1D_int r1( Array1D_int::one_based( c ) );
	EXPECT_EQ( 3u, r1.size() );
	EXPECT_EQ( 3u, r1.size1() );
	EXPECT_EQ( 1, r1.l() );
	EXPECT_EQ( 1, r1.l1() );
	EXPECT_EQ( 3, r1.u() );
	EXPECT_EQ( 3, r1.u1() );
	// Values remain uninitialized
}

TEST( Array1Test, ConstructionOneBasedInitializerList )
{
	Array1D_int c( 3 );
	c( 1 ) = 11;
	c( 2 ) = 22;
	c( 3 ) = 33;
	Array1D_int r( Array1D_int::one_based( { 11, 22, 33 } ) );
	EXPECT_EQ( 3u, r.size() );
	EXPECT_EQ( 3u, r.size1() );
	EXPECT_EQ( 1, r.l() );
	EXPECT_EQ( 1, r.l1() );
	EXPECT_EQ( 3, r.u() );
	EXPECT_EQ( 3, r.u1() );
	EXPECT_EQ( 11, r( 1 ) );
	EXPECT_EQ( 22, r( 2 ) );
	EXPECT_EQ( 33, r( 3 ) );
}

TEST( Array1Test, AssignmentBasic )
{
	Array1D_double v( 22, 55.5 );
	Array1D_double const w( 13, 6.789 );
	v = w;
	EXPECT_TRUE( eq( w, v ) );
	v = 45.6;
	EXPECT_EQ( 13u, v.size() );
	for ( int i = 1; i <= 13; ++i ) {
		EXPECT_EQ( 45.6, v( i ) );
	}
}

TEST( Array1Test, ArrayTail )
{
	Array1D_double v( 22, 55.5 );
	v( 20 ) = 20.0;
	v( 21 ) = 21.0;
	v( 22 ) = 22.0;
	ArrayTail_double t( v.a( 20 ) ); // Tail of last 3 values
	EXPECT_EQ( 3u, t.size() );
	Array1A_double p( t );
	EXPECT_EQ( 3u, p.size() );
	EXPECT_EQ( 20.0, p( 1 ) );
	p( 1 ) = 99.0;
	EXPECT_EQ( 99.0, p( 1 ) );
	EXPECT_EQ( 21.0, p( 2 ) );
	EXPECT_EQ( 22.0, p( 3 ) );
}

TEST( Array1Test, ArrayTailConst )
{
	Array1D_double v( 22, 55.5 );
	v( 20 ) = 20.0;
	v( 21 ) = 21.0;
	v( 22 ) = 22.0;
	ArrayTail_double const t( v.a( 20 ) ); // Tail of last 3 values
	EXPECT_EQ( 3u, t.size() );
	Array1A_double const p( t );
	EXPECT_EQ( 3u, p.size() );
	EXPECT_EQ( 20.0, p( 1 ) );
	EXPECT_EQ( 21.0, p( 2 ) );
	EXPECT_EQ( 22.0, p( 3 ) );
}

TEST( Array1Test, ArgConstruct )
{
	Array1D_int u( 10, 22 );
	Array1A_int a( u );
	EXPECT_EQ( u.I(), a.I() );
	EXPECT_EQ( u( 3 ), a( 3 ) );
	EXPECT_TRUE( eq( Array1D_int( 10, 22 ), a ) );
	++a( 3 );
	EXPECT_EQ( u( 3 ), 23 );
	EXPECT_EQ( u( 3 ), a( 3 ) );
}

TEST( Array1Test, ConstArgConstruct )
{
	Array1D_int const u( 10, 22 );
	Array1A_int const a( u );
	EXPECT_EQ( u.I(), a.I() );
	EXPECT_EQ( u( 3 ), a( 3 ) );
	EXPECT_TRUE( eq( Array1D_int( 10, 22 ), a ) );
}

TEST( Array1Test, ProxyAttach )
{
	Array1D_int u( 10, 22 );
	Array1D_int v( 10, 33 );
	Array1A_int p;
	p.attach( u ).dimension( 5 );
	EXPECT_TRUE( eq( Array1D_int( 5, 22 ), p ) );
	p.attach( v );
	EXPECT_TRUE( eq( Array1D_int( 10, 33 ), p ) );
}

TEST( Array1Test, Operators )
{
	Array1D_int A( 3, 33 );
	Array1A_int B( A );
	Array1D_int const C( A );
	A += B;
	EXPECT_TRUE( eq( Array1D_int( 3, 66 ), A ) );
	EXPECT_TRUE( eq( Array1D_int( 3, 66 ), B ) );
	A += 1;
	EXPECT_TRUE( eq( Array1D_int( 3, 67 ), A ) );
	EXPECT_TRUE( eq( Array1D_int( 3, 67 ), B ) );
	A -= 1;
	EXPECT_TRUE( eq( Array1D_int( 3, 66 ), A ) );
	EXPECT_TRUE( eq( Array1D_int( 3, 66 ), B ) );
	A -= C;
	EXPECT_TRUE( eq( Array1D_int( 3, 33 ), A ) );
	EXPECT_TRUE( eq( Array1D_int( 3, 33 ), B ) );
	A /= 3;
	EXPECT_TRUE( eq( Array1D_int( 3, 11 ), A ) );
	EXPECT_TRUE( eq( Array1D_int( 3, 11 ), B ) );
	A *= 3;
	EXPECT_TRUE( eq( Array1D_int( 3, 33 ), A ) );
	EXPECT_TRUE( eq( Array1D_int( 3, 33 ), B ) );
	A /= C;
	EXPECT_TRUE( eq( Array1D_int( 3, 1 ), A ) );
	EXPECT_TRUE( eq( Array1D_int( 3, 1 ), B ) );
	A *= C;
	EXPECT_TRUE( eq( Array1D_int( 3, 33 ), A ) );
	EXPECT_TRUE( eq( Array1D_int( 3, 33 ), B ) );
}

TEST( Array1Test, Index )
{
	Array1D_int A( 3, 6 );
	Array1D_int const C( 3, 6 );

	EXPECT_EQ( 2u, A.index( 3 ) );
	EXPECT_EQ( 5u, A.index( 6 ) );
	EXPECT_EQ( 2u, C.index( 3 ) );
	EXPECT_EQ( 5u, C.index( 6 ) );

	EXPECT_EQ( 1u, A.index( 2 ) );
}

TEST( Array1Test, OperatorBrackets )
{
	Array1D_int A( 3 );
	A[ 0 ] = 11;
	A[ 1 ] = 22;
	A[ 2 ] = 33;
	EXPECT_EQ( 11, A[ 0 ] );
	EXPECT_EQ( 22, A[ 1 ] );
	EXPECT_EQ( 33, A[ 2 ] );

	Array1D_int const C( 3, { 11, 22, 33 } );
	EXPECT_EQ( 11, C[ 0 ] );
	EXPECT_EQ( 22, C[ 1 ] );
	EXPECT_EQ( 33, C[ 2 ] );
}

TEST( Array1Test, Contains )
{
	Array1D_int A( { 11, 22, 33 } );

	EXPECT_TRUE( A.contains( 1 ) && A.contains( 2 ) && A.contains( 3 ) );
	EXPECT_FALSE( ! A.contains( 11 ) && A.contains( 22 ) && A.contains( 33 ) );
	EXPECT_FALSE( A.contains( 4 ) );
	EXPECT_FALSE( A.contains( -1 ) );
}

TEST( Array1Test, AllocateDeallocate )
{
	Array1D_double A1;
	EXPECT_EQ( 0u, A1.size() );
	EXPECT_EQ( 1, A1.l() );
	EXPECT_EQ( 0, A1.u() );
	EXPECT_FALSE( A1.allocated() );
	A1.allocate( 3 );
	EXPECT_EQ( 3u, A1.size() );
	EXPECT_EQ( 1, A1.l() );
	EXPECT_EQ( 3, A1.u() );
	EXPECT_TRUE( A1.allocated() );
	A1.deallocate();
	EXPECT_EQ( 0u, A1.size() );
	EXPECT_EQ( 1, A1.l() );
	EXPECT_EQ( 0, A1.u() );
	EXPECT_FALSE( allocated( A1 ) );

	Array1D_double A2( { 1.1, 2.2, 3.3 } );
	EXPECT_EQ( 3u, A2.size() );
	EXPECT_EQ( 1, A2.l() );
	EXPECT_EQ( 3, A2.u() );
	EXPECT_TRUE( allocated( A2 ) );
	deallocate( A2 );
	EXPECT_EQ( 0u, A1.size() );
	EXPECT_EQ( 1, A1.l() );
	EXPECT_EQ( 0, A1.u() );
	EXPECT_FALSE( allocated( A2 ) );
}

static void dimension_initializer_function( Array1D_int & A )
{
	for ( int i = A.l(); i <= A.u(); ++i ) {
		A( i ) = i * 10 + i;
	}
}

TEST( Array1Test, Dimension )
{
	Array1D_int A( 3 );
	EXPECT_EQ( 1, A.l() );
	EXPECT_EQ( 3, A.u() );
	EXPECT_EQ( 3u, A.size() );

	A.dimension( { 3, 7 } );
	EXPECT_EQ( 3, A.l() );
	EXPECT_EQ( 7, A.u() );
	EXPECT_EQ( 5u, A.size() );

	A.dimension( { 2, 4 }, 17 );
	EXPECT_EQ( 2, A.l() );
	EXPECT_EQ( 4, A.u() );
	EXPECT_EQ( 3u, A.size() );
	EXPECT_EQ( 17, A( 2 ) );
	EXPECT_EQ( 17, A( 3 ) );
	EXPECT_EQ( 17, A( 4 ) );

	A.dimension( { 4, 6 }, dimension_initializer_function );
	EXPECT_EQ( 4, A.l() );
	EXPECT_EQ( 6, A.u() );
	EXPECT_EQ( 3u, A.size() );
	EXPECT_EQ( 44, A( 4 ) );
	EXPECT_EQ( 55, A( 5 ) );
	EXPECT_EQ( 66, A( 6 ) );

	A.dimension( Array1D_int( { 3, 7 } ) );
	EXPECT_EQ( 3, A.l() );
	EXPECT_EQ( 7, A.u() );
	EXPECT_EQ( 5u, A.size() );

	A.dimension( Array1D_int( { 2, 4 } ), 17 );
	EXPECT_EQ( 2, A.l() );
	EXPECT_EQ( 4, A.u() );
	EXPECT_EQ( 3u, A.size() );
	EXPECT_EQ( 17, A( 2 ) );
	EXPECT_EQ( 17, A( 3 ) );
	EXPECT_EQ( 17, A( 4 ) );

	A.dimension( Array1D_int( { 4, 6 } ), dimension_initializer_function );
	EXPECT_EQ( 4, A.l() );
	EXPECT_EQ( 6, A.u() );
	EXPECT_EQ( 3u, A.size() );
	EXPECT_EQ( 44, A( 4 ) );
	EXPECT_EQ( 55, A( 5 ) );
	EXPECT_EQ( 66, A( 6 ) );
}

TEST( Array1Test, Redimension )
{
	Array1D_int A( 5, { 11, 22, 33, 44, 55 } );

	EXPECT_EQ( 1, A.l() );
	EXPECT_EQ( 5, A.u() );
	EXPECT_EQ( 5u, A.size() );
	EXPECT_EQ( 11, A( 1 ) );
	EXPECT_EQ( 22, A( 2 ) );
	EXPECT_EQ( 33, A( 3 ) );
	EXPECT_EQ( 44, A( 4 ) );
	EXPECT_EQ( 55, A( 5 ) );

	A.redimension( { 3, 7 } );
	EXPECT_EQ( 3, A.l() );
	EXPECT_EQ( 7, A.u() );
	EXPECT_EQ( 5u, A.size() );
	EXPECT_EQ( 33, A( 3 ) );
	EXPECT_EQ( 44, A( 4 ) );
	EXPECT_EQ( 55, A( 5 ) );

	A.redimension( { 0, 4 }, 17 );
	EXPECT_EQ( 0, A.l() );
	EXPECT_EQ( 4, A.u() );
	EXPECT_EQ( 5u, A.size() );
	EXPECT_EQ( 17, A( 0 ) );
	EXPECT_EQ( 17, A( 1 ) );
	EXPECT_EQ( 17, A( 2 ) );
	EXPECT_EQ( 33, A( 3 ) );
	EXPECT_EQ( 44, A( 4 ) );

	Array1D_int B( 5, { 11, 22, 33, 44, 55 } );

	B.redimension( Array1D_int( { 3, 7 } ) );
	EXPECT_EQ( 3, B.l() );
	EXPECT_EQ( 7, B.u() );
	EXPECT_EQ( 5u, B.size() );
	EXPECT_EQ( 33, B( 3 ) );
	EXPECT_EQ( 44, B( 4 ) );
	EXPECT_EQ( 55, B( 5 ) );

	B.redimension( Array1D_int( { 0, 4 } ), 17 );
	EXPECT_EQ( 0, B.l() );
	EXPECT_EQ( 4, B.u() );
	EXPECT_EQ( 5u, B.size() );
	EXPECT_EQ( 17, B( 0 ) );
	EXPECT_EQ( 17, B( 1 ) );
	EXPECT_EQ( 17, B( 2 ) );
	EXPECT_EQ( 33, B( 3 ) );
	EXPECT_EQ( 44, B( 4 ) );

	{
		Array1D_int A( 5, 1 );
		A.redimension( { 1, 5 }, 2 );
		EXPECT_EQ( 1, A.l() );
		EXPECT_EQ( 5, A.u() );
		EXPECT_TRUE( eq( A, 1 ) );
	}

	{
		Array1D_int A( 5, 1 );
		A.redimension( { 2, 4 }, 2 );
		EXPECT_EQ( 2, A.l() );
		EXPECT_EQ( 4, A.u() );
		EXPECT_TRUE( eq( A, 1 ) );
	}

	{
		Array1D_int A( 5, 1 );
		A.redimension( { -2, 0 }, 2 );
		EXPECT_EQ( -2, A.l() );
		EXPECT_EQ( 0, A.u() );
		EXPECT_TRUE( eq( A, 2 ) );
	}

	{
		Array1D_int A( 5, 1 );
		A.redimension( { 7, 9 }, 2 );
		EXPECT_EQ( 7, A.l() );
		EXPECT_EQ( 9, A.u() );
		EXPECT_TRUE( eq( A, 2 ) );
	}

	{
		Array1D_int A( 2, 1 );
		A.redimension( { -1, 4 }, 2 );
		EXPECT_EQ( -1, A.l() );
		EXPECT_EQ( 4, A.u() );
		EXPECT_EQ( 2, A( -1 ) );
		EXPECT_EQ( 2, A( 0 ) );
		EXPECT_EQ( 1, A( 1 ) );
		EXPECT_EQ( 1, A( 2 ) );
		EXPECT_EQ( 2, A( 3 ) );
		EXPECT_EQ( 2, A( 4 ) );
	}

	{
		Array1D_int A( 2, 1 );
		A.redimension( { -1, 2 }, 2 );
		EXPECT_EQ( -1, A.l() );
		EXPECT_EQ( 2, A.u() );
		EXPECT_EQ( 2, A( -1 ) );
		EXPECT_EQ( 2, A( 0 ) );
		EXPECT_EQ( 1, A( 1 ) );
		EXPECT_EQ( 1, A( 2 ) );
	}

	{
		Array1D_int A( 2, 1 );
		A.redimension( { -1, 1 }, 2 );
		EXPECT_EQ( -1, A.l() );
		EXPECT_EQ( 1, A.u() );
		EXPECT_EQ( 2, A( -1 ) );
		EXPECT_EQ( 2, A( 0 ) );
		EXPECT_EQ( 1, A( 1 ) );
	}

	{
		Array1D_int A( 2, 1 );
		A.redimension( { 2, 4 }, 2 );
		EXPECT_EQ( 2, A.l() );
		EXPECT_EQ( 4, A.u() );
		EXPECT_EQ( 1, A( 2 ) );
		EXPECT_EQ( 2, A( 3 ) );
		EXPECT_EQ( 2, A( 4 ) );
	}
}

TEST( Array1Test, Swap )
{
	Array1D_int A( 4, 11 );
	Array1D_int( 5, 22 ).swap( A );
	EXPECT_EQ( IR( 1, 5 ), A.I() );
	EXPECT_EQ( 5u, A.size() );
	for ( int i = A.l(); i <= A.u(); ++i ) {
		EXPECT_EQ( 22, A( i ) );
	}
}

TEST( Array1Test, Functions )
{
	Array1D_int u{ 1, 2, 3 };
	Array1D_int v{ 2, 3, 4 };
	EXPECT_EQ( 14, magnitude_squared( u ) );
	EXPECT_EQ( 3, distance_squared( u, v ) );
	EXPECT_EQ( 20, dot( u, v ) );
}

TEST( Array1Test, Dot )
{
	Array1D_int A( 3 );
	Array1D_int B( 3 );
	A( 1 ) = 4;
	A( 2 ) = 3;
	A( 3 ) = 5;
	B( 1 ) = 7;
	B( 2 ) = 5;
	B( 3 ) = 4;
	EXPECT_EQ( 63, dot( A, B ) );
	EXPECT_EQ( 63, dot( B, A ) );
	EXPECT_EQ( 63, dot_product( A, B ) );
	EXPECT_EQ( 63, dot_product( B, A ) );
}

TEST( Array1Test, EoshiftPos )
{
	Array1D_int A( 5, { 1, 2, 3, 4, 5 } );
	EXPECT_TRUE( eq( Array1D_int( { 3, 4, 5, 0, 0 } ), eoshift( A, 2 ) ) );
	EXPECT_TRUE( eq( Array1D_int( { 3, 4, 5, 9, 9 } ), eoshift( A, 2, 9 ) ) );
}

TEST( Array1Test, EoshiftNeg )
{
	Array1D_int A( 5, { 1, 2, 3, 4, 5 } );
	EXPECT_TRUE( eq( Array1D_int( { 0, 0, 1, 2, 3 } ), eoshift( A, -2 ) ) );
	EXPECT_TRUE( eq( Array1D_int( { 8, 8, 1, 2, 3 } ), eoshift( A, -2, 8 ) ) );
}

TEST( Array1Test, EoshiftMoveAssignment )
{
	Array1D_int A( { 0, 4 }, { 0, 1, 2, 3, 4 } ); // Not 1-based
	A = eoshift( A, 2 ); // eoshift is 1-based but move assignment is conformable so A index ranges shouldn't change
	EXPECT_TRUE( eq( Array1D_int( { 0, 4 }, { 2, 3, 4, 0, 0 } ), A ) );
	EXPECT_TRUE( equal_dimensions( Array1D_int( { 0, 4 }, { 2, 3, 4, 0, 0 } ), A ) ); // Conformable move shouldn't change index ranges
}

TEST( Array1Test, CshiftPos )
{
	Array1D_int A( 5, { 1, 2, 3, 4, 5 } );
	EXPECT_TRUE( eq( Array1D_int( { 3, 4, 5, 1, 2 } ), cshift( A, 2 ) ) );
}

TEST( Array1Test, CshiftNeg )
{
	Array1D_int A( 5, { 1, 2, 3, 4, 5 } );
	EXPECT_TRUE( eq( Array1D_int( { 4, 5, 1, 2, 3 } ), cshift( A, -2 ) ) );
}

TEST( Array1Test, Cross )
{
	Array1D_int A( 3, 33 ), B( 44 - A );
	EXPECT_TRUE( eq( cross( A, B ), cross_product( A, B ) ) );
}

TEST( Array1Test, ProxyConstCorrectness )
{
	Array1D_int const v( 3, 33 );
	Array1A_int p( v ); // Proxy for const array
	EXPECT_TRUE( eq( v, p ) );
	Array1A_int s( v.a( 2 ) ); // Proxy for const array from section of elements (2,3)
	Array1A_int const & sc( s ); // Const proxy for const array from section of elements (2,3)
	EXPECT_EQ( 33, sc( 2 ) ); // OK because const subscript op used
	EXPECT_EQ( 2u, s.size() ); // Lookup triggers assert fail with const proxy checks because non-const subscript op used: OK if p is declared const
}

TEST( Array1Test, Generators )
{
	Array1D_double A( 3, 22.0 ), B( 3, 11.0 );
	EXPECT_TRUE( eq( B, A / 2.0 ) );
	//EXPECT_TRUE( eq( B, A / 2 ) ); // This doesn't compile: Won't convert
}

TEST( Array1Test, FunctionAllocateDeallocate )
{
	Array1D_double A1;
	EXPECT_FALSE( allocated( A1 ) );
	allocate( A1, 3 );
	EXPECT_TRUE( allocated( A1 ) );
	deallocate( A1 );
	EXPECT_FALSE( allocated( A1 ) );

	Array1D_double A2( { 1.0, 2.01, 3.012 } );
	EXPECT_TRUE( allocated( A2 ) );
	deallocate( A2 );
	EXPECT_FALSE( allocated( A2 ) );
}

TEST( Array1Test, FunctionAllAny )
{
	Array1D_bool A1( { true, true, true } );
	EXPECT_TRUE( all( A1 ) );
	EXPECT_TRUE( any( A1 ) );
	EXPECT_FALSE( all( ! A1 ) );
	EXPECT_FALSE( any( ! A1 ) );

	Array1D_bool A2( { false, false, false } );
	EXPECT_FALSE( all( A2 ) );
	EXPECT_FALSE( any( A2 ) );
	EXPECT_TRUE( all( ! A2 ) );
	EXPECT_TRUE( any( ! A2 ) );

	Array1D_bool A3( { false, false, true } );
	EXPECT_FALSE( all( A3 ) );
	EXPECT_TRUE( any( A3 ) );
	EXPECT_FALSE( all( ! A3 ) );
	EXPECT_TRUE( any( ! A3 ) );
}

TEST( Array1Test, FunctionCount )
{
	Array1D_bool A1( { true, true, true, true, true } );
	EXPECT_EQ( 5u, count( A1 ) );
	EXPECT_EQ( 5u, count( A1, 1 ) );

	Array1D_bool A2( { true, false, true, false, true } );
	EXPECT_EQ( 3u, count( A2 ) );
	EXPECT_EQ( 3u, count( A2, 1 ) );

	Array1D_bool A3( { false, false, false, false, false } );
	EXPECT_EQ( 0u, count( A3 ) );
	EXPECT_EQ( 0u, count( A3, 1 ) );
}

TEST( Array1Test, FunctionIsContiguous )
{
	Array1D_double A;
	EXPECT_TRUE( contiguous( A ) );
}

TEST( Array1Test, FunctionLUBound )
{
	Array1D_double A( { 1.0, 2.0, 3.0, 4.0, 5.0 } );
	Array1D_int E11( 1, { 1.0 } );
	Array1D_int E12( 1, { 5.0 } );
	EXPECT_TRUE( eq( E11, lbound( A ) ) );
	EXPECT_TRUE( eq( E12, ubound( A ) ) );
	int const E21 = 1.0;
	int const E22 = 5.0;
	EXPECT_EQ( E21, lbound( A, 1 ) );
	EXPECT_EQ( E22, ubound( A, 1 ) );
}

TEST( Array1Test, FunctionShape )
{
	Array1D_double A( { 1.0, 2.0, 3.0, 4.0, 5.0 } );
	Array1D_int E1( 1, 5 );
	EXPECT_TRUE( eq( E1, shape( A ) ) );
}

TEST( Array1Test, FunctionSize )
{
	int const N = 10;
	Array1D_double A( N );
	EXPECT_EQ( unsigned( N ), size( A ) );
	EXPECT_EQ( unsigned( N ), size( A, 1 ) );
	EXPECT_EQ( A.size(), size( A ) );
}

TEST( Array1Test, FunctionISize )
{
	int const N = 10;
	Array1D_double A( N );
	EXPECT_EQ( N, isize( A ) );
	EXPECT_EQ( N, isize( A, 1 ) );
	EXPECT_EQ( int( size( A ) ), isize( A ) );
}

TEST( Array1Test, FunctionReshape )
{
	Array1D_double A( { 1.0, 2.0, 3.0, 4.0, 5.0 } );
	EXPECT_EQ( 5u, A.size() );
	Array1D_double E( { 1.0, 2.0, 3.0, 4.0, 5.0 } );
	EXPECT_TRUE( eq( E, reshape( A, std::array< int, 1 >{ { 5 } } ) ) );
	EXPECT_TRUE( eq( E, reshape( { 1.0, 2.0, 3.0, 4.0, 5.0 }, std::array< int, 1 >{ { 5 } } ) ) );
	EXPECT_TRUE( eq( E, reshape1( A, Array1D_int( 1, { 5 } ) ) ) );
#if defined(_MSC_VER) && !defined(__INTEL_COMPILER) // VC++2013 bug work-around
	EXPECT_TRUE( eq( E, reshape1( A, std::initializer_list< int >( { 5 } ) ) ) );
#else
	EXPECT_TRUE( eq( E, reshape1( A, { 5 } ) ) );
#endif
	EXPECT_TRUE( eq( E, reshape1( { 1.0, 2.0, 3.0, 4.0, 5.0 }, Array1D_int( 1, { 5 } ) ) ) );
}

TEST( Array1Test, FunctionPack )
{
	Array1D_double A1;
	Array1D_double const E1;
	EXPECT_TRUE( eq( E1, pack( A1, false ) ) );
	EXPECT_TRUE( eq( E1, pack( A1, true ) ) );

	Array1D_double A2( { 1.0, 2.0, 3.0, 4.0, 5.0 } );
	Array1D_double const E2( { 1.0, 2.0, 3.0, 4.0, 5.0 } );
	EXPECT_TRUE( eq( E1, pack( A2, false ) ) );
	EXPECT_TRUE( eq( E2, pack( A2, true ) ) );

	Array1D_double A3( { 1.0, 2.0, 3.0, 4.0, 5.0 } );
	Array1D_double const E3( { 2.0, 4.0 } );
	Array1D_bool const M( { false, true, false, true, false } );
	EXPECT_TRUE( eq( E3, pack( A3, M ) ) );
}

TEST( Array1Test, FunctionCShift )
{
	Array1D_double A( { 1.0, 2.0, 3.0, 4.0, 5.0 } );
	EXPECT_TRUE( eq( A, cshift( A, 0 ) ) );
	EXPECT_TRUE( eq( A, cshift( A, 0, 1 ) ) );

	Array1D_double const E1( { 2.0, 3.0, 4.0, 5.0, 1.0 } );
	EXPECT_TRUE( eq( E1, cshift( A, 1 ) ) );
	EXPECT_TRUE( eq( E1, cshift( A, 1, 1 ) ) );

	Array1D_double const E2( { 3.0, 4.0, 5.0, 1.0, 2.0 } );
	EXPECT_TRUE( eq( E2, cshift( A, 2 ) ) );
	EXPECT_TRUE( eq( E2, cshift( A, 2, 1 ) ) );

	Array1D_double const E3( { 5.0, 1.0, 2.0, 3.0, 4.0 } );
	EXPECT_TRUE( eq( E3, cshift( A, -1 ) ) );
	EXPECT_TRUE( eq( E3, cshift( A, -1, 1 ) ) );
}

TEST( Array1Test, FunctionEOShift )
{
	Array1D_double A( { 1.0, 2.0, 3.0, 4.0, 5.0 } );
	EXPECT_TRUE( eq( A, eoshift( A, 0 ) ) );

	Array1D_double const E11( { 2.0, 3.0, 4.0, 5.0, 0.0 } );
	Array1D_double const E12( { 2.0, 3.0, 4.0, 5.0, 17.0 } );
	EXPECT_TRUE( eq( E11, eoshift( A, 1 ) ) );
	EXPECT_TRUE( eq( E12, eoshift( A, 1, 17.0 ) ) );
	EXPECT_TRUE( eq( E11, eoshift( A, 1, 0.0, 1 ) ) );

	Array1D_double const E21( { 3.0, 4.0, 5.0, 0.0, 0.0 } );
	Array1D_double const E22( { 3.0, 4.0, 5.0, 17.0, 17.0 } );
	EXPECT_TRUE( eq( E21, eoshift( A, 2 ) ) );
	EXPECT_TRUE( eq( E22, eoshift( A, 2, 17.0 ) ) );
	EXPECT_TRUE( eq( E21, eoshift( A, 2, 0.0, 1 ) ) );

	Array1D_double const E31( { 0.0, 1.0, 2.0, 3.0, 4.0 } );
	Array1D_double const E32( { 17.0, 1.0, 2.0, 3.0, 4.0 } );
	EXPECT_TRUE( eq( E31, eoshift( A, -1 ) ) );
	EXPECT_TRUE( eq( E32, eoshift( A, -1, 17.0 ) ) );
	EXPECT_TRUE( eq( E31, eoshift( A, -1, 0.0, 1 ) ) );
}

TEST( Array1Test, FunctionSum )
{
	Array1D_double A( { 1.0, 2.0, 3.0, 4.0, 5.0 } );
	double const E1 = 15.0;
	EXPECT_EQ( E1, sum( A ) );
	EXPECT_EQ( E1, sum( A, 1 ) );
	Array1D_bool M( { true, false, true, false, true } );
	double const E2 = 9.0;
	EXPECT_EQ( E2, sum( A, M ) );
}

TEST( Array1Test, FunctionProduct )
{
	Array1D_double A( { 1.0, 2.0, 3.0, 4.0, 5.0 } );
	double const E1 = 120.0;
	EXPECT_EQ( E1, product( A ) );
	EXPECT_EQ( E1, product( A, 1 ) );
	Array1D_bool M( { true, false, true, false, true } );
	double const E2 = 15.0;
	EXPECT_EQ( E2, product( A, M ) );
}

TEST( Array1Test, FunctionAbs )
{
	Array1D_int A( { -1, -2, -3 } );
	Array1D_int const E( { 1, 2, 3 } );
	EXPECT_TRUE( eq( E, abs( A ) ) );
}

TEST( Array1Test, FunctionPow )
{
	Array1D_int A( { 1, 2, 3 } );
	Array1D_int const E( { 1, 4, 9 } );
	EXPECT_TRUE( eq( E, pow( A, 2 ) ) );
}

TEST( Array1Test, FunctionSign )
{
	Array1D_int A1( { 1, 2, 3 } );
	Array1D_int const E11( { 1, 2, 3 } );
	Array1D_int const E12( { -1, -2, -3 } );
	EXPECT_TRUE( eq( E11, sign( A1, 1 ) ) );
	EXPECT_TRUE( eq( E11, sign( A1, 0 ) ) );
	EXPECT_TRUE( eq( E12, sign( A1, -1 ) ) );

	Array1D_int A2( { -1, -2, -3 } );
	Array1D_int const E21( { 1, 2, 3 } );
	Array1D_int const E22( { -1, -2, -3 } );
	EXPECT_TRUE( eq( E21, sign( A2, 1 ) ) );
	EXPECT_TRUE( eq( E21, sign( A2, 0 ) ) );
	EXPECT_TRUE( eq( E22, sign( A2, -1 ) ) );

	Array1D_int A3( { 1, -2, 3 } );
	Array1D_int const E31( { 1, -1, 1 } );
	Array1D_int const E32( { 0, 0, 0 } );
	EXPECT_TRUE( eq( E31, sign( 1,  A3 ) ) );
	EXPECT_TRUE( eq( E32, sign( 0,  A3 ) ) );
	EXPECT_TRUE( eq( E31, sign( -1, A3 ) ) );
}

TEST( Array1Test, FunctionMinVal )
{
	Array1D_int A( { -1000, -1, 0, 1, 1000 } );
	int const E = -1000;
	EXPECT_EQ( E, minval( A ) );
}

TEST( Array1Test, FunctionMaxVal )
{
	Array1D_int A( { -1000, -1, 0, 1, 1000 } );
	int const E = 1000;
	EXPECT_EQ( E, maxval( A ) );
}

TEST( Array1Test, FunctionMinLoc )
{
	Array1D_int A1( { 1, 2, 3 } );
	int const I1 = 1;
	Array1D_int const E1( 1, I1 );
	EXPECT_TRUE( eq( E1, minloc( A1 ) ) );
	EXPECT_EQ( I1, minloc( A1, 1 ) );

	Array1D_int A2( { 3, 2, 1 } );
	int const I2 = 3;
	Array1D_int const E2( 1, I2 );
	EXPECT_TRUE( eq( E2, minloc( A2 ) ) );
	EXPECT_EQ( I2, minloc( A2, 1 ) );

	Array1D_int A3( { 3, 2, 1, 2, 1 } );
	int const I3 = 3;
	Array1D_int const E3( 1, I3 );
	EXPECT_TRUE( eq( E3, minloc( A3 ) ) );
	EXPECT_EQ( I3, minloc( A3, 1 ) );

	Array1D_int A4( { 1, 2, 3, -2, -1 } );
	int const I4 = 4;
	Array1D_int const E4( 1, I4 );
	EXPECT_TRUE( eq( E4, minloc( A4 ) ) );
	EXPECT_EQ( I4, minloc( A4, 1 ) );
}

TEST( Array1Test, FunctionMaxLoc )
{
	Array1D_int A1( { 1, 2, 3 } );
	int const I1 = 3;
	Array1D_int const E1( 1, I1 );
	EXPECT_TRUE( eq( E1, maxloc( A1 ) ) );
	EXPECT_EQ( I1, maxloc( A1, 1 ) );

	Array1D_int A2( { 3, 2, 1 } );
	int const I2 = 1;
	Array1D_int const E2( 1, I2 );
	EXPECT_TRUE( eq( E2, maxloc( A2 ) ) );
	EXPECT_EQ( I2, maxloc( A2, 1 ) );

	Array1D_int A3( { 1, 2, 3, 2, 3 } );
	int const I3 = 3;
	Array1D_int const E3( 1, I3 );
	EXPECT_TRUE( eq( E3, maxloc( A3 ) ) );
	EXPECT_EQ( I3, maxloc( A3, 1 ) );

	Array1D_int A4( { 1, 2, 3, 4, 3 } );
	int const I4 = 4;
	Array1D_int const E4( 1, I4 );
	EXPECT_TRUE( eq( E4, maxloc( A4 ) ) );
	EXPECT_EQ( I4, maxloc( A4, 1 ) );
}

TEST( Array1Test, FunctionMatMul )
{
	Array1D_int A11( 2, { 2, 3 } );
	Array1D_int A12( 2, { 5, 7 } );
	Array2D_int E1( 2, 2, reshape( { 10, 14, 15, 21 }, std::array< int, 2 >{ { 2, 2 } } ) );

	EXPECT_TRUE( eq( E1, matmul( A11, A12 ) ) );

	Array1D_bool A21( 2, { true, false } );
	Array1D_bool A22( 2, { false, true } );
	Array2D_bool E2( 2, 2, reshape( { false, true, false, false }, std::array< int, 2 >{ { 2, 2 } } ) );

	EXPECT_TRUE( eq( E2, matmul( A21, A22 ) ) );
}
