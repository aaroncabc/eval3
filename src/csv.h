#ifndef CSV_H
#define CSV_H

typedef struct {
    int rows;
    int cols;
    double *data;
} Matrix;

Matrix load_csv(const char *path);
int save_csv(const char *path, const Matrix *m, const char *header);
int save_labels(const char *path, const int *labels, int n);

#endif // CSV_H
