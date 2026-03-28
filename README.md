# Eval3: DBSCAN + UMAP en C vs Python

Este proyecto implementa un pipeline de análisis de datos con DBSCAN y UMAP en C (contenedorizado) y lo compara con un equivalente Python en Jupyter (notebook).

## 1. Requisitos
- Docker y docker-compose instalados.
- Bash o terminal compatible (WSL / Git Bash en Windows).
- Python 3.8+ (opcional, para generar datos localmente sin contenedor).

## 2. Estructura de carpetas
- `docker/`: Dockerfiles para C y Jupyter.
- `data/input/synthetic.csv`: datos de entrada.
- `data/output/`: salida de resultados.
- `src/`: código C (lectura CSV, DBSCAN, UMAP simplificado, etc.).
- `notebooks/comparison.ipynb`: comparación Python vs C.
- `scripts/`: utilidades de ejecución.
- `report/reporte.md`: resumen y conclusiones.

## 3. Flujo de ejecución completo (comandos en orden)

### 3.1 Modo local (sin contenedores)

1. Generar los datos sintéticos (si no existieran):

```bash
cd c:/Users/aaron/Desktop/eval3_IA/eval3
python scripts/generate_data.py
```

2. Compilar y ejecutar el pipeline C local:

```bash
cd c:/Users/aaron/Desktop/eval3_IA/eval3
bash scripts/run_c.sh
```

3. Ejecutar la comparación rápida (local):

```bash
cd c:/Users/aaron/Desktop/eval3_IA/eval3
bash scripts/run_comparison.sh
```

4. (Opcional) Iniciar Jupyter local si se desea:

```bash
cd c:/Users/aaron/Desktop/eval3_IA/eval3
jupyter notebook
```

### 3.2 Modo contenedores (Docker + docker-compose)

1. Generar los datos sintéticos y pipeline C dentro de contenedor:

```bash
cd c:/Users/aaron/Desktop/eval3_IA/eval3
docker-compose run --rm c-builder
```

2. Iniciar servidor Jupyter en contenedor para análisis comparativo:

```bash
cd c:/Users/aaron/Desktop/eval3_IA/eval3
docker-compose up jupyter
```

- Abrir `http://localhost:8888` y cargar `notebooks/comparison.ipynb`.

3. Ejecutar comparación rápida en contenedor (ya contiene una llamada a c-builder):

```bash
cd c:/Users/aaron/Desktop/eval3_IA/eval3
bash scripts/run_comparison.sh
```


## 4. Resultado esperado y archivos de salida

- `data/output/dbscan_labels.csv`
  - Contiene columna `label` con etiqueta DBSCAN calculada por la implementación C.

- `data/output/umap_embedding.csv`
  - Contiene columnas `x`, `y` con reducción 2D del conjunto en C.

- Opcional: `data/output/figures/c_result.png` (si se implementa exportación PNG).

## 5. Cómo leer correctamente los resultados

### Etiquetas de cluster DBSCAN
1. `data/output/dbscan_labels.csv`
2. Los valores `0`, `1`, ... son clusters de C.
3. El valor `-1` (si existiera) sería ruido (fuera de cluster).

Ejemplo en Python:

```python
import pandas as pd
labels = pd.read_csv('data/output/dbscan_labels.csv')
print(labels['label'].value_counts())
```

### Embedding UMAP en 2D
1. `data/output/umap_embedding.csv` (x, y)
2. Representar scatter plots en Python para ver separación:

```python
emb = pd.read_csv('data/output/umap_embedding.csv')
labels = pd.read_csv('data/output/dbscan_labels.csv')
import matplotlib.pyplot as plt
plt.scatter(emb['x'], emb['y'], c=labels['label'], cmap='tab10')
plt.title('UMAP C result')
plt.show()
```

### Comparativa con Python
1. Abrir y ejecutar `notebooks/comparison.ipynb`.
2. La sección de Python recalcula DBSCAN y UMAP con scikit-learn / umap-learn.
3. Comparar patrones de clusters, counts y gráficos entre C y Python.

## 6. Validación de resultados

- Confirmar que `dbscan_labels.csv` y `umap_embedding.csv` existen y contienen filas igual al número de puntos de `data/input/synthetic.csv`.
- Comparar conteos de etiquetas y dispersión gráfica para detectar desajustes.

---

Este README incorpora en un solo lugar el flujo completo y la interpretación de salidas para responder a la pregunta de dónde y cómo leer los resultados.
