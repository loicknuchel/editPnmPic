#include "inc.h"

void printWelcome(FILE * file){
	system("clear");
	fprintf(file, "\n");
	fprintf(file, "Derniere compilation le \033[%sm%s %s\033[0m\n\n", infoColor, __DATE__, __TIME__);
	fprintf(file, "Debut du programme de traitement d'image.\n");
	fprintf(file, "Auteur : \033[%smLoic Knuchel\033[0m\n", infoColor);
	fprintf(file, "Tapez \033[%sm\"help\"\033[0m pour connaitre les instructions disponibles\n\n\n", infoColor);
}

void wrongType(FILE * file, commande com){
	fprintf(file, "  \033[%smL'image destination de la commande %d (%s) n'est pas du bon type pour recevoir les pixels demandes. Son type a donc ete modifie.\033[0m\n", errorColor, com->num, com->param[0]);
}

void printExecError(FILE * file, int err, commande cmd){
	if(err == COMMANDE_INCONNUE){fprintf(file, "  \033[%smLa commande %s (no %d) n'a pas ete reconnue\033[0m\n", errorColor, cmd->param[0], cmd->num);}
	if(err == PARAM_ERR){fprintf(file, "  \033[%smLes parametres de la commande %s (no %d) ne sont pas corrects\033[0m\n", errorColor, cmd->param[0], cmd->num);}
	if(err == USED_PIC){fprintf(file, "  \033[%smLa commande %s (no %d) n'a pas ete execute car elle aurait ecrase une image\033[0m\n", errorColor, cmd->param[0], cmd->num);}
	if(err == MISS_PIC){fprintf(file, "  \033[%smLa commande %s (no %d) a ete appliquee a une image inexistante\033[0m\n", errorColor, cmd->param[0], cmd->num);}
	if(err == MISS_FILE){fprintf(file, "  \033[%smLa commande %s (no %d) a echoue car la fichier demande (%s) n'a pas pu etre ouvert\033[0m\n", errorColor, cmd->param[0], cmd->num, cmd->param[2]);}
	if(err == OVERWRITE_FILE){fprintf(file, "  \033[%smLa commande %s (no %d) n'a pas reussi a ecrire dans le fichier demande\033[0m\n", errorColor, cmd->param[0], cmd->num);}
	if(err == HIGH_IND_IMG){fprintf(file, "  \033[%smLa commande %s (no %d) a echoue car l'index de l'image est trop grand (max: %d)\033[0m\n", errorColor, cmd->param[0], cmd->num, MAX_INDEX_IMG-1);}
	if(err == OTHER){fprintf(file, "  \033[%smLa commande %s (no %d) a rencontre une erreur\033[0m\n", errorColor, cmd->param[0], cmd->num);}
	if(err == FIN_PROG){fprintf(file, "  La commande %s (no %d) termine l'execution du scenario\n", cmd->param[0], cmd->num);}
}

void printHelpGeneral(FILE * file){
	fprintf(file, "  \033[%smListe des instructions \"shell\" disponibles :\033[0m\n", titreColor);
	fprintf(file, "    \033[%smscenario <filename>\033[0m\t\t : charge un scenario et propose son execution de maniere isolee (alias s)\n", protoColor);
	fprintf(file, "    \033[%sminitialise\033[0m\t\t\t : reinitialise l'environnement de travail (supprime toutes les images) (alias i)\n", protoColor);
	fprintf(file, "    \033[%smexec\033[0m\t\t\t : permet de taper directement les commandes a executer dans l'environnement de travail (alias e)\n", protoColor);
	fprintf(file, "    \033[%smscript <filename>\033[0m\t\t : charge un script et propose son execution dans l'environement de travail (alias sc)\n", protoColor);
	fprintf(file, "    \033[%smcarac <no_img>\033[0m\t\t : affiche les caracteristiques d'une image (alias c)\n", protoColor);
	fprintf(file, "    \033[%smusedImages\033[0m\t\t\t : affiche le numero et la taille de toutes les images utilisees dans l'environement de travail (alias u)\n", protoColor);
	fprintf(file, "    \033[%smlisteImages\033[0m\t\t\t : liste toutes les image disponibles dans le repertoire %s (alias li)\n", protoColor, IMG_DIR);
	fprintf(file, "    \033[%smlisteScripts\033[0m\t\t : liste tous les scripts disponibles dans le repertoire %s (alias ls)\n", protoColor, SCRIPT_DIR);
	fprintf(file, "    \033[%smhelp <instruction/commande>\033[0m\t : affiche le help concernant l'objet indique (all affiche tous les helps) (alias h)\n", protoColor);
	fprintf(file, "    \033[%smexit\033[0m\t\t\t : quitte le programme (alias q)\n", protoColor);
}

