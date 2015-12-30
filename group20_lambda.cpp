//
//  main.cpp
//  lambda
//
//  Created by sunny on 10/16/15.
//  Copyright © 2015 bunengzhai. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
int main(int argc, const char * argv[]) {
    unordered_map<int, long> m, m2;
    vector<int> vec;
    long frequency = 0;
    auto size = 0;
    cout << "How many number you want to read in? :";
    cin >> size;
    vec.resize(size);
    
    generate(vec.begin(), vec.end(), [&](){
        int x;
        cout << "please enter an integer:";
        cin>>x;
        return x;
    });


    auto a = max_element(vec.begin(), vec.end(), [&](int a, int b){
        auto countA = count(vec.begin(), vec.end(), a);
        if( m.find(a) == m.end()){
            m[a] = countA;
        }
        auto countB = count(vec.begin(), vec.end(), b);
        if( m.find(b) == m.end()){
            m[b] = countB;
        }
        if( frequency < countA){
            frequency = countA;
        }
        if( frequency < countB){
            frequency = countB;
        }
        return countB > countA;
    
    });

    cout<< "The mode(s) is as the following:"<<endl;
    find_if(m.begin(), m.end(), [&](const std::pair<int, long>& v){
        if (frequency <=1) {
            cout << ":(, we do not find the mode"<<endl;
            return true;
        }
        if(v.second == frequency){
            if(m2.find(v.first) == m2.end()){
                cout << v.first <<endl;
                m2[v.first] = 1l;
            }

        }
        return false;});
    return 0;
}
