#include "inc.h"

int evalOneParam(char * param, image * work_img){
	int cptParam = 0, cptParam0 = 0, cptTmp = 0, fin = 0, tmpOpt1 = 0, tmpOpt2 = 0, opt = 1;
	char tmp[MAX_LENGHT_PARAM], tmpc = '0';
	
	while(fin == 0){
		
		if( isdigit(param[cptParam]) != 0 && opt == 1 ){
			cptTmp = 0;
			while(isdigit(param[cptParam]) != 0){
				tmp[cptTmp] = param[cptParam];
				cptTmp++;
				cptParam++;
			}
			tmp[cptTmp] = '\0';
			
			tmpOpt1 = atoi(tmp);
			
			opt = 0;
		}
		else if( (param[cptParam] == 'h' || param[cptParam] == 'l') && param[cptParam+1] == '(' && opt == 1 ){
			
			cptParam0 = cptParam;
			cptParam += 2;
			cptTmp = 0;
			while(isdigit(param[cptParam]) != 0){
				tmp[cptTmp] = param[cptParam];
				cptTmp++;
				cptParam++;
			}
			tmp[cptTmp] = '\0';
			
			if(param[cptParam] == ')' && emptyImagePnm(work_img[atoi(tmp)]) != 0){
				if(param[cptParam0] == 'h'){tmpOpt1 = get_hauteur(work_img[atoi(tmp)]);}
				else if(param[cptParam0] == 'l'){tmpOpt1 = get_largeur(work_img[atoi(tmp)]);}
				else{return PARAM_ERR;}
			}
			
			cptParam++;
			opt = 0;
		}
		else if( (param[cptParam] == '+' || param[cptParam] == '-' || param[cptParam] == '*' || param[cptParam] == '/') && opt == 0 ){
			if(tmpc == '+' || tmpc == '-' || tmpc == '*' || tmpc == '/'){
				     if(tmpc == '+'){tmpOpt2 += tmpOpt1;}
				else if(tmpc == '-'){tmpOpt2 -= tmpOpt1;}
				else if(tmpc == '*'){tmpOpt2 *= tmpOpt1;}
				else if(tmpc == '/'){tmpOpt2 /= tmpOpt1;}
			}
			else{
				tmpOpt2 = tmpOpt1;
			}
			tmpOpt1 = 0;
			tmpc = param[cptParam];
			cptParam++;
			opt = 1;
		}
		else if( param[cptParam] == '\0' && (opt == 0 || cptParam == 0) ){
			if(cptParam == 0){
				param[0] = '\0';
			}
			else{
				if(tmpc == '+' || tmpc == '-' || tmpc == '*' || tmpc == '/'){
					     if(tmpc == '+'){tmpOpt2 += tmpOpt1;}
					else if(tmpc == '-'){tmpOpt2 -= tmpOpt1;}
					else if(tmpc == '*'){tmpOpt2 *= tmpOpt1;}
					else if(tmpc == '/'){tmpOpt2 /= tmpOpt1;}
				}
				else{
					tmpOpt2 = tmpOpt1;
				}
				sprintf(param, "%d", tmpOpt2);
			}
			fin = 1;
		}
		else{
			return PARAM_ERR;
		}
	}
	
	return EXIT_SUCCES;
}

