#ifndef _PRINT_H_
#define _PRINT_H_

void printWelcome(FILE * file);
void wrongType(FILE * file, commande com);

void printHelpGeneral(FILE * file);
void printHelpCommande(FILE * file);
void printHelpCREATE(FILE * file);
void printHelpINIT(FILE * file);
void printHelpLOAD(FILE * file);
void printHelpSAVE(FILE * file);
void printHelpPRINT(FILE * file);
void printHelpCOPY(FILE * file);
void printHelpPASTE(FILE * file);
void printHelpCUT(FILE * file);
void printHelpADD(FILE * file);
void printHelpFRAME(FILE * file);
void printHelpINV(FILE * file);
void printHelpKEEP(FILE * file);
void printHelpSETPIX(FILE * file);
void printHelpFILTRE(FILE * file);
void printHelpCLOSE(FILE * file);
void printHelpFIN(FILE * file);

void printExecError(FILE * file, int err, commande cmd);

int secretPrint(char ** commande_txt);

long ordi(long min ,long max, long pnj);
void possibilites(long pj, long pnj);
void draw(long pj,long pnj);
void JeuPFC();

#endif /* _PRINT_H_ */



