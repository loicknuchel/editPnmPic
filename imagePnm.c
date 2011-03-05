#include "inc.h"

int init_struct_image(image * img){
	(*img).hauteur = 0;
	(*img).largeur = 0;
	(*img).type = 0;
	(*img).fichier[0] = '\0';
	if((*img).img != NULL){
		free((*img).img);
	}
	return 0;
}

int get_hauteur(image img){
	return img.hauteur;
}

int get_largeur(image img){
	return img.largeur;
}

int get_type(image img){
	return img.type;
}

int set_type(image * img, int type){
	(*img).type = type;
	return 0;
}

int img_indice(image img, int ligne, int colonne){
	if(ligne >= 0 && ligne > get_largeur(img)){return -1;}
	if(colonne >= 0 && colonne > get_hauteur(img)){return -1;}
	return colonne * get_largeur(img) + ligne;
}

void img_ind(image img, int * ligne, int * colonne, int ind){
	if(ind >= get_largeur(img) * get_hauteur(img)){
		*ligne = -1;
		*colonne = -1;
	}
	else{
		*ligne = ind%get_largeur(img);
		*colonne = ind/get_largeur(img);
	}
}

int set_taille_image(image * img, int largeur, int hauteur){
	if(largeur >= 0){(*img).largeur = largeur;}
	if(hauteur >= 0){(*img).hauteur = hauteur;}
	return 0;
}

int alloueImagePnm(image * img){
	(*img).img = (pixel *) malloc((*img).hauteur * (*img).largeur * sizeof(pixel));
	if((*img).img == NULL){return 1;}
	else{return 0;}
}

int initImage_Pnm(image * img){
	int i, nb_pix;
	if((*img).img != NULL){
		nb_pix = get_hauteur(*img) * get_largeur(*img);
		for(i=0; i<nb_pix; i++){
			set_pix_color(&((*img).img[i]), 0, 0, 0);
		}
		return 0;
	}
	else{
		return 1;
	}
}

int emptyImagePnm(image img){
	if(get_type(img) == 0 && get_largeur(img) == 0 && get_hauteur(img) == 0){
		return 0;
	}
	else{
		return 1;
	}
}

int realloueImagePnm(image * img, int new_hauteur, int new_largeur){
	(*img).hauteur = new_hauteur;
	(*img).largeur = new_largeur;
	(*img).img = (pixel *) realloc((*img).img, new_hauteur * new_largeur * sizeof(pixel));
	return 0;
}

int desalloueImagePnm(image * img){
	if((*img).img != NULL){free( (*img).img );}
	return 0;
}

