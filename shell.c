#include "inc.h"

int litShellCommande(char ** cmd, int * debut, int exec, int argc, char ** argv, FILE * logs){
	int i;
	char c;
	
	if(*debut != 1){
		if(exec == 1){
			printf("%s(exec)$ ", PROMPT);
			strcpy(cmd[0], "execR");
			i = 1;
		}
		else{
			printf("%s$ ", PROMPT);
			i = 0;
		}
		
		c = '0';
		while(c != '\n'){
			scanf("%s", cmd[i]);
			if(i == 0){fprintf(logs, "%s", cmd[i]);}else{fprintf(logs, " %s", cmd[i]);}
			c = getchar();
			i++;
		}
		fprintf(logs, "\n");
	}
	else{
		*debut = 0;
		printf("%s$ ", PROMPT);
		for(i=1; i<argc; i++){
			strcpy(cmd[i-1], argv[i]);
			printf("%s ", cmd[i-1]);
			if(i == 1){fprintf(logs, "%s", cmd[i-1]);}else{fprintf(logs, " %s", cmd[i-1]);}
		}
		printf("\n");
		fprintf(logs, "\n");
	}
	
	return 0;
}

int shellScenario(char ** cmd){
	char filename[MAX_LENGHT_PARAM];
	commande com_liste = NULL;
	int tmp;
	char c;
	
	if(cmd[1][0] == '\0'){
		printf("  Vous devez specifier un fichier a executer\n\n");
	}
	else if(cmd[2][0] != '\0'){
		printf("  La commande \"scenario\" prend un seul argument. Prototype : \033[%smscenario <filename>\033[0m\n\n", protoColor);
	}
	else{
		sprintf(filename, "%s%s", SCRIPT_DIR, cmd[1]);
		printf("  \033[%smLecture du fichier de commandes \"%s\" :\033[0m\n", titreColor, filename);
		tmp = lireCommande(&com_liste, filename);
		if(tmp == 0){
			printCommandeLst(com_liste);
			printf("  Fichier de script charge. L'executer ? (y/n) ");
			c = getchar();
			emptyBuffer();
			if(c == '1' || c == 'y'){
				printf("\n");
				tmp = executeCommande(&com_liste);
				tmp = supprimeCommande(&com_liste);
			}
			else{
				tmp = supprimeCommande(&com_liste);
			}
			printf("\n");
		}
		else if(tmp == 1){
			printf("  \033[%smErreur d'ouverture du fichier de commande : %s\033. Il ne peut donc pas etre charge[0m\n\n", errorColor, cmd[1]);
		}
		else{
			printf("  \033[%smUne erreur a ete detectee dans le fichier. Il a donc ete abandonne\033[0m\n", errorColor);
		}
	}
	
	return 0;
}

int shellInitialise(image * work_img){
	int i;
	
	for(i=0; i<MAX_INDEX_IMG; i++){
		if(emptyImagePnm(work_img[i]) != 0){
			deleteImagePnm(&(work_img[i]));
		}
	}
	printf("\n");
	
	return 0;
}

int shellExec(int * exec){
	*exec = 1;
	printf("\n");
	printf("  Vous entrez dans la section d'execution directe. Pour en sortir, tapez \"exit\" ou \"q\"\n");
	printf("  Pour voir les commandes possibles a executer, tapez \"help\"\n");
	printf("  Ce menu vous permet d'executer directement dans l'environnement de travail les commandes que vous tapez\n");
	printf("\n");
	
	return 0;
}

