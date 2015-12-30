//
//  main.cpp
//  570_final_triple
//
//  Created by sunny on 12/18/15. 1218 hahahaha Suprise
//  Copyright © 2015 Runxi Ding. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#define MARGIN 4
#define GRAPH_DOT_DAT "/Users/sunny/test/cs570/final/graph.dat"   //MODIFY ME PLEASE!!!!!!
#define INFINITE INT32_MAX

using namespace std;

struct arc{
    int start_node;
    int end_node;
    int weight;
    arc(int _start_node, int _end_node, int _weight){
        start_node = _start_node;
        end_node = _end_node;
        weight = _weight;
    }
};
struct node{
    int x;
    int y;
    int symbol;
};

int C(int from, int to, map<int, vector<struct arc>> myGraph);
map<map<int,int>, map<int, vector<int>>> getShortestPath(int node, map<int, struct node>  nodes, map<int, vector<struct arc>> myGraph );
void printMatrix(vector<vector<string>> matrix);
string charToString(char c);
vector<arc> generateArcs(string s);
void printChart(map<int, struct node>  nodes, map<int, vector<struct arc>> myGraph );
void generateMatrix(vector<vector<string>> & matrix, map<int, struct node>& nodes, map<int, vector<struct arc>>& myGraph);


int main(int argc, const char * argv[]) {
    vector<vector<string>> matrix;
    //nodeinfo
    map<int, struct node> nodes;
    map<int, vector<struct arc>> myGraph;
    
    generateMatrix(matrix, nodes, myGraph);
    printMatrix(matrix);
    printChart(nodes, myGraph);
    
    return 0;
}



