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


char* getColor(tGraphe graph, tTabCouleurs tab, int pos)
{
	switch (tab[pos])
	{
		case 0 :
			return "red";
		case 1 :
			return "blue";
		case 2 :
			return "green";
		default :
			return "unkown";
	}
}

void graphe2visu(tGraphe graphe, char *outfile, tTabCouleurs tab) 
{
	FILE *fic;
	char commande[80];
	char dotfile[80];
	int ret;
	
	int nbSommets = grapheNbSommets(graphe);
	int i,k;
	tNomSommet origine;
	tNomSommet destination;

	strcpy(dotfile, outfile);
	strcat(dotfile, ".dot");
	fic = fopen(dotfile, "w");
	if (fic==NULL)
		halt ("Ouverture du fichier %s en écriture impossible\n", dotfile);
		
	fprintf(fic, "digraph {\n");
	
	// set color for the node
	for (i=0; i<nbSommets; i++)
	{
		grapheRecupNomSommet(graphe, i, origine);
		fprintf(fic, "%s [color=%s];\n",origine,getColor(graphe,tab,i));
	}

	for (i=0;i<nbSommets;i++)
	{
		grapheRecupNomSommet(graphe, i, origine);
		for (k=0;k<nbSommets;k++)
			if (grapheExisteArcEntre(graphe,i,k))
			{
				grapheRecupNomSommet(graphe, k, destination);
				//printf("%s -> %s;\n", origine, destination);
				fprintf(fic, " %s -> %s;\n", origine, destination);
			}
	}
	fprintf(fic, "}");
	
	fclose(fic);
	
	sprintf(commande, "dot -Tps %s -o ../output/%s", dotfile, outfile);
	ret = system(commande);
	
	if (WEXITSTATUS(ret))
		halt("La commande suivante a échouée\n%s\n", commande);
}

void breadth(tGraphe graph, tNomSommet s, tTabCouleurs tab)
{
	tFileSommets file = fileSommetsAlloue();;
	tCouleur r = 0;
	tCouleur b = 1;
	tCouleur v = 2;
	tNumeroSommet tmp;
	tNomSommet name;
	int i;
	int inc = -1;
	char out[16];
	
	// colorate all nodes in blue excepted s
	colorate(graph,grapheChercheSommetParNom(graph,s),tab);
	
	// colorate s in green
	tab[grapheChercheSommetParNom(graph,s)] = v;
	fileSommetsEnfile (file, grapheChercheSommetParNom(graph,s));
	
	printf("%s ",s);
	
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
				grapheRecupNomSommet (graph, grapheVoisinSommetNumero(graph,tmp,i), name);
				// display
				printf("%s ",name);
				// put it in the fifo
				fileSommetsEnfile (file,grapheVoisinSommetNumero(graph,tmp,i));
			}
		}
		printf("\n");
		// colorate the node
		tab[tmp] = r;
		// generate the outfile
		sprintf(out,"../output/out%d",++inc);
		graphe2visu(graph,out,tab);
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
  
  breadth(graph,sommet,tab);
  
  free(graph); 
	exit(EXIT_SUCCESS);
}
