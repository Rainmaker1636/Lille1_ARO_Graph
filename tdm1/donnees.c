#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/graphe.h"

int main(int argc, char *argv[]) 
{
	if (argc<2) 
    halt("Usage : %s FichierGraphe\n", argv[0]);

  tGraphe graphe;
  tNomSommet nom_s;
  int i;
  int max_v=0;
  int nb_v=0;
  int nb_s=0;
 
 	/* alloc & init graph */
  graphe = grapheAlloue();  
  grapheChargeFichier(graphe, argv[1]);
  
	nb_s = grapheNbSommets(graphe);
	
	for (i=0;i<nb_s;i++)
	{
		grapheRecupNomSommet(graphe, i, nom_s);
		nb_v = grapheNbVoisinsSommet(graphe,grapheChercheSommetParNom(graphe,nom_s));
		if (nb_v == 0)
			printf("Sommet %s, sans voisins\n",nom_s);
		if (max_v < nb_v)
			max_v = nb_v;
	}
	
	for (i=0;i<nb_s;i++)
	{
		grapheRecupNomSommet(graphe, i, nom_s);
		nb_v = grapheNbVoisinsSommet(graphe,grapheChercheSommetParNom(graphe,nom_s));
		if (nb_v == max_v)
			printf("Sommet %s, avec %d voisins\n",nom_s,nb_v);
	}


  grapheLibere(graphe);
  exit(EXIT_SUCCESS);
}