void generateMatrix(vector<vector<string>> & matrix, map<int, struct node>& nodes, map<int, vector<struct arc>>& myGraph ){
    vector<struct arc> arcs =generateArcs(GRAPH_DOT_DAT);
    

    //find all the unique points
    map<int, int> uniqueNodes;
    for (int i = 0; i<arcs.size(); i++) {
        uniqueNodes[arcs[i].start_node] = 1;
        uniqueNodes[arcs[i].end_node] = 1;
    }
    
    
    for (auto it = uniqueNodes.begin(); it != uniqueNodes.end(); it++) {
        vector<struct arc> theArcs;
        for (int i= 0; i<arcs.size(); i++) {
            if (arcs[i].start_node == it->first) {
                theArcs.push_back(arcs[i]);
            }
        }
        myGraph[it->first] = theArcs;
    }
    
    
    //put these nodes on the graph
    auto nodesSize = uniqueNodes.size();
    
    //cal the height and the weight of the graph
    auto sideLength = 16+nodesSize+(nodesSize-1)*10;
    
    //init the graph
    for (int i = 0; i<sideLength; i++) {
        vector<string> vec;
        for (int j = 0; j<sideLength; j++) {
            vec.push_back("");
        }
        matrix.push_back(vec);
    }
    
    
    //put node on the graph the first position of the node should be (3,3)  foreach uniqueNodes
    int x = 8;
    int y = 8;
    for (auto it= uniqueNodes.begin(); it!=uniqueNodes.end(); it++) {
        struct node n;
        n.x = x;
        n.y = y;
        n.symbol = it->first;
        nodes[it->first] = n;
        matrix[y][x] = to_string(it->first);
        y = y+10;
        x = x+10;
    }
    
    
    for (int i = 0; i<arcs.size(); i++) {
        auto iterStart = nodes.find(arcs[i].start_node);
        auto x1 = iterStart->second.x;
        auto y1 = iterStart->second.y;
        //iterStart->second.symbol;
        
        auto iterEnd = nodes.find(arcs[i].end_node);
        auto x2 = iterEnd->second.x;
        auto y2 = iterEnd->second.y;
        if(x2>x1){//if x2>x1
            //from > to ^
            if (matrix[y1][x1+1] == "" ) {
                int _i=x1+1;
                for (; _i<x2; _i++) {
                    if(matrix[y1][_i] == "")
                        matrix[y1][_i] = "-";
                    else
                        matrix[y1][_i]= "=";
                }
                string weight =to_string(arcs[i].weight);
                auto weightLen = weight.length();
                for (char x:weight) {
                    matrix[y1][_i-7+weightLen] = charToString(x);
                    weightLen++;
                }
                
                matrix[y1][_i] = "+";
                
                auto offset = to_string(arcs[i].start_node).length() -1;
                _i += offset;
                
                
                int j = y1+1;
                for (; j<y2; j++) {
                    matrix[j][_i] = "|";
                }
                matrix[j-1][_i] = "V";
                continue;
            }
            //from ^ to ^
            if (matrix[y1-1][x1] == "" ) {
                int _i = y1-1;
                for (; _i>y1-MARGIN; _i--) {
                    if (matrix[_i][x1] == "") {
                        matrix[_i][x1] = "|";
                    }else{
                        matrix[_i][x1] = "=";
                    }
                    
                }
                matrix[_i][x1] = "+";
                int j=x1+1;
                for (; j<x2; j++) {
                    matrix[_i][j] = "-";
                }
                matrix[_i][j] = "+";
                string weight =to_string(arcs[i].weight);
                auto weightLen = weight.length();
                for (char x:weight) {
                    matrix[_i][j-7+weightLen] = charToString(x);
                    weightLen++;
                }
                
                int k=_i+1;
                for (; k<y2; k++) {
                    if(matrix[k][j] == ""){
                        matrix[k][j] = "|";
                    }else{
                        matrix[k][j] = "=";
                    }
                }
                matrix[k-1][j] = "V";
                continue;
            }
            //from < to ^
            if (matrix[y1][x1-1] == "" ) {
                int _i = x1-1;
                for (;_i>x1-MARGIN ; _i--) {
                    if(matrix[y1][_i] == "")
                        matrix[y1][_i]="-";
                    else
                        matrix[y1][_i]="=";
                }
                matrix[y1][_i]="+";
                int j = y1-1;
                for (; j>y1-(MARGIN+2); j--) {
                    if (matrix[j][_i] == "") {
                        matrix[j][_i] = "|";
                    }else{
                        matrix[j][_i] = "=";
                    }
                    
                }
                matrix[j][_i] = "+";
                
                int k = _i+1;
                for (; k<x2; k++) {
                    matrix[j][k]="-";
                }
                matrix[j][k]="+";
                
                string weight =to_string(arcs[i].weight);
                auto weightLen = weight.length();
                for (char x:weight) {
                    matrix[j][k-9+weightLen] = charToString(x);
                    weightLen++;
                }
                
                int l = j+1;
                for (; l<y2; l++) {
                    matrix[l][x2] = "|";
                }
                matrix[l-1][x2] = "V";
                continue;
            }
            //from V to ^
            if (matrix[y1+1][x1] == "" ) {
                int _i = y1+1;
                for (; _i<y1+MARGIN; _i++) {
                    matrix[_i][x1] = "|";
                }
                matrix[_i][x1] = "+";
                int j=x1-1;
                for (; j>x1-(MARGIN+2); j--) {
                    matrix[_i][j]="-";
                }
                matrix[_i][j]="+";
                int k = _i-1;
                for (; k>_i-(MARGIN*2+4); k--) {
                    matrix[k][j]= "|";
                }
                matrix[k][j]= "+";
                
                int l = j+1;
                for (; l<x2; l++) {
                    matrix[k][l]= "-";
                }
                matrix[k][l]= "+";
                
                string weight =to_string(arcs[i].weight);
                auto weightLen = weight.length();
                for (char x:weight) {
                    matrix[k][l-9+weightLen] = charToString(x);
                    weightLen++;
                }
                
                int m=k+1;
                for (; m<y2; m++) {
                    matrix[m][l]="|";
                }
                matrix[m-1][l]="V";
                continue;
            }
            
            
        }else{//if x1>x2
            
            //from < to V
            if (matrix[y1][x1-1] == "") {
                int _i = x1-1;
                for (; _i>x2; _i--) {
                    if(matrix[y1][_i] == "")
                        matrix[y1][_i]="-";
                    else
                        matrix[y1][_i]="=";
                }
                matrix[y1][_i]="+";
                
                string weight =to_string(arcs[i].weight);
                auto weightLen = weight.length();
                for (char x:weight) {
                    matrix[y1][_i+4+weightLen] = charToString(x);
                    weightLen++;
                }
                
                int j = y1-1;
                for (; j>y2; j--) {
                    
                    if(matrix[j][x2]== ""){
                        matrix[j][x2]="|";
                    }else{
                        int aroundCharCnt = 0;
                        if(matrix[j][x2+1] != "") {
                            aroundCharCnt++;
                        }
                        if(matrix[j][x2-1] != "") {
                            aroundCharCnt++;
                        }
                        if(matrix[j+1][x2] != "") {
                            aroundCharCnt++;
                        }
                        if(matrix[j-1][x2] != "") {
                            aroundCharCnt++;
                        }
                        if (aroundCharCnt != 4 && (matrix[j-1][x2] =="|" || matrix[j-1][x2] =="^")) {
                            continue;
                        }
                        if (aroundCharCnt == 4) {
                            matrix[j][x2]="=";
                        }else{
                            matrix[j][x2]="+";
                        }
                    
                    }
                }
                matrix[j+1][x2] = "^";
                continue;
            }
            
            //from V to V
            if (matrix[y1+1][x1] == "") {
                
                int _i = y1+1;
                for (; _i<y1+MARGIN; _i++) {
                    matrix[_i][x1] = "|";
                }
                matrix[_i][x1] = "+";
                
                int j = x1-1;
                for (; j>x2; j--) {
                    matrix[_i][j]= "-";
                }
                matrix[_i][j]= "+";
                
                string weight =to_string(arcs[i].weight);
                auto weightLen = weight.length();
                for (char x:weight) {
                    matrix[_i][j+4+weightLen] = charToString(x);
                    weightLen++;
                }
                
                
                int k = _i-1;
                for (; k>y2; k--) {
                    if(matrix[k][j] != ""){
                        matrix[k][j] = "=";
                    }else{
                        matrix[k][j] = "|";
                    }
                    
                }
                matrix[k+1][j] = "^";
                continue;
            }
            
            //from > to V
            if (matrix[y1][x1+1] == "") {
                int _i = x1+1;
                for (; _i<x1+MARGIN; _i++) {
                    matrix[y1][_i]="-";
                }
                matrix[y1][_i]="+";
                auto offset = to_string(arcs[i].start_node).length() -1;
                _i += offset;
                int j = y1+1;
                for (; j<y1+MARGIN+2; j++) {
                    matrix[j][_i] = "|";
                }
                matrix[j][_i] = "+";
                
                int k=_i-1;
                for (; k>x2; k--) {
                    matrix[j][k] = "-";
                }
                matrix[j][k] = "+";
                
                string weight =to_string(arcs[i].weight);
                auto weightLen = weight.length();
                for (char x:weight) {
                    matrix[j][k+4+weightLen] = charToString(x);
                    weightLen++;
                }
                
                int l = j-1;
                for (; l>y2; l--) {
                    if(matrix[l][k] == ""){
                        matrix[l][k] = "|";
                    }else{
                        matrix[l][k] = "=";
                    }
                }
                matrix[l+1][k] = "^";
                continue;
            }
            
            //from ^ to V
            if (matrix[y1-1][x1] == "") {
                int _i = y1-1;
                for (; _i>y1-MARGIN; _i--) {
                    matrix[_i][x1] = "|";
                }
                matrix[_i][x1] = "+";
                
                int j = x1+1;
                for (; j<x1+MARGIN+2; j++) {
                    matrix[_i][j] = "-";
                }
                matrix[_i][j] = "+";
                
                int k = _i+1;
                for (; k<_i+MARGIN*2+4; k++) {
                    matrix[k][j] = "|";
                }
                matrix[k][j] = "+";
                
                int l = j-1;
                for (; l>x2; l--) {
                    matrix[k][l] = "-";
                }
                matrix[k][l] = "+";
                
                string weight =to_string(arcs[i].weight);
                auto weightLen = weight.length();
                for (char x:weight) {
                    matrix[k][l+4+weightLen] = charToString(x);
                    weightLen++;
                }
                
                int m = k-1;
                for (; m>y2; m--) {
                    if(matrix[m][x2] =="")
                        matrix[m][x2] = "|";
                    else
                        matrix[m][x2] = "=";
                }
                matrix[m+1][x2] = "^";
                
                continue;
            }
        }
    }
    
    for (auto it= nodes.begin(); it!=nodes.end(); it++) {
        matrix[it->second.y][it->second.x-1] = "[";
        matrix[it->second.y][it->second.x+1] = "]";
    }

}

