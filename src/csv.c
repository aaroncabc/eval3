#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Matrix load_csv(const char *path) {
    Matrix m = {0, 0, NULL};
    FILE *f = fopen(path, "r");
    if (!f) return m;

    char line[1024];
    if (!fgets(line, sizeof(line), f)) { fclose(f); return m; }

    int cols = 0;
    char *tok = strtok(line, ",\n\r");
    while (tok) { cols++; tok = strtok(NULL, ",\n\r"); }

    double *data = NULL;
    int rows = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strlen(line) < 2) continue;
        tok = strtok(line, ",\n\r");
        int c = 0;
        while (tok && c < cols) {
            data = realloc(data, sizeof(double) * (rows * cols + c + 1));
            data[rows * cols + c] = atof(tok);
            c++;
            tok = strtok(NULL, ",\n\r");
        }
        if (c == cols) rows++;
    }
    fclose(f);

    m.rows = rows;
    m.cols = cols;
    m.data = data;
    return m;
}

int save_csv(const char *path, const Matrix *m, const char *header) {
    FILE *f = fopen(path, "w");
    if (!f) return -1;
    if (header) fprintf(f, "%s\n", header);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            fprintf(f, "%f", m->data[i * m->cols + j]);
            if (j + 1 < m->cols) fprintf(f, ",");
        }
        fprintf(f, "\n");
    }
    fclose(f);
    return 0;
}

int save_labels(const char *path, const int *labels, int n) {
    FILE *f = fopen(path, "w");
    if (!f) return -1;
    fprintf(f, "label\n");
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d\n", labels[i]);
    }
    fclose(f);
    return 0;
}
