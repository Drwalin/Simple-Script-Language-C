
#ifndef SIMPLE_SCRIPT_LANGUAGE_C_CPP
#define SIMPLE_SCRIPT_LANGUAGE_C_CPP

#include "sslc.h"

#include <map>
#include <set>

#include <stringstream>
#include <iostream>
#include <fstream>

#include <cstdarg>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>

namespace sslc
{
	
	bool type::operator == ( const type & other )
	{
		return ( this->name == other.name ) && ( this->size_bytes == other.size_bytes );
	}
	
	type::type()
	{
		name = "";
		size_bytes = 0;
	}
	
	type::~type()
	{
		name = "";
		size_bytes = 0;
	}
	
	
	
	
	
	void variable::set_value_of( const variable & other )
	{
		
	}
	
	void variable::makereference()
	{
		if( this->data )
			this->references++;
	}
	
	void variable::dereference()
	{
		if( this->data )
		{
			this->references--;
			if( this->references == 0 )
			{
				delete this;
			}
		}
	}
	
	variable::variable()
	{
		type_ref = NULL;
		data = NULL;
		references = 0;
	}
	
	variable::~variable()
	{
		type_ref = NULL;
		if( data )
			free( data );
		references = 0;
	}
	
	
	
	
	
	function::function()
	{
		registered = false;
		return_type = NULL;
	}
	
	function::~function()
	{
		registered = false;
		return_type = NULL;
	}
	
	
	
	
	
	void machine::printchar()
	{
		if( this->stack.back()->type_ref == this->TYPE_char )
			printf( "%c", this->stack.back()->get<char>() );
		this->pop();
	}
	
	void machine::printint()
	{
		if( this->stack.back()->type_ref == this->TYPE_INT )
			printf( "%lli", this->stack.back()->get<long long>() );
		this->pop();
	}
	
	void machine::printreal()
	{
		if( this->stack.back()->type_ref == this->TYPE_REAL )
			printf( "%f", this->stack.back()->get<double>() );
		this->pop();
	}
	
	void machine::printstring()
	{
		if( this->stack.back()->type_ref == this->TYPE_STRING )
			printf( "%s", this->stack.back()->get<std::string>().c_str() );
		this->pop();
	}
	
	void machine::getchar()
	{
		if( this->stack.back()->type_ref == this->TYPE_char )
			scanf( "%c", &(this->stack.back()->access<char>()) );
		this->pop();
	}
	
	void machine::getint()
	{
		if( this->stack.back()->type_ref == this->TYPE_INT )
			scanf( "%lli", &(this->stack.back()->access<long long>()) );
		this->pop();
	}
	
	void machine::getreal()
	{
		if( this->stack.back()->type_ref == this->TYPE_REAL )
			scanf( "%f", &(this->stack.back()->access<double>()) );
		this->pop();
	}
	
	void machine::getstring()
	{
		if( this->stack.back()->type_ref == this->TYPE_STRING )
			std::cin >> this->stack.back()->access<std::string>();
		this->pop();
	}
	
	
	int machine::run( /*int argc, char ** argv*/ )
	{
		//std::vector<std::string> args;
		//for( int i = 0; i < argc; ++i )
		//	args.emplace_back( argv );
		return this->call( "main" /* , argc, args*/ );
	}
	
	machine::machine()
	{
		rip = 0;
		rsp = 0;
		current_function = NULL;
		TYPE_VOID = NULL;
		TYPE_CHAR = NULL;
		TYPE_INT = NULL;
		TYPE_REAL = NULL;
		TYPE_STRING = NULL;
		TYPE_BOOL = NULL;
		TYPE_COMPLEX = NULL;
		TYPE_QUATERNION = NULL;
		TYPE_OCTONION = NULL;
		TYPE_VEC2 = NULL;
		TYPE_VEC3 = NULL;
		TYPE_VEC4 = NULL;
		TYPE_MAT2X2 = NULL;
		TYPE_MAT3X3 = NULL;
		TYPE_MAT4X4 = NULL;
		TYPE_ARRAY = NULL;
		TYPE_MAP = NULL;
		TYPE_SET = NULL;
	}
	
	machine::~machine()
	{
		rip = 0;
		rsp = 0;
		current_function = NULL;
		TYPE_VOID = NULL;
		TYPE_CHAR = NULL;
		TYPE_INT = NULL;
		TYPE_REAL = NULL;
		TYPE_STRING = NULL;
		TYPE_BOOL = NULL;
		TYPE_COMPLEX = NULL;
		TYPE_QUATERNION = NULL;
		TYPE_OCTONION = NULL;
		TYPE_VEC2 = NULL;
		TYPE_VEC3 = NULL;
		TYPE_VEC4 = NULL;
		TYPE_MAT2X2 = NULL;
		TYPE_MAT3X3 = NULL;
		TYPE_MAT4X4 = NULL;
		TYPE_ARRAY = NULL;
		TYPE_MAP = NULL;
		TYPE_SET = NULL;
		while( stack.size() != 0 )
			pop();
		for( auto it = types.begin(); it != types.end(); ++it )
			delete *it;
		types.clear();
		for( auto it = functions.begin(); it != functions.end(); ++it )
			delete *it;
		functions.clear();
	}
	
};

#endif

