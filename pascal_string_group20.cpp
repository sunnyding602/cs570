#ifndef __MYSTRING_H__
#define __MYSTRING_H__

#include <iostream>

class String {
public:
	// Usage: String aStringObj; or	String aStringObj();
	String();


	String(const char* s, bool pascal);

	// Constructor. Converts a char* object to a String  object
	// Usage: String aStringObj("hello"); or String aStringObj = "hello";
	String(const char *s);

	// Copy and move constructors.
	// Usage: String aStringObject(anotherStringObj); or
	// String aStringObject = anotherStringObj;
	String(const String &s);
	String(String&& obj);

	// Destructor
	~String();

	// Assignment operator
	// Usage: aStringObject = anotherStringObj; or
	// aStringObject.operator=(anotherStringObj);
	String &operator=(const String &rhsObject);
	String& operator=(String&& rhs);

	// Mutator operator[]
	// Usage: aStringObject[1] = ’M?;
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
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
void _copy(const char *source, char *dest, int len) {
	for (int i = 0; i < len; i++) {
		dest[i] = source[i];
	}
}

// Default constructor
String::String() {
	arr = new char[1];
	arr[0] = '\0';
	len = 0;
}

// Constructor. Converts a C-string to a String object
String::String(const char *s) {
	len = strlen(s);
	arr = new char[len + 1];
	arr[len] = '\0';
	_copy(s,arr, len);
}

// Copy constructor.
String::String(const String &obj) {
	len = obj.len;
	arr = new char[len + 1];
	arr[len] = '\0';
	_copy(obj.arr, arr, len);
}

// Move constructor.
String::String(String &&obj) {
	len = obj.len;
	arr = obj.arr;
	obj.arr = nullptr;
}

//pascal string constructor
String::String(const char* s , bool pascal) {
	if (pascal == true) {
		len = static_cast<int>(s[0]);
		arr = new char[len + 1];
		arr[len] = '\0';
		_copy(s + 1, arr, len);
	}
	else {
		len = strlen(s);
		arr = new char[len + 1];
		arr[len] = '\0';
		_copy(s, arr, len);
	}

}

// Destructor
String::~String() {
	if (arr != nullptr)
		delete[] arr;
}

// Assignment operator
String &String::operator=(const String &rhs) {
	delete[] arr;
	len = rhs.len;
	arr = new char[len + 1];
	_copy(rhs.arr, arr, len);
	return *this;
}

// Move assignment operator
String &String::operator=(String &&rhs) {
	delete[] arr;
	len = rhs.len;
	arr = rhs.arr;
	rhs.arr = nullptr;
	return *this;
}


// Mutator operator[]
char &String::operator[](int index) {
	// check whether the index is within bounds
	if (index > len || index < 0)
		throw std::out_of_range("Index out of range");
	return arr[index];
}

// Accessor operator[]
char String::operator[](int index) const {
	// check whether the index is within bounds
	if (index > len || index < 0)
		throw std::out_of_range("Index out of range");
	return arr[index];
}

// Get the length (number of characters) of a String object
int String::length() const {
	return len;
}

bool operator==(const String &lhs, const String &rhs) {
	return strcmp(lhs.arr, rhs.arr) == 0;
}

bool operator<(const String &lhs, const String &rhs) {
	return strcmp(lhs.arr, rhs.arr) < 0;
}

// Friend functions for > comparison
bool operator>(const String &lhs, const String &rhs) {
	return rhs < lhs;
}

// Friend functions for <= comparison
bool operator<=(const String &lhs, const String &rhs) {
	return !(rhs < lhs);
}

// Friend functions for >= comparison
bool operator>=(const String &lhs, const String &rhs) {
	return !(lhs  < rhs);
}

// Friend functions for != comparison
bool operator!=(const String &lhs, const String &rhs) {
	return !(lhs == rhs);
}

//	Friend function for string concatination
String operator+(const String &lhs, const String &rhs) {
	int strLength = lhs.len + rhs.len + 1;
	char *tmpStr = new char[strLength];
	for (auto i = 0; i < lhs.len; ++i)
		tmpStr[i] = lhs.arr[i];
	for (auto i = 0; i <= rhs.len; ++i)
		tmpStr[lhs.len + i] = rhs.arr[i];
	tmpStr[lhs.len + rhs.len] = '\0';
	String retStr(tmpStr);
	delete[] tmpStr;
	return retStr;
}

// Return C style character string
const char* String::c_str() const {
	return arr;
}

//	Friend function for output
std::ostream& operator<<(std::ostream &out, const String &obj) {
	return out << obj.c_str();
}

int main() {
	char *str = new char[7];
	str[0] = static_cast<char>(6);
	str[1] = 'G';
	str[2] = 'r';
	str[3] = 'e';
	str[4] = 'a';
	str[5] = 't';
	str[6] = '!';

	char *cstr = new char[7];
	cstr[0] = 'G';
	cstr[1] = 'r';
	cstr[2] = 'e';
	cstr[3] = 'a';
	cstr[4] = 't';
	cstr[5] = '!';
	cstr[6] = '\0';


	String myStr(str, true);
	String myStr2(cstr, false);
	cout << "yo " + myStr << endl;
	cout << myStr2 + "yohohohoho" << endl;
	return 0;
}