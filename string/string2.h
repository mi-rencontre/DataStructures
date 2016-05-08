class String  
{  
public:  
    String(const char* str = "")  
        :_str(new char [strlen(str) + 1])  
    {  
        strcpy(_str, str);  
    }  
      
    String(const String& s):_str(NULL)  
    {  
        String tmp(s._str);  
        swap(_str, tmp._str);  
    }  
  
    String& operator=(const String& s)  
    {  
        if (this != &s)  
        {  
            String tmp(s._str);  
            swap(_str, tmp._str);  
        }  
        return *this;  
    }  
  
    String& operator=(String s)  
    {  
        swap(_str, s._str);  
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
