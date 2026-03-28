#include "umap.h"
#include "matrix.h"
#include <stdlib.h>
#include <math.h>

Matrix umap_embed(const Matrix *data, int n_components) {
    int n = data->rows;
    int d = data->cols;
    if (d < 2 || n_components != 2) {
        // Fallback to simple projection if not 2D
        Matrix emb = create_matrix(n, n_components);
        for (int i = 0; i < n; i++) {
            for (int c = 0; c < n_components; c++) {
                double value = (c < d) ? matrix_get(data, i, c) : 0.0;
                matrix_set(&emb, i, c, value);
            }
        }
        return emb;
    }

    // PCA for 2D data
    double mean[2] = {0.0, 0.0};
    for (int c = 0; c < 2; c++) {
        for (int i = 0; i < n; i++) {
            mean[c] += matrix_get(data, i, c);
        }
        mean[c] /= n;
    }

    Matrix centered = create_matrix(n, 2);
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 2; c++) {
            matrix_set(&centered, i, c, matrix_get(data, i, c) - mean[c]);
        }
    }

    double cov[2][2] = {{0.0, 0.0}, {0.0, 0.0}};
    for (int i = 0; i < n; i++) {
        double x = matrix_get(&centered, i, 0);
        double y = matrix_get(&centered, i, 1);
        cov[0][0] += x * x;
        cov[0][1] += x * y;
        cov[1][0] += y * x;
        cov[1][1] += y * y;
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cov[i][j] /= n;
        }
    }

    // Eigenvalues for 2x2 matrix
    double a = cov[0][0], b = cov[0][1], c_val = cov[1][1];
    double trace = a + c_val;
    double det = a * c_val - b * b;
    double disc = sqrt(trace * trace - 4 * det);
    double lambda1 = (trace + disc) / 2.0;
    double lambda2 = (trace - disc) / 2.0;

    // Eigenvectors
    double v1x = b, v1y = lambda1 - a;
    double norm1 = sqrt(v1x * v1x + v1y * v1y);
    if (norm1 > 0) { v1x /= norm1; v1y /= norm1; }

    double v2x = b, v2y = lambda2 - a;
    double norm2 = sqrt(v2x * v2x + v2y * v2y);
    if (norm2 > 0) { v2x /= norm2; v2y /= norm2; }

    // Project
    Matrix emb = create_matrix(n, 2);
    for (int i = 0; i < n; i++) {
        double x = matrix_get(&centered, i, 0);
        double y = matrix_get(&centered, i, 1);
        matrix_set(&emb, i, 0, x * v1x + y * v1y);
        matrix_set(&emb, i, 1, x * v2x + y * v2y);
    }

    free_matrix(&centered);
    return emb;
}
