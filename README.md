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
python scripts/generate_data.py
```

2. Compilar y ejecutar el pipeline C local:

```bash
bash scripts/run_c.sh
```

3. Ejecutar la comparación rápida (local):

```bash
bash scripts/run_comparison.sh
```

4. (Opcional) Iniciar Jupyter local si se desea:

```bash
jupyter notebook
```

### 3.2 Modo contenedores (Docker + docker-compose)

1. Generar los datos sintéticos y pipeline C dentro de contenedor:

```bash
docker-compose run --rm c-builder
```

2. Iniciar servidor Jupyter en contenedor para análisis comparativo:

```bash
docker-compose up jupyter
```

- Abrir `http://localhost:8888` y cargar `notebooks/comparison.ipynb`.

3. Ejecutar comparación rápida en contenedor (ya contiene una llamada a c-builder):

```bash
cd c:/Users/aaron/Desktop/eval3_IA/eval3
bash scripts/run_comparison.sh
```