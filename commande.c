#include "inc.h"


int lireCommande(commande * com_liste, char * nomFichier){
	FILE * file;
	char lecture[MAX_LENGHT_COMMANDE], tampon[128];
	char ** mots_lecture = calloc(NB_MAX_PARAM, sizeof(char*));
	char c;
	int nb_param, nb_instr, i, tmp, fin = 0, show_lecture = 0;
	
	for(i=0; i<NB_MAX_PARAM; i++){
		mots_lecture[i] = calloc(MAX_LENGHT_PARAM, sizeof(char));
		mots_lecture[i][0] = '\0';
	}
	
	/* suppression des blancs inutiles dans le fichier de script */
	sprintf(tampon, "cat %s | tr -s ' ' ' ' | sed 's/ $//g' | sed 's/^ //g' > %s.tmp.pnmedit && mv %s.tmp.pnmedit %s", nomFichier, nomFichier, nomFichier, nomFichier);
	system(tampon);
	
	file = fopen(nomFichier, "r");
	if(file == NULL){return 1;}
	
	nb_param = 0;
	nb_instr = 1;
	supprimeCommande(com_liste);
	while(feof(file) == 0 && fin == 0){
		tmp = fscanf(file, "%s", lecture);
		if(tmp != -1){
			fscanf(file, "%c", &c);
			if(c == '\n'){
				strcpy(mots_lecture[nb_param], lecture);
				
				if(show_lecture == 1){printf("(%d)%s\n", nb_param, mots_lecture[nb_param]);}
				*com_liste = ajout_queue(*com_liste, mots_lecture, nb_instr);
				nb_instr++;
				if(strcmp(mots_lecture[0], "FIN") == 0){
					fin = 1;
				}
				for(i=0; i<NB_MAX_PARAM; i++){
					mots_lecture[i][0] = '\0';
				}
				nb_param = 0;
			}
			else{
				if(nb_param >= NB_MAX_PARAM){
					printf("  \033[%smLa ligne %d a un nombre de parametres supperieur au nombre maximum de parametres autorise (%d)\033[0m\n", errorColor, nb_instr, NB_MAX_PARAM-1);
					
					fclose(file);
					
					for(i=0; i<NB_MAX_PARAM; i++){
						free(mots_lecture[i]);
					}
					free(mots_lecture);
					
					supprimeCommande(com_liste);
					
					return 2;
				}
				strcpy(mots_lecture[nb_param], lecture);
				if(show_lecture == 1){printf("(%d)%s ", nb_param, mots_lecture[nb_param]);}
				nb_param++;
			}
		}
	}
	
	if(fin != 1){printf("   \033[%smL'instruction \"FIN\" n'a pas ete reperee. Le fichier de scenario a pu etre mal lu.\033[0m\n", errorColor);}
	if(show_lecture == 1){printf("%d instr lues\n", nb_instr-1);}
	
	fclose(file);
	
	for(i=0; i<NB_MAX_PARAM; i++){
		free(mots_lecture[i]);
	}
	free(mots_lecture);
	
	return 0;
}

int printCommande(commande com_liste){
	int i;
	for(i=0; i<NB_MAX_PARAM; i++){
		if(com_liste->param[i][0] != '\0'){printf("%s ", com_liste->param[i]);}
	}
	printf("\n");
	return 0;
}

int printCommandeLst(commande com_liste){
	int i;
	commande tmp = com_liste;
	
	if(tmp != NULL){
		while(tmp != NULL){
			printf("    %.2d. ", tmp->num);
			for(i=0; i<NB_MAX_PARAM; i++){
				if(tmp->param[i][0] != '\0'){printf("%s ", tmp->param[i]);}
			}
			printf("\n");
			tmp = tmp->next;
		}
	}
	else{
		printf("    \033[%smAucune commande enregistee\033[0m\n", errorColor);
	}
	printf("\n");
	
	return 0;
}

int executeCommande(commande * com_liste){
	int i, temp;
	commande tmp = *com_liste;
	image * work_img = calloc(MAX_INDEX_IMG, sizeof(image));
	
	for(i=0; i<MAX_INDEX_IMG; i++){
		init_struct_image(&(work_img[i]));
	}
	
	printf("\n");
	if(tmp != NULL){
		while(tmp != NULL){
			temp = execCommande(tmp, work_img);
			printExecError(stdout, temp, tmp);
			tmp = tmp->next;
		}
	}
	else{
		printf("  \033[%smExecution impossible : aucune commande enregistee\033[0m\n\n", errorColor);
	}
	
	for(i=0; i<MAX_INDEX_IMG; i++){
		deleteImagePnm(&(work_img[i]));
	}
	free(work_img);
	
	
	return 0;
}

int supprimeCommande(commande * com_liste){
	commande tmp = *com_liste;
	while(tmp != NULL){
		tmp = (*com_liste)->next;
		if(*com_liste != NULL){free(*com_liste);}
		*com_liste = tmp;
	}
	if(*com_liste != NULL){
		printf("ERROR supprimeCommande !!!\n");
		return 1;
	}
	return 0;
}

