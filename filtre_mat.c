#include "inc.h"


int read_mat(int *** mat, int x0, int y0, char * txt_mat){
	int i = 0, x, y, neg = 0;
	
	*mat = calloc(y0, sizeof(int*));
	for(i=0; i<y0; i++){
		(*mat)[i] = calloc(x0, sizeof(int));
	}
	
	x = 0;
	y = 0;
	i = 0;
	while(txt_mat[i] != '\0'){
		if(isdigit(txt_mat[i]) != 0){
			(*mat)[y][x] = txt_mat[i] - '0';
			if(neg == 1){(*mat)[y][x] = -(*mat)[y][x]; neg = 0;}
			
			if(x+1 == x0){x = 0; y++;}
			else{x++;}
		}
		else if(txt_mat[i] == '-'){
			neg = 1;
		}
		else{
			return 1;
		}
		i++;
	}
	if(x != 0 || y != y0){printf("x:%d!=%d || y:%d!=%d\n", x, x0-1, y, y0-1); return 1;}
	
	return 0;
}

int mat_moyen(int *** mat1, int x0, int y0){
	int i, j;
	
	*mat1 = calloc(y0, sizeof(int*));
	for(i=0; i<y0; i++){
		(*mat1)[i] = calloc(x0, sizeof(int));
	}
	
	for(j=0; j<y0; j++){
		for(i=0; i<x0; i++){
			(*mat1)[j][i] = 1;
		}
	}
	
	return 0;
}

int mat_sobel(int *** mat1, int *** mat2, int * x0, int * y0){
	int i;
	
	*x0 = 3;
	*y0 = 3;
	*mat1 = calloc(*y0, sizeof(int*));
	*mat2 = calloc(*y0, sizeof(int*));
	for(i=0; i<*y0; i++){
		(*mat1)[i] = calloc(*x0, sizeof(int));
		(*mat2)[i] = calloc(*x0, sizeof(int));
	}
	
	(*mat1)[0][0] = -1;
	(*mat1)[0][1] = 0;
	(*mat1)[0][2] = 1;
	(*mat1)[1][0] = -2;
	(*mat1)[1][1] = 0;
	(*mat1)[1][2] = 2;
	(*mat1)[2][0] = -1;
	(*mat1)[2][1] = 0;
	(*mat1)[2][2] = 1;
	
	(*mat2)[0][0] = 1;
	(*mat2)[0][1] = 2;
	(*mat2)[0][2] = 1;
	(*mat2)[1][0] = 0;
	(*mat2)[1][1] = 0;
	(*mat2)[1][2] = 0;
	(*mat2)[2][0] = -1;
	(*mat2)[2][1] = -2;
	(*mat2)[2][2] = -1;
	
	return 0;
}

int mat_prewitt(int *** mat1, int *** mat2, int * x0, int * y0){
	int i;
	
	*x0 = 3;
	*y0 = 3;
	*mat1 = calloc(*y0, sizeof(int*));
	*mat2 = calloc(*y0, sizeof(int*));
	for(i=0; i<*y0; i++){
		(*mat1)[i] = calloc(*x0, sizeof(int));
		(*mat2)[i] = calloc(*x0, sizeof(int));
	}
	
	(*mat1)[0][0] = -1;
	(*mat1)[0][1] = 0;
	(*mat1)[0][2] = 1;
	(*mat1)[1][0] = -1;
	(*mat1)[1][1] = 0;
	(*mat1)[1][2] = 1;
	(*mat1)[2][0] = -1;
	(*mat1)[2][1] = 0;
	(*mat1)[2][2] = 1;
	
	(*mat2)[0][0] = -1;
	(*mat2)[0][1] = -1;
	(*mat2)[0][2] = -1;
	(*mat2)[1][0] = 0;
	(*mat2)[1][1] = 0;
	(*mat2)[1][2] = 0;
	(*mat2)[2][0] = 1;
	(*mat2)[2][1] = 1;
	(*mat2)[2][2] = 1;
	
	return 0;
}

