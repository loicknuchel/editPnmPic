#ifndef _INC_H_
#define _INC_H_

#define NB_MAX_PARAM 10
#define MAX_LENGHT_PARAM 50
#define MAX_LENGHT_COMMANDE 100
#define MAX_INDEX_IMG 100

#define PROMPT "PnmEdit"
#define IMG_DIR "./images/"
#define SCRIPT_DIR "./scripts/"
#define LOG_FILE "./logs.txt"
#define titreColor "36"
#define protoColor "32"
#define errorColor "31;1"
#define infoColor "33"

#define EXIT_SUCCES 0
#define COMMANDE_INCONNUE 1
#define PARAM_ERR 2
#define USED_PIC 3
#define MISS_PIC 4
#define MISS_FILE 5
#define OVERWRITE_FILE 6
#define HIGH_IND_IMG 7
#define OTHER 9
#define FIN_PROG 10

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#include "filtre_mat.h"
#include "std_fonc.h"
#include "pixel.h"
#include "imagePnm.h"
#include "imageTransformation.h"
#include "commande.h"
#include "instructions.h"
#include "print.h"
#include "shell.h"

#define TRUE 1
#define FALSE 0

#define BUG fprintf( stderr, "\n\tNow in file \"%s\" l.%d\n\n", __FILE__, __LINE__ );

#endif /* _INC_H_ */

