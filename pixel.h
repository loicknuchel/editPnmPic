#ifndef _PIXEL_H_
#define _PIXEL_H_

typedef struct _pixel{
	int rouge;
	int vert;
	int bleu;
} pixel;

/* met a jour la valeur du pixel lorsque celle-ci est correcte (entre 0 et 255) */
void set_pix_color(pixel * pix, int rouge, int vert, int bleu);
int get_pix_r(pixel pix);
int get_pix_v(pixel pix);
int get_pix_b(pixel pix);
void cpy_pix(pixel * dest, pixel source);

#endif /* _PIXEL_H_ */

