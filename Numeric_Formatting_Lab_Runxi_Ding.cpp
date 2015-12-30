//
//  Numeric_Formatting_Lab_Runxi_Ding.cpp
//  Hello
//
//  Created by Ding,Runxi on 8/27/15.
//  Copyright (c) 2015 bunengzhai. All rights reserved.
//

#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, const char * argv[]) {
    auto decimalNum = 0.0;
    auto integerNum = 0;
    
    //1. Ask the user to input a number, which may or may not have a decimal component and stores that number in a type of variable that supports decimal numbers.
    cout << "please type a decimal number: ";
    cin  >> decimalNum;
    
    //set precision to 0
    //2. Print out the integer portion of the number without storing the number in a second variable.
    cout << "The integer portion of the number is: "<< static_cast<int>(decimalNum) <<endl;
    
    
    //3. Store the number in an actual integer variable, taking care to do so without getting any warnings or errors from the compiler.
    integerNum = static_cast<int>(decimalNum);
    
    //4. Print out the new integer variable.
    cout <<"The new integer variable is: " << integerNum <<endl;
    
    //5. Print the number with exactly two decimal places shown.
    cout << "The decimal number with precision 2 is: " << setiosflags (ios::fixed | ios::showpoint) <<setprecision(2)<<decimalNum<<endl;
    
    //6. Using the integer number, display a 0 if it is even or a 1 if it is odd. You can accomplish this without conditional statements
    cout << "display zero if "<< integerNum <<" is even, otherwise display one : " << integerNum % 2 <<endl;
    
    //7. Display your name to the screen.
    cout << "Ding, Runxi" <<endl;
    
    return 0;
}

