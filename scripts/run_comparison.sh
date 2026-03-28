#!/bin/bash
set -e

python scripts/generate_data.py

echo "Ejecutando pipeline C via Docker..."
docker-compose run --rm c-builder

echo "Ejecutando notebook comparativo (sin bloqueo):"
# usa papermill si se quiere reproducir automático
python - <<'PY'
import pandas as pd
from pathlib import Path

c_labels = pd.read_csv('data/output/dbscan_labels.csv')
python_labels = pd.read_csv('data/output/dbscan_labels.csv')

print('DBSCAN labels C:', c_labels['label'].value_counts().to_dict())
print('DBSCAN labels Python (mock):', python_labels['label'].value_counts().to_dict())
PY

echo "Listo"
