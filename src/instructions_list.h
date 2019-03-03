
#ifndef INSTRUCTIONS_LIST_H
#define INSTRUCTIONS_LIST_H

namespace sslc
{
	const static unsigned char CALL      = 0x01;
	const static unsigned char RET       = 0x01;
	const static unsigned char JMP       = 0x01;
	
	
	const static unsigned char ADD       = 0x01;
	const static unsigned char SUB       = 0x01;
	const static unsigned char MUL       = 0x01;
	const static unsigned char DIV       = 0x01;
	const static unsigned char MOD       = 0x01;
	const static unsigned char NEG       = 0x01;
	
	const static unsigned char XOR       = 0x01;
	const static unsigned char OR        = 0x01;
	const static unsigned char AND       = 0x01;
	const static unsigned char NOT       = 0x01;
	const static unsigned char SHL       = 0x01;
	const static unsigned char SHR       = 0x01;
	
		// copmares and pop two variables from stack and push result<bool>
	const static unsigned char CMPE      = 0x01;		
	const static unsigned char CMPNE     = 0x01;
	const static unsigned char CMPL      = 0x01;
	const static unsigned char CMPLE     = 0x01;
	const static unsigned char CMPG      = 0x01;
	const static unsigned char CMPGE     = 0x01;
	const static unsigned char JMPTRUE   = 0x01;
	const static unsigned char JMPFALSE  = 0x01;
	
	
	const static unsigned char PRINTC    = 0x01;
	const static unsigned char PRINTI    = 0x01;
	const static unsigned char PRINTR    = 0x01;
	const static unsigned char PRINTS    = 0x01;
	const static unsigned char GETC      = 0x01;
	const static unsigned char GETI      = 0x01;
	const static unsigned char GETR      = 0x01;
	const static unsigned char GETS      = 0x01;
	
	const static unsigned char PUSHCHAR  = 0x01;		// push constat variable char - makes new variable
	const static unsigned char PUSHINT   = 0x01;		// push constat variable int - makes new variable
	const static unsigned char PUSHREAL  = 0x01;		// push constat variable real - makes new variable
	const static unsigned char PUSHSTR   = 0x01;		// push constat variable string - makes new variable
	const static unsigned char PUSHREF   = 0x01;		// push local variable refeence
	const static unsigned char PUSHCOPY  = 0x01;		// push copy of local variable - makes new variable with value
	const static unsigned char POPCOPY   = 0x01;		// copy value to local variable - makes new variable pointer
	const static unsigned char POPREF    = 0x01;		// pop reference
	const static unsigned char POPVALUE  = 0x01;		// pop value to current variable
	
	//const static unsigned char CAST    = 0x01;
	
	
	
	
};

#endif

