//
//  main.cpp
//  week9
//
//  Created by sunny on 10/29/15.
//  Copyright © 2015 bunengzhai. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>


using namespace std;
//Recursion :  another form of loop
//Recursion never faster than a loop

class myString{
    char *cstr;
public:
    myString(){
        cstr = new char[0];
        cstr[0] = '\0';
    }
    //copy cotr
    myString(const myString & str){
        auto len = strlen(str.cstr);
        cstr = new char[len+1];
        strcpy(cstr, str.cstr);
    }
    //move
    myString(myString && str){
        cstr = str.cstr;
        str.cstr = nullptr;
    }
    //copy again
    myString(const char* cstring){
        auto len = strlen(cstring);
        cstr = new char[len+1];
        strcpy(cstr, cstring);
    }
    
    char operator[](int index){
        if(index<0 || index > strlen(cstr)){
            throw out_of_range("index out of range");
        }
        return cstr[index];
    }
    
    int length() const{
        return strlen(cstr);
    }
    ~myString(){
        if (cstr != nullptr) {
            delete [] cstr;
        }
    }
    friend ostream &operator<<(ostream & out,  const myString & str);
    friend myString operator+(const myString &lhs, const myString &rhs);
};

ostream &operator<<(ostream & out,  const myString & str){
    out<<str.cstr<<endl;
    return out;
}
myString operator+(const myString &lhs, const myString &rhs){
    char *temp = new char[lhs.length() + rhs.length() +1];
    strcpy(temp, lhs.cstr);
    strcat(temp, rhs.cstr);
    myString returnString(temp);
    delete[] temp;
    return returnString;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    myString x = "helloooo";
    
    cout<<x + " world!"<<endl;
   
    return 0;
}

