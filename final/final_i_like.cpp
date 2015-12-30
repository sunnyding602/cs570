#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#define FIVE 5
#define EIGHT 8
#define NINE 9
#define MAXINT INT32_MAX

using namespace std;


struct point{
    int x;
    int y;
    int name;
    point(int _name, int _x=0, int _y=0){
        x = _x;
        y = _y;
        name = _name;
    }
    point(){}
};
struct arc {
    struct point from;
    struct point to;
    int weight;
    arc(point _from, point _to, int _weight)
    {
        from = _from;
        to = _to;
        weight = _weight;
    }
    arc(){}
};
void printMatrix(vector<vector<string>> matrix);

string charToString(char c) {
    stringstream ss;
    string s;
    ss << c;
    ss >> s;
    return s;
}

struct point my_push_back(vector<struct point> & points, point point){
    bool isFound = false;
    if (points.size() == 0) {
        point.x = 10;
        point.y = 10;
        points.push_back(point);
        return point;
    }else{
    for (int i=0; i<points.size(); i++) {
        if(points[i].name ==point.name){
            isFound = true;
            return points[i];
        }
    }
        if (isFound == false) {
            point.x = (points.size()+1)*10;
            point.y = (points.size()+1)*10;
            points.push_back(point);
            return point;
        }

    }
    return  point;
}

int C(int from, int to, map<int, vector<struct arc>> myGraph){
    int  weight = -1;
    auto iter = myGraph.find(from);
    if (iter == myGraph.end()) {
        return -1;
    }
    auto arcs = iter->second;
    for (auto it = arcs.begin(); it != arcs.end(); it++) {
        if (to == it->to.name) {
            weight = it->weight;
        }
    }
    return weight;
}

