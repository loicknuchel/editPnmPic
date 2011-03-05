#include "inc.h"

void set_pix_color(pixel * pix, int rouge, int vert, int bleu){
	if(rouge >= 0 && rouge < 256){(*pix).rouge = rouge;}
	if(vert >= 0 && vert < 256){(*pix).vert = vert;}
	if(bleu >= 0 && bleu < 256){(*pix).bleu = bleu;}
}

int get_pix_r(pixel pix){
	return pix.rouge;
}

int get_pix_v(pixel pix){
	return pix.vert;
}

int get_pix_b(pixel pix){
	return pix.bleu;
}

void cpy_pix(pixel * dest, pixel source){
	(*dest).rouge = source.rouge;
	(*dest).vert = source.vert;
	(*dest).bleu = source.bleu;
}


