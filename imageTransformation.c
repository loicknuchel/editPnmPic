#include "inc.h"

void inverserImage(image * img){
	int max = 0, i = 0;
	
	max = (*img).hauteur * (*img).largeur;
	for(i=0; i<max; i++){
		set_pix_color( &((*img).img[i]), 255 - get_pix_r((*img).img[i]), 255 - get_pix_v((*img).img[i]), 255 - get_pix_b((*img).img[i]) );
	}
}

void keepColorImage(image * img, int color){
	int max = 0, i = 0;
	
	max = (*img).hauteur * (*img).largeur;
	
	for(i=0; i<max; i++){
		if(color == 1){
			set_pix_color(&((*img).img[i]), get_pix_r((*img).img[i]), 0, 0);
		}
		else if(color == 2){
			set_pix_color(&((*img).img[i]), 0, get_pix_v((*img).img[i]), 0);
		}
		else if(color == 3){
			set_pix_color(&((*img).img[i]), 0, 0, get_pix_b((*img).img[i]));
		}
	}
}

void keepColorPixImage(image * img, int color){
	int max = 0, i = 0;
	
	max = (*img).hauteur * (*img).largeur;
	
	for(i=0; i<max; i++){
		if(color == 1){
			if(get_pix_r((*img).img[i]) < (get_pix_v((*img).img[i]) + get_pix_b((*img).img[i])) * 1.1){set_pix_color(&((*img).img[i]), 255, 255, 255);}
		}
		else if(color == 2){
			if(get_pix_v((*img).img[i]) < (get_pix_r((*img).img[i]) + get_pix_b((*img).img[i])) * 1.1){set_pix_color(&((*img).img[i]), 255, 255, 255);}
		}
		else if(color == 3){
			if(get_pix_b((*img).img[i]) < (get_pix_v((*img).img[i]) + get_pix_r((*img).img[i])) * 1.1){set_pix_color(&((*img).img[i]), 255, 255, 255);}
		}
	}
}

int couperImage(image * ptr_image, int x0, int y0, int x1, int y1){
	int i, j, ind, ind2;
	int new_largeur = x1 - x0 + 1, new_hauteur = y1 - y0 + 1;
	image tmp;
	
	/* pour echelonner a partir de 0 au lieu de 1 */
	x0 = x0 - 1;
	x1 = x1 - 1;
	y0 = y0 - 1;
	y1 = y1 - 1;
	
	if(x0 < 0 || x0 > x1 || x1 >= get_largeur(*ptr_image) || y0 < 0 || y0 >= y1 || y1 >= get_hauteur(*ptr_image)){
		return 1;
	}
	else{
		set_taille_image(&tmp, new_largeur, new_hauteur);
		alloueImagePnm(&tmp);
		
		/* copie de la zone selectionne dans une image tampon */
		ind2 = 0;
		for(j=y0; j<=y1; j++){
			for(i=x0; i<=x1; i++){
				ind = img_indice(*ptr_image, i, j);
				cpy_pix(&(tmp.img[ind2]), (*ptr_image).img[ind]);
				ind2++;
			}
		}
		
		/* redimentionnement de l'image */
		realloueImagePnm(ptr_image, new_hauteur, new_largeur);
		
		/* recopie l'image tampon dans l'image redimentionnee */
		cpyImagePnm(ptr_image, tmp);
	
		/* suppression du tampon */
		deleteImagePnm(&tmp);
		
		return 0;
	}
}

