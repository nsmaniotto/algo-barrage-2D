/******************************************************************************

Date : 02/06/2020

Auteur : Nathan Smaniotto

Github : https://github.com/nsmaniotto/algo-barrage-2D

Programme : Calculer la quantité maximale que peut contenir un barrage.
 			Barrage modélisé sous forme de variations de niveau.
 			Variations de niveau sur un espace à deux dimensions.

Version : 1.0, algorithme fonctionnel, donnée d'entrée prédéfinies.

*******************************************************************************/

#include <stdio.h>

#define MONTEE 0
#define DESCENTE 1
#define CUVE 2

int calculerContenance(int barrage[], int tailleBarrage) {
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

int main()
{
	/* INITIALISATION */
	// Barrages
	int barrage1[] = {1, 0, 2, 0, 0, 2, 0};
	int tailleBarrage1 = 7;
	
	int barrage2[] = {0, 1, 2, 4, 2, 3, 1, 0, 0, 5, 6, 3, 4};
	int tailleBarrage2 = 13;
	
	int contenanceBarrage1 = 0;
	int contenanceBarrage2 = 0;
	
	/* TRAITEMENT */
	contenanceBarrage1 = calculerContenance(barrage1, tailleBarrage1);
	contenanceBarrage2 = calculerContenance(barrage2, tailleBarrage2);
	
	printf("Contenance barrage 1 : %d \n", contenanceBarrage1);
	printf("Contenance barrage 2 : %d \n", contenanceBarrage2);

    return 0;
}
