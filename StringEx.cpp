

#include "stringex.h"

void ToUP(string& str)
{
	for(int i=0 ; i<str.length() ; i++)
	{
		if( str[i] >= 'a' && str[i] <= 'z' ) 
			str[i] = str[i] -'a' + 'A' ;
	}
}

string FillChar(string str,char c,int max,int dir)
{
	while( str.length() < max )
	{
		if( dir == 0 )
			str = c + str ;
		else
			str = str + c ;
	}
	return str ;
}

int GetHexValue(char c)
{
	if( c>='0' && c<='9')
		return c - '0' ;
	else if( c>='A' && c<='Z' )
		return c - 'A' + 10 ;
	else if( c>='a' && c<='z' )
		return c - 'a' + 10 ;
	else
		return 0 ;
}

char GetHexChar(int c)
{
	c %= 16 ;
	if( c<10 )
		return c + '0' ;
	else
		return c - 10 + 'A' ;
}

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

bool HexStringToInt(string str,unsigned long int& loc)
{
	loc = 0 ;

	for( int i=0 ; i<str.length() ; i++)
	{
		if( (str[i] >='0' && str[i] <='9') ||
			(str[i] >='a' && str[i] <='f') ||
			(str[i] >='A' && str[i] <='F') )
			loc = (loc*16) + GetHexValue(str[i]) ;
		else
			return false ;
	}
	return true ;
}

string IntToHexString(unsigned long int v)
{
	string r ;
	do
	{
		r = GetHexChar(v%16)+r ;
		v/=16 ;
	}while( v!=0 ) ;

	return r ;
}

bool DecStringToInt(string str,long int& v)
{
	v = 0 ;
	for( int i=0 ; i<str.length() ; i++)
	{
		if( str[i] >='0' && str[i] <= '9' )
			v = v*10 + str[i] - '0' ;
		else
			return false ;
	}
	return true ;
}

string IntToDecString(unsigned long int v)
{
	string r ;
	do
	{
		r = GetHexChar(v%10)+r ;
		v/=10 ;
	}while( v!=0 ) ;
	return r ;
}
