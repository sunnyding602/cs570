//
//  main.cpp
//  huffman_tree
//
//  Created by sunny on 11/29/15.
//  Copyright © 2015 Runxi Ding. All rights reserved.
//
/*
readme!!!!
change the INPUTFILE_PATH and OUTPUTFILE_PATH accordingly
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#define INPUTFILE_PATH "infile.dat"  //modify me~~
#define OUTPUTFILE_PATH "outfile.dat"//modify me~~

using namespace std;
struct node{
    char    symbol;
    int   index;//that's how you find the char in the huffmanTree(array)
    int  frequency;
    node(char s, int idx, int freq){
        symbol = s;
        index = idx;
        frequency = freq;
    }
};

class MyMinHeap{
private:
    vector<struct node> container;
public:
    void add(struct node _node){
        container.push_back(_node);
        int curIdx = static_cast<int>(container.size()-1) ;
        this->bubbleUp(curIdx);
    }
    
    int size(){
        return static_cast<int>(container.size());
    }
    
    void bubbleUp(int curIdx){
        if (curIdx == 0) {
            return;
        }
        int parentIdx = (curIdx+1)/2 -1;
        if (container[curIdx].frequency < container[parentIdx].frequency) {
            swap(container[curIdx], container[parentIdx]);
            bubbleUp(parentIdx);
        }
    }
    
    
    struct node deleteMin(){
        if(container.size() == 0){
            throw "null!!";
        }
        auto minNode = container[0];
        container[0] = container[container.size()-1];
        container.erase(container.end()-1);
        bubbleDown(0);
        return minNode;
    }
    
    void bubbleDown(int curIdx){
        if(container.size()<=1){
            return;
        }
        int leftChildIdx = 2*curIdx+1;
        int rightChildIdx = 2*curIdx+2;
        int smallerChildIdx;
        if (leftChildIdx > container.size()-1) {//has no left child, return
            return;
        }
        if (rightChildIdx > container.size()-1) {//has left child only
            smallerChildIdx = leftChildIdx;
        }else{
            smallerChildIdx = container[leftChildIdx].frequency < container[rightChildIdx].frequency ? leftChildIdx:rightChildIdx;
        }
        
        if (container[curIdx].frequency > container[smallerChildIdx].frequency) {
            swap(container[curIdx], container[smallerChildIdx]);
            bubbleDown(smallerChildIdx);
        }
        
    }
    
};


struct keyValue{
    char key;
    int value;
    
    keyValue(char _key){
        key = _key;
    }
    
};
/*
 a=>10
 a=>11
 */
class MyMap{
private:
    vector<struct keyValue> container;
public:
    int getIndex(char key){
        for (int i=0; i<container.size(); i++) {
            if(container[i].key == key){
                return i;
            }
        }
        return -1;
    }
    vector<struct keyValue> getAll(){
        return container;
    }
    
    
    bool containsKey(char key){
        return this->getIndex(key)>= 0;
    }
    
    int &get(char key){
        int index = this->getIndex(key);
        if (index>=0) {
            return container[index].value;
        }
        struct keyValue kv(key);
        container.push_back(kv);
        return container[container.size()-1].value;
    }
    
    void put(char key, int value){
        this->get(key) =value;
    }
    
    
};

struct huffman_node{
    char symbol;
    int frequency;
    int selfIdx;
    int leftChildIdx=-1;
    int rightChildIdx=-1;
    int parentIdx=-1;
    huffman_node(char s, int idx,int f){
        symbol = s;
        frequency = f;
        selfIdx = idx;
    }
};

string getCodeReverse(struct huffman_node huffmanNode, vector<struct huffman_node> huffmanTree){
    string code="";
    if(huffmanNode.parentIdx == -1){
        return "";
    }
    if(huffmanNode.selfIdx == huffmanTree[huffmanNode.parentIdx].leftChildIdx){
         code += "0";
    }else{
         code += "1";
    }
    code += getCodeReverse(huffmanTree[huffmanNode.parentIdx], huffmanTree);
    
    return code;
}

string charToString(char c){
    stringstream ss;
    string s;
    ss << c;
    ss >> s;
    return s;
}
string getCode(struct huffman_node huffmanNode, vector<struct huffman_node> huffmanTree){
    string codeReverse = getCodeReverse(huffmanNode, huffmanTree);
    string code= "";
    vector<char> stack;
    for (char x: codeReverse) {
        stack.push_back(x);
    }
    for (int i=stack.size()-1; i>=0; --i) {
        code += charToString(stack[i]);
    }
    return code;
}

string file_get_contents(string path){
    ifstream fin(path);
    stringstream buffer;
    buffer << fin.rdbuf();
    string result = buffer.str();
    return result;
}