int shellExecReal(char ** cmd, image * work_img, int * exec){
	commande com = NULL;
	int i, tmp;
	
	if(strcmp(cmd[1], "exit") == 0 || strcmp(cmd[1], "q") == 0){
		*exec = 0;
	}
	else if(strcmp(cmd[1], "help") == 0 || strcmp(cmd[1], "h") == 0){
		     if( ( strcmp(cmd[2], "CREATE") == 0 || strcmp(cmd[2], "create") == 0 ) && cmd[3][0] == '\0' ){ printHelpCREATE(stdout);	}
		else if( ( strcmp(cmd[2], "INIT") == 0   || strcmp(cmd[2], "init") == 0   ) && cmd[3][0] == '\0' ){ printHelpINIT(stdout);	}
		else if( ( strcmp(cmd[2], "LOAD") == 0   || strcmp(cmd[2], "load") == 0   ) && cmd[3][0] == '\0' ){ printHelpLOAD(stdout);	}
		else if( ( strcmp(cmd[2], "SAVE") == 0   || strcmp(cmd[2], "save") == 0   ) && cmd[3][0] == '\0' ){ printHelpSAVE(stdout);	}
		else if( ( strcmp(cmd[2], "PRINT") == 0  || strcmp(cmd[2], "print") == 0  ) && cmd[3][0] == '\0' ){ printHelpPRINT(stdout);	}
		else if( ( strcmp(cmd[2], "COPY") == 0   || strcmp(cmd[2], "copy") == 0   ) && cmd[3][0] == '\0' ){ printHelpCOPY(stdout);	}
		else if( ( strcmp(cmd[2], "PASTE") == 0  || strcmp(cmd[2], "paste") == 0  ) && cmd[3][0] == '\0' ){ printHelpPASTE(stdout);	}
		else if( ( strcmp(cmd[2], "CUT") == 0    || strcmp(cmd[2], "cut") == 0    ) && cmd[3][0] == '\0' ){ printHelpCUT(stdout);	}
		else if( ( strcmp(cmd[2], "ADD") == 0    || strcmp(cmd[2], "add") == 0    ) && cmd[3][0] == '\0' ){ printHelpADD(stdout);	}
		else if( ( strcmp(cmd[2], "FRAME") == 0  || strcmp(cmd[2], "frame") == 0  ) && cmd[3][0] == '\0' ){ printHelpFRAME(stdout);	}
		else if( ( strcmp(cmd[2], "INV") == 0    || strcmp(cmd[2], "inv") == 0    ) && cmd[3][0] == '\0' ){ printHelpINV(stdout);	}
		else if( ( strcmp(cmd[2], "KEEP") == 0   || strcmp(cmd[2], "keep") == 0   ) && cmd[3][0] == '\0' ){ printHelpKEEP(stdout);	}
		else if( ( strcmp(cmd[2], "SETPIX") == 0 || strcmp(cmd[2], "setpix") == 0 ) && cmd[3][0] == '\0' ){ printHelpSETPIX(stdout);	}
		else if( ( strcmp(cmd[2], "FILTRE") == 0 || strcmp(cmd[2], "filtre") == 0 ) && cmd[3][0] == '\0' ){ printHelpFILTRE(stdout);	}
		else if( ( strcmp(cmd[2], "CLOSE") == 0  || strcmp(cmd[2], "close") == 0  ) && cmd[3][0] == '\0' ){ printHelpCLOSE(stdout);	}
		else if( ( strcmp(cmd[2], "FIN") == 0    || strcmp(cmd[2], "fin") == 0    ) && cmd[3][0] == '\0' ){ printHelpFIN(stdout);	}
		else{ 
			printHelpCommande(stdout);
			printf("    \033[%smcarac <no_img>\033[0m\t\t\t\t: affiche les caracteristiques d'une image (alias c)\n", protoColor);
			printf("    \033[%smusedImages\033[0m\t\t\t\t\t: affiche le numero et la taille de toutes les images utilisees dans l'environement de travail (alias u)\n", protoColor);
			printf("    \033[%smexit\033[0m\t\t\t\t\t: quitte le programme (alias q)\n", protoColor);
		}
	}
	else if(strcmp(cmd[1], "usedImages") == 0 || strcmp(cmd[1], "u") == 0){
		shellUnusedImages(work_img);
	}
	else if(strcmp(cmd[1], "carac") == 0 || strcmp(cmd[1], "c") == 0){
		shellCarac(cmd, work_img);
	}
	else if(strcmp(cmd[1], "script") == 0 || strcmp(cmd[1], "sc") == 0){
		strcpy(cmd[0], cmd[1]);
		strcpy(cmd[1], cmd[2]);
		strcpy(cmd[2], cmd[3]);
		shellScript(cmd, work_img);
	}
	else{
		for(i=0; i<9; i++){
			strcpy(cmd[i], cmd[i+1]);
		}
		cmd[9][0] = '\0';
		com = create_commande(cmd, 1);
	
		tmp = execCommande(com, work_img);
		printExecError(stdout, tmp, com);
	
		supprimeCommande(&com);
	}
	printf("\n");
	
	return 0;
}