int dessinCadre(image * ptr_image, int x0, int y0, int x1, int y1, short int R, short int V, short int B){
	int i, j, ind;
	
	/* pour echelonner a partir de 0 au lieu de 1 */
	x0 = x0 - 1;
	x1 = x1 - 1;
	y0 = y0 - 1;
	y1 = y1 - 1;
	
	if(x0 < 0 || x0 > x1 || x1 >= get_largeur(*ptr_image) || y0 < 0 || y0 >= y1 || y1 >= get_hauteur(*ptr_image) || R < 0 || R > 255 || V < 0 || V > 255 || B < 0 || B > 255){
		return 1;
	}
	else{
		/* dessin des lignes horizontales */
		for(i=x0; i<=x1; i++){
			ind = img_indice(*ptr_image, i, y0);
			/*printf("i:%d, j:%d => ind:%d\n", i, y0, ind);*/
			set_pix_color(&((*ptr_image).img[ind]), R, V, B);
			ind = img_indice(*ptr_image, i, y1);
			/*printf("i:%d, j:%d => ind:%d\n", i, y1, ind);*/
			set_pix_color(&((*ptr_image).img[ind]), R, V, B);
		}
	
		/* dessin des lignes verticales */
		for(j=y0; j<=y1; j++){
			ind = img_indice(*ptr_image, x0, j);
			/*printf("i:%d, j:%d => ind:%d\n", x0, j, ind);*/
			set_pix_color(&((*ptr_image).img[ind]), R, V, B);
			ind = img_indice(*ptr_image, x1, j);
			/*printf("i:%d, j:%d => ind:%d\n", x1, j, ind);*/
			set_pix_color(&((*ptr_image).img[ind]), R, V, B);
		}
	
		return 0;
	}
}

int ajouterImage(image * ptr_image1, char * cote, image * ptr_image2){
	int ret;
	int x0, y0, x1, y1; /* x0 et y0 : endroit ou on copie l'image1, x1 et y1 : endroit ou on copie l'image2 */
	int new_largeur, new_hauteur, nb_pix;
	image tmp;
	
	if(strcmp(cote, "gauche") == 0){
		new_largeur = get_largeur(*ptr_image1) + get_largeur(*ptr_image2);
		new_hauteur = imax(get_hauteur(*ptr_image1), get_hauteur(*ptr_image2));
		x0 = get_largeur(*ptr_image2);
		y0 = 0;
		x1 = 0;
		y1 = 0;
	}
	else if(strcmp(cote, "haut") == 0){
		new_largeur = imax(get_largeur(*ptr_image1), get_largeur(*ptr_image2));
		new_hauteur = get_hauteur(*ptr_image1) + get_hauteur(*ptr_image2);
		x0 = 0;
		y0 = get_hauteur(*ptr_image2);
		x1 = 0;
		y1 = 0;
	}
	else if(strcmp(cote, "droit") == 0 || strcmp(cote, "droite") == 0 ){
		new_largeur = get_largeur(*ptr_image1) + get_largeur(*ptr_image2);
		new_hauteur = imax(get_hauteur(*ptr_image1), get_hauteur(*ptr_image2));
		x0 = 0;
		y0 = 0;
		x1 = get_largeur(*ptr_image1);
		y1 = 0;
	}
	else if(strcmp(cote, "bas") == 0){
		new_largeur = imax(get_largeur(*ptr_image1), get_largeur(*ptr_image2));
		new_hauteur = get_hauteur(*ptr_image1) + get_hauteur(*ptr_image2);
		x0 = 0;
		y0 = 0;
		x1 = 0;
		y1 = get_hauteur(*ptr_image1);
	}
	else{
		return 1;
	}
	
	/* initialisation du tampon */
	nb_pix = new_largeur * new_hauteur;
	set_taille_image(&tmp, new_largeur, new_hauteur);
	alloueImagePnm(&tmp);
	initImage_Pnm(&tmp);
	
	/* recopie de l'image1 dans le tampon a la position qu'elle doit avoir */
	ret = colleImagePnm(&tmp, *ptr_image1, x0+1, y0+1, NULL);
	if(ret != 0){return 2;}
	
	/* recopie de l'image2 dans le tampon a la position qu'elle doit avoir */
	ret = colleImagePnm(&tmp, *ptr_image2, x1+1, y1+1, NULL);
	if(ret != 0){return 2;}
	
	
	/* redimentionnement de l'image a modifier */
	realloueImagePnm(ptr_image1, new_hauteur, new_largeur);
	
	/* recopie l'image tampon dans l'image a modifier (1) */
	cpyImagePnm(ptr_image1, tmp);
	
	/* suppression du tampon */
	deleteImagePnm(&tmp);
	
	
	return 0;
}