string filterString(string str){
    string returnStr = "";
    for (char c :str) {
        int i = static_cast<int>(c);
        int ascii_a = static_cast<int>('a');
        int ascii_z = static_cast<int>('z');
        int ascii_A = static_cast<int>('A');
        int ascii_Z = static_cast<int>('Z');
        int ascii_0 = static_cast<int>('0');
        int ascii_9 = static_cast<int>('9');
        if ( (i >= ascii_a && i<= ascii_z) ||
            (i>=ascii_A && i<= ascii_Z) ||
            (i>=ascii_0 && i<= ascii_9)) {
            returnStr += charToString(c);
            
        }
    }
    return returnStr;
}

void file_put_contents(string path, string str,  unsigned int openmode=ios::out){
    std::ofstream out(path, openmode);
    out << str;
    out.close();
}
int main(int argc, const char * argv[]) {
    string str = file_get_contents(INPUTFILE_PATH);
    str = filterString(str);
    
    // construct the frequency table start
    MyMap mm;
    for (char c :str) {
        if (mm.containsKey(c)) {
            mm.get(c) = mm.get(c) +1;
        }else{
            mm.put(c, 1);
        }
    }
    // construct the frequency table end
    
    //init huffmanTree
    vector<struct huffman_node> huffmanTree;
    auto allKeyValueInMap = mm.getAll();
    for (int i=0; i<allKeyValueInMap.size(); i++) {
        struct huffman_node hn1(allKeyValueInMap[i].key, i,allKeyValueInMap[i].value);
        huffmanTree.push_back(hn1);
    }

    //put nodes into minHeap, so that we can find the two smallest numbers
    MyMinHeap mmh;
    for (int i =0; i<huffmanTree.size(); ++i) {
     struct node minHeapNode(huffmanTree[i].symbol, huffmanTree[i].selfIdx, huffmanTree[i].frequency);
        mmh.add(minHeapNode);
    }
    
    char newSymbol = '$';
    while (mmh.size() > 1) {
        auto leastOne = mmh.deleteMin();
        auto leastTwo = mmh.deleteMin();
        auto newFrequency = leastOne.frequency + leastTwo.frequency;

        auto newIndex = static_cast<int>(huffmanTree.size());
        struct huffman_node hn(newSymbol, newIndex, newFrequency);
        huffmanTree.push_back(hn);
        //update node info start
        huffmanTree[leastOne.index].parentIdx = newIndex;
        huffmanTree[leastTwo.index].parentIdx = newIndex;
        huffmanTree[newIndex].leftChildIdx = leastOne.index;
        huffmanTree[newIndex].rightChildIdx = leastTwo.index;
        //update node info end
        struct node newMinHeapNode(newSymbol, newIndex, newFrequency);
        mmh.add(newMinHeapNode);
    }

    cout << "Frequency table:"<<endl;
    file_put_contents(OUTPUTFILE_PATH, "Frequency table:\n", ios::app);
    cout << "Symbol\tFrequency"<<endl;
    file_put_contents(OUTPUTFILE_PATH, "Symbol\tFrequency\n", ios::app);
    for(int i=0; i<mm.getAll().size();i++){
        cout << mm.getAll()[i].key << " " << mm.getAll()[i].value <<endl;
        file_put_contents(OUTPUTFILE_PATH, charToString(mm.getAll()[i].key)+
                          "\t\t" +
                          to_string(mm.getAll()[i].value)+
                          "\n", ios::app);
    }
    cout <<endl;
    file_put_contents(OUTPUTFILE_PATH, "\n", ios::app);
    int numberOfbits=0;
    
    cout << "Letter =====> huffmancode"<<endl;
    file_put_contents(OUTPUTFILE_PATH, "Letter =====> huffmancode\n", ios::app);
    for (int i=0; i<huffmanTree.size(); ++i) {
        if(huffmanTree[i].symbol == newSymbol) break;
        auto code = getCode(huffmanTree[i], huffmanTree) ;
        numberOfbits += mm.get(huffmanTree[i].symbol)* code.length();
        cout <<huffmanTree[i].symbol<<": "<< code<<endl;
        file_put_contents(OUTPUTFILE_PATH,charToString(huffmanTree[i].symbol)+
                          ": "+
                          code+
                          "\n", ios::app);
    }
    
    cout <<endl;
    file_put_contents(OUTPUTFILE_PATH, "\n", ios::app);
    cout <<"the length of the coded message is:"<< numberOfbits << " bits"<<endl;
    file_put_contents(OUTPUTFILE_PATH,"the length of the coded message is:" +
                      to_string(numberOfbits) +
                      "\n", ios::app);

    return 0;
}
