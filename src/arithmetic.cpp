
#ifndef ARITHMETIC_CPP
#define ARITHMETIC_CPP

#include "sslc.h"

#include <glm/glm.hpp>
#include <boost/math/octonion.hpp>
#include <boost/math/quaternion.hpp>
#include <complex>

namespace sslc
{
	void machine::add()
	{
		variable * tmp = this->stack[this->stack.size()-2];
		variable * a = variable::make( this, tmp->type_ref );
		a->set_value_of( *tmp );
		variable * b = this->stack[this->stack.size()-1];
		
		if( a->type_ref == this->TYPE_CHAR )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<char>() += b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<char>() += b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<char>() += b->get<double>();
		}
		else if( a->type_ref == this->TYPE_INT )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<long long>() += b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<long long>() += b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<long long>() += b->get<double>();
		}
		else if( a->type_ref == this->TYPE_REAL )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<double>() += b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<double>() += b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<double>() += b->get<double>();
		}
		else if( a->type_ref == this->TYPE_STRING )
		{
			if( b->type_ref == this->TYPE_STRING )
				a->access<std::string>() += b->get<std::string>();
			
			else if( b->type_ref == this->TYPE_CHAR )
				a->access<std::string>() += std::to_string(b->get<char>());
			else if( b->type_ref == this->TYPE_INT )
				a->access<std::string>() += std::to_string(b->get<long long>());
			else if( b->type_ref == this->TYPE_REAL )
				a->access<std::string>() += std::to_string(b->get<double>());
			
			else if( b->type_ref == this->TYPE_COMPLEX )
			{
				a->access<std::string>() += "(";
				a->access<std::string>() += b->get<complex>().real();
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<complex>().imag();
				a->access<std::string>() += ")";
			}
			else if( b->type_ref == this->TYPE_QUATERNION )
			{
				a->access<std::string>() += "(";
				a->access<std::string>() += b->get<quaternion>().R_component_1();
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<quaternion>().R_component_2();
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<quaternion>().R_component_3();
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<quaternion>().R_component_4();
				a->access<std::string>() += ")";
			}
			else if( b->type_ref == this->TYPE_OCTONION )
			{
				a->access<std::string>() += "(";
				a->access<std::string>() += b->get<octonion>().R_component_1();
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<octonion>().R_component_2();
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<octonion>().R_component_3();
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<octonion>().R_component_4();
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<octonion>().R_component_5();
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<octonion>().R_component_6();
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<octonion>().R_component_7();
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<octonion>().R_component_8();
				a->access<std::string>() += ")";
			}
			
			else if( b->type_ref == this->TYPE_VEC2 )
			{
				a->access<std::string>() += "(";
				a->access<std::string>() += b->get<glm::vec2>().x;
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<glm::vec2>().y;
				a->access<std::string>() += ")";
			}
			else if( b->type_ref == this->TYPE_VEC3 )
			{
				a->access<std::string>() += "(";
				a->access<std::string>() += b->get<glm::vec3>().x;
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<glm::vec3>().y;
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<glm::vec3>().z;
				a->access<std::string>() += ")";
			}
			else if( b->type_ref == this->TYPE_VEC4 )
			{
				a->access<std::string>() += "(";
				a->access<std::string>() += b->get<glm::vec4>().x;
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<glm::vec4>().y;
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<glm::vec4>().z;
				a->access<std::string>() += ",";
				a->access<std::string>() += b->get<glm::vec4>().w;
				a->access<std::string>() += ")";
			}
			
			else if( b->type_ref == this->TYPE_MAT2X2 )
			{
				a->access<std::string>() += "(";
				for( int i = 0; i < 2; ++i )
				{
					if( i != 0 )
						a->access<std::string>() += ",";
					a->access<std::string>() += "(";
					for( int j = 0; j < 2; ++j )
					{
						if( j != 0 )
							a->access<std::string>() += ",";
						a->access<std::string>() += std::to_string( b->get<glm::mat2x2>()[i][j] );
					}
					a->access<std::string>() += ")";
				}
				a->access<std::string>() += ")";
			}
			else if( b->type_ref == this->TYPE_MAT3X3 )
			{
				a->access<std::string>() += "(";
				for( int i = 0; i < 3; ++i )
				{
					if( i != 0 )
						a->access<std::string>() += ",";
					a->access<std::string>() += "(";
					for( int j = 0; j < 3; ++j )
					{
						if( j != 0 )
							a->access<std::string>() += ",";
						a->access<std::string>() += std::to_string( b->get<glm::mat3x3>()[i][j] );
					}
					a->access<std::string>() += ")";
				}
				a->access<std::string>() += ")";
			}
			else if( b->type_ref == this->TYPE_MAT4X4 )
			{
				a->access<std::string>() += "(";
				for( int i = 0; i < 4; ++i )
				{
					if( i != 0 )
						a->access<std::string>() += ",";
					a->access<std::string>() += "(";
					for( int j = 0; j < 4; ++j )
					{
						if( j != 0 )
							a->access<std::string>() += ",";
						a->access<std::string>() += std::to_string( b->get<glm::mat4x4>()[i][j] );
					}
					a->access<std::string>() += ")";
				}
				a->access<std::string>() += ")";
			}
		}
		else if( a->type_ref == b->type_ref )
		{
			if( b->type_ref == this->TYPE_COMPLEX )
				a->access<complex>() += b->get<complex>();
			else if( b->type_ref == this->TYPE_QUATERNION )
				a->access<quaternion>() += b->get<quaternion>();
			else if( b->type_ref == this->TYPE_OCTONION )
				a->access<octonion>() += b->get<octonion>();
			
			else if( b->type_ref == this->TYPE_VEC2 )
				a->access<glm::vec2>() += b->get<glm::vec2>();
			else if( b->type_ref == this->TYPE_VEC3 )
				a->access<glm::vec3>() += b->get<glm::vec3>();
			else if( b->type_ref == this->TYPE_VEC4 )
				a->access<glm::vec4>() += b->get<glm::vec4>();
			else if( b->type_ref == this->TYPE_MAT2X2 )
				a->access<glm::mat2x2>() += b->get<glm::mat2x2>();
			else if( b->type_ref == this->TYPE_MAT3X3 )
				a->access<glm::mat3x3>() += b->get<glm::mat3x3>();
			else if( b->type_ref == this->TYPE_MAT4X4 )
				a->access<glm::mat4x4>() += b->get<glm::mat4x4>();
		}
		
		this->pop();
		this->pop();
		this->push( *a );
	}
	
	void machine::sub()
	{
		variable * tmp = this->stack[this->stack.size()-2];
		variable * a = variable::make( this, tmp->type_ref );
		a->set_value_of( *tmp );
		variable * b = this->stack[this->stack.size()-1];
		
		if( a->type_ref == this->TYPE_CHAR )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<char>() -= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<char>() -= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<char>() -= b->get<double>();
		}
		else if( a->type_ref == this->TYPE_INT )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<long long>() -= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<long long>() -= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<long long>() -= b->get<double>();
		}
		else if( a->type_ref == this->TYPE_REAL )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<double>() -= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<double>() -= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<double>() -= b->get<double>();
		}
		else if( a->type_ref == b->type_ref )
		{
			if( b->type_ref == this->TYPE_COMPLEX )
				a->access<complex>() -= b->get<complex>();
			else if( b->type_ref == this->TYPE_QUATERNION )
				a->access<quaternion>() -= b->get<quaternion>();
			else if( b->type_ref == this->TYPE_OCTONION )
				a->access<octonion>() -= b->get<octonion>();
			
			else if( b->type_ref == this->TYPE_VEC2 )
				a->access<glm::vec2>() -= b->get<glm::vec2>();
			else if( b->type_ref == this->TYPE_VEC3 )
				a->access<glm::vec3>() -= b->get<glm::vec3>();
			else if( b->type_ref == this->TYPE_VEC4 )
				a->access<glm::vec4>() -= b->get<glm::vec4>();
			else if( b->type_ref == this->TYPE_MAT2X2 )
				a->access<glm::mat2x2>() -= b->get<glm::mat2x2>();
			else if( b->type_ref == this->TYPE_MAT3X3 )
				a->access<glm::mat3x3>() -= b->get<glm::mat3x3>();
			else if( b->type_ref == this->TYPE_MAT4X4 )
				a->access<glm::mat4x4>() -= b->get<glm::mat4x4>();
		}
		
		this->pop();
		this->pop();
		this->push( *a );
	}
	
	void machine::mul()
	{
		variable * tmp = this->stack[this->stack.size()-2];
		variable * a = variable::make( this, tmp->type_ref );
		a->set_value_of( *tmp );
		variable * b = this->stack[this->stack.size()-1];
		
		if( a->type_ref == this->TYPE_CHAR )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<char>() *= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<char>() *= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<char>() *= b->get<double>();
		}
		else if( a->type_ref == this->TYPE_INT )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<long long>() *= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<long long>() *= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<long long>() *= b->get<double>();
		}
		else if( a->type_ref == this->TYPE_REAL )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<double>() *= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<double>() *= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<double>() *= b->get<double>();
		}
		
		else if( a->type_ref == this->TYPE_COMPLEX )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<complex>() *= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<complex>() *= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<complex>() *= b->get<double>();
			else if( b->type_ref == this->TYPE_COMPLEX )
				a->access<complex>() *= b->get<complex>();
		}
		else if( a->type_ref == this->TYPE_QUATERNION )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<quaternion>() *= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<quaternion>() *= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<quaternion>() *= b->get<double>();
			else if( b->type_ref == this->TYPE_COMPLEX )
				a->access<quaternion>() *= b->get<complex>();
			else if( b->type_ref == this->TYPE_QUATERNION )
				a->access<quaternion>() *= b->get<quaternion>();
		}
		else if( a->type_ref == this->TYPE_OCTONION )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<octonion>() *= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<octonion>() *= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<octonion>() *= b->get<double>();
			else if( b->type_ref == this->TYPE_COMPLEX )
				a->access<octonion>() *= b->get<complex>();
			else if( b->type_ref == this->TYPE_QUATERNION )
				a->access<octonion>() *= b->get<quaternion>();
			else if( b->type_ref == this->TYPE_OCTONION )
				a->access<octonion>() *= b->get<octonion>();
		}
		
		else if( a->type_ref == this->TYPE_VEC2 )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<glm::vec2>() *= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<glm::vec2>() *= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<glm::vec2>() *= b->get<double>();
		}
		else if( a->type_ref == this->TYPE_VEC3 )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<glm::vec3>() *= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<glm::vec3>() *= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<glm::vec3>() *= b->get<double>();
		}
		else if( a->type_ref == this->TYPE_VEC4 )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<glm::vec4>() *= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<glm::vec4>() *= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<glm::vec4>() *= b->get<double>();
		}
		
		else if( a->type_ref == this->TYPE_MAT2X2 )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<glm::mat2x2>() *= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<glm::mat2x2>() *= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<glm::mat2x2>() *= b->get<double>();
			else if( b->type_ref == this->TYPE_MAT2X2 )
				a->access<glm::mat2x2>() *= b->get<glm::mat2x2>();
		}
		else if( a->type_ref == this->TYPE_MAT3X3 )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<glm::mat3x3>() *= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<glm::mat3x3>() *= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<glm::mat3x3>() *= b->get<double>();
			else if( b->type_ref == this->TYPE_MAT3X3 )
				a->access<glm::mat3x3>() *= b->get<glm::mat3x3>();
		}
		else if( a->type_ref == this->TYPE_MAT4X4 )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<glm::mat4x4>() *= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<glm::mat4x4>() *= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<glm::mat4x4>() *= b->get<double>();
			else if( b->type_ref == this->TYPE_MAT4X4 )
				a->access<glm::mat4x4>() *= b->get<glm::mat4x4>();
		}
		
		this->pop();
		this->pop();
		this->push( *a );
	}
	
	void machine::div()
	{
		variable * tmp = this->stack[this->stack.size()-2];
		variable * a = variable::make( this, tmp->type_ref );
		a->set_value_of( *tmp );
		variable * b = this->stack[this->stack.size()-1];
		
		if( a->type_ref == this->TYPE_CHAR )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<char>() /= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<char>() /= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<char>() /= b->get<double>();
		}
		else if( a->type_ref == this->TYPE_INT )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<long long>() /= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
			{
				printf( "\n DIV" );
				printf( "\n this->stack.size() = %lli", (long long)(this->stack.size()) );
				printf( "\n this->rsp = %lli", (long long)(this->rsp) );
				printf( "\n a = %lli ; b = %lli", a->get<long long>(), b->get<long long>() );
				a->access<long long>() /= b->get<long long>();
			}
			else if( b->type_ref == this->TYPE_REAL )
				a->access<long long>() /= b->get<double>();
		}
		else if( a->type_ref == this->TYPE_REAL )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<double>() /= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<double>() /= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<double>() /= b->get<double>();
		}
		
		else if( a->type_ref == this->TYPE_COMPLEX )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<complex>() /= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<complex>() /= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<complex>() /= b->get<double>();
			else if( b->type_ref == this->TYPE_COMPLEX )
				a->access<complex>() /= b->get<complex>();
		}
		else if( a->type_ref == this->TYPE_QUATERNION )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<quaternion>() /= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<quaternion>() /= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<quaternion>() /= b->get<double>();
			else if( b->type_ref == this->TYPE_COMPLEX )
				a->access<quaternion>() /= b->get<complex>();
			else if( b->type_ref == this->TYPE_QUATERNION )
				a->access<quaternion>() /= b->get<quaternion>();
		}
		else if( a->type_ref == this->TYPE_OCTONION )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<octonion>() /= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<octonion>() /= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<octonion>() /= b->get<double>();
			else if( b->type_ref == this->TYPE_COMPLEX )
				a->access<octonion>() /= b->get<complex>();
			else if( b->type_ref == this->TYPE_QUATERNION )
				a->access<octonion>() /= b->get<quaternion>();
			else if( b->type_ref == this->TYPE_OCTONION )
				a->access<octonion>() /= b->get<octonion>();
		}
		
		else if( a->type_ref == this->TYPE_VEC2 )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<glm::vec2>() /= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<glm::vec2>() /= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<glm::vec2>() /= b->get<double>();
		}
		else if( a->type_ref == this->TYPE_VEC3 )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<glm::vec3>() /= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<glm::vec3>() /= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<glm::vec3>() /= b->get<double>();
		}	
		else if( a->type_ref == this->TYPE_VEC4 )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<glm::vec4>() /= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<glm::vec4>() /= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<glm::vec4>() /= b->get<double>();
		}
		
		else if( a->type_ref == this->TYPE_MAT2X2 )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<glm::mat2x2>() /= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<glm::mat2x2>() /= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<glm::mat2x2>() /= b->get<double>();
			else if( b->type_ref == this->TYPE_MAT2X2 )
				a->access<glm::mat2x2>() /= b->get<glm::mat2x2>();
		}
		else if( a->type_ref == this->TYPE_MAT3X3 )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<glm::mat3x3>() /= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<glm::mat3x3>() /= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<glm::mat3x3>() /= b->get<double>();
			else if( b->type_ref == this->TYPE_MAT3X3 )
				a->access<glm::mat3x3>() /= b->get<glm::mat3x3>();
		}
		else if( a->type_ref == this->TYPE_MAT4X4 )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<glm::mat4x4>() /= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
				a->access<glm::mat4x4>() /= b->get<long long>();
			else if( b->type_ref == this->TYPE_REAL )
				a->access<glm::mat4x4>() /= b->get<double>();
			else if( b->type_ref == this->TYPE_MAT4X4 )
				a->access<glm::mat4x4>() /= b->get<glm::mat4x4>();
		}
		
		this->pop();
		this->pop();
		this->push( *a );
	}
	
	void machine::mod()
	{
		variable * tmp = this->stack[this->stack.size()-2];
		variable * a = variable::make( this, tmp->type_ref );
		a->set_value_of( *tmp );
		variable * b = this->stack[this->stack.size()-1];
		
		if( a->type_ref == b->type_ref )
		{
			if( b->type_ref == this->TYPE_CHAR )
				a->access<char>() %= b->get<char>();
			else if( b->type_ref == this->TYPE_INT )
			{
				printf( "\n MOD" );
				printf( "\n this->stack.size() = %lli", (long long)(this->stack.size()) );
				printf( "\n this->rsp = %lli", (long long)(this->rsp) );
				printf( "\n a = %lli ; b = %lli", a->get<long long>(), b->get<long long>() );
				a->access<long long>() %= b->get<long long>();
			}
			else if( b->type_ref == this->TYPE_REAL )
				a->set<double>( fmod( a->get<double>(), b->get<double>() ) );
		}
		
		this->pop();
		this->pop();
		this->push( *a );
	}
	
	void machine::neg()
	{
		variable * b = this->stack[this->stack.size()-1];
		variable * a = variable::make( this, b->type_ref );
		
		if( a->type_ref == this->TYPE_CHAR )
			a->set<char>( -(b->get<char>()) );
		else if( a->type_ref == this->TYPE_INT )
			a->set<long long>( -(b->get<long long>()) );
		else if( a->type_ref == this->TYPE_REAL )
			a->set<double>( -(b->get<double>()) );
		else if( a->type_ref == this->TYPE_COMPLEX )
			a->set<complex>( -(b->get<complex>()) );
		else if( a->type_ref == this->TYPE_QUATERNION )
			a->set<quaternion>( -(b->get<quaternion>()) );
		else if( a->type_ref == this->TYPE_OCTONION )
			a->set<octonion>( -(b->get<octonion>()) );
		
		else if( a->type_ref == this->TYPE_VEC2 )
			a->set<glm::vec2>( -(b->get<glm::vec2>()) );
		else if( a->type_ref == this->TYPE_VEC3 )
			a->set<glm::vec3>( -(b->get<glm::vec3>()) );
		else if( a->type_ref == this->TYPE_VEC4 )
			a->set<glm::vec4>( -(b->get<glm::vec4>()) );
		else if( a->type_ref == this->TYPE_MAT2X2 )
			a->set<glm::mat2x2>( -(b->get<glm::mat2x2>()) );
		else if( a->type_ref == this->TYPE_MAT3X3 )
			a->set<glm::mat3x3>( -(b->get<glm::mat3x3>()) );
		else if( a->type_ref == this->TYPE_MAT4X4 )
			a->set<glm::mat4x4>( -(b->get<glm::mat4x4>()) );
		
		this->pop();
		this->push( a );
	}
	
	void machine::binary_xor()
	{
		variable * tmp = this->stack[this->stack.size()-2];
		variable * a = variable::make( this, tmp->type_ref );
		a->set_value_of( *tmp );
		variable * b = this->stack[this->stack.size()-1];
		
		if( a->type_ref == this->TYPE_BOOL )
		{
			if( b->type_ref == this->TYPE_BOOL )
				a->set<char>( ( ( a->get<char>() && b->get<char>() == 0 ) || ( a->get<char>() == 0 && b->get<char>() ) ) ? 1 : 0 );
		}
		else if( a->type_ref == this->TYPE_ARRAY )
		{
			
		}
		else if( a->type_ref == this->TYPE_SET )
		{
			
		}
		else if( a->type_ref == this->TYPE_MAP )
		{
			
		}
		else if( a->type_ref == this->TYPE_STRING && b->type_ref == this->TYPE_STRING )
		{
			unsigned long long size = a->get<std::string>().size();
			if( size < b->get<std::string>().size() )
				size = b->get<std::string>().size();
			++size;
			
			a->access<std::string>().resize( size );
			
			unsigned long long i;
			for( unsigned long long i = 0; i < size; ++i )
				a->access<std::string>()[i] ^= b->access<std::string>()[i];
		}
		else
		{
			unsigned long long size = a->type_ref->size_bytes;
			if( size > b->type_ref->size_bytes )
				size = b->type_ref->size_bytes;
			
			unsigned char * A = (unsigned char*)(a->data);
			unsigned char * B = (unsigned char*)(a->data);
			unsigned char * AE = A + size;
			
			for( ; A < AE; ++A, ++B )
				*A ^= *B;
		}
		
		this->pop();
		this->pop();
		this->push( *a );
	}
	
	void machine::binary_or()
	{
		variable * tmp = this->stack[this->stack.size()-2];
		variable * a = variable::make( this, tmp->type_ref );
		a->set_value_of( *tmp );
		variable * b = this->stack[this->stack.size()-1];
		
		if( a->type_ref == this->TYPE_BOOL )
		{
			if( b->type_ref == this->TYPE_BOOL )
				a->set<char>( ( a->get<char>() | b->get<char>() ) ? 1 : 0 );
		}
		else if( a->type_ref == this->TYPE_ARRAY )
		{
			
		}
		else if( a->type_ref == this->TYPE_SET )
		{
			
		}
		else if( a->type_ref == this->TYPE_MAP )
		{
			
		}
		else if( a->type_ref == this->TYPE_STRING && b->type_ref == this->TYPE_STRING )
		{
			unsigned long long size = a->get<std::string>().size();
			if( size < b->get<std::string>().size() )
				size = b->get<std::string>().size();
			++size;
			
			a->access<std::string>().resize( size );
			
			unsigned long long i;
			for( unsigned long long i = 0; i < size; ++i )
				a->access<std::string>()[i] |= b->access<std::string>()[i];
		}
		else
		{
			unsigned long long size = a->type_ref->size_bytes;
			if( size > b->type_ref->size_bytes )
				size = b->type_ref->size_bytes;
			
			unsigned char * A = (unsigned char*)(a->data);
			unsigned char * B = (unsigned char*)(a->data);
			unsigned char * AE = A + size;
			
			for( ; A < AE; ++A, ++B )
				*A |= *B;
		}
		
		this->pop();
		this->pop();
		this->push( *a );
	}
	
	void machine::binary_and()
	{
		variable * tmp = this->stack[this->stack.size()-2];
		variable * a = variable::make( this, tmp->type_ref );
		a->set_value_of( *tmp );
		variable * b = this->stack[this->stack.size()-1];
		
		if( a->type_ref == this->TYPE_BOOL )
		{
			if( b->type_ref == this->TYPE_BOOL )
				a->set<char>( ( a->get<char>() & b->get<char>() ) ? 1 : 0 );
		}
		else if( a->type_ref == this->TYPE_ARRAY )
		{
			
		}
		else if( a->type_ref == this->TYPE_SET )
		{
			
		}
		else if( a->type_ref == this->TYPE_MAP )
		{
			
		}
		else if( a->type_ref == this->TYPE_STRING && b->type_ref == this->TYPE_STRING )
		{
			unsigned long long size = a->get<std::string>().size();
			if( size < b->get<std::string>().size() )
				size = b->get<std::string>().size();
			++size;
			
			a->access<std::string>().resize( size );
			
			unsigned long long i;
			for( unsigned long long i = 0; i < size; ++i )
				a->access<std::string>()[i] &= b->access<std::string>()[i];
		}
		else
		{
			unsigned long long size = a->type_ref->size_bytes;
			if( size > b->type_ref->size_bytes )
				size = b->type_ref->size_bytes;
			
			unsigned char * A = (unsigned char*)(a->data);
			unsigned char * B = (unsigned char*)(a->data);
			int i;
			
			for( i = 0; i < size; ++i, ++A, ++B )
				*A &= *B;
			size = a->type_ref->size_bytes;
			for( ; i < size; ++i, ++A )
				*A &= 0;
		}
		
		this->pop();
		this->pop();
		this->push( *a );
	}
	
	void machine::binary_not()
	{
		variable * b = this->stack[this->stack.size()-1];
		variable * a = variable::make( this, b->type_ref );
		
		if( a->type_ref == this->TYPE_BOOL )
		{
			a->set<char>( b->get<char>() ? 0 : 1 );
		}
		else if( a->type_ref == this->TYPE_ARRAY )
		{
			
		}
		else if( a->type_ref == this->TYPE_SET )
		{
			
		}
		else if( a->type_ref == this->TYPE_MAP )
		{
			
		}
		else if( a->type_ref == this->TYPE_STRING )
		{
			
		}
		else
		{
			unsigned long long size = a->type_ref->size_bytes;
			
			unsigned char * A = (unsigned char*)(a->data);
			unsigned char * AE = A + size;
			
			for( ; A < AE; ++A )
				*A = ~(*A);
		}
		
		this->pop();
		this->push( *a );
	}
	
	/*
	void machine::binary_shl();
	void machine::binary_shr();
	*/
	
	
	
	
	void machine::cmpe()
	{
		variable * a = this->stack[this->stack.size()-2];
		variable * b = this->stack[this->stack.size()-1];
		
		bool value = false;
		
		if( a->type_ref == this->TYPE_BOOL )
		{
			if( b->type_ref == this->TYPE_BOOL )
			{
				if( a->get<char>() && b->get<char>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_CHAR )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<char>() == b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<char>() == b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<char>() == b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_INT )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<long long>() == b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				printf( "\n { %lli == %lli } -> ", a->get<long long>(), b->get<long long>() );
				if( a->get<long long>() == b->get<long long>() )
					value = true;
				printf( value ? "true" : "false" );
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<long long>() == b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_REAL )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<double>() == b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<double>() == b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<double>() == b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_STRING && b->type_ref == this->TYPE_STRING )
		{
			if( a->get<std::string>() == b->get<std::string>() )
				value = true;
		}
		
		this->pop();
		this->pop();
		this->push<bool>(value);
		this->stack.back()->set<char>( value ? 1 : 0 );
	}
	
	void machine::cmpne()
	{
		variable * a = this->stack[this->stack.size()-2];
		variable * b = this->stack[this->stack.size()-1];
		
		bool value = false;
		
		if( a->type_ref == this->TYPE_BOOL )
		{
			if( b->type_ref == this->TYPE_BOOL )
				if( ( a->get<char>() && b->get<char>() == 0 ) || ( a->get<char>() == 0 && b->get<char>() ) )
					value = true;
		}
		else if( a->type_ref == this->TYPE_CHAR )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<char>() != b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<char>() != b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<char>() != b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_INT )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<long long>() != b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<long long>() != b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<long long>() != b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_REAL )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<double>() != b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<double>() != b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<double>() != b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_STRING && b->type_ref == this->TYPE_STRING )
		{
			if( a->get<std::string>() != b->get<std::string>() )
				value = true;
		}
		
		this->pop();
		this->pop();
		this->push<bool>(value);
		this->stack.back()->set<char>( value ? 1 : 0 );
	}
	
	void machine::cmpl()
	{
		variable * a = this->stack[this->stack.size()-2];
		variable * b = this->stack[this->stack.size()-1];
		
		bool value = false;
		
		if( a->type_ref == this->TYPE_CHAR )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<char>() < b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<char>() < b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<char>() < b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_INT )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<long long>() < b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<long long>() < b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<long long>() < b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_REAL )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<double>() < b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<double>() < b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<double>() < b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_STRING && b->type_ref == this->TYPE_STRING )
		{
			if( a->get<std::string>() < b->get<std::string>() )
				value = true;
		}
		
		this->pop();
		this->pop();
		this->push<bool>(value);
		this->stack.back()->set<char>( value ? 1 : 0 );
	}
	
	void machine::cmple()
	{
		variable * a = this->stack[this->stack.size()-2];
		variable * b = this->stack[this->stack.size()-1];
		
		bool value = false;
		
		if( a->type_ref == this->TYPE_CHAR )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<char>() <= b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<char>() <= b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<char>() <= b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_INT )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<long long>() <= b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<long long>() <= b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<long long>() <= b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_REAL )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<double>() <= b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<double>() <= b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<double>() <= b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_STRING && b->type_ref == this->TYPE_STRING )
		{
			if( a->get<std::string>() <= b->get<std::string>() )
				value = true;
		}
		
		this->pop();
		this->pop();
		this->push<bool>(value);
		this->stack.back()->set<char>( value ? 1 : 0 );
	}
	
	void machine::cmpg()
	{
		variable * a = this->stack[this->stack.size()-2];
		variable * b = this->stack[this->stack.size()-1];
		
		bool value = false;
		
		if( a->type_ref == this->TYPE_CHAR )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<char>() > b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<char>() > b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<char>() > b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_INT )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<long long>() > b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<long long>() > b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<long long>() > b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_REAL )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<double>() > b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<double>() > b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<double>() > b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_STRING && b->type_ref == this->TYPE_STRING )
		{
			if( a->get<std::string>() > b->get<std::string>() )
				value = true;
		}
		
		this->pop();
		this->pop();
		this->push<bool>(value);
		this->stack.back()->set<char>( value ? 1 : 0 );
	}
	
	void machine::cmpge()
	{
		variable * a = this->stack[this->stack.size()-2];
		variable * b = this->stack[this->stack.size()-1];
		
		bool value = false;
		
		if( a->type_ref == this->TYPE_CHAR )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<char>() >= b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<char>() >= b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<char>() >= b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_INT )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<long long>() >= b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<long long>() >= b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<long long>() >= b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_REAL )
		{
			if( b->type_ref == this->TYPE_CHAR )
			{
				if( a->get<double>() >= b->get<char>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_INT )
			{
				if( a->get<double>() >= b->get<long long>() )
					value = true;
			}
			else if( b->type_ref == this->TYPE_REAL )
			{
				if( a->get<double>() >= b->get<double>() )
					value = true;
			}
		}
		else if( a->type_ref == this->TYPE_STRING && b->type_ref == this->TYPE_STRING )
		{
			if( a->get<std::string>() >= b->get<std::string>() )
				value = true;
		}
		
		this->pop();
		this->pop();
		this->push<bool>(value);
		this->stack.back()->set<char>( value ? 1 : 0 );
	}
	
};

#endif

