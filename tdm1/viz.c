#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include "../include/graphe.h"

void graphe2visu(tGraphe graphe, char *outfile) 
{
	FILE *fic;
	char commande[80];
	char dotfile[80];
	int ret;
	
	int nbSommets;
	int i,k;
	tNomSommet origine;
	tNomSommet destination;

	strcpy(dotfile, outfile);
	strcat(dotfile, ".dot");
	fic = fopen(dotfile, "w");
	if (fic==NULL)
		halt ("Ouverture du fichier %s en écriture impossible\n", dotfile);
		
	fprintf(fic, "digraph {\n");
	
	nbSommets = grapheNbSommets(graphe);
	for (i=0;i<nbSommets;i++)
	{
		grapheRecupNomSommet(graphe, i, origine);
		for (k=0;k<nbSommets;k++)
			if (grapheExisteArcEntre(graphe,i,k))
			{
				grapheRecupNomSommet(graphe, k, destination);
				printf("%s -> %s;\n", origine, destination);
				fprintf(fic, " %s -> %s;\n", origine, destination);
			}
	}
	fprintf(fic, "}");
	
	fclose(fic);
	
	sprintf(commande, "dot -Tps %s -o %s", dotfile, outfile);
	ret = system(commande);
	
	if (WEXITSTATUS(ret))
		halt("La commande suivante a échouée\n%s\n", commande);
}

int main(int argc, char *argv[]) 
{
  if (argc<3) 
  	halt("Usage : %s FichierGraphe outfile\n", argv[0]);
  	
  tGraphe graphe;
  
  /* alloc & init graph */
  graphe = grapheAlloue();  
  grapheChargeFichier(graphe,  argv[1]);

	/* generate output */
	graphe2visu(graphe, argv[2]);

  grapheLibere(graphe);
  exit(EXIT_SUCCESS);
}
