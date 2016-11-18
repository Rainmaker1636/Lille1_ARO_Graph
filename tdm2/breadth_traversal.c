#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/graphe.h"

typedef enum {ROUGE=0, BLEU=1, VERT=2} tCouleur;
typedef tCouleur tTabCouleurs[MAX_SOMMETS];

static tTabCouleurs tab;

void colorate(tGraphe graph, tNumeroSommet exculded)
{
	int i;
	tCouleur b = 1;
	
	for (i=0;i<grapheNbSommets(graph);i++)
		if (i != exculded)
			tab[i] = b;
}

void breadth(tGraphe graph, tNomSommet s)
{
	tFileSommets file;
	file = fileSommetsAlloue();
	tCouleur r = 0;
	tCouleur b = 1;
	tCouleur v = 2;
	tNumeroSommet tmp;
	tNomSommet name;
	//int nb_v;
	int i;
	
	// colorate all nodes in blue excepted s
	colorate(graph,grapheChercheSommetParNom(graph,s));
	
	// colorate s in green
	tab[grapheChercheSommetParNom(graph,s)] = v;
	fileSommetsEnfile (file, grapheChercheSommetParNom(graph,s));
	
	while (file != NULL)
	{
		tmp  = fileSommetsDefile(file);
		//nb_v = grapheNbVoisinsSommet(graph,tmp);
		for (i=0; i<grapheNbVoisinsSommet(graph,tmp); i++)
		{
			if (tab[grapheVoisinSommetNumero(graph,tmp,i)] == b)
			{
				tab[grapheVoisinSommetNumero(graph,tmp,i)] = v;
				grapheRecupNomSommet (graph, grapheVoisinSommetNumero(graph,tmp,i), name);
				printf("%s ",name);
				fileSommetsEnfile (file,grapheVoisinSommetNumero(graph,tmp,i));
			}
		}
		printf("\n");
		tab[tmp] = r;
	}
	
	free(file);
}


int main(int argc, char **argv)
{
	if (argc<3) 
    halt("Usage : %s FichierGraphe SommetDepart\n", argv[0]);
    
  tGraphe graph;
  tNomSommet sommet;
  
  graph = grapheAlloue();
  grapheChargeFichier(graph, argv[1]);
  strcpy(sommet,argv[2]);
  printf(">>%s\n",sommet);
  
  grapheAffiche(graph);
  printf("-----\n");
  breadth(graph,sommet);

	
	free(graph); 
	return 0;
}
