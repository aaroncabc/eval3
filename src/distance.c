#include "distance.h"
#include <math.h>

double euclidean(const Matrix *data, int i, int j) {
    double sum = 0.0;
    int d = data->cols;
    for (int k = 0; k < d; k++) {
        double diff = data->data[i * d + k] - data->data[j * d + k];
        sum += diff * diff;
    }
    return sqrt(sum);
}
