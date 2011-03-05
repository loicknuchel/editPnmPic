#ifndef _FILTRE_MAT_H_
#define _FILTRE_MAT_H_

/* Ces fonctions créent les matrices pour les filtres */

int read_mat(int *** mat, int x0, int y0, char * txt_mat);

int mat_moyen(int *** mat1, int x0, int y0);

int mat_sobel(int *** mat1, int *** mat2, int * x0, int * y0);
int mat_prewitt(int *** mat1, int *** mat2, int * x0, int * y0);
int mat_roberts(int *** mat1, int *** mat2, int * x0, int * y0);
int mat_mdif(int *** mat1, int *** mat2, int * x0, int * y0);


#endif /* _FILTRE_MAT_H_ */
