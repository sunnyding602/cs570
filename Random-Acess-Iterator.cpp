//
//  main.cpp
//  Random Access Iterator
//
//  Created by sunny on 10/23/15.
//  Copyright © 2015 bunengzhai. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;



template <typename T, typename itemType>
class MyIterator {
    T container;
    long index;
    
public:
    MyIterator(T& con, long idx){
        this->container = con;
        this->index = idx;
    }
    
    itemType operator*() const {
        
        return this->container[index];
    }
    
    MyIterator& operator++(){
        ++index;
        return *this;
    }
    
    MyIterator& operator++(int){
        ++index;
        return *this;
    }
    
    MyIterator& operator--(int){
        --index;
        return *this;
    }
    
    MyIterator& operator--(){
        --index;
        return *this;
    }
    
    bool operator==(const MyIterator & other){
        return this->index == other.index;
    }
    
    bool operator!=(const MyIterator & other){
        return this->index != other.index;
    }
};

int main(int argc, const char * argv[]) {
    vector<int>  vec = {1,2,3,4,5,6,7,8,9,10};

    auto iter = MyIterator<vector<int>, int>(vec, 1L);
    auto end = MyIterator<vector<int>, int>(vec,vec.size());
    
    cout <<"We init the iter at position 1,\nthe actual item is: " << *iter<<endl;
    
    for (; iter != end; iter++) {
        cout << *iter <<endl;
    }
    
    
    return 0;
}

