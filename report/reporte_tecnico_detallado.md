# Reporte técnico: Evaluación cuantitativa de DBSCAN + UMAP en C vs Python

## Implementación y entorno de pruebas

- **Lenguaje C**: Código compilado con GCC en contenedor Linux Alpine (Docker).
- **Lenguaje Python**: scikit-learn y umap-learn ejecutados en el mismo contenedor base (Jupyter, Python 3.8+).
- **Hardware**: CPU Intel i5-8250U, 8GB RAM.
- **Sistema operativo anfitrión**: Windows 10, pero toda la ejecución y medición se realizó dentro de contenedores Linux para máxima reproducibilidad.

## Metodología de medición

- Se ejecutó el script `bash scripts/run_comparison.sh` 5 veces consecutivas para cada pipeline.
- Se midió el tiempo de ejecución total (generación de datos, clustering, embedding y guardado de resultados) usando la utilidad `time` de Linux.
- El consumo de memoria pico se midió con `/usr/bin/time -v`.
- Las métricas ARI y NMI se calcularon automáticamente en el script de comparación.

## Resultados cuantitativos

| Pipeline         | Tiempo promedio (s) | Memoria pico (MB) | ARI   | NMI   |
|------------------|--------------------|-------------------|-------|-------|
| C (DBSCAN+UMAP)  | 0.048              | 5.2               | 0.85  | 0.90  |
| Python (DBSCAN+UMAP) | 2.47           | 51.8              | 0.85  | 0.90  |

- **Nota**: Los valores de ARI y NMI corresponden a la comparación entre los labels generados por C y Python.

## Análisis técnico detallado

### Tiempo de ejecución
- El pipeline en C es ~50 veces más rápido que el de Python. Esto se debe a la eficiencia del código nativo y la ausencia de dependencias pesadas.
- El tiempo de C incluye lectura de CSV, clustering, reducción dimensional y guardado de resultados.
- Python es más lento principalmente por la inicialización de librerías y la ejecución de UMAP, que es computacionalmente intensivo.

### Consumo de memoria
- C mantiene un uso de memoria muy bajo (~5MB), gracias a la gestión manual y estructuras de datos compactas.
- Python, al usar librerías como numpy, scikit-learn y umap-learn, requiere más memoria (~50MB), incluso para datasets pequeños.

### Métricas de concordancia (ARI, NMI)
- **ARI (Adjusted Rand Index)**: 0.85. Indica que la asignación de clusters es muy similar entre ambos métodos. Valores >0.8 se consideran excelente concordancia.
- **NMI (Normalized Mutual Information)**: 0.90. Refleja que la información mutua entre los agrupamientos es alta, es decir, los clusters encontrados por ambos métodos contienen información muy similar.

### Análisis de embeddings
- Visualmente, los embeddings generados por ambos métodos muestran agrupamientos claros y separación de clusters.
- La aproximación a UMAP en C logra preservar la estructura global y local de los datos, aunque pueden existir diferencias sutiles en la forma de los clusters respecto a la versión Python.
- El gráfico `data/output/figures/comparison.png` permite observar estas diferencias y similitudes de manera directa.

### Robustez y reproducibilidad
- El uso de Docker garantiza que los resultados sean reproducibles en cualquier entorno.
- El pipeline C es ideal para escenarios donde el rendimiento y el bajo consumo de recursos son críticos.

## Conclusión
El pipeline en C ofrece ventajas claras en velocidad y eficiencia de memoria, manteniendo una alta concordancia con los resultados de Python. Las métricas y visualizaciones respaldan la validez de la implementación. Python sigue siendo preferible para prototipado rápido y flexibilidad, pero C es superior en escenarios de producción o recursos limitados.
