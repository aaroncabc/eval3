#ifndef DBSCAN_H
#define DBSCAN_H

#include "csv.h"

int *dbscan(const Matrix *data, double eps, int minPts);

#endif // DBSCAN_H
