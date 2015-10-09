//
//  main.cpp
//  tic-tac-toe
//
//  Created by sunny on 10/9/15.
//  Copyright © 2015 bunengzhai. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class graph{
private:
    int matrix[4][4];
    string matrixStr[4][4];
public:
    graph();
    void draw();
    int setMatrix(int x, int y, int value){
        if(x > 3 || x < 1){
            return -1;
        }
        if(y > 3 || y < 1){
            return -1;
        }
        if(0 != matrix[x][y]){
            return -1;
        }
        matrix[x][y] = value;
        return 0;
    }
    int calWiner(){
        for(int i = 1; i<4 ; i++){
            if(matrix[i][1] == -1 && matrix[i][2] == -1 && matrix[i][3] == -1){
                return -1;
            }
            if(matrix[i][1] == 1 && matrix[i][2] == 1 && matrix[i][3] == 1){
                return 1;
            }
            if(matrix[1][i] == 1 && matrix[2][i] == 1 && matrix[3][i] == 1){
                return 1;
            }
            if(matrix[1][i] == 1 && matrix[2][i] == 1 && matrix[3][i] == 1){
                return 1;
            }
            if(matrix[1][i] == 1 && matrix[2][i] == 1 && matrix[3][i] == 1){
                return 1;
            }
            if(matrix[1][i] == -1 && matrix[2][i] == -1 && matrix[3][i] == -1){
                return -1;
            }
            if(matrix[1][i] == -1 && matrix[2][i] == -1 && matrix[3][i] == -1){
                return -1;
            }
            if(matrix[1][i] == -1 && matrix[2][i] == -1 && matrix[3][i] == -1){
                return -1;
            }
            
            
            
        }

        if(matrix[1][1] == 1 && matrix[2][2] == 1 && matrix[2][3] == 1){
            return 1;
        }
        if(matrix[1][1] == -1 && matrix[2][2] == -1 && matrix[2][3] == -1){
            return -1;
        }
        
        if(matrix[1][3] == -1 && matrix[2][2] == -1 && matrix[3][1] == -1){
            return -1;
        }
        
        if(matrix[1][3] == 1 && matrix[2][2] == 1 && matrix[3][1] == 1){
            return 1;
        }
        return 0;
    }
};

graph::graph(){
    for (int i =0; i<4; i++) {
        for (int j = 0; j<4; j++) {
            matrix[i][j] = 0;
        }
    }
}

void graph::draw(){


    for (int i = 1; i<= 3; i++) {  
        for (int j=1; j<=3; j++) {
            matrixStr[i][j] = " ";
            if(matrix[i][j] == -1){
                matrixStr[i][j] = "x";
            }else if (matrix[i][j] == 1){
                matrixStr[i][j] = "o";
            }
           
            
        }
    }
    cout<<"   1   2   3 "<<endl;
    cout<<" 1 "<<matrixStr[1][1]<<" | "<<matrixStr[1][2]<<" | "<<matrixStr[1][3]<<" "<<endl;
    cout<<"  ---+---+---"<<endl;
    cout<<" 2 "<<matrixStr[2][1]<<" | "<<matrixStr[2][2]<<" | "<<matrixStr[2][3]<<" "<<endl;
    cout<<"  ---+---+---"<<endl;
    cout<<" 3 "<<matrixStr[3][1]<<" | "<<matrixStr[3][2]<<" | "<<matrixStr[3][3]<<" "<<endl;
    
}
int main(int argc, const char * argv[]) {

    graph g;
    g.draw();
    int x, y, round, value;
    
    round = 1;
    while (true) {
        value = -1;
        if(round % 2 == 0){
            value = 1;
        }
        cin >> x >> y;
        if( -1 == g.setMatrix(x, y, value)){
            cout << "enter the number again..." <<endl;
            continue;
        }
        g.draw();
        int winner = g.calWiner();
        if ( winner == -1) {
            cout << "winner is x!!!"<<endl;
            break;
        }else if(winner == 1){
            cout << "winner is o!!!"<<endl;
            break;
        }
        round++;
    }


    return 0;
}