void printHelpCommande(FILE * file){
	fprintf(file, "  \033[%smListe des commandes executables sur les images :\033[0m\n", titreColor);
	fprintf(file, "    \033[%sm%s\033[0m\t\t: cree une image initialisee dans le numero vide specifie avec les largeur et hauteur d'une autre image ou celles mises en parametre\n", protoColor, ProtoCREATE);
	fprintf(file, "    \033[%sm%s\033[0m\t\t\t\t\t: met tous les pixels de l'image a 0 (noir)\n", protoColor, ProtoINIT);
	fprintf(file, "    \033[%sm%s\033[0m\t\t\t: charge une image a partir d'un fichier dont le nom est donne\n", protoColor, ProtoLOAD);
	fprintf(file, "    \033[%sm%s\033[0m\t\t: enregistre une image dans le fichier designe, dans son format original ou dans le format specifie par (int) <type>\n", protoColor, ProtoSAVE);
	fprintf(file, "    \033[%sm%s\033[0m\t\t: affiche l'image ou une portion de l'image dans le terminal\n", protoColor, ProtoPRINT);
	fprintf(file, "    \033[%sm%s\033[0m\t\t\t\t: copie l'image 2 dans l'image 1. Elles doivent avoir la meme dimention\n", protoColor, ProtoCOPY);
	fprintf(file, "    \033[%sm%s\033[0m\t: copie l'image 2 sur l'image 1 en positionnant le coin en haut a gauche en (x0,y0) et avec une option de transparence\n", protoColor, ProtoPASTE);
	fprintf(file, "    \033[%sm%s\033[0m\t\t: conserve uniquement le cadre defini dans l'image. L'image est redimentionnee\n", protoColor, ProtoCUT);
	fprintf(file, "    \033[%sm%s\033[0m\t\t\t: ajoute l'image 2 a cote de l'image 1. Le cote est defini par <pos>. L'image 1 est redimentionnee\n", protoColor, ProtoADD);
	fprintf(file, "    \033[%sm%s\033[0m\t: cree un cadre de 1px sur l'image. Le cadre est defini par ses 2 coins (haut-gauche et bas-droit)\n", protoColor, ProtoFRAME);
	fprintf(file, "    \033[%sm%s\033[0m\t\t\t\t\t: passe l'image en negatif\n", protoColor, ProtoINV);
	fprintf(file, "    \033[%sm%s\033[0m\t\t\t: conserve uniquement la couleur voulue dans l'image (le canal par defaut ou les pixels si l'option est mise)\n", protoColor, ProtoKEEP);
	fprintf(file, "    \033[%sm%s\033[0m\t\t: modifie le pixel de l'image en lui mettant la couleur definie\n", protoColor, ProtoSETPIX);
	fprintf(file, "    \033[%sm%s\033[0m\t\t: applique un filtre sur l'image (voir \"help filtre\" pour plus d'informations)\n", protoColor, ProtoFILTRE);
	fprintf(file, "    \033[%sm%s\033[0m\t\t\t\t\t: supprime une image\n", protoColor, ProtoCLOSE);
	fprintf(file, "    \033[%sm%s\033[0m\t\t\t\t\t\t: termine l'enchainement et reinitialise toutes les images\n", protoColor, ProtoFIN);
}

void printHelpCREATE(FILE * file){
	fprintf(file, "  \033[%sm%s\033[0m\n", protoColor, ProtoCREATE);
	fprintf(file, "    La commande CREATE est utiliser pour creer des images initialisees sans les charger depuis des fichiers.\n");
	fprintf(file, "    L'image cree est affectee au numero (int) <no> (qui doit etre libre\n");
	fprintf(file, "    La taille de l'image est soit definie en parametre (int) <l> et (int) <h> soit heritee d'une autre image deja creee (int) <no>\n");
	fprintf(file, "    Le type de l'image est systematiquement 3\n");
	fprintf(file, "    [INFO] La commande \"usedImages\" liste les images utilisees dans l'espace de travail ce qui permet de savoir lesquelles sont utilisees\n");
}

void printHelpINIT(FILE * file){
	fprintf(file, "  \033[%sm%s\033[0m\n", protoColor, ProtoINIT);
	fprintf(file, "    La commande INIT prend un seul entier en parametre qui est le numero de l'image cible (<no>).\n");
	fprintf(file, "    Cette commande effece le contenu de l'image cible et le met a 0.\n");
	fprintf(file, "    [INFO] La commande \"PRINT\" permet de voir tout ou partie d'une image.\n");
}

