
# algo-barrage-2D.c v1.1

Le but de ce programme est de répondre au **problème du barrage**, m'ayant été introduit en début de troisième année d'ingénieur informatique à l'INSA Toulouse, lors de l'introduction au cours d'algorithmie théorique.

Ce programme, grâce à l'algorithme qu'il implémente, permet de calculer la **contenance maximale** que peut posséder un **barrage** modélisé sous forme de variations de niveaux, ici en **deux dimensions**.

## Banque d'exemple de données

|Taille          |Entrée                                       |Sortie attendue  |
|----------------|---------------------------------------------|-----------------|
|1               |`{5}`                                        |0                |
|2               |`{1, 3}`                                     |0                |
|3               |`{1, 0, 3}`                                  |1                |
|4               |`{4, 2, 3, 5}`                               |3                |
|7               |`{1, 0, 2, 0, 0, 2, 0}`                      |5                |
|13              |`{0, 1, 2, 4, 2, 3, 1, 0, 0, 5, 6, 3, 4}`    |15               |

Pour se faire, modifier les lignes ci-dessous présentes dans le fichier `algo-barrage-2D.c` aux lignes **96** et **97** en y spécifiant l'entrée voulue ainsi que sa taille.

```c
int barrage[] = {4, 2, 3, 5}; // sortie attendue : 3
int tailleBarrage = 4;
``` 

## Améliorations possibles

- Générer aléatoirement des barrages
- Afficher graphiquement un barrage donné