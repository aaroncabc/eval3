import numpy as np
import pandas as pd

# Generar dataset sintético simple
X1 = np.random.normal(loc=[1.0, 2.0], scale=0.1, size=(100,2))
X2 = np.random.normal(loc=[5.0, 8.0], scale=0.1, size=(100,2))
X3 = np.random.normal(loc=[10.0, 0.0], scale=0.1, size=(100,2))
X = np.vstack([X1, X2, X3])

pd.DataFrame(X, columns=['x','y']).to_csv('data/input/synthetic.csv', index=False)
print('Datos generados en data/input/synthetic.csv')
