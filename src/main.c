#include <stdio.h>
#include <stdlib.h>
#include "csv.h"
#include "dbscan.h"
#include "matrix.h"
#include "umap.h"

int main(void) {
    printf("Starting C pipeline\n");
    const char *input_path = "data/input/synthetic.csv";
    const char *labels_path = "data/output/dbscan_labels.csv";
    const char *embed_path = "data/output/umap_embedding.csv";

    Matrix data = load_csv(input_path);
    if (!data.data) {
        fprintf(stderr, "Error cargando %s\n", input_path);
        return 1;
    }

    int minPts = 2;
    double eps = 1.0;
    int *labels = dbscan(&data, eps, minPts);
    if (!labels) {
        fprintf(stderr, "Error ejecutando DBSCAN\n");
        free_matrix(&data);
        return 1;
    }
    printf("DBSCAN done\n");

    Matrix emb = umap_embed(&data, 2);
    printf("UMAP done\n");

    save_labels(labels_path, labels, data.rows);
    save_csv(embed_path, &emb, "x,y");

    printf("C pipeline finalizado.\n");
    free(labels);
    free_matrix(&data);
    free_matrix(&emb);

    return 0;
}
