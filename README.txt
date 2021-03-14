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


Test result disscussion:
- test1
  run the test using command, ./MMULT.o test1
    Memory attached at 35028000
    Child Process: working with row 0
    Child Process: working with row 1
    Child Process: working with row 2
    Child Process: working with row 3
    Matrix m:
    1     3     5     7
    3     5     7     9
    5     7     9     11
    7     9     11     13
    
    Matrix n:
    2     4     6     8
    4     6     8     10
    6     8     10     12
    8     10     12     16
    
    Matrix q:
    100     132     164     210
    140     188     236     302
    180     244     308     394
    220     300     380     486
    
    The largest integer in Q is 486
    Start?Time:?1613953779.152880?sec?from?Epoch?(1970‐01‐01?00:00:00?+0000?(UTC))
    End?Time:?1613953779.153822?sec?from?Epoch?(1970‐01‐01?00:00:00?+0000?(UTC))
    
    Elapsed?Time:?942?micro?sec

  Discussion for test 1:
    The terminal output three matrices m, n, q after chile process finish the calculation.
    The terminal output the largest integer in Matrix q which is correct.
    The terminal successfully output the start, end time and time cost for the total calculation.  

-test2
  run the test using command, ./MMULT.o test2
    Memory attached at 8C4D3000
    Child Process: working with row 0
    Child Process: working with row 1
    Child Process: working with row 2
    Child Process: working with row 3
    Matrix m:
    5     8     10     6
    8     15     24     70
    21     19     8     10
    37     29     1     8
    
    Matrix n:
    21     14     61     48
    34     42     81     14
    56     28     16     12
    18     10     12     16
    
    Matrix q:
    1045     746     1185     568
    3282     2114     2927     2002
    1715     1416     3068     1530
    1963     1844     4718     2322
    
    The largest integer in Q is 4718
    Start?Time:?1613953686.082088?sec?from?Epoch?(1970‐01‐01?00:00:00?+0000?(UTC))
    End?Time:?1613953686.082662?sec?from?Epoch?(1970‐01‐01?00:00:00?+0000?(UTC))
    
    Elapsed?Time:?574?micro?sec
    
  Discussion for test 2:
    The terminal output three matrices m, n, q after chile process finish the calculation.
    The terminal output the largest integer in Matrix q which is correct.
    The terminal successfully output the start, end time and time cost for the total calculation.  
    
- Mandatory Test
  run the test using command, ./MMULT.o
    Memory attached at 5F150000
    Child Process: working with row 0
    Child Process: working with row 1
    Child Process: working with row 2
    Child Process: working with row 3
    Matrix m:
    20     20     50     40
    10     6     70     8
    40     3     2     10
    8     7     6     5
    
    Matrix n:
    10     30     50     70
    1     3     6     8
    9     5     5     7
    8     6     4     2
    
    Matrix q:
    990     1150     1530     1990
    800     716     918     1254
    501     1279     2068     2858
    181     321     492     668
    
    The largest integer in Q is 2858
    Start?Time:?1613953740.809226?sec?from?Epoch?(1970‐01‐01?00:00:00?+0000?(UTC))
    End?Time:?1613953740.809943?sec?from?Epoch?(1970‐01‐01?00:00:00?+0000?(UTC))
    
    Elapsed?Time:?717?micro?sec
    
  Discussion for Mandatory Test:
    The terminal output three matrices m, n, q after chile process finish the calculation.
    The terminal output the largest integer in Matrix q which is correct.
    The terminal successfully output the start, end time and time cost for the total calculation.  


Goals of design:
MMULT is a program that calculates the multiplication result of two matrices. And there are some specialties in this project.

1. MMULT.c include three test data(hardcode), and the test ran is based on the input argument
2. MMULT.c includes a function called print_matrix which could printout the corresponding matrix based on the function input parameter.
  - This function is used when a matrix needs to be printed out on the console.
3. MMULT.h includes the structure of the shared memory used in this project.
4. Project used gettimeofday to calculate and printout the time used on calculation.
5. Each child Process only works on one row, and the child process automatically exits after finish the row.