/*
 * Author: Zijun Hu
 * Copyright © 2021 Zijun Hu. All rights reserved.
 */
#ifndef MMULT_h
#define MMULT_h

typedef int matrix[4][4];
struct shared_use_st {
    matrix m;
    matrix n;
    matrix q;   // Result matrix
    int L;      // Largest number in result matrix q
};
#endif