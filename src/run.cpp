
#ifndef RUN_CPP
#define RUN_CPP

#include "sslc.h"

namespace sslc
{
	void machine::interprete()
	{
		unsigned long long i, j;
		std::string str;
		function * func;
		while( this->current_function )
		{
			switch( *(this->rip) )
			{
			case CALL:
				//printf( "\n CALL at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				
				this->stack.emplace_back( (variable*)(this->rsp) );
				this->stack.emplace_back( (variable*)( this->rip + 1 + strlen((const char*)(this->rip+1)) + 1 ) );
				this->stack.emplace_back( (variable*)(this->current_function) );
				
				this->rsp = this->stack.size();
				
				str = *(const char*)(this->rip+1);
				this->current_function = this->functions[(const char*)(this->rip+1)];
				for( i = 0; i < this->current_function->local_variables_types.size(); ++i )
					this->push( *variable::make( this->current_function->local_variables_types[i] ) );
				
				this->rip = &(this->current_function->code.front());
				//printf( "\n     DONE!" );
				break;
			
			
			
			case RET:
				//printf( "\n RET at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				
				for( i = this->rsp - 3 - this->current_function->args_types.size(); i < this->rsp-3; ++i )
					this->stack[i]->dereference();
				for( i = this->rsp; i < this->rsp + this->current_function->local_variables_types.size(); ++i )
					this->stack[i]->dereference();
				
				i = this->rsp;
				
				func = this->current_function;
				
				this->current_function = (function*)(this->stack[i-1]);
				this->rip = /*&(func->code.front()) + */(unsigned char*)(this->stack[i-2]);
				this->rsp = (long long)(this->stack[i-3]);
				
				this->stack.erase( this->stack.begin() + i - 3 - func->args_types.size(), this->stack.begin() + i + func->local_variables_types.size() );
				
				//printf( "\n     DONE!" );
				break;
			
			
			
			case JMP:
				//printf( "\n JMP at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				this->rip = &(this->current_function->code.front()) + *(const unsigned long long*)(this->rip+1);
				//printf( "\n     DONE!" );
				break;
			
			
			
			case ADD:
				this->add();
				this->rip++;
				break;
			
			case SUB:
				this->sub();
				this->rip++;
				break;
			
			case MUL:
				this->mul();
				this->rip++;
				break;
			
			case DIV:
				this->div();
				this->rip++;
				break;
			
			case MOD:
				//printf( "\n MOD at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				this->mod();
				this->rip++;
				//printf( "\n     DONE!" );
				break;
			
			
			
			case NEG:
				this->neg();
				this->rip++;
				break;
			
			case XOR:
				this->binary_xor();
				this->rip++;
				break;
			
			case OR:
				this->binary_or();
				this->rip++;
				break;
			
			case AND:
				this->binary_and();
				this->rip++;
				break;
			
			case NOT:
				this->binary_not();
				this->rip++;
				break;
			/*
			case SHL:
				this->binary_shl();
				break;
			
			case SHR:
				this->binary_shr();
				break;
				*/
			
			
			
			case CMPE:
				//printf( "\n CMPE at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				this->cmpe();
				this->rip++;
				//printf( "\n     DONE!" );
				break;
			case CMPNE:
				//printf( "\n CMPNE at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				this->cmpne();
				this->rip++;
				//printf( "\n     DONE!" );
				break;
			case CMPL:
				this->cmpl();
				this->rip++;
				break;
			case CMPLE:
				this->cmple();
				this->rip++;
				break;
			case CMPG:
				this->cmpg();
				this->rip++;
				break;
			case CMPGE:
				this->cmpge();
				this->rip++;
				break;
				
			case JMPTRUE:
				//printf( "\n JMPTRUE at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				if( this->stack.back()->get<bool>() == true )
					this->rip = &(this->current_function->code.front()) + *(const unsigned long long*)(this->rip+1);
				else
					this->rip += 1 + sizeof(long long);
				this->pop();
				//printf( "\n     DONE!" );
				break;
			case JMPFALSE:
				//printf( "\n JMPFALSE at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				if( this->stack.back()->get<bool>() == false )
					this->rip = &(this->current_function->code.front()) + *(const unsigned long long*)(this->rip+1);
				else
					this->rip += 1 + sizeof(long long);
				this->pop();
				//printf( "\n     DONE!" );
				break;
			
			
			
			case PRINTC:
				this->printchar();
				this->rip++;
				break;
			case PRINTI:
				//printf( "\n PRINTI at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				this->printint();
				this->rip++;
				//printf( "\n     DONE!" );
				break;
			case PRINTR:
				this->printreal();
				this->rip++;
				break;
			case PRINTS:
				//printf( "\n PRINTS at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				this->printstring();
				this->rip++;
				//printf( "\n     DONE!" );
				break;
			case GETC:
				this->getchar();
				this->rip++;
				break;
			case GETI:
				//printf( "\n GETI at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				this->getint();
				this->rip++;
				//printf( "\n     DONE!" );
				break;
			case GETR:
				this->getreal();
				this->rip++;
				break;
			case GETS:
				this->getstring();
				this->rip++;
				break;
			
			case PUSHCHAR:
				//printf( "\n PUSHCHAR at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				this->push<char>( *(char*)(this->rip+1) );
				this->rip += 1 + sizeof(char);
				//printf( "\n     DONE!" );
				break;
			case PUSHINT:
				//printf( "\n PUSHINT at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				this->push<long long>( *(long long*)(this->rip+1) );
				this->rip += 1 + sizeof(long long);
				//printf( "\n     DONE!" );
				break;
			case PUSHREAL:
				//printf( "\n PUSHREAL at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				this->push<double>( *(double*)(this->rip+1) );
				this->rip += 1 + sizeof(double);
				//printf( "\n     DONE!" );
				break;
			case PUSHSTR:
				//printf( "\n PUSHSTR at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				str = (const char*)(this->rip+1);
				//printf( "\n AAA" );
				this->push<std::string>( str );
				//printf( "\n BBB" );
				this->rip += 1 + str.size() + 1;
				//printf( "\n     DONE!" );
				break;
			
			case PUSHREF:
				//printf( "\n PUSHREF at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				this->push( *(this->stack[this->rsp+*(const long long*)(this->rip+1)]) );
				this->rip += 1 + sizeof(long long);
				//printf( "\n     DONE!" );
				break;
			case PUSHCOPY:
				//printf( "\n PUSHCOPY at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				this->push( *variable::make( this->stack[this->rsp+*(const long long*)(this->rip+1)]->type_ref ) );
				this->stack.back()->set_value_of( *(this->stack[this->rsp+*(const long long*)(this->rip+1)]) );
				this->rip += 1 + sizeof(long long);
				//printf( "\n     DONE!" );
				break;
			
			case POPCOPY:
				//printf( "\n POPCOPY at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				i = this->rsp + *(const long long*)(this->rip+1);
				this->stack[i]->dereference();
				this->stack[i] = variable::make( this->stack[this->rsp+*(const long long*)(this->rip+1)]->type_ref );
				this->stack[i]->set_value_of( *(this->stack[this->rsp+*(const long long*)(this->rip+1)]) );
				this->rip += 1 + sizeof(long long);
				this->pop();
				//printf( "\n     DONE!" );
				break;
			case POPREF:
				//printf( "\n POPREF at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				i = this->rsp + *(const long long*)(this->rip+1);
				this->stack[i]->dereference();
				this->stack.back()->makereference();
				this->stack[i] = this->stack.back();
				this->rip += 1 + sizeof(long long);
				this->pop();
				//printf( "\n     DONE!" );
				break;
			case POPVALUE:
				//printf( "\n POPVALUE at: 0x%X", unsigned(this->rip-&(this->current_function->code[0])) );
				i = this->rsp + *(const long long*)(this->rip+1);
				this->stack[i]->set_value_of( *(this->stack.back()) );
				this->rip += 1 + sizeof(long long);
				this->pop();
				//printf( "\n     DONE!" );
				break;
			
			default:
				//printf( "\n Instruction [0x%X]0x%2.2X not found", unsigned(this->rip-&(this->current_function->code[0])), unsigned(*(this->rip)) );
				this->rip++;
				//printf( "\n     DONE!" );
			}
		}
	}
};

#endif

