
#ifndef INIT_CPP
#define INIT_CPP

#include "sslc.h"

#define REGISTER_TYPE( _name, size )		\
		{								\
			t = new type;				\
			t->name = _name;				\
			t->size_bytes = size;		\
			this->types[_name] = t;		\
			t = NULL;					\
		}

namespace sslc
{
	
	
	void machine::init()
	{
		type * t = NULL;
		
		REGISTER_TYPE( "void", 1 );
		this->TYPE_VOID = this->types["void"];
		
		REGISTER_TYPE( "bool", 1 );
		this->TYPE_BOOL = this->types["bool"];
		REGISTER_TYPE( "int", sizeof(long long) );
		this->TYPE_INT = this->types["int"];
		
		REGISTER_TYPE( "char", sizeof(char) );
		this->TYPE_CHAR = this->types["char"];
		REGISTER_TYPE( "string", sizeof(std::string) );
		this->TYPE_STRING = this->types["string"];
		
		REGISTER_TYPE( "real", sizeof(double) );
		this->TYPE_REAL = this->types["real"];
		REGISTER_TYPE( "complex", sizeof(complex) );
		this->TYPE_COMPLEX = this->types["complex"];
		REGISTER_TYPE( "quaternion", sizeof(quaternion) );
		this->TYPE_QUATERNION = this->types["quaternion"];
		REGISTER_TYPE( "octonion", sizeof(octonion) );
		this->TYPE_OCTONION = this->types["octonion"];
		
		REGISTER_TYPE( "vec2", sizeof(glm::vec2) );
		this->TYPE_VEC2 = this->types["vec2"];
		REGISTER_TYPE( "vec3", sizeof(glm::vec3) );
		this->TYPE_VEC3 = this->types["vec3"];
		REGISTER_TYPE( "vec4", sizeof(glm::vec4) );
		this->TYPE_VEC4 = this->types["vec4"];
		REGISTER_TYPE( "mat2x2", sizeof(glm::mat2x2) );
		this->TYPE_MAT2X2 = this->types["mat2x2"];
		REGISTER_TYPE( "mat3x3", sizeof(glm::mat3x3) );
		this->TYPE_MAT3X3 = this->types["mat3x3"];
		REGISTER_TYPE( "mat4x4", sizeof(glm::mat4x4) );
		this->TYPE_MAT4X4 = this->types["mat4x4"];
		
		//REGISTER_TYPE( "array", sizeof(???) );
		//this->TYPE_ARRAY = this->types["array"];
		//REGISTER_TYPE( "map", sizeof(???) );
		//this->TYPE_MAP = this->types["map"];
		//REGISTER_TYPE( "set", sizeof(???) );
		//this->TYPE_SET = this->types["set"];
	}
	
};

#undef REGISTER_TYPE

#endif

