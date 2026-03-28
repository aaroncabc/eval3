#!/bin/bash
set -e

echo "Generando datos sintéticos..."
docker-compose run --rm jupyter python scripts/generate_data.py

echo "Ejecutando pipeline C via Docker..."
docker-compose run --rm c-builder

echo "Ejecutando comparación Python y generando gráficos..."
docker-compose run --rm jupyter python scripts/run_comparison.py