int instrCreate(commande com, image * work_img, int * nb_img){ /* CREATE <no> (<l> <h>)|(<no>) */
	int no_img1, largeur, hauteur;
	
	if(com->param[3][0] != '\0'){
		if(evalOneParam(com->param[2], work_img) != EXIT_SUCCES){return PARAM_ERR;}
		if(evalOneParam(com->param[3], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	}
	
	if(isint(com->param[1]) == 0 && isint(com->param[2]) == 0 && (isint(com->param[3]) == 0 || com->param[3][0] == '\0') ){
		if(atoi(com->param[1]) >= MAX_INDEX_IMG){return HIGH_IND_IMG;}
		
		no_img1 = atoi(com->param[1]);
		if(com->param[3][0] == '\0'){
			if(emptyImagePnm(work_img[atoi(com->param[2])]) != 0){
				largeur = get_largeur(work_img[atoi(com->param[2])]);
				hauteur = get_hauteur(work_img[atoi(com->param[2])]);
			}
			else{
				return MISS_PIC;
			}
		}
		else if(com->param[4][0] == '\0'){
			largeur = atoi(com->param[2]);
			hauteur = atoi(com->param[3]);
		}
		else{
			return PARAM_ERR;
		}
	
		if(emptyImagePnm(work_img[no_img1]) == 0){
			work_img[no_img1].type = 3;
			strcpy(work_img[no_img1].fichier, "CREATE");
			set_taille_image(&(work_img[no_img1]), largeur, hauteur);
			alloueImagePnm(&(work_img[no_img1]));
			initImage_Pnm(&(work_img[no_img1]));
			(*nb_img)++;
		}
		else{
			return USED_PIC;
		}
	}
	else{
		return PARAM_ERR;
	}

	return 0;
}

int instrInit(commande com, image * work_img){ /* INIT <no> */
	int no_img1;
	
	if(isint(com->param[1]) == 0 && com->param[2][0] == '\0'){
		if(atoi(com->param[1]) >= MAX_INDEX_IMG){return HIGH_IND_IMG;}
		
		no_img1 = atoi(com->param[1]);
		if(emptyImagePnm(work_img[no_img1]) != 0){
			initImage_Pnm(&(work_img[no_img1]));
		}
		else{
			return MISS_PIC;
		}
	}
	else{
		return PARAM_ERR;
	}
	return 0;
}

int instrLoad(commande com, image * work_img, int * nb_img){ /* LOAD <no> <filename> */
	char filename[MAX_LENGHT_PARAM];
	int tmp, no_img1;
	
	if(isint(com->param[1]) == 0 && ispath(com->param[2]) == 0 && com->param[3][0] == '\0'){
		if(atoi(com->param[1]) >= MAX_INDEX_IMG){return HIGH_IND_IMG;}
		
		no_img1 = atoi(com->param[1]);
		sprintf(filename, "%s%s", IMG_DIR, com->param[2]);
		if(emptyImagePnm(work_img[no_img1]) == 0){
			tmp = lireImagePnm(filename, &(work_img[no_img1]));
			if(tmp != 0){return MISS_FILE;}
			(*nb_img)++;
			printf("  Taille de l'image chargee dans l'image %d est : %dx%d (lxh) (type %d)\n", no_img1, get_largeur(work_img[no_img1]), get_hauteur(work_img[no_img1]), get_type(work_img[no_img1]));
		}
		else{
			return USED_PIC;
		}
	}
	else{
		return PARAM_ERR;
	}
	return 0;
}

int instrSave(commande com, image * work_img){ /* SAVE <no> <filename> */
	int no_img1, type, tmp;
	
	if(isint(com->param[1]) == 0 && ispath(com->param[2]) == 0 && com->param[3][0] == '\0'){
		if(atoi(com->param[1]) >= MAX_INDEX_IMG){return HIGH_IND_IMG;}
		
		no_img1 = atoi(com->param[1]);
		if(emptyImagePnm(work_img[no_img1]) != 0){
			if(com->param[3][0] == '\0'){type = 0;}
			else if(isint(com->param[3]) == 0 && atoi(com->param[3]) >= 1 && atoi(com->param[3]) <= 3){type = atoi(com->param[3]);}
			else{return PARAM_ERR;}
				
			tmp = sauverImagePnm(com->param[2], &(work_img[no_img1]), no_img1, type);
			if(tmp != 0){return OVERWRITE_FILE;}
		}
		else{
			return MISS_PIC;
		}
	}
	else{
		return PARAM_ERR;
	}
	return 0;
}

int instrPrint(commande com, image * work_img){ /* PRINT <no> [<x0> <y0> <x1> <y1>] */
	int no_img1, tmp, x0, y0, x1, y1;
	char c;
	static int no_print = 1;
	
	if(evalOneParam(com->param[2], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	if(evalOneParam(com->param[3], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	if(evalOneParam(com->param[4], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	if(evalOneParam(com->param[5], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	
	if(isint(com->param[1]) == 0){
		if(atoi(com->param[1]) >= MAX_INDEX_IMG){return HIGH_IND_IMG;}
		
		no_img1 = atoi(com->param[1]);
		if(emptyImagePnm(work_img[no_img1]) != 0){
			
			if(com->param[2][0] == '\0'){ /* PRINT de tte l'image */
				if(get_largeur(work_img[no_img1]) * get_hauteur(work_img[no_img1]) > 200){
					printf("  \033[%smL'image qui doit etre affichee a un format de %dx%d (lxh). Etes vous sur de vouloir l'afficher ? (y/n)\033[0m\n", infoColor, get_largeur(work_img[no_img1]), get_hauteur(work_img[no_img1]));
					c = getchar();
					emptyBuffer();
					if(c != 'y' && c != '1'){printf("\n"); return 0;}
				}
				printf("(PRINT no %d) Affichage de l'image %d :\n", no_print, no_img1);
				no_print++;
				tmp = printImagePnm(stdout, &(work_img[no_img1]), get_type(work_img[no_img1]), 1);
				printf("\n");
				if(tmp != 0){return OTHER;}
			}
			else if(isint(com->param[2]) == 0 && atoi(com->param[2]) > 0 && isint(com->param[3]) == 0 && atoi(com->param[3]) > 0 && isint(com->param[4]) == 0 && atoi(com->param[4]) >= atoi(com->param[2]) && atoi(com->param[4]) <= get_largeur(work_img[no_img1]) && isint(com->param[5]) == 0 && atoi(com->param[5]) >= atoi(com->param[3]) && atoi(com->param[5]) <= get_hauteur(work_img[no_img1]) && com->param[6][0] == '\0'){ /* PRINT d'une partie de l'image */
				x0 = atoi(com->param[2]);
				y0 = atoi(com->param[3]);
				x1 = atoi(com->param[4]);
				y1 = atoi(com->param[5]);
			
				tmp = printSquareImagePnm(stdout, &(work_img[no_img1]), x0, y0, x1, y1, get_type(work_img[no_img1]), 1);
				if(tmp != 0){return OTHER;}
			}
			else{
				return PARAM_ERR;
			}
		}
		else{
			return MISS_PIC;
		}
	}
	else{
		return PARAM_ERR;
	}
	
	return 0;
}

int instrCopy(commande com, image * work_img){ /* COPY <no1> <no2> */
	int no_img1, no_img2, tmp;
	
	if(isint(com->param[1]) == 0 && isint(com->param[2]) == 0 && com->param[3][0] == '\0'){
		if(atoi(com->param[1]) >= MAX_INDEX_IMG || atoi(com->param[2]) >= MAX_INDEX_IMG){return HIGH_IND_IMG;}
		
		no_img1 = atoi(com->param[1]);
		no_img2 = atoi(com->param[2]);
		if(emptyImagePnm(work_img[no_img1]) != 0 && emptyImagePnm(work_img[no_img2]) != 0){
			if( get_largeur(work_img[no_img1]) == get_largeur(work_img[no_img2]) && get_hauteur(work_img[no_img1]) == get_hauteur(work_img[no_img2]) ){
				if(get_type(work_img[no_img1]) < get_type(work_img[no_img2])){
					wrongType(stdout, com);
					set_type(&(work_img[no_img1]), get_type(work_img[no_img2]));
				}
				
				tmp = cpyImagePnm(&(work_img[no_img1]), work_img[no_img2]);
				if(tmp != 0){return OTHER;}
			}
			else{
				return OTHER;
			}
		}
		else{
			return MISS_PIC;
		}
	}
	else{
		return PARAM_ERR;
	}
	return 0;
}

int instrPaste(commande com, image * work_img){ /* PASTE <no1> <x0> <y0> <no2> [-tr <%>] */
	int no_img1, no_img2, x0, y0, tmp, i;
	char ** liste_mot;
	
	if(evalOneParam(com->param[2], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	if(evalOneParam(com->param[3], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	
	if(isint(com->param[1]) == 0 && isint(com->param[2]) == 0  && isint(com->param[3]) == 0  && isint(com->param[4]) == 0){
		if(atoi(com->param[1]) >= MAX_INDEX_IMG || atoi(com->param[4]) >= MAX_INDEX_IMG){return HIGH_IND_IMG;}
		
		no_img1 = atoi(com->param[1]);
		x0 = atoi(com->param[2]);
		y0 = atoi(com->param[3]);
		no_img2 = atoi(com->param[4]);
		
		if(emptyImagePnm(work_img[no_img1]) != 0 && emptyImagePnm(work_img[no_img2]) != 0){
			
			if(com->param[5][0] == '\0'){ /* PASTE sans parametre optionnel */
				
				if(get_type(work_img[no_img1]) < get_type(work_img[no_img2])){
					wrongType(stdout, com);
					set_type(&(work_img[no_img1]), get_type(work_img[no_img2]));
				}
				tmp = colleImagePnm(&(work_img[no_img1]), work_img[no_img2], x0, y0, NULL);
				if(tmp != 0){return OTHER;}
				
			}
			else{ /* PASTE avec parametre optionnel */
				
				liste_mot = calloc(NB_MAX_PARAM, sizeof(char*));
				for(i=0; i<NB_MAX_PARAM; i++){
					liste_mot[i] = calloc(MAX_LENGHT_PARAM, sizeof(char));
					liste_mot[i][0] = '\0';
				}
				
				for(i=5; i<NB_MAX_PARAM; i++){
					strcpy(liste_mot[i-5], com->param[i]);
				}
				
				if( (strcmp(liste_mot[0], "-tr") == 0 && isint(liste_mot[1]) == 0 && atoi(liste_mot[1]) > 0 && atoi(liste_mot[1]) <= 100)){
					
					if(get_type(work_img[no_img1]) < get_type(work_img[no_img2])){
						wrongType(stdout, com);
						set_type(&(work_img[no_img1]), get_type(work_img[no_img2]));
					}
					tmp = colleImagePnm(&(work_img[no_img1]), work_img[no_img2], x0, y0, liste_mot);
					
					for(i=0; i<NB_MAX_PARAM; i++){
						if(liste_mot[i] != NULL){free(liste_mot[i]);}
					}
					if(liste_mot != NULL){free(liste_mot);}
					
					if(tmp != 0){return OTHER;}
					
				}
				else{
					
					for(i=0; i<NB_MAX_PARAM; i++){
						if(liste_mot[i] != NULL){free(liste_mot[i]);}
					}
					if(liste_mot != NULL){free(liste_mot);}
					
					return PARAM_ERR;
					
				}
			}
		}
		else{
			return MISS_PIC;
		}
	}
	else{
		return PARAM_ERR;
	}
	return 0;
}

int instrCut(commande com, image * work_img){ /* CUT <no> <x0> <y0> <x1> <y1> */
	int no_img1, x0, y0, x1, y1, tmp;
	
	if(evalOneParam(com->param[2], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	if(evalOneParam(com->param[3], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	if(evalOneParam(com->param[4], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	if(evalOneParam(com->param[5], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	
	if(isint(com->param[1]) == 0 && atoi(com->param[1]) < MAX_INDEX_IMG && isint(com->param[2]) == 0  && isint(com->param[3]) == 0  && isint(com->param[4]) == 0  && isint(com->param[5]) == 0){
		no_img1 = atoi(com->param[1]);
		x0 = atoi(com->param[2]);
		y0 = atoi(com->param[3]);
		x1 = atoi(com->param[4]);
		y1 = atoi(com->param[5]);
		if(emptyImagePnm(work_img[no_img1]) != 0){
			tmp = couperImage(&(work_img[no_img1]), x0, y0, x1, y1);
			if(tmp != 0){return OTHER;}
		}
		else{
			return MISS_PIC;
		}
	}
	else{
		return PARAM_ERR;
	}
	
	return 0;
}

int instrAdd(commande com, image * work_img){ /* ADD <no1> <pos> <no2> */
	int no_img1, no_img2, tmp;
	
	if( isint(com->param[1]) == 0 && atoi(com->param[1]) < MAX_INDEX_IMG && isint(com->param[3]) == 0 && atoi(com->param[3]) < MAX_INDEX_IMG && (strcmp(com->param[2], "haut") == 0 || strcmp(com->param[2], "droit") == 0 || strcmp(com->param[2], "droite") == 0 || strcmp(com->param[2], "bas") == 0 || strcmp(com->param[2], "gauche") == 0) ){
		no_img1 = atoi(com->param[1]);
		no_img2 = atoi(com->param[3]);
		if(emptyImagePnm(work_img[no_img1]) != 0 && emptyImagePnm(work_img[no_img2]) != 0){
			if(get_type(work_img[no_img1]) < get_type(work_img[no_img2])){
				wrongType(stdout, com);
				set_type(&(work_img[no_img1]), get_type(work_img[no_img2]));
			}
			tmp = ajouterImage(&(work_img[no_img1]), com->param[2], &(work_img[no_img2]));
			if(tmp != 0){return OTHER;}
		}
		else{
			return MISS_PIC;
		}
	}
	else{
		return PARAM_ERR;
	}
	return 0;
}

int instrFrame(commande com, image * work_img){ /* FRAME <no> <x0> <y0> <x1> <y1> <R> <V> <B> */
	int no_img1, x0, y0, x1, y1, R, V, B, tmp;
	
	if(evalOneParam(com->param[2], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	if(evalOneParam(com->param[3], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	if(evalOneParam(com->param[4], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	if(evalOneParam(com->param[5], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	
	if(isint(com->param[1]) == 0 && atoi(com->param[1]) < MAX_INDEX_IMG && isint(com->param[2]) == 0 && isint(com->param[3]) == 0 && isint(com->param[4]) == 0 && isint(com->param[5]) == 0 && isint(com->param[6]) == 0 && atoi(com->param[6]) < 256 && isint(com->param[7]) == 0 && atoi(com->param[7]) < 256 && isint(com->param[8]) == 0 && atoi(com->param[8]) < 256){
		no_img1 = atoi(com->param[1]);
		x0 = atoi(com->param[2]);
		y0 = atoi(com->param[3]);
		x1 = atoi(com->param[4]);
		y1 = atoi(com->param[5]);
		R = atoi(com->param[6]);
		V = atoi(com->param[7]);
		B = atoi(com->param[8]);
		if(emptyImagePnm(work_img[no_img1]) != 0){
			if(get_type(work_img[no_img1]) == 1 && (R != V || R != B || (R != 1 && R != 0))){
				wrongType(stdout, com);
				if(R == V && V == B){
					set_type(&(work_img[no_img1]), 2);
				}
				else{
					set_type(&(work_img[no_img1]), 3);
				}
			}
			if(get_type(work_img[no_img1]) == 2 && (R != V || R != B)){
				wrongType(stdout, com);
				set_type(&(work_img[no_img1]), 3);
			}
			tmp = dessinCadre(&(work_img[no_img1]), x0, y0, x1, y1, R, V, B);
			if(tmp != 0){return OTHER;}
		}
		else{
			return MISS_PIC;
		}
	}
	else{
		return PARAM_ERR;
	}
	return 0;
}

int instrInv(commande com, image * work_img){  /* INV <no> */
	int no_img1;
	
	if(isint(com->param[1]) == 0 && atoi(com->param[1]) < MAX_INDEX_IMG){
		no_img1 = atoi(com->param[1]);
		if(emptyImagePnm(work_img[no_img1]) != 0){
			inverserImage(&(work_img[no_img1]));
		}
		else{
			return MISS_PIC;
		}
	}
	else{
		return PARAM_ERR;
	}
	return 0;
}

int instrKeep(commande com, image * work_img){ /* KEEP <no> R/V/B */
	int no_img1, tmp;
	
	if(isint(com->param[1]) == 0 && atoi(com->param[1]) < MAX_INDEX_IMG && (strcmp(com->param[2], "R") == 0 || strcmp(com->param[2], "V") == 0 || strcmp(com->param[2], "B") == 0) ){
		no_img1 = atoi(com->param[1]);
		if(emptyImagePnm(work_img[no_img1]) != 0){
			if( get_type(work_img[no_img1]) == 1 || get_type(work_img[no_img1]) == 2 ){
				printf("  \033[%smLe KEEP (cmd no %d) a ete applique a une image noir et blanc (type %d)... Il est donc inutile !!!\033[0m\n", errorColor, com->num, get_type(work_img[no_img1]) );
				return 0;
			}
			if(strcmp(com->param[2], "R") == 0){tmp = 1;}
			else if(strcmp(com->param[2], "V") == 0){tmp = 2;}
			else if(strcmp(com->param[2], "B") == 0){tmp = 3;}
			if(com->param[3][0] == '\0'){
				keepColorImage(&(work_img[no_img1]), tmp);
			}
			else if(strcmp(com->param[3], "pix") == 0){
				keepColorPixImage(&(work_img[no_img1]), tmp);
			}
			else{
				return PARAM_ERR;
			}
		}
		else{
			return MISS_PIC;
		}
	}
	else{
		return PARAM_ERR;
	}
	return 0;
}

int instrSetpix(commande com, image * work_img){ /* SETPIX <no> <x0> <y0> <R> <V> <B> */
	int no_img1, x0, y0, R, V, B, tmp;
	
	if(evalOneParam(com->param[2], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	if(evalOneParam(com->param[3], work_img) != EXIT_SUCCES){return PARAM_ERR;}
	
	if(isint(com->param[1]) == 0 && atoi(com->param[1]) < MAX_INDEX_IMG && isint(com->param[2]) == 0 && isint(com->param[3]) == 0 && isint(com->param[4]) == 0 && atoi(com->param[4]) < 256 && isint(com->param[5]) == 0 && atoi(com->param[5]) < 256 && isint(com->param[6]) == 0 && atoi(com->param[6]) < 256){
		no_img1 = atoi(com->param[1]);
		x0 = atoi(com->param[2]);
		y0 = atoi(com->param[3]);
		R = atoi(com->param[4]);
		V = atoi(com->param[5]);
		B = atoi(com->param[6]);
		if(emptyImagePnm(work_img[no_img1]) != 0){
			if(get_type(work_img[no_img1]) == 1 && (R != V || R != B || (R != 1 && R != 0))){
				wrongType(stdout, com);
				if(R == V && V == B){
					set_type(&(work_img[no_img1]), 2);
				}
				else{
					set_type(&(work_img[no_img1]), 3);
				}
			}
			if(get_type(work_img[no_img1]) == 2 && (R != V || R != B)){
				wrongType(stdout, com);
				set_type(&(work_img[no_img1]), 3);
			}
			tmp = set_img_pix(&(work_img[no_img1]), x0, y0, R, V, B);
			if(tmp != 0){return OTHER;}
		}
		else{
			return MISS_PIC;
		}
	}
	else{
		return PARAM_ERR;
	}
	return 0;
}

int instrFiltre(commande com, image * work_img){ /* FILTRE <no> <type> [<params>] */
	int no_img1, x0, y0, i, tmp, div;
	int ** filtre1, ** filtre2;
	
	if(isint(com->param[1]) == 0 && atoi(com->param[1]) < MAX_INDEX_IMG){
		no_img1 = atoi(com->param[1]);
		if(emptyImagePnm(work_img[no_img1]) != 0){
			if(strcmp(com->param[2], "-sobel") == 0 && com->param[3][0] == '\0'){ /* FILTRE <no> -sobel */
				
				mat_sobel(&filtre1, &filtre2, &x0, &y0);
				
				tmp = filtre_2(&(work_img[no_img1]), filtre1, filtre2, x0, y0);
				
				for(i=0; i<y0; i++){
					free(filtre1[i]);
				}
				free(filtre1);
				
				if(tmp != 0){return OTHER;}
			}
			else if(strcmp(com->param[2], "-moy") == 0 && isint(com->param[3]) == 0 && com->param[4][0] == '\0'){ /* FILTRE <no> -moy <taille> */
				if(atoi(com->param[3]) < imin(get_largeur(work_img[no_img1]), get_hauteur(work_img[no_img1]))){
					x0 = 2*atoi(com->param[3])+1;
					y0 = 2*atoi(com->param[3])+1;
					mat_moyen(&filtre1, x0, y0);
				
					tmp = filtre_1(&(work_img[no_img1]), filtre1, x0, y0, 0);
				
					for(i=0; i<y0; i++){
						free(filtre1[i]);
					}
					free(filtre1);
					
					if(tmp != 0){return OTHER;}
				}
				else{
					return PARAM_ERR;
				}
			}
			else if(strcmp(com->param[2], "-med") == 0 && isint(com->param[3]) == 0 && com->param[4][0] == '\0'){ /* FILTRE <no> -med <taille> */
				tmp = filtreMedian(&(work_img[no_img1]), atoi(com->param[3]));
				if(tmp != 0){return OTHER;}
			}
			else if(strcmp(com->param[2], "-prewitt") == 0 && com->param[3][0] == '\0'){
				mat_prewitt(&filtre1, &filtre2, &x0, &y0);
				tmp = filtre_2(&(work_img[no_img1]), filtre1, filtre2, x0, y0);
				for(i=0; i<y0; i++){
					free(filtre1[i]);
				}
				free(filtre1);
				if(tmp != 0){return OTHER;}
			}
			else if(strcmp(com->param[2], "-roberts") == 0 && com->param[3][0] == '\0'){
				mat_roberts(&filtre1, &filtre2, &x0, &y0);
				tmp = filtre_2(&(work_img[no_img1]), filtre1, filtre2, x0, y0);
				for(i=0; i<y0; i++){
					free(filtre1[i]);
				}
				free(filtre1);
				if(tmp != 0){return OTHER;}
			}
			else if(strcmp(com->param[2], "-mdif") == 0 && com->param[3][0] == '\0'){
				mat_mdif(&filtre1, &filtre2, &x0, &y0);
				tmp = filtre_2(&(work_img[no_img1]), filtre1, filtre2, x0, y0);
				for(i=0; i<y0; i++){
					free(filtre1[i]);
				}
				free(filtre1);
				if(tmp != 0){return OTHER;}
			}
			else if(strcmp(com->param[2], "-f1") == 0 && isint(com->param[3]) == 0  && isint(com->param[4]) == 0 && com->param[5][0] != '\0' && ( com->param[6][0] == '\0' || isint(com->param[6]) == 0) &&  com->param[7][0] == '\0'){ /*FILTRE <no> -f1 <x0> <y0> <mat> [<div>]*/
				
				x0 = atoi(com->param[3]);
				y0 = atoi(com->param[4]);
				tmp = read_mat(&filtre1, x0, y0, com->param[5]);
				if(tmp != 0){return PARAM_ERR;}
				
				if(isint(com->param[6]) == 0){div = atoi(com->param[6]);}
				else{div = 0;}
				
				tmp = filtre_1(&(work_img[no_img1]), filtre1, x0, y0, div);
				
				for(i=0; i<y0; i++){
					free(filtre1[i]);
				}
				free(filtre1);
				
				if(tmp != 0){return OTHER;}
			}
			else if(strcmp(com->param[2], "-f2") == 0 && isint(com->param[3]) == 0  && isint(com->param[4]) == 0 && com->param[5][0] != '\0' && com->param[6][0] != '\0' &&  com->param[7][0] == '\0'){ /*FILTRE <no> -f2 <x0> <y0> <mat1> <mat2>*/
				
				x0 = atoi(com->param[3]);
				y0 = atoi(com->param[4]);
				tmp = read_mat(&filtre1, x0, y0, com->param[5]);
				if(tmp != 0){return PARAM_ERR;}
				tmp = read_mat(&filtre2, x0, y0, com->param[6]);
				if(tmp != 0){return PARAM_ERR;}
				
				tmp = filtre_2(&(work_img[no_img1]), filtre1, filtre2, x0, y0);
				
				for(i=0; i<y0; i++){
					free(filtre1[i]);
				}
				free(filtre1);
				
				if(tmp != 0){return OTHER;}
			}
			else{
				return PARAM_ERR;
			}
		}
		else{
			return MISS_PIC;
		}
	}
	else{
		return PARAM_ERR;
	}
	return 0;
}

int instrClose(commande com, image * work_img, int * nb_img){ /* CLOSE <no> */
	int no_img1, tmp;
	
	if(isint(com->param[1]) == 0 && atoi(com->param[1]) < MAX_INDEX_IMG){
		no_img1 = atoi(com->param[1]);
		if(emptyImagePnm(work_img[no_img1]) != 0){
			tmp = deleteImagePnm(&(work_img[no_img1]));
			(*nb_img)--;
			if(tmp != 0){return OTHER;}
		}
		else{
			return MISS_PIC;
		}
	}
	else{
		return PARAM_ERR;
	}
	return 0;
}

int structFin(image * work_img, int * nb_img){ /* FIN */
	int i;
	
	if(*nb_img != 0){
		printf("  \033[%smToutes les images n'ont pas ete fermees (%d images ouvertes)\033[0m\n", errorColor, *nb_img);
	}
	for(i=0; i<MAX_INDEX_IMG; i++){
		if(emptyImagePnm(work_img[i]) != 0){
			deleteImagePnm(&(work_img[i]));
		}
	}
	*nb_img = 0;
	return FIN_PROG;
}