int lireImagePnm(char * filename, image * img){
	FILE * file;
	char tmp[10];
	int i = 0, nb = 0, cpt = 0, max = 0, lu = 0;
	int show_lecture = 0; /* si a 1, affiche ce qui est lu */
	
	file = fopen(filename, "r");
	if(file == NULL){return 1;}
	
	strcpy((*img).fichier, filename);
	
	fscanf(file, "%s", tmp);
	if(show_lecture == 1){printf("Lecture image %s :\n", filename);}
	if(show_lecture == 1){printf("%s\n", tmp);}
	if(tmp[0] == 'P' && (tmp[1] == '1' || tmp[1] == '2' || tmp[1] == '3') ){ /* si le type du fichier est correct : P1, P2 ou P3*/
		(*img).type = (int) tmp[1] - '0';
	}
	else{
		return 2;
	}
	
	fscanf(file, "%s", tmp); /* lecture de la largeur*/
	if(show_lecture == 1){printf("%s ", tmp);}
	if(atoi(tmp) != 0){(*img).largeur = atoi(tmp);}else{return 3;}
	
	fscanf(file, "%s", tmp); /* lecture de la hauteur */
	if(show_lecture == 1){printf("%s\n", tmp);}
	if(atoi(tmp) != 0){(*img).hauteur = atoi(tmp);}else{return 4;}
	
	alloueImagePnm(img);
	
	if((*img).type == 2 || (*img).type == 3){ /* pour les types 2 et 3, on lit quel est le nb max*/
		fscanf(file, "%s", tmp);
		if(show_lecture == 1){printf("%s\n", tmp);}
		if(atoi(tmp) != 0){max = atoi(tmp);}else{return 5;}
	}
	
	nb = 0; /* contient le nbre de pixel lus */
	cpt = 0; /* contient le nbre de chiffres lus */
	while(feof(file) == 0){
		lu = fscanf(file, "%s", tmp);
		if(show_lecture == 1){printf("%s ", tmp);}
		
		if(lu == 1){
			if( (atoi(tmp) != 0 || tmp[0] == '0') && ((*img).hauteur * (*img).largeur) >= nb){ /* si la lecture est correcte : (nbre != 0 ou caractere 0) et nbre pixel image >= nbre de pixel lus */
				if( ( (*img).type == 1 && (atoi(tmp) == 0 || atoi(tmp) == 1) ) ){ /* type 1 : on met le chiffre lu dans ttes les cases du pixel en le multipliant par 255 ( 0*255=0 et 1*255=1)*/
					set_pix_color(&((*img).img[nb]), 255*(1-atoi(tmp)), 255*(1-atoi(tmp)), 255*(1-atoi(tmp))); /* ATTENTION, 0 est transforme en 255 et 1 en 0... */
				}
				else if((*img).type == 2 && (atoi(tmp) >= 0 || atoi(tmp) <= 255) ){ /* type 2 : on met le chiffre lu dans ttes les cases du pixel en le ramenant la valeur max sur 255*/
					set_pix_color(&((*img).img[nb]), (int) (255/max)*atoi(tmp), (int) (255/max)*atoi(tmp), (int) (255/max)*atoi(tmp));
				}
				else if((*img).type == 3 && (atoi(tmp) >= 0 || atoi(tmp) <= 255) ){ /* type 3 : idem que 2 mais on met les nombres dans chaque case du pixel a tour de role. l'indice nb n'est incremente que tous les 3 coup*/
					/* l'operation cpt%3 est le module. Elle renvoi donc la congruence a 3 de cpt. ex : 4%3 = 1, 8%3 = 2, 12%3 = 0*/
					if(cpt%3 == 0){set_pix_color(&((*img).img[nb]), (int) (255/max)*atoi(tmp), -1, -1);}
					if(cpt%3 == 1){set_pix_color(&((*img).img[nb]), -1, (int) (255/max)*atoi(tmp), -1);}
					if(cpt%3 == 2){set_pix_color(&((*img).img[nb]), -1, -1, (int) (255/max)*atoi(tmp)); nb++;}
					nb--;
				}
				else{
					return 6;
				}
			}
			nb++;
			cpt++;
		}
	}
	if(show_lecture == 1){printf("\nFin lecture image %s.\n\n", filename);}
	
	if( ((*img).hauteur * (*img).largeur) < nb){
		printf("ATTENTION, l'image contient trop de pixels (%d < %d) !!!\nLes derniers pixels ont ete ignores\n", ((*img).hauteur * (*img).largeur), nb);
	}
	else if( ((*img).hauteur * (*img).largeur) > nb){
		printf("ATTENTION, l'image ne contient pas assez de pixels (%d > %d) !!!\nLes derniers pixels sont mis a 0\n", ((*img).hauteur * (*img).largeur), nb);
		for(i=nb; i<(*img).hauteur * (*img).largeur; i++){
			set_pix_color(&((*img).img[nb]), 0, 0, 0);
		}
	}
	
	fclose(file);
	
	return 0;
}

int sauverImagePnm(char * filename, image * img, int no_img, int type){
	FILE * file;
	int tmp = 0;
	char c, s[512], nomFile[512];
	
	if(type < 1 || type > 3){type = get_type(*img);}
	
	if(type == 1){sprintf(nomFile, "%s%s.pbm", IMG_DIR, filename);}
	else if(type == 2){sprintf(nomFile, "%s%s.pgm", IMG_DIR, filename);}
	else if(type == 3){sprintf(nomFile, "%s%s.ppm", IMG_DIR, filename);}
	else{sprintf(nomFile, "%s%s.pnm", IMG_DIR, filename);}
	
	while(fichierExist(nomFile) == 0){
		printf("  \033[%smEnregistrement de l'image %d : le fichier %s existe deja. Voulez-vous l'ecraser ? (y/n)\033[0m ", infoColor, no_img, nomFile);
		c = getchar();
		emptyBuffer();
		if(c != 'y' && c != '1'){
			printf("  \033[%smVoulez-vous l'enregistrer sous un autre nom ? Si oui, tapez ce nom, sinon tapez \"n\".\033[0m ", infoColor);
			scanf("%s", s);
			emptyBuffer();
			if(strcmp(s, "n") != 0 && strcmp(s, "0") != 0){
				if(type == 1){sprintf(nomFile, "%s%s.pbm", IMG_DIR, s);}
				else if(type == 2){sprintf(nomFile, "%s%s.pgm", IMG_DIR, s);}
				else if(type == 3){sprintf(nomFile, "%s%s.ppm", IMG_DIR, s);}
				else{sprintf(nomFile, "%s%s.pnm", IMG_DIR, s);}
			}
			else{
				printf("  L'image %d n'a pas ete enregistree dans le fichier %s.\n", no_img, nomFile);
				return 0;
			}
		}
		else{
			break;
		}
	}
	
	file = fopen(nomFile, "w");
	if(file == NULL){printf("erreur ouverture du fichier : %s\n", filename); return 1;}
	
	tmp = printImagePnm(file, img, type, 0);
	printf("  Sauvegarde de l'image %d dans %s\n", no_img, nomFile);
	
	fclose(file);
	
	return tmp;
}