int emptyCommande(commande com_liste){
	int i;
	for(i=0; i<NB_MAX_PARAM; i++){
		if(com_liste->param[i][0] != '\0'){return 1;}
	}
	return 0;
}


int execCommande(commande com, image * work_img){
	/* valeurs de retour :
		1: commande inconnue
		2: erreurs dans les parametres
		3: une image existante a ete ecrasee. Pour utiliser a nouveau un numero il faut le fermer.
		4: operation effectuee sur une image n'existant pas
		5: probleme lors de la lecture d'un fichier
		6: probleme lors de l'ecriture d'un fichier
		9: autre
		10: fin
	*/
	char ** liste_mot;
	int i, tmp, show_edit = 0;
	static int nb_img = 0;
	
	liste_mot = calloc(NB_MAX_PARAM, sizeof(char*));
	for(i=0; i<NB_MAX_PARAM; i++){
		liste_mot[i] = calloc(MAX_LENGHT_PARAM, sizeof(char));
		liste_mot[i][0] = '\0';
	}
	
	switch(com->com){
		
		case CREATE: /* CREATE <no> (<l> <h>)|(<no>) */
			if(show_edit == 1){printf("i: CREATE %s %s %s %s\n", com->param[1], com->param[2], com->param[3], com->param[4]);}
			tmp = instrCreate(com, work_img, &nb_img);
			if(show_edit == 1){printf("f: CREATE %s %s %s %s\n", com->param[1], com->param[2], com->param[3], com->param[4]);}
			if(tmp != 0){return tmp;}
			break;
		
		case INIT: /* INIT <no> */
			tmp = instrInit(com, work_img);
			if(tmp != 0){return tmp;}
			break;
		
		case LOAD: /* LOAD <no> <filename> */
			tmp = instrLoad(com, work_img, &nb_img);
			if(tmp != 0){return tmp;}
			break;
		
		
		case SAVE: /* SAVE <no> <filename> */
			tmp = instrSave(com, work_img);
			if(tmp != 0){return tmp;}
			break;
			
		case PRINT: /* PRINT <no> [<x0> <y0> <x1> <y1>] */
			if(show_edit == 1){printf("i: CREATE %s %s %s %s %s\n", com->param[1], com->param[2], com->param[3], com->param[4], com->param[5]);}
			tmp = instrPrint(com, work_img);
			if(show_edit == 1){printf("f: CREATE %s %s %s %s %s\n", com->param[1], com->param[2], com->param[3], com->param[4], com->param[5]);}
			if(tmp != 0){return tmp;}
			break;
		
		case COPY: /* COPY <no1> <no2> */
			tmp = instrCopy(com, work_img);
			if(tmp != 0){return tmp;}
			break;
		
		case PASTE: /* PASTE <no1> <x0> <y0> <no2> */
			if(show_edit == 1){printf("i: PASTE %s %s %s %s\n", com->param[1], com->param[2], com->param[3], com->param[4]);}
			tmp = instrPaste(com, work_img);
			if(show_edit == 1){printf("f: PASTE %s %s %s %s\n", com->param[1], com->param[2], com->param[3], com->param[4]);}
			if(tmp != 0){return tmp;}
			break;
		
		case CUT: /* CUT <no> <x0> <y0> <x1> <y1> */ 
			if(show_edit == 1){printf("i: CUT %s %s %s %s %s\n", com->param[1], com->param[2], com->param[3], com->param[4], com->param[5]);}
			tmp = instrCut(com, work_img);
			if(show_edit == 1){printf("f: CUT %s %s %s %s %s\n", com->param[1], com->param[2], com->param[3], com->param[4], com->param[5]);}
			if(tmp != 0){return tmp;}
			break;
		
		case ADD: /* ADD <no1> <pos> <no2> */
			tmp = instrAdd(com, work_img);
			if(tmp != 0){return tmp;}
			break;
		
		case FRAME: /* FRAME <no> <x0> <y0> <x1> <y1> <R> <V> <B> */
			if(show_edit == 1){printf("i: FRAME %s %s %s %s %s %s %s %s\n", com->param[1], com->param[2], com->param[3], com->param[4], com->param[5], com->param[6], com->param[7], com->param[8]);}
			tmp = instrFrame(com, work_img);
			if(show_edit == 1){printf("f: FRAME %s %s %s %s %s %s %s %s\n", com->param[1], com->param[2], com->param[3], com->param[4], com->param[5], com->param[6], com->param[7], com->param[8]);}
			if(tmp != 0){return tmp;}
			break;
		
		case INV: /* INV <no> */
			tmp = instrInv(com, work_img);
			if(tmp != 0){return tmp;}
			break;
		
		case KEEP: /* KEEP <no> R/V/B */
			tmp = instrKeep(com, work_img);
			if(tmp != 0){return tmp;}
			break;
		
		case SETPIX: /* SETPIX <no> <x0> <y0> <R> <V> <B> */
			if(show_edit == 1){printf("i: SETPIX %s %s %s %s %s %s\n", com->param[1], com->param[2], com->param[3], com->param[4], com->param[5], com->param[6]);}
			tmp = instrSetpix(com, work_img);
			if(show_edit == 1){printf("f: SETPIX %s %s %s %s %s %s\n", com->param[1], com->param[2], com->param[3], com->param[4], com->param[5], com->param[6]);}
			if(tmp != 0){return tmp;}
			break;
		
		case FILTRE: /* FILTRE <no> <type> [<params>] */
			tmp = instrFiltre(com, work_img);
			if(tmp != 0){return tmp;}
			break;
		
		case CLOSE: /* CLOSE <no> */
			tmp = instrClose(com, work_img, &nb_img);
			if(tmp != 0){return tmp;}
			break;
		
		case FIN: /* FIN */
			tmp = structFin(work_img, &nb_img);
			if(tmp != 0){return tmp;}
			break;
		
		default:
			return COMMANDE_INCONNUE;
	}
	
	
	for(i=0; i<NB_MAX_PARAM; i++){
		if(liste_mot[i] != NULL){free(liste_mot[i]);}
	}
	if(liste_mot != NULL){free(liste_mot);}
	
	return 0;
}