int filtre_1(image * img, int ** filtre, int xfiltre, int yfiltre, int cpt){
	int i, j, k, l, ind, nb_pix;
	pixel sum;
	image tmp_img;
	
	if(filtre == NULL || xfiltre%2 != 1 || yfiltre%2 != 1){return 1;}
	else{
		xfiltre = (xfiltre-1) / 2;
		yfiltre = (yfiltre-1) / 2;
	}
	
	nb_pix = get_largeur(*img) * get_hauteur(*img);
	set_taille_image(&tmp_img, get_largeur(*img), get_hauteur(*img));
	alloueImagePnm(&tmp_img);
	initImage_Pnm(&tmp_img);
	
	if(cpt == 0){
		for(j=0; j<yfiltre; j++){
			for(i=0; i<xfiltre; i++){
				cpt += filtre[j][i];
			}
		}
		if(cpt == 0){cpt = 1;}
	}
	
	for(i=0; i<get_largeur(*img); i++){
		for(j=0; j<get_hauteur(*img); j++){
			
			if(j < yfiltre || j >= get_hauteur(*img)-yfiltre || i < xfiltre || i >= get_largeur(*img)-xfiltre){
				ind = img_indice(tmp_img, i, j);
				/*set_pix_color(&(tmp_img.img[ind]), get_pix_r((*img).img[ind]), get_pix_v((*img).img[ind]), get_pix_b((*img).img[ind]));*/
				set_pix_color(&(tmp_img.img[ind]), 0, 0, 0);
			}
			else{
				set_pix_color(&sum, 0, 0, 0);
				for(k=j-yfiltre; k<=j+yfiltre; k++){
					for(l=i-xfiltre; l<=i+xfiltre; l++){
						ind = img_indice(*img, l, k);
						sum.rouge += filtre[k-(j-yfiltre)][l-(i-xfiltre)] * get_pix_r((*img).img[ind]);
						sum.vert += filtre[k-(j-yfiltre)][l-(i-xfiltre)] * get_pix_v((*img).img[ind]);
						sum.bleu += filtre[k-(j-yfiltre)][l-(i-xfiltre)] * get_pix_b((*img).img[ind]);
					}
				}
				set_pix_color(&sum, sum.rouge / cpt, sum.vert / cpt, sum.bleu / cpt);
				
				ind = img_indice(*img, i, j);
				set_pix_color(&(tmp_img.img[ind]), get_pix_r(sum), get_pix_v(sum), get_pix_b(sum));
			}
		}
	}
	
	cpyImagePnm(img, tmp_img);
	
	deleteImagePnm(&tmp_img);
	
	return 0;
}

