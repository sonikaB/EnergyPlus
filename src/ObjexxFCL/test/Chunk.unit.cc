// ObjexxFCL::Chunk Unit Tests
//
// Project: Objexx Fortran Compatibility Library (ObjexxFCL)
//
// Version: 4.0.0
//
// Language: C++
//
// Copyright (c) 2000-2014 Objexx Engineering, Inc. All Rights Reserved.
// Use of this source code or any derivative of it is restricted by license.
// Licensing is available from Objexx Engineering, Inc.:  http://objexx.com

// Google Test Headers
#include <gtest/gtest.h>

// ObjexxFCL Headers
#include <ObjexxFCL/Chunk.hh>
#include <ObjexxFCL/TypeTraits.hh>

// C++ Headers
#include <iomanip>
#include <ostream>

// Stream Output
template< typename T >
std::ostream &
operator <<( std::ostream & stream, ObjexxFCL::Chunk< T > const & c )
{
	if ( c.empty() ) return stream;

	// Types
	using namespace ObjexxFCL;
	using std::setw;
	typedef  TypeTraits< T >  Traits;
	typedef  typename Chunk< T >::size_type  size_type;

	// Save current stream state and set persistent state
	std::ios_base::fmtflags const old_flags( stream.flags() );
	int const old_precision( stream.precision( Traits::precision() ) );
	stream << std::right << std::showpoint << std::uppercase;

	// Output array to stream
	size_type const e( c.size() - 1 );
	int const w( Traits::width() );
	for ( size_type i = 0; i < e; ++i ) {
		stream << setw( w ) << c[ i ] << ' ';
	} stream << setw( w ) << c[ e ];

	// Restore previous stream state
	stream.precision( old_precision );
	stream.flags( old_flags );

	return stream;
}

using namespace ObjexxFCL;

typedef  ObjexxFCL::Chunk< int >  Chunk_int;
typedef  ObjexxFCL::Chunk< float >  Chunk_float;

TEST( ChunkTest, Construction )
{
	{ // Default constructor
		Chunk_int v;
		Chunk_int w( v );
		EXPECT_EQ( v, w );
		EXPECT_EQ( w, v );
		EXPECT_EQ( 0U, v.size() );
		EXPECT_EQ( 0U, w.size() );
	}

	{ // Copy constructor and assignment
		Chunk_int v( 10, 22 );
		Chunk_int w( v );
		EXPECT_EQ( v, w );
		EXPECT_EQ( w, v );
		w += 1;
		v = w;
		EXPECT_EQ( v, w );
		EXPECT_EQ( w, v );
	}

	{ // Copy constructor and assignment template
		Chunk_int v( 10, 22 );
		Chunk_float f( v );
		EXPECT_EQ( Chunk_float( 10, 22.0f ), f );
		v += 1;
		EXPECT_EQ( Chunk_int( 10, 23 ), v );
		f = v;
		EXPECT_EQ( Chunk_float( 10, 23.0f ), f );
	}

	{ // Size + value constructor and subscripting
		Chunk_int v( 10, 2 );
		EXPECT_EQ( 10U, v.size() );
		for ( Chunk_int::size_type i = 0; i < v.size(); ++i ) {
			v[ i ] = i;
			EXPECT_EQ( int( i ), v[ i ] );
		}
	}
}

TEST( ChunkTest, Assignment )
{
	Chunk_int v( 10, 22 );
	v += 2;
	EXPECT_EQ( Chunk_int( 10, 24 ), v );
	v -= 2;
	EXPECT_EQ( Chunk_int( 10, 22 ), v );
	v *= 2;
	EXPECT_EQ( Chunk_int( 10, 44 ), v );
	v /= 2;
	EXPECT_EQ( Chunk_int( 10, 22 ), v );
	v.assign( 20, 33 );
	EXPECT_EQ( Chunk_int( 20, 33 ), v );
	v += v;
	EXPECT_EQ( Chunk_int( 20, 66 ), v );
	v -= v;
	EXPECT_EQ( Chunk_int( 20, 0 ), v );
	v = 55;
	EXPECT_EQ( Chunk_int( 20, 55 ), v );
	Chunk_int w( 20, 33 );
	v += w;
	EXPECT_EQ( Chunk_int( 20, 88 ), v );
}

