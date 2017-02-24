


#include <string>
using namespace std ;

void ToUP(string& str) ;

string FillChar(string str,char c,int max,int dir) ;

int GetHexValue(char c) ;

char GetHexChar(int c) ;

bool HexStringToInt(string str,unsigned long int& loc) ;

string IntToHexString(unsigned long int v) ;

bool DecStringToInt(string str,long int& v) ;

string IntToDecString(unsigned long int v) ;
