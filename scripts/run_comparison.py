import pandas as pd
from sklearn.cluster import DBSCAN
from sklearn.preprocessing import StandardScaler
import umap
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.metrics import adjusted_rand_score, normalized_mutual_info_score
import os

os.makedirs('data/output/figures', exist_ok=True)

data = pd.read_csv('data/input/synthetic.csv')
X = StandardScaler().fit_transform(data.values)

py_labels = DBSCAN(eps=1.0, min_samples=2).fit_predict(X)
py_emb = umap.UMAP(n_components=2, random_state=42).fit_transform(X)

pd.DataFrame({'label': py_labels}).to_csv('data/output/python_dbscan_labels.csv', index=False)
pd.DataFrame({'x': py_emb[:,0], 'y': py_emb[:,1]}).to_csv('data/output/python_umap_embedding.csv', index=False)

c_labels = pd.read_csv('data/output/dbscan_labels.csv')
c_emb = pd.read_csv('data/output/umap_embedding.csv')

ari = adjusted_rand_score(c_labels['label'], py_labels)
nmi = normalized_mutual_info_score(c_labels['label'], py_labels)
print(f'ARI (C vs Python): {ari:.4f}')
print(f'NMI (C vs Python): {nmi:.4f}')

fig, axes = plt.subplots(2, 2, figsize=(14, 12))

sns.scatterplot(x=c_emb['x'], y=c_emb['y'], hue=c_labels['label'], palette='tab10', ax=axes[0,0], s=80)
axes[0,0].set_title('C PCA (C labels)')

sns.scatterplot(x=py_emb[:, 0], y=py_emb[:, 1], hue=py_labels, palette='tab10', ax=axes[0,1], s=80)
axes[0,1].set_title('Python UMAP (Python labels)')

sns.scatterplot(x=c_emb['x'], y=c_emb['y'], hue=py_labels, palette='tab10', ax=axes[1,0], s=80)
axes[1,0].set_title('C PCA (Python labels)')

sns.scatterplot(x=py_emb[:, 0], y=py_emb[:, 1], hue=c_labels['label'], palette='tab10', ax=axes[1,1], s=80)
axes[1,1].set_title('Python UMAP (C labels)')

plt.tight_layout()
plt.savefig('data/output/figures/comparison.png')
print('Plots saved to data/output/figures/comparison.png')

print('DBSCAN labels C:', c_labels['label'].value_counts().to_dict())
print('DBSCAN labels Python:', pd.Series(py_labels).value_counts().to_dict())