map<map<int,int>, map<int, vector<int>>> getShortestPath(int node, map<int, struct point>  nodes, map<int, vector<struct arc>> myGraph ){
    map<int,int> D;
    map<int, vector<int>> path;
    vector<int> nodeSatck;
    for (auto it = nodes.begin(); it!=nodes.end(); it++) {
        int toNode = it->first;
        vector<int> vec;
        if (node != it->first) {
            D[toNode] = MAXINT;
            path[toNode] = vec;
        }
    }
    
    auto iter = myGraph.find(node);
    auto arcs = iter->second;
    
    int leastWeight = MAXINT;
    int leastNode = -1;
    
    for (int i =0; i<arcs.size(); i++) {
        
        if (leastWeight> arcs[i].weight) {
            leastWeight = arcs[i].weight;
            leastNode = arcs[i].to.name;
        }
        
        D[arcs[i].to.name] = arcs[i].weight;
        if (arcs[i].weight < MAXINT) {
            path[arcs[i].to.name].push_back(arcs[i].to.name);
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
            if(arcs[i].to.name == node) continue;
            int Dn = D[arcs[i].to.name];
            int bylN = D[lN] + C(lN, arcs[i].to.name, myGraph);
            if (Dn > bylN){
                D[arcs[i].to.name] = bylN;
                if (path[arcs[i].to.name].size()>0) {
                    path[arcs[i].to.name].erase(path[arcs[i].to.name].end()-1);
                    
                }
                path[arcs[i].to.name].push_back(lN);
                path[arcs[i].to.name].push_back(arcs[i].to.name);
            }else{
                path[arcs[i].to.name].erase(path[arcs[i].to.name].begin(), path[arcs[i].to.name].end());
                path[arcs[i].to.name].push_back(lN);
            }
            
        }
        int leastWeight = MAXINT;
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



void printChart(map<int, struct point>  nodes, map<int, vector<struct arc>> myGraph ){

    for (auto nodesIt = nodes.begin(); nodesIt!=nodes.end(); nodesIt++) {
        auto node =nodesIt->first;
        auto res =  getShortestPath(node ,nodes, myGraph);
        auto D = res.begin()->first;
        auto paths = res.begin()->second;
        
        cout <<"When the number start from "<< node<<"."<<endl;
        for (auto it = paths.begin(); it != paths.end(); it++) {
            
            auto dots = it->second;
            auto key = it->first;
            cout <<node<<" to ";
            for (auto dotsIt = dots.begin(); dotsIt != dots.end(); dotsIt++) {
                
                if (dotsIt == dots.end()-1) {
                    
                    cout << *dotsIt ;
                }else{
                    cout << *dotsIt <<" to ";
                }
                
            }
            if(D[key] == MAXINT){
                cout << key;
            }
            string weight = "infinite ";
            if (D[key] != MAXINT) {
                weight = to_string(D[key]);
            }
            cout <<"     the weight is "<<weight<<"."<<endl;
        }
        cout<<endl;
        
    }

}


int main() {
    map<int, vector<struct arc>> myGraph;
    vector<struct arc> arcs;
    vector<struct point> points;
    ifstream infile;
    string line;
    string sub;
    infile.open("/Users/sunny/test/cs570/final/graph.dat");
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
            nodesInfo[0];//1
            nodesInfo[i];//2
            nodesInfo[i+1];//10
            struct point p1(nodesInfo[0]);
            struct point p2(nodesInfo[i]);

            p1 = my_push_back(points, p1);
            p2 = my_push_back(points, p2);
            struct arc arc1(p1,p2,nodesInfo[i+1]);
            auto it = myGraph.find(p2.name);
            if (it == myGraph.end()) {
                myGraph[p2.name];
            }
            myGraph[p1.name].push_back(arc1);
            arcs.push_back(arc1);
            
        }
    }

    

    vector<vector<string>> canvas;
    
    
    for (int j = 1; j < 101; j++)
    {
        vector<string> vec3;
        for (int i = 1; i < 101; i++)
        {
            vec3.push_back("");
        }
        canvas.push_back(vec3);
    }
    
    
    for (int i = 0; i < points.size(); i++)//zuobiao 1010 2020 3030 4040
    {
        int x=(i + 1) * 10;
        int y=(i + 1) * 10;
        points[i].x = x;
        points[i].y = y;
        canvas[y][x] = to_string (points[i].name);
    }
    
    
    
    for (int t=0;t<arcs.size(); t++)
    {
//        arcs[t].from.x;                //(x1,y1)
//        arcs[t].from.y;
//        arcs[t].to.x;                  //(x2,y2)
//        arcs[t].to.y;
//        
        int x1 = arcs[t].from.x;
        int y1 = arcs[t].from.y;
        int x2 = arcs[t].to.x;
        int y2 = arcs[t].to.y;
        string weight = to_string(arcs[t].weight);
        if (x1<x2) {
            if (canvas[y1][x1+1]== "")//> ^
            {
                for (int i = x1+1; i < x2; i++)
                {
                    canvas[y1][i] = "-";
                }
                canvas[y1][x2] = "+";
                
                int ii=0;
                for (char x : weight) {
                    canvas[y1][x1+3+ii] = charToString(x);
                    ii++;
                }
                
                
                for (int j = y1+1; j < y2; j++)
                {
                    canvas[j][y2] = "|";
                }
                canvas[y2-1][x2] = "V";
            }
            else if(canvas[y1-1][x1]=="")//^ ^
            {
                for(int j=y1-1;j>y1-FIVE;j--)
                {
                    canvas[j][x1]="|";
                }
                canvas[y1-FIVE][x1]="+";
                
                for(int i=x1+1;i<x2;i++)
                {
                canvas[y1-FIVE][i]="-";
                }
                canvas[y1-FIVE][x2]="+";
                
                int ii=0;
                for (char x : weight) {
                    canvas[y1-FIVE][x1+4+ii] = charToString(x);
                    ii++;
                }
                
                for(int j=y1-FIVE+1;j<y2;j++)
                {
                canvas[j][x2]="|";
                }
                canvas[y2-1][x2]="V";
            }
            else if(canvas[y1][x1-1]=="")
            {
                for(int i=x1-1;i>x1-FIVE;i--)
                {
                canvas[y1][i]="-";
                }
                canvas[y1][x1-FIVE]="+";
                
                for(int j=y1-1;j>y1-EIGHT;j--)
                {
                canvas[j][x1-FIVE]="|";
                }
                canvas[y1-EIGHT][x1-FIVE]="+";
                
                for(int i=x1-4;i<x2;i++)
                {
                canvas[y1-EIGHT][i]="-";
                }
                canvas[y1-EIGHT][x2]="+";
                
                
                int ii=0;
                for (char x : weight) {
                    canvas[y1-EIGHT][x1-1+ii] = charToString(x);
                    ii++;
                }
                
                for(int j=y1-7;j<y2;j++)
                {
                canvas[j][x2]="|";
                }
                canvas[y2-1][x2]="V";
            }
            else if(canvas[y1+1][x1]=="")
            {
                for(int j=y1+1;j<y1+FIVE;j++)
                {
                    canvas[j][x1]="|";
                }
                canvas[y1+FIVE][x1]="+";
                for(int i=x1-1;i>x1-EIGHT;i--)
                {
                    canvas[y1+FIVE][i]="-";
                }
                canvas[y1+FIVE][x1-EIGHT]="+";
                for(int j=y1+4;j>y1-NINE;j--)
                {
                    canvas[j][x1-EIGHT]="|";
                }
                canvas[y1-NINE][x1-EIGHT]="+";
                for(int i=x1-7;i<x2;i++)
                {
                canvas[y1-NINE][i]="-";
                }
                canvas[y1-NINE][x2]="+";
                
                int ii=0;
                for (char x : weight) {
                    canvas[y1-NINE][x1-4+ii] = charToString(x);
                    ii++;
                }
                
                
                
                for(int j=y1-EIGHT;j<y2;j++)
                {
                canvas[j][x2]="|";
                }
                canvas[y2-1][x2]="V";
            }
        }
        
        
        else{
            if(canvas[y1][x1-1]=="")
            {
                for(int i=x1-1;i>x2;i--)
                {
                canvas[y1][i]="-";
                }
                canvas[y1][x2]="+";
                
                int ii=0;
                for (char x : weight) {
                    canvas[y1][x1-4+ii] = charToString(x);
                    ii++;
                }
                
                
                for(int j=y1-1;j>y2;j--)
                {
                    canvas[j][x2]="|";
                }
                canvas[y2+1][x2]="^";
            }
            else if(canvas[y1+1][x1]=="")
            {
                for(int j=y1+1;j<y1+FIVE;j++)
                {
                canvas[j][x1]="|";
                }
                canvas[y1+FIVE][x1]="+";
                for(int i=x1-1;i>x2;i--)
                {
                    canvas[y1+FIVE][i]="-";
                }
                canvas[y1+FIVE][x2]="+";
                
                int ii=0;
                for (char x : weight) {
                    canvas[y1+FIVE][x1-4+ii] = charToString(x);
                    ii++;
                }
                
                
                for(int j=y1+4;j>y2;j--)
                {
                    if(canvas[j][x2]=="")
                    {
                        canvas[j][x2]="|";
                    }
                    else
                    {
                        canvas[j][x2]="=";
                    }
                }
                canvas[y2+1][x2]="^";
                
            }
            else if (canvas[y1][x1+1]=="")
            {
                for(int i=x1+1;i<x1+FIVE;i++)
                {
                canvas[y1][i]="-";
                }
                canvas[y1][x1+FIVE]="+";
                for(int j=y1+1;j<y1+EIGHT;j++)
                {
                canvas[j][x1+FIVE]="|";
                }
                canvas[y1+EIGHT][x1+FIVE]="+";
                for(int i=x1+4;i>x2;i--)
                {
                canvas[y1+EIGHT][i]="-";
                }
                canvas[y1+EIGHT][x2]="+";
                
                
                int ii=0;
                for (char x : weight) {
                    canvas[y1+EIGHT][x1+1+ii] = charToString(x);
                    ii++;
                }
                
                
                for(int j=y1+7;j>y2;j--)
                {
                if(canvas[j][x2]=="")
                {
                    canvas[j][x2]="|";
                }
                else
                {
                canvas[j][x2]="=";
                }
                }
                canvas[y2+1][x2]="^";
            }
           else if(canvas[y1-1][x1]=="")
           {
               for (int j=y1-1;j>y1-FIVE;j--)
               {
               canvas[j][x1]="|";
               }
               canvas[y1-FIVE][x1]="+";
               
               for(int i=x1+1;i<x1+EIGHT;i++)
               {
               canvas[y1-FIVE][i]="-";
               }
               canvas[y1-FIVE][x1+EIGHT]="+";
               for(int j=y1-4;j<y1+NINE;j++)
               {
               canvas[j][x1+EIGHT]="|";
               }
               canvas[y1+NINE][x1+EIGHT]="+";
               for (int i=x1+7;i>x2;i--)
               {
               canvas[y1+NINE][i]="-";
               }
               canvas[y1+NINE][x2]="+";
               
               
               int ii=0;
               for (char x : weight) {
                   canvas[y1+NINE][x1+4+ii] = charToString(x);
                   ii++;
               }
               
               
               for(int j=y1+EIGHT;j>y2;j--)
               {
               if(canvas[j][x2]=="")
               {
                   canvas[j][x2]="|";}
               else
               {
               canvas[j][x2]="=";}
               }
               canvas[y2+1][x2]="^";
           }
        
        }

    }
    
    
    
    for (int i=0; i<points.size() ; i++) {
        canvas[points[i].y][points[i].x-1] = "[";
        canvas[points[i].y][points[i].x+1] = "]";
        
        
    }
    
    
    map<int, struct point>  nodes;
    for (int i = 0; i<points.size(); i++) {
        nodes[points[i].name] = points[i];
    }

    
    
    
    printMatrix(canvas);
    printChart(nodes, myGraph);
    
    
    
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

