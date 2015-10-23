//
//  main.cpp
//  iterators
//
//  Created by sunny on 10/22/15.
//  Copyright © 2015 bunengzhai. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;


template <typename T>
class FakeIterator{
private:
    T t;
public:
    FakeIterator(T t){
        this->t =t;
    }
    T operator*() { return 10*this->t; }
    bool operator==(const FakeIterator &other){
        return this->t == other.t;
    }
    
    bool operator!=(const FakeIterator &other){
        return this->t != other.t;
    }
    
    FakeIterator& operator++(){
        t++;
        return *this;
    }
    
    FakeIterator& operator++(int){
        t++;
        return *this;
    }

};
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    vector<int> vect = {1,2,3,4,5,6,7,8,9};
    for (auto iter = FakeIterator<int>(0); iter != FakeIterator<int>(25); iter++) {
        
        cout<< *iter <<endl;
    }
    return 0;
}

