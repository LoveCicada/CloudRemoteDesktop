/**
 * @file testMouseMove.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include "Command2.h"
using namespace std;

/*
@brief
100 ==> 0x64
101 ==> 0x65
25701 ==> 0x64 65

*/

int main(int argc, char** argv)
{
    unsigned char uc[8] = {0};
    uc[5] = 100;
    uc[6] = 101;
    CmdMouseMove cm(uc);
    int delta = 0;
    cm.GetDelta(delta);
    cout << "delta = " << delta << endl;

    return 0;
}

/*
@result 
./bin/testMouseMove 
delta = 25701
*/