int shellScript(char ** cmd, image * work_img){
	char filename[MAX_LENGHT_PARAM];
	commande com_liste = NULL;
	int tmp;
	char c;
	
	if(cmd[1][0] == '\0'){
		printf("  Vous devez specifier un fichier a executer\n\n");
	}
	else if(cmd[2][0] != '\0'){
		printf("  La commande \"script\" prend un seul argument. Prototype : \033[%smscript <filename>\033[0m\n\n", protoColor);
	}
	else{
		sprintf(filename, "%s%s", SCRIPT_DIR, cmd[1]);
		printf("  \033[%smLecture du fichier de commandes \"%s\" :\033[0m\n", titreColor, filename);
		tmp = lireCommande(&com_liste, filename);
		if(tmp == 0){
			printCommandeLst(com_liste);
			printf("  Fichier de script charge. L'executer ? (y/n) ");
			c = getchar();
			emptyBuffer();
			if(c == '1' || c == 'y'){
				printf("\n");
				if(com_liste != NULL){
					while(com_liste != NULL){
						tmp = execCommande(com_liste, work_img);
						printExecError(stdout, tmp, com_liste);
						if(tmp == 10){break;}
						com_liste = com_liste->next;
					}
				}
				else{
					printf("  \033[%smExecution impossible : aucune commande enregistee\033[0m\n\n", errorColor);
				}
				
				tmp = supprimeCommande(&com_liste);
			}
			else{
				tmp = supprimeCommande(&com_liste);

			}
			printf("\n");
		}
		else if(tmp == 1){
			printf("  \033[%smErreur d'ouverture du fichier de commande : %s\033. Il ne peut donc pas etre charge[0m\n\n", errorColor, cmd[1]);
		}
		else{
			printf("  \033[%smUne erreur a ete detectee dans le fichier. Il a donc ete abandonne\033[0m\n", errorColor);
		}
	}
	
	return 0;
}

int shellCarac(char ** cmd, image * work_img){
	int tmp;
	
	if(isint(cmd[1]) == 0){
		tmp = atoi(cmd[1]);
		if(emptyImagePnm(work_img[tmp]) == 1){
			printf("  Caracteristiques de l'image %d : \n", tmp);
			printf("    image creee a partir de %s\n", work_img[tmp].fichier);
			printf("    dimentions : %dx%d (lxh)\n", get_largeur(work_img[tmp]), get_hauteur(work_img[tmp]));
			printf("    type : %d\n", get_type(work_img[tmp]));
		}
		else{
			printf("  \033[%smL'image que vous tentez de voir est vide\033[0m\n", errorColor);
		}
	}
	else{
		printf("  \033[%smL'argument de la commande carac doit etre un numero d'image\033[0m\n", errorColor);
	}
	printf("\n");
	return 0;
}

int shellUnusedImages(image * work_img){
	int i, nb;
	
	printf("  \033[%smImages utilisees dans l'environnement de travail :\033[0m\n", titreColor);
	nb = 0;
	for(i=0; i<MAX_INDEX_IMG; i++){
		if(emptyImagePnm(work_img[i]) == 1){
			printf("    Image no %d,\t%dx%d (lxh),\ttype %d,\tcree par %s\n", i, get_largeur(work_img[i]), get_hauteur(work_img[i]), get_type(work_img[i]), work_img[i].fichier);
			nb++;
		}
	}
	if(nb == 0){printf("    Aucune image utilisee\n");}
	printf("\n");
	
	return 0;
}

int shellListeImages(){
	char tmp[100];
	
	printf("\n  \033[%smListe des images disponibles :\033[0m\n\n", titreColor);
	sprintf(tmp, "cd %s && ls -1 -s -h --color=auto *.pnm *.pbm *.pgm *.ppm && cd ..", IMG_DIR);
	system(tmp);
	printf("\n\n");
	return 0;
}

int shellListeScripts(){
	char tmp[100];
	printf("\n  \033[%smListe des scripts disponibles :\033[0m\n\n", titreColor);
	sprintf(tmp, "cd %s && ls -1 -h -X --color=auto *[!~$] && cd ..", SCRIPT_DIR);
	system(tmp);
	printf("\n\n");
	return 0;
}

