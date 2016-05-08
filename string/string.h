class String
{
public:
	String()
		:_str(new char[1])
	{
		//_str = "";
		//_str[0] = '\0';
		*_str = '\0';
		//*_str = 0;
	}

	String(char* str)
		:_str(new char[strlen(str) + 1])
	{
		strcpy(_str, str);
	}

	String(const String& s)
		:_str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* tmp = new char[strlen(s._str) + 1];
			strcpy(tmp, s._str);
			delete[] _str;
			_str = tmp;
		}

		return *this;
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = NULL;
		}
	}

private:
	char* _str;
};