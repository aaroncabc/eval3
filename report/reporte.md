# Reporte de evaluación: DBSCAN + UMAP en C vs Python

## Objetivo
Comparar una implementación pipeline en C (compilada en contenedor) con la misma en Python (cuaderno Jupyter).

## Estructura del proyecto
- `docker/` - Dockerfiles para C y Jupyter.
- `data/input/synthetic.csv` - datos de entrada sintéticos.
- `data/output/` - salidas del pipeline C.
- `src/` - código fuente C.
- `notebooks/comparison.ipynb` - análisis comparativo Python.
- `scripts/` - manejo pipeline.
- `report/reporte.md` - este reporte.

## Uso
1. Generar datos: `python scripts/generate_data.py`
2. Ejecutar C: `bash scripts/run_c.sh` o `docker-compose run --rm c-builder`
3. Jupyter: `docker-compose up jupyter` y abrir `http://localhost:8888`
4. Comparar: `bash scripts/run_comparison.sh`

## Métricas comparadas
- tiempo de ejecución (C vs Python)
- resultados (etiquetas DBSCAN, embedding UMAP)
- consumo de memoria

## Conclusión (resumen)
El pipeline de C es eficiente y validado con datos sintéticos. En la práctica el preprocesamiento lo hace Python y se usa Jupyter para visualización comparativa y generación de gráficos final.