int shellHelp(char ** cmd){
	     if(   cmd[1][0] == '\0')												  { printHelpGeneral(stdout);	}
	else if( ( strcmp(cmd[1], "exec") == 0   || strcmp(cmd[1], "e") == 0      ) && cmd[2][0] == '\0' ){ printHelpCommande(stdout);}
	else if( ( strcmp(cmd[1], "CREATE") == 0 || strcmp(cmd[1], "create") == 0 ) && cmd[2][0] == '\0' ){ printHelpCREATE(stdout);	}
	else if( ( strcmp(cmd[1], "INIT") == 0   || strcmp(cmd[1], "init") == 0   ) && cmd[2][0] == '\0' ){ printHelpINIT(stdout);	}
	else if( ( strcmp(cmd[1], "LOAD") == 0   || strcmp(cmd[1], "load") == 0   ) && cmd[2][0] == '\0' ){ printHelpLOAD(stdout);	}
	else if( ( strcmp(cmd[1], "SAVE") == 0   || strcmp(cmd[1], "save") == 0   ) && cmd[2][0] == '\0' ){ printHelpSAVE(stdout);	}
	else if( ( strcmp(cmd[1], "PRINT") == 0  || strcmp(cmd[1], "print") == 0  ) && cmd[2][0] == '\0' ){ printHelpPRINT(stdout);	}
	else if( ( strcmp(cmd[1], "COPY") == 0   || strcmp(cmd[1], "copy") == 0   ) && cmd[2][0] == '\0' ){ printHelpCOPY(stdout);	}
	else if( ( strcmp(cmd[1], "PASTE") == 0  || strcmp(cmd[1], "paste") == 0  ) && cmd[2][0] == '\0' ){ printHelpPASTE(stdout);	}
	else if( ( strcmp(cmd[1], "CUT") == 0    || strcmp(cmd[1], "cut") == 0    ) && cmd[2][0] == '\0' ){ printHelpCUT(stdout);	}
	else if( ( strcmp(cmd[1], "ADD") == 0    || strcmp(cmd[1], "add") == 0    ) && cmd[2][0] == '\0' ){ printHelpADD(stdout);	}
	else if( ( strcmp(cmd[1], "FRAME") == 0  || strcmp(cmd[1], "frame") == 0  ) && cmd[2][0] == '\0' ){ printHelpFRAME(stdout);	}
	else if( ( strcmp(cmd[1], "INV") == 0    || strcmp(cmd[1], "inv") == 0    ) && cmd[2][0] == '\0' ){ printHelpINV(stdout);	}
	else if( ( strcmp(cmd[1], "KEEP") == 0   || strcmp(cmd[1], "keep") == 0   ) && cmd[2][0] == '\0' ){ printHelpKEEP(stdout);	}
	else if( ( strcmp(cmd[1], "SETPIX") == 0 || strcmp(cmd[1], "setpix") == 0 ) && cmd[2][0] == '\0' ){ printHelpSETPIX(stdout);	}
	else if( ( strcmp(cmd[1], "FILTRE") == 0 || strcmp(cmd[1], "filtre") == 0 ) && cmd[2][0] == '\0' ){ printHelpFILTRE(stdout);	}
	else if( ( strcmp(cmd[1], "CLOSE") == 0  || strcmp(cmd[1], "close") == 0  ) && cmd[2][0] == '\0' ){ printHelpCLOSE(stdout);	}
	else if( ( strcmp(cmd[1], "FIN") == 0    || strcmp(cmd[1], "fin") == 0    ) && cmd[2][0] == '\0' ){ printHelpFIN(stdout);	}
	else if( ( strcmp(cmd[1], "ALL") == 0    || strcmp(cmd[1], "all") == 0    ) && cmd[2][0] == '\0' ){
		printHelpGeneral(stdout);printf("\n");
		printHelpCommande(stdout);printf("\n\n");
		printf("  \033[%smDetail des commandes executables sur les images :\033[0m\n\n", titreColor);
		printHelpCREATE(stdout);printf("\n");
		printHelpINIT(stdout);printf("\n");
		printHelpLOAD(stdout);printf("\n");
		printHelpSAVE(stdout);printf("\n");
		printHelpPRINT(stdout);printf("\n");
		printHelpCOPY(stdout);printf("\n");
		printHelpPASTE(stdout);printf("\n");
		printHelpCUT(stdout);printf("\n");
		printHelpADD(stdout);printf("\n");
		printHelpFRAME(stdout);printf("\n");
		printHelpINV(stdout);printf("\n");
		printHelpKEEP(stdout);printf("\n");
		printHelpSETPIX(stdout);printf("\n");
		printHelpFILTRE(stdout);printf("\n");
		printHelpCLOSE(stdout);printf("\n");
		printHelpFIN(stdout);
	}
	else{
		printf("  Pas de help pour cet element\n");
	}
	printf("\n");
	return 0;
}

int shellUnknow(char ** cmd){
	int i;
	
	if(secretPrint(cmd) != 0){
		printf("  Commande \" ");
		for(i=1; i<NB_MAX_PARAM; i++){
			if(cmd[i][0] != '\0'){printf("%s ", cmd[i]);}
			else{break;}
		}
		printf("\" inconnue\n\n");
	}
	return 0;
}




