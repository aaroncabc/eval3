#include "dbscan.h"
#include "distance.h"
#include <stdlib.h>

int *dbscan(const Matrix *data, double eps, int minPts) {
    int n = data->rows;
    int *labels = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) labels[i] = -1;

    int cluster_id = 0;
    for (int i = 0; i < n; i++) {
        if (labels[i] != -1) continue;

        int *neighbors = malloc(sizeof(int) * n * n);
        int ncount = 0;
        for (int j = 0; j < n; j++) {
            if (euclidean(data, i, j) <= eps) {
                neighbors[ncount++] = j;
            }
        }

        if (ncount < minPts) { labels[i] = -1; free(neighbors); continue; }

        labels[i] = cluster_id;
        for (int idx = 0; idx < ncount; idx++) {
            int j = neighbors[idx];
            if (labels[j] != -1) continue;
            labels[j] = cluster_id;
            int *neighbors2 = malloc(sizeof(int) * n * n);
            int ncount2 = 0;
            for (int k = 0; k < n; k++) {
                if (euclidean(data, j, k) <= eps) {
                    neighbors2[ncount2++] = k;
                }
            }
            if (ncount2 >= minPts) {
                for (int k = 0; k < ncount2; k++) {
                    neighbors[ncount++] = neighbors2[k];
                }
            }
            free(neighbors2);
        }
        cluster_id++;
        free(neighbors);
    }

    return labels;
}
