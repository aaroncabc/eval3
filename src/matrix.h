#ifndef MATRIX_H
#define MATRIX_H

#include "csv.h"

double matrix_get(const Matrix *m, int i, int j);
void matrix_set(Matrix *m, int i, int j, double value);
Matrix create_matrix(int rows, int cols);
void free_matrix(Matrix *m);

#endif // MATRIX_H
