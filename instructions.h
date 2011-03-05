#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_
#include "commande.h"

int evalOneParam(char * param, image * work_img);

int instrCreate(commande com, image * work_img, int * nb_img);
int instrInit(commande com, image * work_img);
int instrLoad(commande com, image * work_img, int * nb_img);
int instrSave(commande com, image * work_img);
int instrPrint(commande com, image * work_img);
int instrCopy(commande com, image * work_img);
int instrPaste(commande com, image * work_img);
int instrCut(commande com, image * work_img);
int instrAdd(commande com, image * work_img);
int instrFrame(commande com, image * work_img);
int instrInv(commande com, image * work_img);
int instrKeep(commande com, image * work_img);
int instrSetpix(commande com, image * work_img);
int instrFiltre(commande com, image * work_img);
int instrClose(commande com, image * work_img, int * nb_img);
int structFin(image * work_img, int * nb_img);


#endif /* _INSTRUCTIONS_H_ */


