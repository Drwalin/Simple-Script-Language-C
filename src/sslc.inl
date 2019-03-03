
#ifndef SIMPLE_SCRIPT_LANGUAGE_C_INL
#define SIMPLE_SCRIPT_LANGUAGE_C_INL

#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <map>

#include <typeinfo>
#include <type_traits>

namespace sslc
{
	
	template<typename Test, template<typename...> class Ref>
	struct is_specialization : std::false_type {};
	
	template<template<typename...> class Ref, typename... Args>
	struct is_specialization<Ref<Args...>, Ref>: std::true_type {};
	
	inline bool variable::valid()
	{
		if( this->data )
			return true;
		return false;
	}
	
	template < typename T >
	inline T & variable::access()
	{
		return *((T*)(this->data));
	}
	
	template < typename T >
	inline T variable::get() const
	{
		return *((const T*)(this->data));
	}
	
	template < typename T >
	inline void variable::set( T value )
	{
		*((T*)(this->data)) = value;
	}
	
	template < typename T >
	inline variable * variable::make( class machine * env )
	{
		variable * ret = new variable();
		ret->type_ref = env->get_type<T>();
		ret->data = malloc( ret->type_ref->size_bytes );
		ret->references = 1;
		return ret;
	}
	
	inline variable * variable::make( type * type_ref )
	{
		variable * ret = new variable();
		ret->type_ref = type_ref;
		ret->data = malloc( ret->type_ref->size_bytes );
		ret->references = 1;
		return ret;
	}
	
	
	
	
	
	template < typename T >
	type * machine::get_type_one_two() const
	{
		if( is_specialization<T,std::vector>::value )
			return this->TYPE_ARRAY;
		else if( is_specialization<T,std::set>::value )
			return this->TYPE_SET;
		else if( is_specialization<T,std::map>::value )
			return this->TYPE_MAP;
		return NULL;
	}
	
	template < typename T >
	type * machine::get_type() const
	{
		if( typeid(T) == typeid(char) )
			return this->TYPE_CHAR;
		else if( typeid(T) == typeid(bool) )
			return this->TYPE_BOOL;
		else if( typeid(T) == typeid(short) )
			return this->TYPE_INT;
		else if( typeid(T) == typeid(int) )
			return this->TYPE_INT;
		else if( typeid(T) == typeid(long long) )
			return this->TYPE_INT;
		else if( typeid(T) == typeid(unsigned char) )
			return this->TYPE_INT;
		else if( typeid(T) == typeid(unsigned short) )
			return this->TYPE_INT;
		else if( typeid(T) == typeid(unsigned int) )
			return this->TYPE_INT;
		else if( typeid(T) == typeid(unsigned long long) )
			return this->TYPE_INT;
			
		else if( typeid(T) == typeid(float) )
			return this->TYPE_REAL;
		else if( typeid(T) == typeid(double) )
			return this->TYPE_REAL;
			
		else if( typeid(T) == typeid(std::string) )
			return this->TYPE_STRING;
		
		else if( typeid(T) == typeid(complex) )
			return this->TYPE_COMPLEX;
		else if( typeid(T) == typeid(quaternion) )
			return this->TYPE_QUATERNION;
		else if( typeid(T) == typeid(octonion) )
			return this->TYPE_OCTONION;
		
		else if( typeid(T) == typeid(glm::vec2) )
			return this->TYPE_VEC2;
		else if( typeid(T) == typeid(glm::vec3) )
			return this->TYPE_VEC3;
		else if( typeid(T) == typeid(glm::vec4) )
			return this->TYPE_VEC4;
		else if( typeid(T) == typeid(glm::mat2x2) )
			return this->TYPE_MAT2X2;
		else if( typeid(T) == typeid(glm::mat3x3) )
			return this->TYPE_MAT3X3;
		else if( typeid(T) == typeid(glm::mat4x4) )
			return this->TYPE_MAT4X4;
		
		type * ret = this->get_type_one_two<T>();
		if( ret )
			return ret;
			
		return this->TYPE_VOID;
	}
	
	template < typename T >
	inline void machine::push( T & value )
	{
		if( typeid(decltype(value)) == typeid(variable) )
		{
			this->stack.emplace_back( (variable*)&value );
			this->stack.back()->makereference();
		}
		else
		{
			variable * var = variable::make<T>( this );
			if( var )
			{
				if( var->valid() )
				{
					var->references = 1;
					var->access<T>() = value;
					this->stack.emplace_back( var );
				}
				else
					delete var;
			}
		}
	}
	
	inline void machine::pop( bool treat_as_sslc_variable )
	{
		if( treat_as_sslc_variable )
		{
			this->stack.back()->dereference();
			this->stack.resize( this->stack.size() - 1 );
		}
		else
		{
			this->stack.resize( this->stack.size() - 1 );
		}
	}
	
	inline void machine::call_()
	{
		return;
	}
	
	template < typename T >
	inline void machine::call_( T arg )
	{
		this->push( arg );
	}
	
	template < typename T, typename... Args >
	inline void machine::call_( T arg, Args... args )
	{
		this->call_( arg );
		this->call_( args... );
	}
	
	template < typename Ret >
	inline Ret machine::call( const char * function_name )
	{
		this->current_function = this->functions[function_name];
		if( this->current_function )
		{
			this->stack.push_back( (variable*)(0) );
			this->stack.push_back( (variable*)(0) );
			this->stack.push_back( (variable*)(0) );
			this->rsp = this->stack.size();
			for( long long i = 0; i < this->current_function->local_variables_types.size(); ++i )
				this->push( *variable::make( this->current_function->local_variables_types[i] ) );
			this->rip = &(this->current_function->code[0]);
			this->interprete();
			Ret ret = this->stack.back()->get<Ret>();
			this->pop();
			return ret;
		}
		printf( "\n ERROR! No function called \"%s\" found", function_name );
		return Ret();
	}
	
	template < typename Ret, typename... Args >
	inline Ret machine::call( const char * function_name, Args... args )
	{
		this->call_( args... );
		return this->call<Ret>( function_name );
	}
	
};

#endif