void printHelpLOAD(FILE * file){
	fprintf(file, "  \033[%sm%s\033[0m\n", protoColor, ProtoLOAD);
	fprintf(file, "    La commande LOAD prend deux arguments. Le numero (int) de l'image qui recevra le contenu du fichier (<no>) et le nom du fichier (avec l'extention) (<filename>).\n");
	fprintf(file, "    L'image est automatiquement cherchee dans le dossier %s. Pour changer de dossier, il suffit de preciser l'arborescence.\n", IMG_DIR);
	fprintf(file, "    Le numero designe doit etre libre (pas d'image chargee) sinon l'image ne sera pas cree.\n");
	fprintf(file, "    [INFO] La commande \"usedImages\" liste les images utilisees (pour l'espace de travail).\n");
}

void printHelpSAVE(FILE * file){
	fprintf(file, "  \033[%sm%s\033[0m\n", protoColor, ProtoSAVE);
	fprintf(file, "    La commande SAVE prend deux arguments obligatoires. Le numero (int) de l'image a enregistrer, le nom du fichier ou enregistrer l'image (sans l'extention).\n");
	fprintf(file, "    Par defaut, l'image est enregistree dans son type d'origine et recoit l'extention en rapport.\n");
	fprintf(file, "    Il est toutefois possible de force le type de l'image enregistree avec le troisieme argument (int) qui peut prendre les valeurs 1, 2 ou 3.\n");
	fprintf(file, "    L'image est automatiquement enregistree dans le dossier %s. Pour changer de dossier, il suffit de preciser l'arborescence.\n", IMG_DIR);
}

void printHelpPRINT(FILE * file){
	fprintf(file, "  \033[%sm%s\033[0m\n", protoColor, ProtoPRINT);
	fprintf(file, "    La commande PRINT prend un seul argument obligatoire qui est le numero de l'image a afficher (<no>).\n");
	fprintf(file, "    Pour les grandes images et de maniere optionnelle, il est possible d'afficher qu'une partie de l'image selectionnee par le coin haut gauche (x0,y0) et bas droit (x1,y1).\n");
	fprintf(file, "    x0, y0, x1, y1 sont des entiers et doivent etre situes dans l'image.\n");
}

void printHelpCOPY(FILE * file){
	fprintf(file, "  \033[%sm%s\033[0m\n", protoColor, ProtoCOPY);
	fprintf(file, "    La commande COPY prend deux arguments. Le premier est le numero de l'image (int) <no1> qui recevra la copie et le second le numero de l'image (int) <no2> qui sera copiee\n");
	fprintf(file, "    Les deux images doivent avoir exactement la meme taille pour pouvoir etre copiees.\n");
	fprintf(file, "    [INFO] Pour la copie d'images n'ayant pas la meme dimension, voir le commande PASTE.\n");
}

void printHelpPASTE(FILE * file){
	fprintf(file, "  \033[%sm%s\033[0m\n", protoColor, ProtoPASTE);
	fprintf(file, "    La commande PASTE prend quatre arguments obligatoires. Le premier est le numero de l'image (int) <no1> qui recevra la copie. Le second (int) <x0> et le troisieme (int) <y (int) <x0>0> sont les coordonnes ou se positionnera le coin haut gauche de l'image a copier. Le quatrieme (int) <no2> est le numero de l'image qui sera copiee sur l'image 1.\n");
	fprintf(file, "    Les tailles des images 1 et 2 n'ont pas d'importance. Les pixels de l'image 2 depassant de l'image 1 seront tout simplement ignores.\n");
	fprintf(file, "    Deux arguments optionnels sont disponibles. Il permettent de definir le type de copie.\n");
	fprintf(file, "    Actuellement, seul le mode transparence est disponible. Pour l'activer, l'argument <type> prend la valeur \"moy\" et l'argument (int) <%%> prend une valeur du pourcentage de transparence de l'image copiee (entre 0 et 100).\n");
}

void printHelpCUT(FILE * file){
	fprintf(file, "  \033[%sm%s\033[0m\n", protoColor, ProtoCUT);
	fprintf(file, "    La commande CUT prend cinq arguments. Le premier (int) <no> est le numero de l'image qui sera coupee. Les quatre autres (int) <x0> (int) <y0> (int) <x1> (int) <y1> definissent la zone de l'image qui sera conservee par le coin haut gauche (x0,y0) et bas droit (x1,y1).\n");
	fprintf(file, "    L'image cible sera donc redimentionnee en consequence.\n");
}

