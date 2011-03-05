Concernant les dimensions et les coordonnees, il est possible d'utiliser celles des images.
Par exemple, il est possible de définir la dimension : h(5)+(h2)+3
La priorite des operations n'est pas respectee. Les operations sont effectuees dans l'ordre et il n'est pas possible de mettre des parentheses.

  Liste des instructions disponibles :
    scenario <filename>	 : charge un scenario et propose son execution independament de l'environement de travail (alias s)
    initialise		 : reinitialise l'environnement de travail (supprime toutes les images) (alias i)
    exec <commande>	 : execute la commande passee en parametre dans l'environement de travail (alias e)
    script <filename>	 : charge un script et propose son execution dans l'environement de travail (alias sc)
    carac <no_img>	 : affiche les caracteristiques de l'image demandee (alias c)
    usedImages		 : affiche le numero et la taille de toutes les images utilisees dans l'environement de travail (alias u)
    listeImages		 : liste les fichiers image disponibles dans le repertoire ./images/ (alias l)
    help <instruction>	 : affiche le help concernant l'instruction precisee (alias h)
    exit		 : quitte le programme (alias q)

  Liste des commandes executables :
    CREATE <no> (<l> <h>)|(<no>)		 : cree une image initialisee avec les largeur et hauteur specifies
    INIT <no>					 : met tous les pixels de l'image a 0 (noir)
    LOAD <no> <filename>			 : charge une image a partir du fichier dont le nom est donne
    SAVE <no> <filename> [<type>]		 : enregistre une image dans le fichier designe dans son format original ou dans le forma specifie
    PRINT <no> [<x0> <y0> <x1> <y1>]		 : affiche l'image ou une portion d'image dans le terminal
    COPY <no1> <no2>				 : copie l'image 2 dans l'image 1. Elles doivent avoir la meme dimention
    PASTE <no1> <x0> <y0> <no2> [<type> <%>]	 : copie l'image 2 sur l'image 1 en positionnant le coin en haut a gauche en x0,y0 et avec un fondu en option
    CUT <no> <x0> <y0> <x1> <y1>		 : conserve dans l'image uniquement le cadre defini. L'image est redimentionnee
    ADD <no1> <pos> <no2>			 : ajoute l'image 2 a cote de l'image 1. Le cote est defini par <pos>. L'image 1 est redimentionnee
    FRAME <no> <x0> <y0> <x1> <y1> <R> <V> <B>	 : cree un cadre de 1px sur l'image. Le cadre est defini par ses 2 coins
    INV <no>					 : inverse tous les pixels de l'image
    KEEP <no> R/V/B [pix]			 : conserve uniquement la couleur voulue dans l'image
    SETPIX <no> <x0> <y0> <R> <V> <B>		 : modifie le pixel de l'image en lui mettant la couleur definie
    FILTRE <no> <type> [<params>]		 : applique un filtre sur l'image (NE FONCTIONNE PAS !)
    CLOSE <no>					 : supprime l'image (cad desalloue)
    FIN						 : termine l'enchainement et reinitialise tout

  CREATE <no> (<l> <h>)|(<no>)
    La commande CREATE prend trois entiers en parametre. Le numero d'image (<no>), la largeur (<l>) et la hauteur (<h>) de l'image a creer.
    Cette commande cree une image initialisee avec les dimentions donnees et la stock au numero designe.
    Le numero designe doit etre libre (pas d'image chargee) sinon l'image ne sera pas cree.
    [INFO] La commande "usedImages" liste les images utilisees (pour l'espace de travail).

  INIT <no>
    La commande INIT prend un seul entier en parametre qui est le numero de l'image cible (<no>).
    Cette commande effece le contenu de l'image cible et le met a 0.
    [INFO] La commande "PRINT" permet de voir tout ou partie d'une image.

  LOAD <no> <filename>
    La commande LOAD prend deux arguments. Le numero (int) de l'image qui recevra le contenu du fichier (<no>) et le nom du fichier (avec l'extention) (<filename>).
    L'image est automatiquement cherchee dans le dossier ./images/. Pour changer de dossier, il suffit de preciser l'arborescence.
    Le numero designe doit etre libre (pas d'image chargee) sinon l'image ne sera pas cree.
    [INFO] La commande "usedImages" liste les images utilisees (pour l'espace de travail).

  SAVE <no> <filename> [<type>]
    La commande SAVE prend deux arguments obligatoires. Le numero (int) de l'image a enregistrer, le nom du fichier ou enregistrer l'image (sans l'extention).
    Par defaut, l'image est enregistree dans son type d'origine et recoit l'extention en rapport.
    Il est toutefois possible de force le type de l'image enregistree avec le troisieme argument (int) qui peut prendre les valeurs 1, 2 ou 3.
    L'image est automatiquement enregistree dans le dossier ./images/. Pour changer de dossier, il suffit de preciser l'arborescence.

  PRINT <no> [<x0> <y0> <x1> <y1>]
    La commande PRINT prend un seul argument obligatoire qui est le numero de l'image a afficher (<no>).
    Pour les grandes images et de maniere optionnelle, il est possible d'afficher qu'une partie de l'image selectionnee par le coin haut gauche (x0,y0) et bas droit (x1,y1).
    x0, y0, x1, y1 sont des entiers et doivent etre situes dans l'image.

  COPY <no1> <no2>
    La commande COPY prend deux arguments. Le premier est le numero de l'image (int) <no1> qui recevra la copie et le second le numero de l'image (int) <no2> qui sera copiee
    Les deux images doivent avoir exactement la meme taille pour pouvoir etre copiees.
    [INFO] Pour la copie d'images n'ayant pas la meme dimension, voir le commande PASTE.

  PASTE <no1> <x0> <y0> <no2> [<type> <%>]
    La commande PASTE prend quatre arguments obligatoires. Le premier est le numero de l'image (int) <no1> qui recevra la copie. Le second (int) <x0> et le troisieme (int) <y (int) <x0>0> sont les coordonnes ou se positionnera le coin haut gauche de l'image a copier. Le quatrieme (int) <no2> est le numero de l'image qui sera copiee sur l'image 1.
    Les tailles des images 1 et 2 n'ont pas d'importance. Les pixels de l'image 2 depassant de l'image 1 seront tout simplement ignores.
    Deux arguments optionnels sont disponibles. Il permettent de definir le type de copie.
    Actuellement, seul le mode transparence est disponible. Pour l'activer, l'argument <type> prend la valeur "moy" et l'argument (int) <%> prend une valeur du pourcentage de transparence de l'image copiee (entre 0 et 100).

  CUT <no> <x0> <y0> <x1> <y1>
    La commande CUT prend cinq arguments. Le premier (int) <no> est le numero de l'image qui sera coupee. Les quatre autres (int) <x0> (int) <y0> (int) <x1> (int) <y1> definissent la zone de l'image qui sera conservee par le coin haut gauche (x0,y0) et bas droit (x1,y1).
    L'image cible sera donc redimentionnee en consequence.

  ADD <no1> <pos> <no2>
    La commande ADD prend trois arguments. Les numeros des deux images associees (int) <no1> (int) <no2> ainsi que la position de l'image 2 par rapport a l'image 1.
    Les attributs de positionnement de l'image 2 sont : "haut", "droite", "bas" et "gauche"
    La nouvelle image composee des deux images juxtaposee est stockee dans l'image 1 qui est donc redimentionnee pour pouvoir accueillir l'image 2.

  FRAME <no> <x0> <y0> <x1> <y1> <R> <V> <B>
    La commande FRAME prend huit arguments. Le numero de l'image concernee (int) <no>, le positionnement du cadre a l'aide du coin haut gauche ( (int) <x0>, (int) <y0> ) et du coin bas droit ( (int) <x1>, (int) <y1> ). Le cadre dessine est de la couleur definie par (int) <R> (int) <V> (int) <B>.
    Les entiers des couleurs doivent etre definis entre 0 et 255.

  INV <no>
    La commande INV inverse tous les pixels de l'image cible designee par le parametre (int) <no>.
    L'operation effectuee est 255-pix

  KEEP <no> R/V/B [pix]
    La commande KEEP conserve uniquement la composante choisie de l'image cible designee par le parametre (int) <no>.
    La couleur est determinee par R, V ou B

  SETPIX <no> <x0> <y0> <R> <V> <B>
    La commande SETPIX permet de definir librement la couleur de n'importe quel pixel.
    Elle prend donc en argument le numero de l'image modifiee (int) <no>, la position du pixel a modifier (int) <x0> (int) <y0> et la couleur a mettre dans le pixel (int) <R> (int) <V> (int) <B>
    Les entiers des couleurs doivent etre definis entre 0 et 255.

  FILTRE <no> <type> [<params>]
    La commande FILTRE execute un filtre sur l'image designee par (int) <no>.
    Les filtres actuellement disponibles sont :
      - sobel	: FILTRE <no> -sobel				: filtre de sobel.
      - moy	: FILTRE <no> -moy <taille>			: filtre de moyennage des pixels. Le parametre (int) <taille> definit la carre traite
      - med	: FILTRE <no> -med <taille>			: filtre median. Le parametre (int) <taille> definit la carre traite
      - prewitt	: FILTRE <no> -prewitt				: filtre de prewitt
      - roberts	: FILTRE <no> -roberts				: filtre de roberts
      - mdif	: FILTRE <no> -mdif				: filtre mdif
      - f1	: FILTRE <no> -f1 <x0> <y0> <mat> [<div>]	; defini un filtre avec une matrice unique
      - f2	: FILTRE <no> -f2 <x0> <y0> <mat1> <mat2>	: defini un filtre avec deux matrices
    Pour les deux dernieres options (-f1 et -f2), (int) <x0> et (int) <y0> definissent les largeurs et hauteurs des matrices utilisees. <mat>, <mat1> et <mat2> definissent les matrices. Le coefficients vont de -9 a 9 et sont tous colles pour ne former qu'un mot. Pour l'instruction -f1, le parametre (int) <div> permet de diviser tous coefficients par cette valeur. S'il n'est pas precise, les coefficients seront divises par la somme des coefficients de la matrice ou 1 ci celle-ci vaut 0.

  CLOSE <no>
    La commande CLOSE permet de fermer une image utilisee. Cela a pour effet de liberer la memoire utilisee par cette image et de rendre a nouveau disponible ce numero d'image.
    Elle prend donc en argument le numero de l'image a fermer (int) <no>.
    Toutes les images doivent etre fermees avant la fin de la sequence.

  FIN
    La commande FIN termine une sequence d'instructions.
    Toutes les instructions se trouvant apres cette commande sont ignorees et toutes les images encore ouvertes sont fermees lorsqu'elle s'execute. Cette commande doit toujours etre presente pour terminer une sequence.
    

