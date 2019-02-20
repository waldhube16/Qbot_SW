/*
* Based on:
* URL: https://github.com/muodov/kociemba/blob/master/kociemba/ckociemba/include/edge.h
* Author: Maxim Tsoy
* LICENSE: GPL-2.0
* Used by: Simon Waldhuber
* Available:https://github.com/waldhube16/Qbot_SW/blob/master/SolverBackend/AlgorithmEmbeddedC/edge.h
*/


#ifndef EDGE_H
#define EDGE_H
// The names of the edge positions of the cube. Edge UR e.g., has an U(p) and R(ight) facelet.
typedef enum {
    UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR
} edge_t;

#define EDGE_COUNT 12
#endif
