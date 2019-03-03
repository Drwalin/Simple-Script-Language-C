
#ifndef RUN_CPP
#define RUN_CPP

#include "sslc.h"

namespace sslc
{
	void machine::interprete()
	{
		unsigned long long i;
		std::string str;
		while( this->current_function )
		{
			switch( *(this->rip) )
			{
			case CALL:
				
				this->stack.emplace_back( this->rsp );
				this->stack.emplace_back( this->rip );
				this->stack.emplace_back( this->current_function );
				
				this->rsp = this->stack.size();
				
				str = *(const char*)(this->rip+1);
				this->current_function = this->functions[*(const char*)(this->rip+1)];
				for( i = 0; i < this->current_function->local_variables_types.size(); ++i )
					this->push( *varaible::make( this->current_function->local_variables_types[i] ) );
				
				this->rip = &(this->current_function->code.front());
				
				break;
			
			
			
			case RET:
				
				for( i = this->rsp - 3 - this->current_funtion->args_types.size(); i < this->rsp-3; ++i )
					this->stack[i]->dereference();
				for( i = this->rsp-3; i < this->rsp + this->current_funtion->local_variables_types.size(); ++i )
					this->stack[i]->dereference();
				
				i = this->rsp;
				
				this->current_funtion = this->stack[i];
				this->rip = this->stack[i-1];
				this->rsp = this->stack[i-2];
				
				this->stack.erase( this->stack.begin() + i - 3 - this->current_funtion->args_types.size(), this->stack.begin() + i + this->current_funtion->local_variables_types.size() );
				
				break;
			
			
			
			case JMP:
				this->rip = &(this->current_function->code.front()) + *(const unsigned long long*)(this->rip+1);
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
				this->mod();
				this->rip++;
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
				this->cmpe();
				this->rip++;
				break;
			case CMPNE:
				this->cmpne();
				this->rip++;
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
				if( this->stack.back()->get<bool>() == true )
					this->rip = &(this->current_function->code.front()) + *(const unsigned long long*)(this->rip+1);
				else
					this->rip += 1 + sizeof(long long);
				this->pop();
				break;
			case JMPFALSE:
				if( this->stack.back()->get<bool>() == false )
					this->rip = &(this->current_function->code.front()) + *(const unsigned long long*)(this->rip+1);
				else
					this->rip += 1 + sizeof(long long);
				this->pop();
				break;
			
			
			
			case PRINTC:
				this->printchar();
				break;
			case PRINTI:
				this->printint();
				break;
			case PRINTR:
				this->printreal();
				break;
			case PRINTS:
				this->printstring();
				break;
			case GETC:
				this->printchar();
				break;
			case GETI:
				this->printint();
				break;
			case GETR:
				this->printreal();
				break;
			case GETS:
				this->printstring();
				break;
			
			case PUSHCHAR:
				this->push<char>( *(const char*)(this->rip+1) );
				this->rip += 1 + sizeof(char);
				break;
			case PUSHINT:
				this->push<long long>( *(const long long*)(this->rip+1) );
				this->rip += 1 + sizeof(long long);
				break;
			case PUSHREAL:
				this->push<char>( *(const double*)(this->rip+1) );
				this->rip += 1 + sizeof(double);
				break;
			case PUSHSTR:
				this->push<std::string>( std::string(*(const char*)(this->rip+1)) );
				i = strlen( *(const char*)(this->rip+1) );
				this->rip += 1 + strlen( *(const char*)(this->rip+1) ) + 1;
				break;
			
			case PUSHREF:
				this->push<variable>( *(this->stack[this->rsp+*(const long long*)(this->rip+1)]) );
				this->rip += 1 + sizeof(long long);
				break;
			case PUSHCOPY:
				this->push( *variable::make( this->stack[this->rsp+*(const long long*)(this->rip+1)]->type_ref ) );
				this->stack.back()->set_value_of( *(this->stack[this->rsp+*(const long long*)(this->rip+1)]) );
				this->rip += 1 + sizeof(long long);
				break;
			
			case POPCOPY:
				i = this->rsp + *(const long long*)(this->rip+1)
				this->stack[i]->dereference();
				this->stack[i]->set_value_of( *(this->stack[this->rsp+*(const long long*)(this->rip+1)]) );
				this->rip += 1 + sizeof(long long);
				this->pop();
				break;
			case POPREF:
				i = this->rsp + *(const long long*)(this->rip+1)
				 this->stack[i]->dereference();
				 this->stack.back()->reference();
				 this->stack[i] = this->stack.back();
				this->rip += 1 + sizeof(long long);
				this->pop();
				break;
			case POPVALUE:
				i = this->rsp + *(const long long*)(this->rip+1)
				this->stack[i]->set_value_of( *(this->stack.back()) );
				this->rip += 1 + sizeof(long long);
				this->pop();
				break;
			
			default:
				this->rip++;
			}
		}
	}
};

#endif