int printImagePnm(FILE * file, image * img, int type, int align){
	int i = 0, max = 0;
	
	if(type < 1 || type > 3){type = get_type(*img);}
	
	fprintf(file, "P%d\n", type);
	fprintf(file, "%d %d\n", get_largeur(*img), get_hauteur(*img));
	if(type == 2 || type == 3){fprintf(file, "255\n");}
	
	max = get_hauteur(*img) * get_largeur(*img);
	
	if(type == 1){
		for(i=0; i<max; i++){
			fprintf(file, "%d ", (255 - get_pix_r((*img).img[i])) / 255);
			if(i%get_largeur(*img) == get_largeur(*img) - 1){fprintf(file, "\n");} /* lorsqu'on a ecrit autant de pixel qu'il y en a dans une ligne (largeur), on saute une ligne.*/
		}
	}
	else if(type == 2){
		for(i=0; i<max; i++){
			if(align == 1){fprintf(file, "%.3d ", get_pix_r((*img).img[i]));}


			else{fprintf(file, "%d ", get_pix_r((*img).img[i]));}
			if(i%get_largeur(*img) == get_largeur(*img) - 1){fprintf(file, "\n");} /* lorsqu'on a ecrit autant de pixel qu'il y en a dans une ligne (largeur), on saute une ligne.*/
		}
	}
	else{
		for(i=0; i<max; i++){
			if(align == 1){fprintf(file, "%.3d %.3d %.3d  ", get_pix_r((*img).img[i]), get_pix_v((*img).img[i]), get_pix_b((*img).img[i]) );}
			else{fprintf(file, "%d %d %d ", get_pix_r((*img).img[i]), get_pix_v((*img).img[i]), get_pix_b((*img).img[i]) );}
			if(i%get_largeur(*img) == get_largeur(*img) - 1){fprintf(file, "\n");} /* lorsqu'on a ecrit autant de pixel qu'il y en a dans une ligne (largeur), on saute une ligne.*/
		}
	}
	
	if(align != 1){fprintf(file, "\n");}
	
	return 0;
}

int printSquareImagePnm(FILE * file, image * img, int x0, int y0, int x1, int y1, int type, int align){
	int i = 0, j = 0, ind = 0;
	
	if(type < 1 || type > 3){type = get_type(*img);}
	
	if(x0>0 && x1>=x0 && x1<=get_largeur(*img) && y0>0 && y1>=y0 && y1<=get_hauteur(*img)){
		fprintf(file, "P%d\n", type);
		fprintf(file, "%d %d\n", get_largeur(*img), get_hauteur(*img));
		if(type == 2 || type == 3){fprintf(file, "255\n");}
		fprintf(file, "reduction de l'image au carre delimite par : (%d,%d) et (%d,%d)\n", x0, y0, x1, y1);
		
		/* passage d'une origine a 1 a une origine a 0 */
		x0 = x0 - 1;
		y0 = y0 - 1;
		x1 = x1 - 1;
		y1 = y1 - 1;
		
		if(type == 1){
			for(j=y0; j<=y1; j++){
				for(i=x0; i<=x1; i++){
					ind = img_indice(*img, i, j);
					fprintf(file, "%d ", (255 - get_pix_r((*img).img[ind])) / 255);
				}
				fprintf(file, "\n");
			}
		}
		else if(type == 2){
			for(j=y0; j<=y1; j++){
				for(i=x0; i<=x1; i++){
					ind = img_indice(*img, i, j);
					if(align == 1){fprintf(file, "%.3d  ", get_pix_r((*img).img[ind]));}
					else{fprintf(file, "%d ", get_pix_r((*img).img[ind]));}
				}
				fprintf(file, "\n");
			}
		}
		else{
			for(j=y0; j<=y1; j++){
				for(i=x0; i<=x1; i++){
					ind = img_indice(*img, i, j);
					if(align == 1){fprintf(file, "%.3d %.3d %.3d  ", get_pix_r((*img).img[ind]), get_pix_v((*img).img[ind]), get_pix_b((*img).img[ind]) );}
					else{fprintf(file, "%d %d %d ", get_pix_r((*img).img[ind]), get_pix_v((*img).img[ind]), get_pix_b((*img).img[ind]) );}
				}
				fprintf(file, "\n");
			}
		}
	
		if(align != 1){fprintf(file, "\n");}
		
		return 0;
	}
	else{
		return 1;
	}
}

