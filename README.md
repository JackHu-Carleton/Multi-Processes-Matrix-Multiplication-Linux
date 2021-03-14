# Multi-Processes-Matrix-Multiplication-Linux
Author: Zijun Hu  
Copyright © 2021 Zijun Hu. All rights reserved.  

MMULT is a program that calculates the multiplication result of two matrices.  
  - MMULT.c:  The main file for the program
  - MMULT.h:  Include the structure of the shared memory
  - test_result_discussion.txt:  Include the test result for three different test case and the discussion to the result
  - Goals_of_design.txt:  Include the explanation for the project specialty
  - Makefile:  The makefile for the project

Setup Instruction:  
1. Compile the program using a makefile. (make sure the terminal location is in the project MMULT)  
	- Use command make, the program will automatically compile, and generate an output file called MMULT.o  

2. Run MMULT.o using the command in terminal (make sure the terminal location is in the project MMULT),  
		./MMULT.o <Option Argument>  
	
Option Argument:  
	- test1: the program will using the following as input matrices.  
	    matrix m_1 = {{1, 3, 5,  7},  
                      {3, 5, 7,  9},  
                      {5, 7, 9,  11},  
                      {7, 9, 11, 13}};  
        matrix n_1 = {{2, 4,  6,  8},  
                      {4, 6,  8,  10},  
                      {6, 8,  10, 12},  
                      {8, 10, 12, 16}};  
	- test2: the program will using the following as input matrices.  
        matrix m_2 = {{5,  8,  10, 6},  
                      {8,  15, 24, 70},  
                      {21, 19, 8,  10},  
                      {37, 29, 1,  8}};  
        matrix n_2 = {{21, 14, 61, 48},  
                      {34, 42, 81, 14},  
                      {56, 28, 16, 12},  
                      {18, 10, 12, 16}};  
No Argument inputted:  
	- The program will use Mandatory Test Data as input matrices  
        matrix m_d = {{20, 20, 50, 40},  
                      {10, 6,  70, 8},  
                      {40, 3,  2,  10},  
                      {8,  7,  6,  5}};  
        matrix n_d = {{10, 30, 50, 70},  
                      {1,  3,  6,  8},  
                      {9,  5,  5,  7},  
                      {8,  6,  4,  2}};  
 
