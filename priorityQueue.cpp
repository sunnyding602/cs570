//
//  main.cpp
//  PriorityQueues
//
//  Created by sunny on 11/12/15.
//  Copyright © 2015 bunengzhai. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PriorityQueues{
private:
    vector<int> queue={};
    void bubbleUp(int currentIndex);//used for insert
    void bubbleDown(int rootIndex);//used for deleteMax
public:
    bool isEmpty() const;

    int getSize() const;
    
    void insert(const int & newItem);
    
    int deleteMax();
    
    string toString();
};

bool PriorityQueues::isEmpty() const{
    return this->getSize() == 0;
}

int PriorityQueues::getSize() const{
    return static_cast<int>(queue.size());
}

void PriorityQueues::bubbleUp(int currentIndex){
    if (currentIndex == 0) {
        return;
    }
    int parentIndex = static_cast<int>(currentIndex/2);
    if (queue[currentIndex] > queue[parentIndex]) {
        swap(queue[currentIndex], queue[parentIndex]);
        this->bubbleUp(parentIndex);
    }

}
void PriorityQueues::bubbleDown(int rootIndex=0){
    int root = rootIndex+1;
    int leftChildIndex = root*2-1;
    int rightChildIndex = root*2+1-1;
    if (rightChildIndex+1 > this->getSize()) {
        return;
    }
    if (queue[leftChildIndex] > queue[rightChildIndex]) {
        swap(queue[leftChildIndex], queue[rootIndex]);
        this->bubbleDown(leftChildIndex);
    }
}
void PriorityQueues::insert(const int &newItem){
    int currentIndex;
    queue.push_back(newItem);
    currentIndex = this->getSize()-1;
    this->bubbleUp(currentIndex);
}

int PriorityQueues::deleteMax(){
    if (this->getSize() == 0) {
        throw  std::invalid_argument("no item in the queue");
    }
    int max = queue[0];
    swap(queue[0], queue[this->getSize()-1]);
    queue.pop_back();
    this->bubbleDown();
    return max;
}

string PriorityQueues::toString(){
    string str = "";
    for (vector<int>::iterator it=queue.begin(); it!=queue.end(); it++) {
        str += std::to_string(*it) + ", ";
    }
    return str;
}


int main(int argc, const char * argv[]) {
    PriorityQueues pq;
    
    pq.insert(3);
    pq.insert(8);
    pq.insert(10);
    pq.insert(1);
    
    cout<<pq.toString()<<endl;
    cout<<pq.deleteMax()<<endl;
    cout<<pq.toString()<<endl;

    return 0;
}

