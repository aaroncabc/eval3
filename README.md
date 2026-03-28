# Eval3: DBSCAN + PCA (como UMAP simplificado) en C vs Python

Este proyecto implementa un pipeline de análisis de datos con DBSCAN y una reducción dimensional (PCA como aproximación simplificada de UMAP) en C (contenedorizado) y lo compara con un equivalente Python en Jupyter (notebook) usando scikit-learn DBSCAN y umap-learn.

## 1. Requisitos
- Docker y docker-compose instalados.
- Bash o terminal compatible (WSL / Git Bash en Windows).
- Python 3.8+ con scikit-learn, umap-learn, matplotlib, seaborn (para comparación local).


## 2. Estructura de carpetas
- `docker/`: Dockerfiles para C y Jupyter.
- `data/input/synthetic.csv`: datos de entrada sintéticos (3 clusters 2D).
- `data/output/`: salidas C (labels DBSCAN, embedding UMAP), Python (labels, embedding UMAP, figuras).
- `src/`: código C puro (lectura CSV, DBSCAN, UMAP para reducción dimensional).
- `scripts/`: scripts para ejecutar pipeline completo.
- `report/reporte.md`: reporte con métricas y conclusiones.

## 3. Flujo de ejecución completo

### Comando único para todo el proyecto:
```bash
bash scripts/run_comparison.sh
```

Este script realiza automáticamente:
1. Genera datos sintéticos si no existen.
2. Compila y ejecuta el pipeline C (DBSCAN + PCA).
3. Ejecuta DBSCAN + UMAP en Python.
4. Calcula métricas de concordancia (ARI, NMI).
5. Genera gráficos de comparación (4 paneles) y los guarda en `data/output/figures/comparison.png`.
6. Imprime resultados en consola.

### Modo detallado (paso a paso):

1. Generar datos:
```bash
python scripts/generate_data.py
```

2. Ejecutar pipeline C:
```bash
docker-compose run --rm c-builder
# O local: make all && ./eval3_c
```

3. Ejecutar comparación:
```bash
python scripts/run_comparison.py
```


## 4. Salidas generadas
- `data/output/dbscan_labels.csv`: Labels de clusters C.
- `data/output/umap_embedding.csv`: Embedding UMAP C (2D).
- `data/output/python_dbscan_labels.csv`: Labels Python.
- `data/output/python_umap_embedding.csv`: Embedding UMAP Python.
- `data/output/figures/comparison.png`: Gráficos comparativos (imprescindible para el análisis y reporte).

## 5. Notas técnicas
- **DBSCAN C**: Implementación pura con eps=1.0, minPts=2.
- **Reducción C**: UMAP real o aproximación lo más cercana posible en C.
- **Comparación**: Métricas ARI/NMI, visualizaciones para validar concordancia.
- **Rendimiento**: C es más rápido y eficiente en memoria.

Ejecuta `bash scripts/run_comparison.sh` para ver el proyecto en acción. El archivo `data/output/figures/comparison.png` es clave para interpretar los resultados y argumentar el desempeño de ambos enfoques.