int cpyImagePnm(image * dest, image source){
	int i, nb_pix;
	
	if(get_largeur(*dest) != get_largeur(source) || get_hauteur(*dest) != get_hauteur(source)){
		return 1;
	}
	else{
		nb_pix = get_largeur(source) * get_hauteur(source);
		for(i=0; i<nb_pix; i++){
			cpy_pix(&((*dest).img[i]), source.img[i]);
		}
		return 0;
	}
}

int colleImagePnm(image * dest, image source, int x0, int y0, char ** param){
	int tmp, i, j, ind, ind2, max_hauteur, max_largeur;
	pixel pix;
	
	x0 = x0 - 1;
	y0 = y0 - 1;
	
	if(x0 < 0 || x0 >= get_largeur(*dest) || y0 < 0 || y0 >= get_hauteur(*dest)){
		return 1;
	}
	else{
		max_largeur = imin(x0+get_largeur(source), get_largeur(*dest));
		max_hauteur = imin(y0+get_hauteur(source), get_hauteur(*dest));
		
		for(j=y0; j<max_hauteur; j++){
			for(i=x0; i<max_largeur; i++){
				ind = img_indice(*dest, i, j);
				ind2 = img_indice(source, i-x0, j-y0);
				
				if(param == NULL || param[0][0] == '\0'){
					cpy_pix(&((*dest).img[ind]), source.img[ind2]);
				}
				else if(strcmp(param[0], "-tr") == 0){
					tmp = atoi(param[1]);
					set_pix_color(&pix, ((100-tmp) * get_pix_r((*dest).img[ind]) + tmp * get_pix_r(source.img[ind2]))/100, ((100-tmp) * get_pix_v((*dest).img[ind]) + tmp * get_pix_v(source.img[ind2]))/100, ((100-tmp) * get_pix_b((*dest).img[ind]) + tmp * get_pix_b(source.img[ind2]))/100);
					cpy_pix(&((*dest).img[ind]), pix);
				}
				/*else if(strcmp(param[0], "add") == 0){
					set_pix_color(&pix, imax(get_pix_r((*dest).img[ind]) + get_pix_r(source.img[ind2]), 255), imax(get_pix_v((*dest).img[ind]) + get_pix_v(source.img[ind2]), 255), imax(get_pix_b((*dest).img[ind]) + get_pix_b(source.img[ind2]), 255));
					cpy_pix(&((*dest).img[ind]), pix);
				}
				else if(strcmp(param[0], "mult") == 0){
					set_pix_color(&pix, imax(get_pix_r((*dest).img[ind]) * get_pix_r(source.img[ind2]), 255), imax(get_pix_v((*dest).img[ind]) * get_pix_v(source.img[ind2]), 255), imax(get_pix_b((*dest).img[ind]) * get_pix_b(source.img[ind2]), 255));
					cpy_pix(&((*dest).img[ind]), pix);
				}*/
				else{
					return PARAM_ERR;
				}
			}
		}
		return 0;
	}
}

int set_img_pix(image * img, int x0, int y0, short int R, short int V, short int B){
	int ind = img_indice(*img, x0-1, y0-1);
	set_pix_color(&((*img).img[ind]), R, V, B);
	return 0;
}

int deleteImagePnm(image * img){
	if(emptyImagePnm(*img) != 0){
		desalloueImagePnm(img);
	}
	(*img).hauteur = 0;
	(*img).largeur = 0;
	(*img).type = 0;
	(*img).fichier[0] = '\0';
	return 0;
}


