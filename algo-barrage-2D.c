/******************************************************************************

Date : 02/07/2020

Auteur : Nathan Smaniotto

Github : https://github.com/nsmaniotto/algo-barrage-2D

Programme : Calculer la quantité maximale que peut contenir un barrage.
 			Barrage modélisé sous forme de variations de niveau.
 			Variations de niveau sur un espace à deux dimensions.

Version : 1.3, algorithme fonctionnel
		  Une seule donnée d'entrée, modifiable manuellement (lignes 208, 209).
		  Visualisation graphique du barrage.
		  Visualisation graphique de la contenance du barrage.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MONTEE 0
#define DESCENTE 1
#define CUVE 2

#define NE_PAS_AJOUTER_CONTENANCE 0
#define AJOUTER_CONTENANCE 1

#define CASE_VIDE 0
#define CASE_PLEINE 1
#define CASE_CONTENANCE 2

#define CARACTERE_CASE_VIDE " "
#define CARACTERE_CASE_PLEINE 219
#define CARACTERE_CASE_CONTENANCE 177

int calculerContenance(int barrage[], int tailleBarrage, int ajouterContenance, int (*graphiqueBarrage)[tailleBarrage]) {
	/* INITIALISATION */
	int contexte = MONTEE; // Au début nous passons du niveau par défaut : 0, à un niveau forcément >=
	int contenanceBarrage = 0;
	int niveauMaximum = 0;
	int niveauPrecedent = 0;
	int dernierNiveauTraite = 0;	
	int i, j, k;
	
	
	/* TRAITEMENT */
	// Pour tous les niveaux du barrage
	for(i = 0; i < tailleBarrage; i++) {
		
		// Mettre à jour le contexte, ici nous traitons une montée
		if(barrage[i] > niveauPrecedent) {
			if((contexte == DESCENTE) || (contexte == CUVE)) {
				contexte = CUVE;
			} else {
				contexte = MONTEE;
			}
			
			// Si en plus de cela nous sommes dans une cuve, alors nous traitons le niveau rencontré
			if(contexte == CUVE) {
					
				// Traiter le cas de plusieurs cuves dans le barrage
				if(barrage[i] < dernierNiveauTraite) {
					// Mettre à jour le dernier niveau traité
					dernierNiveauTraite = niveauPrecedent;
				}
				
				// Traiter le cas où on peut monter de plusieurs niveau en un seul changement de position, donc traiter tous les niveaux intermédiaires
				for(k = niveauPrecedent + 1; (k <= barrage[i]) && k <= niveauMaximum; k++) {
					
					j = i - 1; // Nous nous plaçons à la position précédente
					
					while(barrage[j] < k) {
						if(ajouterContenance) {
							graphiqueBarrage[k][j] = CASE_CONTENANCE;
						}
						
						j--;
					}
					
					// Mettre à jour la contenance grâce à la différence des deux indices
					contenanceBarrage += i - j - 1;
					
					// Mettre à jour le dernier niveau traité
					dernierNiveauTraite = k;
				}				
			}
			
		} else { // Nous sommes dans une descente
			
			contexte = DESCENTE;
		
			// Mettre à jour le dernier niveau traité afin de déterminer le fond d'une cuve
			dernierNiveauTraite = barrage[i];
			
		}
		
		// Mettre à jour le niveau maximum rencontré et traité
		if(barrage[i] > niveauMaximum) {
			niveauMaximum = barrage[i];
		}
		
		// Mettre à jour le niveau précédent
		niveauPrecedent = barrage[i];
	}
	
	return contenanceBarrage;
}

void afficherBarrageVide(int barrage[], int tailleBarrage) {
	/* INITIALISATION */
	int niveauMaximum = 0;
	int i, j;
	
	/* TRAITEMENT */
	// Trouver le niveau maximum
	for(i = 0; i < tailleBarrage; i++) {
		if(barrage[i] > niveauMaximum) {
			niveauMaximum = barrage[i];
		}
	}
	
	// Retour à la ligne (marge à l'affichage)
	printf("\n");
	
	// Afficher chaque ligne de cette espace à deux dimensions de haut en bas
	for(j = niveauMaximum; j >= 0; j--) {
		// Afficher chaque colonne de gauche à droite
		for(i = 0; i < tailleBarrage; i++) {
			if(barrage[i] >= j) {
				printf("%c%c", CARACTERE_CASE_PLEINE, CARACTERE_CASE_PLEINE);
			} else {
				printf("  ");
			}
		}
		
		// Retour à la ligne
		printf("\n");
	}
	
	// Retour à la ligne
	printf("\n");
}

void afficherBarrageContenance(int barrage[], int tailleBarrage) {
	/* INITIALISATION */
	int niveauMaximum = 0;
	int i, j;
	
	/* TRAITEMENT */
	// Trouver le niveau maximum
	for(i = 0; i < tailleBarrage; i++) {
		if(barrage[i] > niveauMaximum) {
			niveauMaximum = barrage[i];
		}
	}
	
	// Générer le tableau à deux dimensions
	int graphiqueBarrage[niveauMaximum + 1][tailleBarrage];
	
	// Parcourir le barrage en entrée afin de remplir ce graphique
	for(j = niveauMaximum; j >= 0; j--) {
		for(i = 0; i < tailleBarrage; i++) {
			if(barrage[i] >= j) {
				graphiqueBarrage[j][i] = CASE_PLEINE;
			} else {
				graphiqueBarrage[j][i] = CASE_VIDE;
			}
		}
	}
	
	// Ajouter la contenance à ce graphique
	calculerContenance(barrage, tailleBarrage, AJOUTER_CONTENANCE, graphiqueBarrage);
	
	// Retour à la ligne (marge à l'affichage)
	printf("\n");
	
	// Parcourir ce nouveau graphique et afficher des caractères en conséquent
	for(j = niveauMaximum; j >= 0; j--) {
		for(i = 0; i < tailleBarrage; i++) {
			if(graphiqueBarrage[j][i] == CASE_VIDE) {
				printf(CARACTERE_CASE_VIDE);
				printf(CARACTERE_CASE_VIDE);
			} else if(graphiqueBarrage[j][i] == CASE_PLEINE) {
				printf("%c", CARACTERE_CASE_PLEINE);
				printf("%c", CARACTERE_CASE_PLEINE);
			} else if(graphiqueBarrage[j][i] == CASE_CONTENANCE) {
				printf("%c", CARACTERE_CASE_CONTENANCE);
				printf("%c", CARACTERE_CASE_CONTENANCE);
			}
		}
		
		// Retour à la ligne
		printf("\n");
	}
	
	// Retour à la ligne
	printf("\n");
}

int main()
{	
	/* INITIALISATION */
	// Barrages
	int barrage[] = {0, 1, 2, 4, 2, 3, 1, 0, 0, 5, 6, 3, 4} ; // sortie attendue : 15
	int tailleBarrage = 13;
	
	int contenanceBarrage = 0;
	
	/* TRAITEMENT */
	afficherBarrageVide(barrage, tailleBarrage);
	
	afficherBarrageContenance(barrage, tailleBarrage);
	
	contenanceBarrage = calculerContenance(barrage, tailleBarrage, NE_PAS_AJOUTER_CONTENANCE, NULL);
	
	printf("Contenance du barrage barrage : %d \n", contenanceBarrage);

    return 0;
}
