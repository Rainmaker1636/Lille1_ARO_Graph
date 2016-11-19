#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#include "../include/graphe.h"

typedef enum {ROUGE=0, BLEU=1, VERT=2} tCouleur;
typedef tCouleur tTabCouleurs[MAX_SOMMETS];

void colorate(tGraphe graph, tNumeroSommet exculded, tTabCouleurs tab)
{
	int i;
	tCouleur b = 1;
	
	for (i=0;i<grapheNbSommets(graph);i++)
		if (i != exculded)
			tab[i] = b;
}

void shortest(tGraphe graph, tNomSommet s, tTabCouleurs tab)
{
	tFileSommets file = fileSommetsAlloue();;
	tCouleur r = 0;
	tCouleur b = 1;
	tCouleur v = 2;
	tNumeroSommet tmp;
	int i;
	int d[MAX_SOMMETS] = {0};
	tNumeroSommet pred[MAX_SOMMETS] = {0};
	
	// colorate all nodes in blue excepted s
	colorate(graph,grapheChercheSommetParNom(graph,s),tab);
	
	// colorate s in green
	tab[grapheChercheSommetParNom(graph,s)] = v;
	fileSommetsEnfile (file, grapheChercheSommetParNom(graph,s));
	
	//d(s) = 0
	d[grapheChercheSommetParNom(graph,s)] = 0;
	
	while (file != NULL)
	{
		tmp  = fileSommetsDefile(file);
		
		// check neighbours
		for (i=0; i<grapheNbVoisinsSommet(graph,tmp); i++)
		{
			// check if the node isn't visited yet
			if (tab[grapheVoisinSommetNumero(graph,tmp,i)] == b)
			{
				// colorate the node in green
				tab[grapheVoisinSommetNumero(graph,tmp,i)] = v;
				
				// calculate d(y) n pred(y)
				d[grapheVoisinSommetNumero(graph,tmp,i)] = d[tmp] + 1;
				pred[grapheVoisinSommetNumero(graph,tmp,i)] = tmp;
				
				//display
				printf("d[%d]=%d , pred[%d]=%d\n",
					grapheVoisinSommetNumero(graph,tmp,i),d[grapheVoisinSommetNumero(graph,tmp,i)],
					grapheVoisinSommetNumero(graph,tmp,i),pred[grapheVoisinSommetNumero(graph,tmp,i)]);
				
				// put it in the fifo
				fileSommetsEnfile (file,grapheVoisinSommetNumero(graph,tmp,i));
			}
		}
		// colorate the node
		tab[tmp] = r;
	}
	
	free(file);
	return;
}


int main(int argc, char **argv)
{
	if (argc<3) 
    halt("Usage : %s FichierGraphe SommetDepart\n", argv[0]);
  tGraphe graph;
  tNomSommet sommet;
  tTabCouleurs tab;
  
  graph = grapheAlloue();
  grapheChargeFichier(graph, argv[1]);
  strcpy(sommet,argv[2]);
  
  shortest(graph,sommet,tab);
  
  free(graph);
	exit(EXIT_SUCCESS);
}
