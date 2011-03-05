#ifndef _IMAGETRANSFORMATION_H_
#define _IMAGETRANSFORMATION_H_
#include "pixel.h"
#include "imagePnm.h"

void inverserImage(image * img);
int couperImage(image * ptr_image, int x0, int y0, int x1, int y1);
int dessinCadre(image * ptr_image, int x0, int y0, int x1, int y1, short int R, short int V, short int B);
int ajouterImage(image * ptr_image1, char * cote, image * ptr_image2);

void keepColorImage(image * img, int color);
void keepColorPixImage(image * img, int color);

int filtreMedian(image * img, int voisinage);

int filtre_1(image * img, int ** filtre, int xfiltre, int yfiltre, int cpt);
int filtre_2(image * img, int ** filtre1, int ** filtre2, int xfiltre, int yfiltre);

#endif /* _IMAGETRANSFORMATION_H_*/


