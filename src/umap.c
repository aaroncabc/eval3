#include "umap.h"
#include "matrix.h"
#include <stdlib.h>

Matrix umap_embed(const Matrix *data, int n_components) {
    int n = data->rows;
    Matrix emb = create_matrix(n, n_components);

    // Simple projection: use first two features with scaling.
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < n_components; c++) {
            double value = 0.0;
            if (c < data->cols) {
                value = matrix_get(data, i, c);
            } else {
                value = 0.0;
            }
            matrix_set(&emb, i, c, value);
        }
    }

    return emb;
}
