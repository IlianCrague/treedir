#include "parse.h"
#include "arbre.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define TAILLE_MAX 1024

char **read_command(FILE *file){
	char *ligne =malloc(TAILLE_MAX);
	if (fgets(ligne, TAILLE_MAX, file) == NULL) {
		free(ligne);
		return NULL;
	}
	
	ligne[strcspn(ligne, "\r\n")] = 0;

	printf("> %s\n", ligne);
	char **args = split_string(ligne, " ");
	free(ligne);
	return args;
}
