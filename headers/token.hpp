#ifndef __TOKEN__
	#define __TOKEN__

#include <string>
#include <fstream>
/**
 * @struct Token
*/
 using namespace std;
 
struct Token {
	string str;
	int col;

	friend ostream& operator<<(ostream& os, const Token& tk)
	{
	    os << "(" << tk.str <<  ", " << tk.col << ")";
	    return os;
	}
};

#endif