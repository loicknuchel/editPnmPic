#ifndef _COMMANDE_H_
#define _COMMANDE_H_

#define ProtoCREATE "CREATE <no> (<l> <h>)|(<no>)"
#define ProtoINIT "INIT <no>"
#define ProtoLOAD "LOAD <no> <filename>"
#define ProtoSAVE "SAVE <no> <filename> [<type>]"
#define ProtoPRINT "PRINT <no> [<x0> <y0> <x1> <y1>]"
#define ProtoCOPY "COPY <no1> <no2>"
#define ProtoPASTE "PASTE <no1> <x0> <y0> <no2> [-tr <%>]"
#define ProtoCUT "CUT <no> <x0> <y0> <x1> <y1>"
#define ProtoADD "ADD <no1> <pos> <no2>"
#define ProtoFRAME "FRAME <no> <x0> <y0> <x1> <y1> <R> <V> <B>"
#define ProtoINV "INV <no>"
#define ProtoKEEP "KEEP <no> R|V|B [pix]"
#define ProtoSETPIX "SETPIX <no> <x0> <y0> <R> <V> <B>"
#define ProtoFILTRE "FILTRE <no> <type> [<params>]"
#define ProtoFILTREsobel "FILTRE <no> -sobel"
#define ProtoFILTREmoy "FILTRE <no> -moy <taille>"
#define ProtoFILTREmed "FILTRE <no> -med <taille>"
#define ProtoFILTREprewitt "FILTRE <no> -prewitt"
#define ProtoFILTREroberts "FILTRE <no> -roberts"
#define ProtoFILTREmdif "FILTRE <no> -mdif"
#define ProtoFILTREf1 "FILTRE <no> -f1 <x0> <y0> <mat> [<div>]"
#define ProtoFILTREf2 "FILTRE <no> -f2 <x0> <y0> <mat1> <mat2>"
#define ProtoCLOSE "CLOSE <no>"
#define ProtoFIN "FIN"

typedef enum {VOID, CREATE, INIT, LOAD, SAVE, PRINT, COPY, PASTE, CUT, ADD, FRAME, INV, KEEP, SETPIX, FILTRE, CLOSE, FIN} ordre;

typedef struct _commande{
	ordre com;
	int num;
	char param[NB_MAX_PARAM][MAX_LENGHT_PARAM];
	struct _commande * next;
} * commande;


int lireCommande(commande * com_liste, char * nomFichier);
int printCommande(commande com_liste);
int printCommandeLst(commande com_liste);
int executeCommande(commande * com_liste);
int supprimeCommande(commande * com_liste);
int emptyCommande(commande com_liste); /* oui:0, non:1 */

int execCommande(commande com, image * work_img);
commande ajout_queue(commande com_liste, char ** commande_txt, int no_instr);
commande create_commande(char ** commande_txt, int no_instr);

#endif /* _COMMANDE_H_ */



