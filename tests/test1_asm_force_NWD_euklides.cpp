
#include "../src/arithmetic.cpp"
#include "../src/sslc.cpp"
#include "../src/run.cpp"
#include "../src/init.cpp"

template < typename T >
void add( std::vector < unsigned char > & code, const T & value )
{
	code.resize( code.size() + sizeof(T) );
	(*(T*)(&(code[code.size()-sizeof(T)]))) = value;
	//code.insert( code.end(), &value, (&value)+sizeof(T) );
}

int main()
{
	sslc::machine * env = new sslc::machine();
	env->init();
	
	sslc::function * func = new sslc::function;
	func->registered = false;
	func->args_types.emplace_back( env->get_type<long long>() );
	func->args_types.emplace_back( env->get_type<long long>() );
	func->local_variables_types.emplace_back( env->get_type<long long>() );
	func->return_type = env->get_type<long long>();
	
#define INSTRUCTION( x ) add<unsigned char>( func->code, sslc::x );
#define VALUE( x ) add<long long>( func->code, x );

#define PUSH_A { INSTRUCTION( PUSHREF ); VALUE( -4 ); }
#define PUSH_B { INSTRUCTION( PUSHREF ); VALUE( -5 ); }
#define PUSH_C { INSTRUCTION( PUSHREF ); VALUE( 0 ); }
#define POP_A { INSTRUCTION( POPVALUE ); VALUE( -4 ); }
#define POP_B { INSTRUCTION( POPVALUE ); VALUE( -5 ); }
#define POP_C { INSTRUCTION( POPVALUE ); VALUE( 0 ); }
#define PUSH_0 { INSTRUCTION( PUSHINT ); VALUE( 0 ); }
	
	PUSH_B;						// 0x00
	PUSH_0;						// 0x09
	INSTRUCTION( CMPNE );		// 0x12
	INSTRUCTION( JMPTRUE );		// 0x13
	VALUE( 0x26 );				// 0x14
	PUSH_A;						// 0x1C
	INSTRUCTION( RET );			// 0x25
	
		PUSH_A;					// 0x26
		PUSH_B;					// 0x2F
		INSTRUCTION( MOD );		// 0x38
		POP_C;					// 0x39
		
		PUSH_B;					// 0x42
		POP_A;					// 0x4B
		
		PUSH_C;					// 0x54
		POP_B;					// 0x5D
		
		PUSH_A;
		INSTRUCTION( PRINTI );
		PUSH_B;
		INSTRUCTION( PRINTI );
		
		INSTRUCTION( JMP );		// 0x66
		VALUE( 0 );				// 0x67
	
	
	env->add_function_manually( "NWD", func );
	
	long long a, b, c;
	a = 12;
	b = 16;
	//scanf( "%lli%lli", &a, &b );
	
	c = env->call<long long>( "NWD", a, b );
	
	printf( "\n NWD( %lli, %lli ) = %lli", a, b, c );
	
	delete env;
	
	return 0;
}



