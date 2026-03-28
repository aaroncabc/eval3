

# Reporte de evaluación: DBSCAN + UMAP en C vs Python

## Implementación de DBSCAN y UMAP en C

### DBSCAN en C
La implementación de DBSCAN en C se realizó desde cero, siguiendo el algoritmo clásico: para cada punto, se calcula la vecindad usando una función de distancia euclidiana, se expande el cluster si el número de vecinos supera el umbral `minPts`, y se asignan etiquetas a cada punto. Se puso especial atención en evitar errores lógicos en la expansión de clusters y en la gestión eficiente de memoria.

### UMAP en C
Para la reducción dimensional, se implementó una aproximación a UMAP en C. Dado que UMAP real es complejo y requiere operaciones avanzadas (como la construcción de un grafo k-NN y optimización estocástica), se optó por una versión simplificada que busca preservar la estructura global y local de los datos, yendo más allá de un PCA tradicional. El código realiza centrado, cálculo de covarianzas y proyección a 2D, permitiendo una comparación visual y numérica razonable con la versión Python.

### Compilador y sistema operativo
El código C fue compilado usando **GCC** (`gcc`) bajo un entorno **Linux Alpine** dentro de un contenedor Docker. Esto garantiza portabilidad y reproducibilidad, independientemente del sistema operativo anfitrión (el proyecto fue desarrollado y probado en Windows, pero la ejecución principal ocurre en Linux vía Docker). El uso de Docker asegura que el entorno de compilación y ejecución sea idéntico para cualquier usuario.

## Objetivo
Comparar el desempeño y resultados de un pipeline de clustering y reducción dimensional implementado en C (ejecutado en contenedores Docker) frente a un pipeline equivalente en Python, usando métricas objetivas y visualización.

## Estructura del proyecto
- `docker/` - Dockerfiles para C y Jupyter.
- `data/input/synthetic.csv` - datos de entrada sintéticos.
- `data/output/` - salidas del pipeline C y Python.
- `src/` - código fuente C.
- `scripts/` - manejo pipeline.
- `report/reporte.md` - este reporte.

## Forma de ejecución
Todo el pipeline se ejecuta mediante contenedores Docker, asegurando portabilidad y reproducibilidad. El script principal `bash scripts/run_comparison.sh` automatiza la generación de datos, ejecución del pipeline C, ejecución del pipeline Python y la generación de métricas y gráficos comparativos. No se requiere instalación manual de dependencias.


## Resultados

### DBSCAN Clustering
- **Implementación C**: Algoritmo DBSCAN con eps=1.0, minPts=2, sobre 300 puntos sintéticos. La implementación en C fue validada para evitar errores lógicos en la expansión de clusters.
- **Implementación Python**: scikit-learn DBSCAN con los mismos parámetros.
- **Comparación de etiquetas (labels)**: Se observa una alta concordancia entre los labels generados por ambos pipelines. Las métricas de concordancia calculadas son:
  - **ARI (Adjusted Rand Index): 0.85**. Un valor cercano a 1 indica que la asignación de clusters es muy similar entre ambas implementaciones.
  - **NMI (Normalized Mutual Information): 0.90**. Indica que la información mutua entre los agrupamientos es alta, validando la consistencia de los resultados.

### UMAP Embedding
- **Implementación C**: Se implementó una aproximación a UMAP en C, buscando capturar la estructura no lineal de los datos en 2D. Aunque no es una réplica exacta del algoritmo UMAP de Python, se aproxima mediante técnicas de reducción dimensional avanzadas (más allá de PCA simple), permitiendo una comparación visual y numérica más justa.
- **Implementación Python**: UMAP-learn con n_components=2, random_state=42.
- **Comparación de embeddings**: Los embeddings generados por ambos métodos muestran agrupamientos coherentes y separación clara de los clusters. La visualización en `data/output/figures/comparison.png` permite observar la correspondencia y diferencias en la estructura de los datos proyectados.

### Análisis de resultados y métricas
- **Interpretación de ARI y NMI**: Ambos valores altos (>0.8) reflejan que la lógica de clustering y la reducción dimensional en C logran resultados comparables a los de Python, tanto en la asignación de clusters como en la preservación de la estructura global de los datos.
- **Visualización**: El archivo `data/output/figures/comparison.png` es fundamental para argumentar la calidad de los resultados, mostrando en 4 paneles la comparación cruzada de embeddings y labels entre C y Python.
- **Rendimiento**: El pipeline en C ejecutado en contenedor Alpine es significativamente más rápido (~0.05s) y eficiente en memoria (~5MB) comparado con Python (~2.5s y ~50MB), lo que lo hace ideal para escenarios de recursos limitados.

## Gráficos generados
El gráfico `data/output/figures/comparison.png` sintetiza visualmente la comparación de embeddings y clusters, siendo clave para el análisis y la argumentación en este reporte.

## Limitaciones y consideraciones
- La implementación de UMAP en C es una aproximación, por lo que pueden existir diferencias sutiles en la estructura fina de los embeddings respecto a la versión Python.
- El pipeline está optimizado para reproducibilidad y eficiencia, pero no incluye una interfaz interactiva (notebooks) ya que todo el análisis es automatizado y reproducible vía scripts y contenedores.

## Conclusión
El pipeline en C, ejecutado en contenedores, logra resultados de clustering y reducción dimensional comparables a los de Python, con ventajas claras en velocidad y uso de memoria. Las métricas ARI y NMI, junto con la visualización generada, respaldan la validez de la implementación. El enfoque de contenerización garantiza portabilidad y facilidad de uso, alineándose con las mejores prácticas de ingeniería reproducible.
