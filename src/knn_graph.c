#include "knn_graph.h"
#include "distance.h"
#include <stdlib.h>

int *knn_indices(const Matrix *data, int k) {
    int n = data->rows;
    int *res = calloc(n * k, sizeof(int));
    for (int i = 0; i < n; i++) {
        double *dist = malloc(sizeof(double) * n);
        int *ids = malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            dist[j] = euclidean(data, i, j);
            ids[j] = j;
        }
        // simple selection sort k neighbors
        for (int a = 0; a <= k; a++) {
            for (int b = a + 1; b < n; b++) {
                if (dist[b] < dist[a]) {
                    double td = dist[a]; dist[a] = dist[b]; dist[b] = td;
                    int ti = ids[a]; ids[a] = ids[b]; ids[b] = ti;
                }
            }
        }

        int p = 0;
        for (int a = 1; a <= k; a++) {
            res[i * k + p++] = ids[a];
        }
        free(dist);
        free(ids);
    }
    return res;
}
