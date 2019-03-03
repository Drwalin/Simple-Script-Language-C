
#ifndef INSTRUCTIONS_LIST_H
#define INSTRUCTIONS_LIST_H

namespace sslc
{
	const static unsigned char CALL      = 0x01;
	const static unsigned char RET       = 0x02;
	const static unsigned char JMP       = 0x03;
	
	
	const static unsigned char ADD       = 0x10;
	const static unsigned char SUB       = 0x11;
	const static unsigned char MUL       = 0x12;
	const static unsigned char DIV       = 0x13;
	const static unsigned char MOD       = 0x14;
	const static unsigned char NEG       = 0x15;
	
	const static unsigned char XOR       = 0x20;
	const static unsigned char OR        = 0x21;
	const static unsigned char AND       = 0x22;
	const static unsigned char NOT       = 0x23;
	const static unsigned char SHL       = 0x24;
	const static unsigned char SHR       = 0x25;
	
		// copmares and pop two variables from stack and push result<bool>
	const static unsigned char CMPE      = 0x30;		
	const static unsigned char CMPNE     = 0x31;
	const static unsigned char CMPL      = 0x32;
	const static unsigned char CMPLE     = 0x33;
	const static unsigned char CMPG      = 0x34;
	const static unsigned char CMPGE     = 0x35;
	const static unsigned char JMPTRUE   = 0x36;
	const static unsigned char JMPFALSE  = 0x37;
	
	
	const static unsigned char PRINTC    = 0x40;
	const static unsigned char PRINTI    = 0x41;
	const static unsigned char PRINTR    = 0x42;
	const static unsigned char PRINTS    = 0x43;
	const static unsigned char GETC      = 0x44;
	const static unsigned char GETI      = 0x45;
	const static unsigned char GETR      = 0x46;
	const static unsigned char GETS      = 0x47;
	
	const static unsigned char PUSHCHAR  = 0x50;		// push constat variable char - makes new variable
	const static unsigned char PUSHINT   = 0x51;		// push constat variable int - makes new variable
	const static unsigned char PUSHREAL  = 0x52;		// push constat variable real - makes new variable
	const static unsigned char PUSHSTR   = 0x53;		// push constat variable string - makes new variable
	const static unsigned char PUSHREF   = 0x54;		// push local variable refeence
	const static unsigned char PUSHCOPY  = 0x55;		// push copy of local variable - makes new variable with value
	const static unsigned char POPCOPY   = 0x56;		// copy value to local variable - makes new variable pointer
	const static unsigned char POPREF    = 0x57;		// pop reference
	const static unsigned char POPVALUE  = 0x58;		// pop value to current variable
	
	//const static unsigned char CAST    = 0x60;
};

#endif

