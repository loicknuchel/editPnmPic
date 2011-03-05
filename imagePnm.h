#ifndef _IMAGEPNM_H_
#define _IMAGEPNM_H_
#include "pixel.h"

typedef struct _image{
	int hauteur;
	int largeur;
	int type;
	char fichier[MAX_LENGHT_PARAM];
	pixel * img;
} image;

int init_struct_image(image * img);

int get_hauteur(image img);
int get_largeur(image img);
int get_type(image img);
int set_type(image * img, int type);

int img_indice(image img, int ligne, int colonne); /* donne l'indice lineaire du pixel en fonction de sa ligne et de sa colonne */
void img_ind(image img, int * ligne, int * colonne, int ind);

int set_taille_image(image * img, int largeur, int hauteur);
int alloueImagePnm(image * img);
int initImage_Pnm(image * img);
int emptyImagePnm(image img); /* 0:oui, 1:non */
int realloueImagePnm(image * img, int new_hauteur, int new_largeur);
int desalloueImagePnm(image * img);


int lireImagePnm(char * filename, image * img);
int sauverImagePnm(char * filename, image * img, int no_img, int type);
int printImagePnm(FILE * file, image * img, int type, int align);
int printSquareImagePnm(FILE * file, image * img, int x0, int y0, int x1, int y1, int type, int align);
int cpyImagePnm(image * dest, image source); /* Copie une image dans une autre. Les deux images doivent avoir la meme dimention */
int colleImagePnm(image * dest, image source, int x0, int y0, char ** param); /* Copie une image dans une autre a partir de la position indiquee (coin en haut a gauche). Si des pixels sont dehors, il ne sont pas copies. */
int set_img_pix(image * img, int x0, int y0, short int R, short int V, short int B);
int deleteImagePnm(image * img);


#endif /* _IMAGEPNM_H_ */