TEST( ChunkTest, Subscripting )
{
	Chunk_int v( 10, 22 );
	v[ 3 ] = 33;
	EXPECT_EQ( 33, v[ 3 ] );
}

TEST( ChunkTest, Swap )
{
	Chunk_int a( 10, 22 ), A( a );
	Chunk_int b( 8, 33 ), B( b );
	a.swap( b );
	EXPECT_EQ( B, a );
	EXPECT_EQ( A, b );
	b.swap( a );
	EXPECT_EQ( A, a );
	EXPECT_EQ( B, b );
	swap( a, b );
	EXPECT_EQ( B, a );
	EXPECT_EQ( A, b );
	std::swap( a, b );
	EXPECT_EQ( A, a );
	EXPECT_EQ( B, b );
}

TEST( ChunkTest, FrontBack )
{
	Chunk_int v( 10 );
	for ( Chunk_int::size_type i = 0; i < 10; ++i ) {
		v[ i ] = int( i );
		EXPECT_EQ( int( i ), v[ i ] );
	}
	EXPECT_EQ( 0, v.front() );
	EXPECT_EQ( int( v.size() - 1 ), v.back() );
}

TEST( ChunkTest, Resize )
{
	Chunk_int v( 10, 22 );
	v.resize( 20 ); // Added values are uninitialized
	EXPECT_EQ( 20U, v.size() );
	for ( Chunk_int::size_type i = 0; i < 10; ++i ) {
		EXPECT_EQ( 22, v[ i ] );
	}
}

TEST( ChunkTest, ResizeFill )
{
	Chunk_int v( 10, 22 );
	v.resize( 20, 33 );
	EXPECT_EQ( 20U, v.size() );
	for ( Chunk_int::size_type i = 0; i < 10; ++i ) {
		EXPECT_EQ( 22, v[ i ] );
	}
	for ( Chunk_int::size_type i = 10; i < 20; ++i ) {
		EXPECT_EQ( 33, v[ i ] );
	}
}

TEST( ChunkTest, NonpreservingResize )
{
	Chunk_int v( 10, 22 );
	v.non_preserving_resize( 20 ); // Values can be arbitrary
	EXPECT_EQ( 20U, v.size() );
	EXPECT_EQ( 20U, v.capacity() ); // Resize forced reallocation
}

TEST( ChunkTest, NonpreservingResizeFill )
{
	Chunk_int v( 10, 22 );
	v.non_preserving_resize( 20, 33 );
	EXPECT_EQ( 20U, v.size() );
	EXPECT_EQ( 20U, v.capacity() ); // Resize forced reallocation
	for ( Chunk_int::size_type i = 0; i < 20; ++i ) {
		EXPECT_EQ( 33, v[ i ] );
	}
}

TEST( ChunkTest, ReservePushPopShrink )
{
	Chunk_int v( 10, 22 );
	EXPECT_EQ( 10U, v.size() );
	EXPECT_EQ( 10U, v.capacity() );
	v.reserve( 12 );
	EXPECT_EQ( 10U, v.size() );
	EXPECT_EQ( 12U, v.capacity() );
	for ( Chunk_int::size_type i = 0; i < 10; ++i ) {
		EXPECT_EQ( 22, v[ i ] );
	}
	v.push_back( 33 );
	EXPECT_EQ( 11U, v.size() );
	EXPECT_EQ( 12U, v.capacity() );
	v.push_back( 44 );
	EXPECT_EQ( 12U, v.size() );
	EXPECT_EQ( 12U, v.capacity() );
	v.push_back( 55 );
	EXPECT_EQ( 13U, v.size() );
	EXPECT_EQ( 24U, v.capacity() );
	v.pop_back();
	EXPECT_EQ( 12U, v.size() );
	EXPECT_EQ( 24U, v.capacity() );
	v.pop_back();
	EXPECT_EQ( 11U, v.size() );
	EXPECT_EQ( 24U, v.capacity() );
	v.shrink();
	EXPECT_EQ( 11U, v.size() );
	EXPECT_EQ( 11U, v.capacity() );
}
