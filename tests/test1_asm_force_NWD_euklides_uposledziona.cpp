
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
	func->local_variables_types.emplace_back( env->get_type<long long>() );
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
#define INST2S( A, B ) { INSTRUCTION( A ); add( func->code, B ); }
#define INST2( A, B ) { INSTRUCTION( A ); VALUE( B ); }
#define INST1( A ) INSTRUCTION( A );
	
	INST2( PUSHREF, -4 );		// 0
	INST2( PUSHINT, 0 );		// 9
	INST1( CMPE );				// 18
	INST2( JMPFALSE, 47 );		// 19
	INST2( PUSHINT, 1 );		// 28 : ret X
	INST2( PUSHINT, 0 );		// 37 : ret Y
	INST1( RET );				// 46
		
		
		INST2( PUSHREF, -5 );	// 47
		INST2S( PUSHSTR, std::string("\n  ( A=") );
		INST1( PRINTS );
		INST1( PRINTI );
		INST2( PUSHCOPY, -4 );
		INST2S( PUSHSTR, std::string(", B=") );
		INST1( PRINTS );
		INST1( PRINTI );
		INST2S( PUSHSTR, std::string(" )\n CALL NWD\n") );
		INST1( PRINTS );
		
		
		INST2( PUSHCOPY, -4 );	// 56 : push B as arg to NWD
		INST2( PUSHCOPY, -5 );	// 65 : push A
		INST2( PUSHCOPY, -4 );	// 74 : push B
		INST1( MOD );			// 83 : a%b as arg to NWD
		INST2S( CALL, std::string("NWD") );		// 92
		
		INST2S( PUSHSTR, std::string("\n RETURN FROM NWD\n") );
		INST1( PRINTS );
		
		INST2( POPVALUE, 1 );	// 97
		INST2( POPVALUE, 0 );	// 106
		
		INST2( PUSHREF, 0 );	// 47
		INST2S( PUSHSTR, std::string("\n  ( X=") );
		INST1( PRINTS );
		INST1( PRINTI );
		INST2( PUSHCOPY, 1 );
		INST2S( PUSHSTR, std::string(", Y=") );
		INST1( PRINTS );
		INST1( PRINTI );
		INST2S( PUSHSTR, std::string(" )\n") );
		INST1( PRINTS );
		
		
		
		
		INST2( PUSHCOPY, 1 );	// 115
		
		// PUSH ( x - ( y * (A%B) ) );
		INST2( PUSHCOPY, 0 );
		INST2( PUSHCOPY, 1 );
		INST2( PUSHCOPY, -5 );
		INST2( PUSHCOPY, -4 );
		INST1( DIV );
		INST1( MUL );
		INST1( SUB );
		/*
		INST2( POPVALUE, 1 );
		INST2( POPVALUE, 0 );
		
		INST2( PUSHCOPY, 0 );
		INST2( PUSHCOPY, 1 );
		*/
		INSTRUCTION( RET );
	
	env->add_function_manually( "NWD", func );
	
	
	
	
	
	
	
	std::string format;
	
	func = new sslc::function;
	func->registered = false;
	func->local_variables_types.emplace_back( env->get_type<long long>() );
	func->local_variables_types.emplace_back( env->get_type<long long>() );
	func->local_variables_types.emplace_back( env->get_type<long long>() );
	func->local_variables_types.emplace_back( env->get_type<long long>() );
	func->return_type = env->get_type<long long>();
	
	
	INST2( PUSHREF, 0 );
	INST1( GETI );
	INST2( PUSHREF, 1 );
	INST1( GETI );
	
	INST2( PUSHCOPY, 0 );
	INST2( PUSHCOPY, 1 );
	INST2S( CALL, std::string("NWD") );
	INST2( POPVALUE, 3 );
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
	
	INST2( PUSHREF, 0 );
	INST1( PRINTI );
	INST2S( PUSHSTR, std::string("*") );
	INST1( PRINTS );
	INST2( PUSHREF, 2 );
	INST1( PRINTI );
	
	INST2S( PUSHSTR, std::string(" + ") );
	INST1( PRINTS );
	
	INST2( PUSHREF, 1 );
	INST1( PRINTI );
	INST2S( PUSHSTR, std::string("*") );
	INST1( PRINTS );
	INST2( PUSHREF, 3 );
	INST1( PRINTI );
	
	INST2S( PUSHSTR, std::string(" \n") );
	INST1( PRINTS );
	
	INST2( PUSHINT, 0 );
	INST1( RET );
	
	
	env->add_function_manually( "main", func );
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	env->call<long long>( "main" );
	
	delete env;
	
	return 0;
}