int C(int from, int to, map<int, vector<struct arc>> myGraph){
    int  weight = -1;
    auto iter = myGraph.find(from);
    if (iter == myGraph.end()) {
        return -1;
    }
    auto arcs = iter->second;
    for (auto it = arcs.begin(); it != arcs.end(); it++) {
        if (to == it->end_node) {
            weight = it->weight;
        }
    }
    return weight;
}

map<map<int,int>, map<int, vector<int>>> getShortestPath(int node, map<int, struct node>  nodes, map<int, vector<struct arc>> myGraph ){
    map<int,int> D;
    map<int, vector<int>> path;
    vector<int> nodeSatck;
    for (auto it = nodes.begin(); it!=nodes.end(); it++) {
        int toNode = it->first;
        vector<int> vec;
        if (node != it->first) {
            D[toNode] = INFINITE;
            path[toNode] = vec;
        }
    }
    
    auto iter = myGraph.find(node);
    auto arcs = iter->second;
    
    int leastWeight = INFINITE;
    int leastNode = -1;
    for (int i =0; i<arcs.size(); i++) {
        
        if (leastWeight> arcs[i].weight) {
            leastWeight = arcs[i].weight;
            leastNode = arcs[i].end_node;
        }
        
        D[arcs[i].end_node] = arcs[i].weight;
        if (arcs[i].weight < INFINITE) {
            path[arcs[i].end_node].push_back(arcs[i].end_node);
        }
    }
    nodeSatck.push_back(leastNode);
    myGraph.erase(iter);
    
    
    while (myGraph.size() > 0) {
        int lN =  *(nodeSatck.end()-1);
        auto it = myGraph.find(lN);
        if (it == myGraph.end()) {
            break;
        }
        auto arcs = it->second;
        if (arcs.size() == 0) {
            break;
        }
        
        for (int i =0; i<arcs.size(); i++) {
            if(arcs[i].end_node == node) continue;
            int Dn = D[arcs[i].end_node];
            int bylN = D[lN] + C(lN, arcs[i].end_node, myGraph);
            if (Dn > bylN){
                D[arcs[i].end_node] = bylN;
                if (path[arcs[i].end_node].size()>0) {
                    path[arcs[i].end_node].erase(path[arcs[i].end_node].end()-1);
                    
                }
                path[arcs[i].end_node].push_back(lN);
                path[arcs[i].end_node].push_back(arcs[i].end_node);
            }else{
                path[arcs[i].end_node].erase(path[arcs[i].end_node].begin(), path[arcs[i].end_node].end());
                path[arcs[i].end_node].push_back(lN);
            }
            
        }
        int leastWeight = INFINITE;
        int leastNode = -1;
        auto D_copy = D;
        for (int i = 0; i<nodeSatck.size(); i++) {
            auto dIt =  D_copy.find(nodeSatck[i]);
            D_copy.erase(dIt);
        }
        for (auto dIt=D_copy.begin(); dIt != D_copy.end(); dIt++) {
            if (leastWeight > dIt->second) {
                leastWeight = dIt->second;
                leastNode = dIt->first;
            }
        }
        nodeSatck.push_back(leastNode);
        
        myGraph.erase(it);
    }
    
    map<map<int,int>, map<int, vector<int>>> res;
    res[D] = path;
    return res;
}





