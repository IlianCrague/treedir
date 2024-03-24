#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"
#include "parse.h"
#include "commands.h"


void sandbox(noeud* arbre){
	printf("'%s'\n",chemin_to_parent(arbre, "/")->nom);
	
}

int main(int argc, char * argv[]) {
	FILE* file=NULL;

	if (argc == 1) file = stdin;
	else if (argc == 2) file = fopen(argv[1], "r");
	assert(file != NULL);

	noeud * arbre = init_arbre();
	noeud * tmp = arbre;
	char **cmd;
	while ((cmd = read_command(file)) != NULL){
		int argc = 0;
		for (char **cur = cmd; *cur != NULL; ++cur) ++argc;
		tmp = exec_command(arbre, argc, cmd);
		for (char **cur = cmd; *cur != NULL; ++cur) free(*cur);
		free(cmd);
		if (tmp == NULL) {
			printf("La commande a échoué.\n");
			free_noeud(arbre->racine);
			fclose(file);
			return EXIT_FAILURE;
		}
		arbre = tmp;
	}
	free_noeud(arbre->racine);
	fclose(file);
}
