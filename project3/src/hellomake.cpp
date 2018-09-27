/*==============================================================================
Title:           FYS3150 Project 3 -
Author:          Erik Johannes B. L. G. Husom
Date:            2018-09-26
Version:         0.1
Description:
USAGE:
==============================================================================*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
// #include <armadillo>
#include "hellofunc.h"
using namespace std;

int main(int argc, char *argv[])
{
  cout << (double) std::chrono::high_resolution_clock::period::num
             / std::chrono::high_resolution_clock::period::den;
  myPrintHelloMake();
  cout << "test\n";

  return 0;
} // end of main function
