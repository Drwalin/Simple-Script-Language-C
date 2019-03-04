
#include "../src/arithmetic.cpp"
#include "../src/sslc.cpp"
#include "../src/run.cpp"
#include "../src/init.cpp"

template < typename T >
void add( std::vector < unsigned char > & code, const T & value )
{
	if( typeid(T) == typeid(std::string) )
	{
		std::string v = *(std::string*)(&value);
		for( int i = 0; i <= v.size(); ++i )
			code.emplace_back( v[i] );
	}
	else
	{
		code.resize( code.size() + sizeof(T) );
		(*(T*)(&(code[code.size()-sizeof(T)]))) = value;
	}
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
#define VALUE( x ) add<long long>( func->code, (long long)(x) );

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
	
		/*
		PUSH_A;					// 0x26
		PUSH_B;					// 0x2F
		INSTRUCTION( MOD );		// 0x38
		POP_C;					// 0x39
		
		PUSH_B;					// 0x42
		POP_A;					// 0x4B
		
		PUSH_C;					// 0x54
		POP_B;					// 0x5D
		
		INSTRUCTION( JMP );		// 0x66
		VALUE( 0 );				// 0x67
		*/
		
		
		PUSH_A;					// 0x26
		PUSH_B;					// 0x2F
		INSTRUCTION( MOD );		// 0x38
		PUSH_B;					// 0x39
		
		POP_A;					// 0x42
		POP_B;					// 0x4B
		
		INSTRUCTION( JMP );		// 0x54
		VALUE( 0 );				// 0x55
	
	
	env->add_function_manually( "NWD", func );
	
	
	
	
	
	
	
	std::string format;
	
	func = new sslc::function;
	func->registered = false;
	func->local_variables_types.emplace_back( env->get_type<long long>() );
	func->local_variables_types.emplace_back( env->get_type<long long>() );
	func->local_variables_types.emplace_back( env->get_type<long long>() );
	func->return_type = env->get_type<long long>();
	
#define INST2S( A, B ) { INSTRUCTION( A ); add( func->code, B ); }
#define INST2( A, B ) { INSTRUCTION( A ); VALUE( B ); }
#define INST1( A ) INSTRUCTION( A );
	
	INST2( PUSHREF, 0 );
	INST1( GETI );
	INST2( PUSHREF, 1 );
	INST1( GETI );
	
	INST2( PUSHCOPY, 0 );
	INST2( PUSHCOPY, 1 );
	INST2S( CALL, std::string("NWD") );
	INST2( POPVALUE, 2 );
	
	INST2S( PUSHSTR, std::string("\n NWD( ") );
	INST1( PRINTS );
	INST2( PUSHREF, 0 );
	INST1( PRINTI );
	INST2S( PUSHSTR, std::string(", ") );
	INST1( PRINTS );
	INST2( PUSHREF, 1 );
	INST1( PRINTI );
	INST2S( PUSHSTR, std::string(" ) = ") );
	INST1( PRINTS );
	INST2( PUSHREF, 2 );
	INST1( PRINTI );
	INST2S( PUSHSTR, std::string("\n") );
	INST1( PRINTS );
	
	INST2( PUSHINT, 0 );
	INST1( RET );
	
	
	env->add_function_manually( "main", func );
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	env->call<long long>( "main" );
	
	delete env;
	
	return 0;
}