void printHelpADD(FILE * file){
	fprintf(file, "  \033[%sm%s\033[0m\n", protoColor, ProtoADD);
	fprintf(file, "    La commande ADD prend trois arguments. Les numeros des deux images associees (int) <no1> (int) <no2> ainsi que la position de l'image 2 par rapport a l'image 1.\n");
	fprintf(file, "    Les attributs de positionnement de l'image 2 sont : \"haut\", \"droite\", \"bas\" et \"gauche\"\n");
	fprintf(file, "    La nouvelle image composee des deux images juxtaposee est stockee dans l'image 1 qui est donc redimentionnee pour pouvoir accueillir l'image 2.\n");
}

void printHelpFRAME(FILE * file){
	fprintf(file, "  \033[%sm%s\033[0m\n", protoColor, ProtoFRAME);
	fprintf(file, "    La commande FRAME prend huit arguments. Le numero de l'image concernee (int) <no>, le positionnement du cadre a l'aide du coin haut gauche ( (int) <x0>, (int) <y0> ) et du coin bas droit ( (int) <x1>, (int) <y1> ). Le cadre dessine est de la couleur definie par (int) <R> (int) <V> (int) <B>.\n");
	fprintf(file, "    Les entiers des couleurs doivent etre definis entre 0 et 255.\n");
}

void printHelpINV(FILE * file){
	fprintf(file, "  \033[%sm%s\033[0m\n", protoColor, ProtoINV);
	fprintf(file, "    La commande INV inverse tous les pixels de l'image cible designee par le parametre (int) <no>.\n");
	fprintf(file, "    L'operation effectuee est 255-pix\n");
}

void printHelpKEEP(FILE * file){
	fprintf(file, "  \033[%sm%s\033[0m\n", protoColor, ProtoKEEP);
	fprintf(file, "    La commande KEEP conserve uniquement la composante choisie de l'image cible designee par le parametre (int) <no>.\n");
	fprintf(file, "    La couleur est determinee par R, V ou B\n");
}

void printHelpSETPIX(FILE * file){
	fprintf(file, "  \033[%sm%s\033[0m\n", protoColor, ProtoSETPIX);
	fprintf(file, "    La commande SETPIX permet de definir librement la couleur de n'importe quel pixel.\n");
	fprintf(file, "    Elle prend donc en argument le numero de l'image modifiee (int) <no>, la position du pixel a modifier (int) <x0> (int) <y0> et la couleur a mettre dans le pixel (int) <R> (int) <V> (int) <B>\n");
	fprintf(file, "    Les entiers des couleurs doivent etre definis entre 0 et 255.\n");
}

void printHelpFILTRE(FILE * file){
	fprintf(file, "  \033[%sm%s\033[0m\n", protoColor, ProtoFILTRE);
	fprintf(file, "    La commande FILTRE execute un filtre sur l'image designee par (int) <no>.\n");
	fprintf(file, "    Les filtres actuellement disponibles sont :\n");
	fprintf(file, "      - sobel\t: \033[%sm%s\033[0m\t\t\t\t: filtre de sobel.\n", protoColor, ProtoFILTREsobel);
	fprintf(file, "      - moy\t: \033[%sm%s\033[0m\t\t\t: filtre de moyennage des pixels. Le parametre (int) <taille> definit le voisinage\n", protoColor, ProtoFILTREmoy);
	fprintf(file, "      - med\t: \033[%sm%s\033[0m\t\t\t: filtre median. Le parametre (int) <taille> definit le voisinage\n", protoColor, ProtoFILTREmed);
	fprintf(file, "      - prewitt\t: \033[%sm%s\033[0m\t\t\t\t: filtre de prewitt\n", protoColor, ProtoFILTREprewitt);
	fprintf(file, "      - roberts\t: \033[%sm%s\033[0m\t\t\t\t: filtre de roberts\n", protoColor, ProtoFILTREroberts);
	fprintf(file, "      - mdif\t: \033[%sm%s\033[0m\t\t\t\t: filtre mdif\n", protoColor, ProtoFILTREmdif);
	fprintf(file, "      - f1\t: \033[%sm%s\033[0m\t; defini un filtre avec une matrice unique\n", protoColor, ProtoFILTREf1);
	fprintf(file, "      - f2\t: \033[%sm%s\033[0m\t: defini un filtre avec deux matrices\n", protoColor, ProtoFILTREf2);
	fprintf(file, "    Pour les deux dernieres options (-f1 et -f2), (int) <x0> et (int) <y0> definissent les largeurs et hauteurs des matrices utilisees. <mat>, <mat1> et <mat2> definissent les matrices. Le coefficients vont de -9 a 9 et sont tous colles pour ne former qu'un mot. Pour l'instruction -f1, le parametre (int) <div> permet de diviser tous coefficients par cette valeur. S'il n'est pas precise, les coefficients seront divises par la somme des coefficients de la matrice ou 1 ci celle-ci vaut 0.\n");
}

