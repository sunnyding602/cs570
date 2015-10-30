#ifndef __MYSTRING_H__
#define __MYSTRING_H__

#include <iostream>

class String {
public:
    // Usage: String aStringObj; or	String aStringObj();
    String();
    
    // Constructor. Converts a char* object to a String  object
    // Usage: String aStringObj("hello"); or String aStringObj = "hello";
    String(const char *s);
    
    // Copy and move constructors.
    // Usage: String aStringObject(anotherStringObj); or
    // String aStringObject = anotherStringObj;
    String(const String &s);
    String(String&& obj);
    
    String(const char *str, bool pascal);
    // Destructor
    ~String();
    
    // Assignment operator
    // Usage: aStringObject = anotherStringObj; or
    // aStringObject.operator=(anotherStringObj);
    String &operator=(const String &rhsObject);
    String& operator=(String&& rhs);
    
    // Mutator operator[]
    // Usage: aStringObject[1] = �M�;
    char &operator[] (int index);
    
    // Accessor operator[]
    // Usage: char ch = aStringObject[1];
    char operator[] (int index) const;
    
    // Get the length (number of characters) of a String object
    // Usage: int len = aStringObject.Length();
    int length() const;
    
    // Friend functions for == comparison
    // Usage: if (aStringObject == anotherStringObj) {...} or
    //        if (aStringObject == "hello") {...} or
    //        if ("hello" == aStringObj) {...} or
    friend bool operator==(const String &lhsObject, const String &rhsObject);
    
    // The other five comparison operators
    // !=, <, >, <=, >= are similarly handled as in line 13.
    
    friend bool operator<(const String &lhsObject, const String &rhsObject);
    friend bool operator>(const String &lhsObject, const String &rhsObject);
    friend bool operator<=(const String &lhsObject, const String &rhsObject);
    friend bool operator>=(const String &lhsObject, const String &rhsObject);
    friend bool operator!=(const String &lhsObject, const String &rhsObject);
    
    // Friend function for string concatenation
    // Usage: StringOne = StringTwo + StringThree  or
    //        StringOne = "hello" + StringTwo  or
    //        StringOne = StringTwo + "hello"
    friend String operator+(const String &lhs, const String &rhs);
    
    // Return C style character string
    // Usage: const char *str = aStringObj.C_str();
    const char *c_str() const;
    
    // Friend function for output
    // Usage: cout << aStringObj;
    friend std::ostream &operator<<(std::ostream &out, const String &obj);
    
private:
    // arr implements the String object as a dynamic array
    char *arr;
    
    // len keeps track of the length
    int len;
};

#endif