commande ajout_queue(commande com_liste, char ** commande_txt, int no_instr){
	int i;
	commande tmp;
	commande new_com = create_commande(commande_txt, no_instr);
	
	
	if(commande_txt[0][0] == '#'){
		free(new_com);
	}
	else if(new_com->com != VOID){
		if(com_liste == NULL){
			return new_com;
		}
		else{
			tmp = com_liste;
			while(tmp->next != NULL){
				tmp = tmp->next;
			}
			tmp->next = new_com;
		}
	}
	else{
		printf("  \033[%smLa commande no %d \"%s", errorColor, no_instr, commande_txt[0]);
		for(i=1; i<NB_MAX_PARAM; i++){
			if(commande_txt[i][0] != '\0'){printf(" %s", commande_txt[i]);}
		}
		printf("\" n'a pas ete reconnue. Elle est donc ignoree\033[0m\n");
		
		free(new_com);
	}
	
	return com_liste;
}

commande create_commande(char ** commande_txt, int no_instr){
	int i;
	commande new_com = calloc(1,sizeof(*new_com));
	if(new_com == NULL){
		return NULL;
	}
	
	if(strcmp(commande_txt[0], "CREATE") == 0 || strcmp(commande_txt[0], "create") == 0){
		new_com->com = CREATE;
	}
	else if(strcmp(commande_txt[0], "INIT") == 0 || strcmp(commande_txt[0], "init") == 0){
		new_com->com = INIT;
	}
	else if(strcmp(commande_txt[0], "LOAD") == 0 || strcmp(commande_txt[0], "load") == 0){
		new_com->com = LOAD;
	}
	else if(strcmp(commande_txt[0], "SAVE") == 0 || strcmp(commande_txt[0], "save") == 0){
		new_com->com = SAVE;
	}
	else if(strcmp(commande_txt[0], "PRINT") == 0 || strcmp(commande_txt[0], "print") == 0){
		new_com->com = PRINT;
	}
	else if(strcmp(commande_txt[0], "COPY") == 0 || strcmp(commande_txt[0], "copy") == 0){
		new_com->com = COPY;
	}
	else if(strcmp(commande_txt[0], "PASTE") == 0 || strcmp(commande_txt[0], "paste") == 0){
		new_com->com = PASTE;
	}
	else if(strcmp(commande_txt[0], "CUT") == 0 || strcmp(commande_txt[0], "cut") == 0){
		new_com->com = CUT;
	}
	else if(strcmp(commande_txt[0], "ADD") == 0 || strcmp(commande_txt[0], "add") == 0){
		new_com->com = ADD;
	}
	else if(strcmp(commande_txt[0], "FRAME") == 0 || strcmp(commande_txt[0], "frame") == 0){
		new_com->com = FRAME;
	}
	else if(strcmp(commande_txt[0], "INV") == 0 || strcmp(commande_txt[0], "inv") == 0){
		new_com->com = INV;
	}
	else if(strcmp(commande_txt[0], "KEEP") == 0 || strcmp(commande_txt[0], "inv") == 0){
		new_com->com = KEEP;
	}
	else if(strcmp(commande_txt[0], "SETPIX") == 0 || strcmp(commande_txt[0], "setpix") == 0){
		new_com->com = SETPIX;
	}
	else if(strcmp(commande_txt[0], "CLOSE") == 0 || strcmp(commande_txt[0], "close") == 0){
		new_com->com = CLOSE;
	}
	else if(strcmp(commande_txt[0], "FILTRE") == 0 || strcmp(commande_txt[0], "filtre") == 0){
		new_com->com = FILTRE;
	}
	else if(strcmp(commande_txt[0], "FIN") == 0 || strcmp(commande_txt[0], "fin") == 0){
		new_com->com = FIN;
	}
	else{
		new_com->com = VOID;
		return new_com;
	}
	
	for(i=0; i<NB_MAX_PARAM; i++){
		strcpy(new_com->param[i], commande_txt[i]);
	}
	new_com->num = no_instr;
	
	new_com->next = NULL;
	
	return new_com;
}