int mat_roberts(int *** mat1, int *** mat2, int * x0, int * y0){
	int i;
	
	*x0 = 3;
	*y0 = 3;
	*mat1 = calloc(*y0, sizeof(int*));
	*mat2 = calloc(*y0, sizeof(int*));
	for(i=0; i<*y0; i++){
		(*mat1)[i] = calloc(*x0, sizeof(int));
		(*mat2)[i] = calloc(*x0, sizeof(int));
	}
	
	(*mat1)[0][0] = 0;
	(*mat1)[0][1] = 0;
	(*mat1)[0][2] = 0;
	(*mat1)[1][0] = 0;
	(*mat1)[1][1] = 0;
	(*mat1)[1][2] = 1;
	(*mat1)[2][0] = 0;
	(*mat1)[2][1] = -1;
	(*mat1)[2][2] = 0;
	
	(*mat2)[0][0] = 0;
	(*mat2)[0][1] = 0;
	(*mat2)[0][2] = 0;
	(*mat2)[1][0] = 0;
	(*mat2)[1][1] = -1;
	(*mat2)[1][2] = 0;
	(*mat2)[2][0] = 0;
	(*mat2)[2][1] = 0;
	(*mat2)[2][2] = 1;
	
	return 0;
}

int mat_mdif(int *** mat1, int *** mat2, int * x0, int * y0){
	int i;
	
	*x0 = 5;
	*y0 = 5;
	*mat1 = calloc(*y0, sizeof(int*));
	*mat2 = calloc(*y0, sizeof(int*));
	for(i=0; i<*y0; i++){
		(*mat1)[i] = calloc(*x0, sizeof(int));
		(*mat2)[i] = calloc(*x0, sizeof(int));
	}
	
	(*mat1)[0][0] = 0;
	(*mat1)[0][1] = -1;
	(*mat1)[0][2] = 0;
	(*mat1)[0][3] = 1;
	(*mat1)[0][4] = 0;
	(*mat1)[1][0] = -1;
	(*mat1)[1][1] = -2;
	(*mat1)[1][2] = 0;
	(*mat1)[1][3] = 1;
	(*mat1)[1][4] = 2;
	(*mat1)[2][0] = -1;
	(*mat1)[2][1] = -3;
	(*mat1)[2][2] = 0;
	(*mat1)[2][3] = 3;
	(*mat1)[2][4] = 1;
	(*mat1)[3][0] = -1;
	(*mat1)[3][1] = -2;
	(*mat1)[3][2] = 0;
	(*mat1)[3][3] = 2;
	(*mat1)[3][4] = 1;
	(*mat1)[4][0] = 0;
	(*mat1)[4][1] = -1;
	(*mat1)[4][2] = 0;
	(*mat1)[4][3] = 1;
	(*mat1)[4][4] = 0;
	
	(*mat2)[0][0] = 0;
	(*mat2)[0][1] = -1;
	(*mat2)[0][2] = -1;
	(*mat2)[0][3] = -1;
	(*mat2)[0][4] = 0;
	(*mat2)[1][0] = -1;
	(*mat2)[1][1] = -2;
	(*mat2)[1][2] = -3;
	(*mat2)[1][3] = -2;
	(*mat2)[1][4] = -1;
	(*mat2)[2][0] = 0;
	(*mat2)[2][1] = 0;
	(*mat2)[2][2] = 0;
	(*mat2)[2][3] = 0;
	(*mat2)[2][4] = 0;
	(*mat2)[3][0] = 1;
	(*mat2)[3][1] = 2;
	(*mat2)[3][2] = 3;
	(*mat2)[3][3] = 2;
	(*mat2)[3][4] = 1;
	(*mat2)[4][0] = 0;
	(*mat2)[4][1] = 1;
	(*mat2)[4][2] = 1;
	(*mat2)[4][3] = 1;
	(*mat2)[4][4] = 0;
	
	return 0;
}


