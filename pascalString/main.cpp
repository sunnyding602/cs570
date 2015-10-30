#include <iostream>
#include <algorithm>
#include "MyString.h"
using namespace std;
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
    std::copy(s, s + len + 1, arr);
}

//pascal String constructor
String::String(const char *str, bool pascal){
    if (pascal != true) {
        len = strlen(str);
        arr = new char[len + 1];
        std::copy(str, str + len + 1, arr);
    }else{
        len = static_cast<int>(str[0]);
        arr = new char[len];
        std::copy(str+1, str + len+1, arr);
    }
}

// Copy constructor.
String::String(const String &obj) {
    len = obj.len;
    arr = new char[len + 1];
    std::copy(obj.arr, obj.arr + len + 1, arr);
}

// Move constructor.
String::String(String &&obj) {
    len = obj.len;
    arr = obj.arr;
    obj.arr = nullptr;
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
    std::copy(rhs.arr, rhs.arr + len + 1, arr);
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



int main(){
    char *str = new char[7];
    str[0] = 6;
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

    String myStr(str,true);
    String myStr2(cstr,false);
    String myStr3 = "Hello, world!";
    cout <<  "yo "+myStr<<endl;
    cout <<  "Hi "+myStr2<<endl;
    cout <<  myStr3 + " yo:)"<<endl;
    

}