int filtre_2(image * img, int ** filtre1, int ** filtre2, int xfiltre, int yfiltre){
	int i, j, k, l, ind, nb_pix;
	pixel sum1, sum2;
	image tmp_img;
	
	if(filtre1 == NULL || filtre2 == NULL || xfiltre%2 != 1 || yfiltre%2 != 1){return 1;}
	else{
		xfiltre = (xfiltre-1) / 2;
		yfiltre = (yfiltre-1) / 2;
	}
	
	nb_pix = get_largeur(*img) * get_hauteur(*img);
	set_taille_image(&tmp_img, get_largeur(*img), get_hauteur(*img));
	alloueImagePnm(&tmp_img);
	initImage_Pnm(&tmp_img);
	
	for(i=0; i<get_largeur(*img); i++){
		for(j=0; j<get_hauteur(*img); j++){
			
			if(j < yfiltre || j >= get_hauteur(*img)-yfiltre || i < xfiltre || i >= get_largeur(*img)-xfiltre){
				ind = img_indice(tmp_img, i, j);
				set_pix_color(&(tmp_img.img[ind]), 0, 0, 0);
			}
			else{
				set_pix_color(&sum1, 0, 0, 0);
				set_pix_color(&sum2, 0, 0, 0);
				for(k=j-yfiltre; k<=j+yfiltre; k++){
					for(l=i-xfiltre; l<=i+xfiltre; l++){
						ind = img_indice(*img, l, k);
						sum1.rouge += filtre1[k-(j-yfiltre)][l-(i-xfiltre)] * get_pix_r((*img).img[ind]);
						sum1.vert += filtre1[k-(j-yfiltre)][l-(i-xfiltre)] * get_pix_v((*img).img[ind]);
						sum1.bleu += filtre1[k-(j-yfiltre)][l-(i-xfiltre)] * get_pix_b((*img).img[ind]);
						sum2.rouge += filtre2[k-(j-yfiltre)][l-(i-xfiltre)] * get_pix_r((*img).img[ind]);
						sum2.vert += filtre2[k-(j-yfiltre)][l-(i-xfiltre)] * get_pix_v((*img).img[ind]);
						sum2.bleu += filtre2[k-(j-yfiltre)][l-(i-xfiltre)] * get_pix_b((*img).img[ind]);
					}
				}
				set_pix_color(&sum1, (int) sqrt((double) sum1.rouge*sum1.rouge+sum2.rouge*sum2.rouge), (int) sqrt((double) sum1.vert*sum1.vert+sum2.vert*sum2.vert), (int) sqrt((double) sum1.bleu*sum1.bleu+sum2.bleu*sum2.bleu));
				
				ind = img_indice(*img, i, j);
				set_pix_color(&(tmp_img.img[ind]), get_pix_r(sum1), get_pix_v(sum1), get_pix_b(sum1));
			}
		}
	}
	
	cpyImagePnm(img, tmp_img);
	
	deleteImagePnm(&tmp_img);
	
	return 0;
}


int filtreMedian(image * img, int voisinage){
	int i, j, k, l, ind, cpt, nb_pix, t_long;
	int * poids_r, * poids_v, * poids_b;
	image tmp_img;
	
	t_long = (2*voisinage+1)*(2*voisinage+1);
	
	poids_r = calloc(t_long, sizeof(int*));
	poids_v = calloc(t_long, sizeof(int*));
	poids_b = calloc(t_long, sizeof(int*));
	
	for(i=0; i<t_long; i++){
		poids_r[i] = 0;
		poids_v[i] = 0;
		poids_b[i] = 0;
	}
	
	nb_pix = get_largeur(*img) * get_hauteur(*img);
	set_taille_image(&tmp_img, get_largeur(*img), get_hauteur(*img));
	alloueImagePnm(&tmp_img);
	initImage_Pnm(&tmp_img);
	
	for(i=0; i<get_largeur(*img); i++){
		for(j=0; j<get_hauteur(*img); j++){
			
			if(j < voisinage || j >= get_hauteur(*img)-voisinage || i < voisinage || i >= get_largeur(*img)-voisinage){
				ind = img_indice(tmp_img, i, j);
				/*set_pix_color(&(tmp_img.img[ind]), get_pix_r((*img).img[ind]), get_pix_v((*img).img[ind]), get_pix_b((*img).img[ind]));*/
				set_pix_color(&(tmp_img.img[ind]), 0, 0, 0);
			}
			else{
				cpt = 0;
				for(k=j-voisinage; k<=j+voisinage; k++){
					for(l=i-voisinage; l<=i+voisinage; l++){
						ind = img_indice(*img, l, k);
						poids_r[cpt] = get_pix_r((*img).img[ind]);
						poids_v[cpt] = get_pix_v((*img).img[ind]);
						poids_b[cpt] = get_pix_b((*img).img[ind]);
						cpt++;
					}
				}
				
				ind = img_indice(*img, i, j);
				set_pix_color(&(tmp_img.img[ind]), mediane(poids_r, t_long), mediane(poids_v, t_long), mediane(poids_b, t_long));
			}
		}
	}
	
	cpyImagePnm(img, tmp_img);
	
	deleteImagePnm(&tmp_img);
	free(poids_r);
	free(poids_v);
	free(poids_b);
	
	return 0;
}