void printMatrix(vector<vector<string>> matrix) {
    
    for (int i = 0; i<matrix.size(); i++) {
        string line = "";
        string displayLine = "";
        for (int j = 0; j<matrix[i].size(); j++) {
            line += matrix[i][j];
            if (matrix[i][j] == "") {
                displayLine += " ";
            }else {
                displayLine +=matrix[i][j];
            }
        }
        //if ("" != line) {
        cout<<displayLine<<endl;
        //}
        //cout<<line<<endl;
    }
}
string charToString(char c) {
    stringstream ss;
    string s;
    ss << c;
    ss >> s;
    return s;
}
vector<arc> generateArcs(string s){
    vector<arc> arcs;
    ifstream infile;
    string line;
    string sub;
    infile.open(s);
    while(!infile.eof()){
        vector<int>nodesInfo;
        getline(infile, line);
        istringstream iss(line);
        
        do
        {
            string sub;
            iss >> sub;
            if(sub!=""){
                nodesInfo.push_back(stoi(sub));
            }
            
        } while (iss);
        
        for(int i=1;i<nodesInfo.size();i=i+2){
            arc arc1(nodesInfo[0],nodesInfo[i],nodesInfo[i+1]);
            arcs.push_back(arc1);
        }
    }
    return arcs;
}


void printChart(map<int, struct node>  nodes, map<int, vector<struct arc>> myGraph ){
    
    for (auto nodesIt = nodes.begin(); nodesIt!=nodes.end(); nodesIt++) {
        auto node =nodesIt->first;
        auto res =  getShortestPath(node,nodes, myGraph);
        auto D = res.begin()->first;
        auto paths = res.begin()->second;
        
        cout <<"START FROM "<< node<<": "<<endl;
        for (auto it = paths.begin(); it != paths.end(); it++) {
            
            auto dots = it->second;
            auto key = it->first;
            cout <<node<<"->";
            for (auto dotsIt = dots.begin(); dotsIt != dots.end(); dotsIt++) {
                
                if (dotsIt == dots.end()-1) {
                    
                    cout << *dotsIt ;
                }else{
                    cout << *dotsIt <<"->";
                }
                
            }
            if(D[key] == INFINITE){
                cout << key;
            }
            string cost = "∞";
            if (D[key] != INFINITE) {
                cost = to_string(D[key]);
            }
            cout <<"     COST: "<<cost<<endl;
        }
        cout<<endl;
        
    }
}

