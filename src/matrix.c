#include "matrix.h"
#include <stdlib.h>

double matrix_get(const Matrix *m, int i, int j) {
    return m->data[i * m->cols + j];
}

void matrix_set(Matrix *m, int i, int j, double value) {
    m->data[i * m->cols + j] = value;
}

Matrix create_matrix(int rows, int cols) {
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    m.data = calloc(rows * cols, sizeof(double));
    return m;
}

void free_matrix(Matrix *m) {
    if (m->data) free(m->data);
    m->data = NULL;
    m->rows = m->cols = 0;
}
