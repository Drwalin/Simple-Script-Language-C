
#ifndef SIMPLE_SCRIPT_LANGUAGE_C_INL
#define SIMPLE_SCRIPT_LANGUAGE_C_INL

#include <string>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>
#include <boost/math/octonion.hpp>
#include <boost/math/quaternion.hpp>
#include <complex>

#include <typeinfo>

namespace sslc
{
	
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
	inline variable * variable::make( class machine * env );
	{
		variable * ret = new variable();
		ret->type_ref = env->get_type<T>();
		ret->data = malloc( type->type_ref->size_bytes );
		ret->references = 1;
		return ret;
	}
	
	static inline variable * variable::make( type * type_ref )
	{
		variable * ret = new variable();
		ret->type_ref = type_ref;
		ret->data = malloc( type->type_ref->size_bytes );
		ret->references = 1;
		return ret;
	}
	
	
	
	template < template<typename...> class T >
	type * machine::get_type_one() const
	{
		if( typeid(T) == typeid(std::vector) )
			return this->TYPE_ARRAY;
		else if( typeid(T) == typeid(std::set) )
			return this->TYPE_SET;
		return NULL;
	}
	
	template < template<typename...> class T >
	type * machine::get_type_two() const
	{
		if( typeid(T) == typeid(std::map) )
			return this->TYPE_MAP;
		return NULL;
	}
	
	template < typename T >
	type * machine::get_type() const
	{
		if( typeid(T) == typeid(char) )
			return this->TYPE_char;
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
		
		else if( typeid(T) == typeid(std::complex) )
			return this->TYPE_COMPLEX;
		else if( typeid(T) == typeid(boost::math::quaternion) )
			return this->TYPE_QUATERNION;
		else if( typeid(T) == typeid(boost::math::octonion) )
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
		
		type * ret = this->get_type_one<T>();
		if( ret )
			return ret;
			
		return this->get_type_two<T>();
	}
	
	template < typename T >
	inline void machine::push( T & value )
	{
		if( typeid(decltype(value)) == typeid(type) )
		{
			this->stack.emplace_back( &value );
		}
		else
		{
			varaible * var = variable::make<T>( this );
			if( var )
			{
				if( var->valid() )
				{
					var->access<T>() = value;
					this->stack.emplace_back( &var );
				}
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
			this->interprete();
			Ret ret = this->stack.back()->get();
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
		return this->call( function_name );
	}
	
};

#endif

