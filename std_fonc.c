#include "inc.h"

int imax(int a, int b){
	if(a>b){return a;}
	else{return b;}
}

int imin(int a, int b){
	if(a<b){return a;}
	else{return b;}
}

int isint(char * s){
	unsigned int i;
	char cpy[50];
	strcpy(cpy, s);
	
	if(strlen(cpy) != 0){
		for(i=0; i<strlen(cpy); i++){
			if(isdigit(cpy[i]) == 0){
				return 1;
			}
		}
		return 0;
	}
	else{
		return 1;
	}
}

int ispath(char * s){
	if(s[0] == '\0'){
		return 1;
	}
	else{
		return 0;
	}
}

void emptyBuffer(){
	while(getchar() != '\n'){
		;
	}
}

int fichierExist(char * filename){
	FILE * test = NULL;
	test = fopen(filename, "rb");
	if(test == NULL){
		return 1;
	}
	else{
		fclose(test);
		return 0;
	}
}

void tri_bulle(int * tab, int t_long){
	int i, modif = 1, tmp = 0;
	
	t_long = t_long -1;
	
	while(modif > 0){
		modif = 0;
		for(i=0; i<t_long; i++){
			if(tab[i] > tab[i+1]){
				tmp = tab[i];
				tab[i] = tab[i+1];
				tab[i+1] = tmp;
				modif++;
			}
		}
	}
}

int mediane(int * tab, int t_long){
	int ind;
	
	tri_bulle(tab, t_long);
	ind = t_long/2 + t_long%2 - 1;
	return tab[ind];
}