void printHelpCLOSE(FILE * file){
	fprintf(file, "  \033[%sm%s\033[0m\n", protoColor, ProtoCLOSE);
	fprintf(file, "    La commande CLOSE permet de fermer une image utilisee. Cela a pour effet de liberer la memoire utilisee par cette image et de rendre a nouveau disponible ce numero d'image.\n");
	fprintf(file, "    Elle prend donc en argument le numero de l'image a fermer (int) <no>.\n");
	fprintf(file, "    Toutes les images doivent etre fermees avant la fin de la sequence.\n");
}

void printHelpFIN(FILE * file){
	fprintf(file, "  \033[%sm%s\033[0m\n", protoColor, ProtoFIN);
	fprintf(file, "    La commande FIN termine une sequence d'instructions.\n");
	fprintf(file, "    Toutes les instructions se trouvant apres cette commande sont ignorees et toutes les images encore ouvertes sont fermees lorsqu'elle s'execute. Cette commande doit toujours etre presente pour terminer une sequence.\n");
}














































int secretPrint(char ** commande_txt){
	if(strcmp(commande_txt[0], "42") == 0){
	  printf("\n\n               (    \\              /    )\n");
		printf("                \\    \\            /    /\n");
		printf("                 \\    \\          /    /\n");
		printf("                  \\.../;¯.|.¯`\\ /    /\n");
		printf("                  /    |....|....  (¯`\\ \n");
		printf("                 |     |;¯.|;¯.|\\    |\n");
		printf("                 \\      ` ¯..¯ ;     /\n");
		printf("                  \\_ ____________ _/\n\n\n\n");
		return 0;
	}
	else if(strcmp(commande_txt[0], "La") == 0 && strcmp(commande_txt[1], "grande") == 0 && strcmp(commande_txt[2], "question") == 0 && strcmp(commande_txt[3], "de") == 0 && strcmp(commande_txt[4], "la") == 0 && strcmp(commande_txt[5], "vie") == 0){
		printf("\n                                  42\n\n\n");	
		return 0;
	}
	else if(strcmp(commande_txt[0], "PFC") == 0){
		JeuPFC();
		printf("\n");
		return 0;
	}
	
	return 1;
}

long ordi(long min ,long max, long pnj){
    	srand(time(NULL));
    	pnj = (rand() % (max - min + 1)) + min;
	return pnj;
}

void possibilites(long pj, long pnj){
   static long scpj=0 , scpnj=0;
   if ((pj == 1 && pnj==1) || (pj==2 && pnj==2) || (pj==3 && pnj==3)){
	printf("Manche nulle, Score: vous %ld , ordinateur %ld\n\n", scpj, scpnj);
   }
   else if((pj == 2 && pnj==1)||(pj==3 && pnj==2)||(pj==1 && pnj==3)){
      scpj++;
      printf("Vous remportez la manche, Score: vous %ld , ordinateur %ld\n\n", scpj, scpnj);
   }
   else if ((pj == 1 && pnj==2)||(pj==2 && pnj==3)||(pj==3 && pnj==1)){
      scpnj+=1;
      printf("L'ordinateur remporte la manche, Score: vous %ld , ordinateur %ld\n\n", scpj, scpnj);
   }
}

void draw(long pj,long pnj){
	switch(pj){
		case 1:
			printf("Joueur : Pierre  \n");
			break;
		case 2:
			printf("Joueur : Feuille  \n");
			break;
		case 3:
			printf("Joueur : Ciseau  \n");
			break;
		default:
			break;
	}
	
	switch(pnj){
		case 1:
			printf("Ordi : Pierre  \n");
			break;
		case 2:
			printf("Ordi : Feuille  \n");
			break;
		case 3:
			printf("Ordi : Ciseau  \n");
			break;
		default:
			break;
	}
}

void JeuPFC(){
   long pj=0 , min=1 , max=3 , pnj=0 , stop=0 ;
   system("clear");
   printf("Bienvenue dans PFC\n\n");
   while(stop==0)
   {
      printf("1.Pierre\n2.Feuille\n3.Ciseau\n\n");
      scanf("%ld", &pj);
      if(pj == -1){break;}
      pnj=ordi(min,max,pnj);
      system("clear");
      draw(pj,pnj);
      possibilites(pj,pnj);
   }
}




