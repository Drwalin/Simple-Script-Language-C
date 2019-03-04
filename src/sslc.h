
#ifndef SIMPLE_SCRIPT_LANGUAGE_C_H
#define SIMPLE_SCRIPT_LANGUAGE_C_H

#include <string>
#include <unordered_map>
#include <vector>

#include <typeindex>

#include <glm/glm.hpp>
#include <boost/math/octonion.hpp>
#include <boost/math/quaternion.hpp>
#include <complex>

namespace sslc
{
	typedef std::complex<double> complex;
	typedef boost::math::quaternion<double> quaternion;
	typedef boost::math::octonion<double> octonion;
	
	class type
	{
	private:
		
		std::string name;
		unsigned size_bytes;
		
	public:
		
		friend class variable;
		friend class function;
		friend class machine;
		
		bool operator == ( const type & other );
		
		type();
		~type();
	};
	
	class variable
	{
	private:
		
		class machine * env;
		type * type_ref;
		void * data;
		
		unsigned references;
		
		variable();
		~variable();
		
	public:
		
		friend class type;
		friend class function;
		friend class machine;
		
		
		
		void set_value_of( const variable & other );		// no check vor validity and equal types
		
		void makereference();
		void dereference();
		
		inline bool valid();
		
		template < typename T >
		inline T & access();						// no check for validity
		template < typename T >
		inline T get() const;						// no check for validity
		template < typename T >
		inline void set( T value );					// no check for validity
		
		template < typename T >
		static inline variable * make( class machine * env );						// initial this->references = 1
		static inline variable * make( class machine * env, type * type_ref );		// initial this->references = 1
	};
	
	class function
	{
	private:
	public:
		
		bool registered;		// true -> function::code contains function pointer : false -> function::code contains 'compiled' code
		std::vector < unsigned char > code;
		std::vector < type * > args_types;
		std::vector < type * > local_variables_types;
		type * return_type;
		
	public:
		
		friend class type;
		friend class variable;
		friend class machine;
		
		
		
		function();
		~function();
	};
	
	/*
	Stack frame construction for:
		machine::stack
	
	    -N-3->          -3->               -2->               -1->                         0->                   L->       
	 ... | - arguments - | - previous RSP - | - previous RIP - | - previous function ptr - | - local variables - | ...
	
	*/
	
	class machine
	{
	private:
		
		std::unordered_map < std::string, type * > types;
		std::unordered_map < std::string, function * > functions;
		
		unsigned char * rip;
		function * current_function;
		
		unsigned long long rsp;
		std::vector < variable * > stack;			// pointers to variables
		
		inline void call_();
		template < typename T >
		inline void call_( T arg );
		template < typename T, typename... Args >
		inline void call_( T arg, Args... args );
		
		template < typename T >
		inline void push( T & value );
		inline void pop( bool treat_as_sslc_variable = true );
		
		void interprete();
		
		template < typename T >
		type * get_type_one_two() const;
		
		void constructor( void * data, type * type_ref );
		void destructor( void * data, type * type_ref );
		
		void cmpe();
		void cmpne();
		void cmpl();
		void cmple();
		void cmpg();
		void cmpge();
		
		void add();
		void sub();
		void mul();
		void div();
		void mod();
		void neg();
		
		void binary_xor();
		void binary_or();
		void binary_and();
		void binary_not();
		void binary_shl();
		void binary_shr();
		
		void printchar();
		void printint();
		void printreal();
		void printstring();
		
		// sets value of this->stack.back() - as reference
		void getchar();
		void getint();
		void getreal();
		void getstring();
		
		type * TYPE_VOID;
		type * TYPE_CHAR;
		type * TYPE_INT;
		type * TYPE_REAL;
		type * TYPE_STRING;
		type * TYPE_BOOL;
		type * TYPE_COMPLEX;
		type * TYPE_QUATERNION;
		type * TYPE_OCTONION;
		type * TYPE_VEC2;
		type * TYPE_VEC3;
		type * TYPE_VEC4;
		type * TYPE_MAT2X2;
		type * TYPE_MAT3X3;
		type * TYPE_MAT4X4;
		type * TYPE_ARRAY;
		type * TYPE_MAP;
		type * TYPE_SET;
		
	public:
		
		friend class type;
		friend class variable;
		friend class function;
		
		
		
		int add_function_manually( const char * function_name, function * func );
		
		template < typename T >
		type * get_type() const;
		
		unsigned compile( const char * file_name );			// throws error while trying to override function name or type name
		unsigned recompile( const char * file_name );		// overrides type and function names and functions when needed
		
		int run( /*int argc, char ** argv*/ );					// runs main
		
		template < typename Ret >
		inline Ret call( const char * function_name );
		template < typename Ret, typename... Args >
		inline Ret call( const char * function_name, Args... args );
		
		void init();
		
		machine();
		~machine();
	};
	
};

#include "sslc.inl"
#include "instructions_list.h"

#endif

