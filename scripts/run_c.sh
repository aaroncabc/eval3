#!/bin/bash
set -e

echo "Compilando proyecto C..."
make all

echo "Ejecutando pipeline C..."
./eval3_c

echo "Salida C generada en data/output"
