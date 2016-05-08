#include <iostream>
using namespace std;

class String
{
public:
	String(const char *str)
		:_str(new char[strlen(str)+5])
	{
		*((int*)_str) = 1;
		_str += 4;
		strcpy(_str, str);
	}

	String(const String& s):_str(s._str)
	{
		*((int*)_str - 1) += 1;
	}

	String& operator=(const String& s)
	{
		if(_str != s._str)
		{
			if(--(*((int*)_str - 1)) == 0)
			{
				delete[] (_str-4);
			}
			_str = s._str;
			*((int*)_str - 1) += 1;
		}
		return *this;
	}

	~String()
	{
		if(--(*((int*)_str-1)) == 0)
		{
			delete[] (_str-4);
		}
	}
private:
	char *_str;
};

int main()
{
	String s1("qweer");
	String s2(s1);
	String s3("aaaaaaaaa");
	s1 = s3;
	return 0;
}