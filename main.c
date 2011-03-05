#include "inc.h"
	
int main(int argc, char ** argv){
	int i, debut = 0, exec = 0;
	char ** cmd = calloc(10, sizeof(char*));
	image * work_img = calloc(MAX_INDEX_IMG, sizeof(image));
	FILE * logs = NULL;
	
	for(i=0; i<MAX_INDEX_IMG; i++){
		init_struct_image(&(work_img[i]));
	}
	for(i=0; i<10; i++){
		cmd[i] = calloc(50, sizeof(char));
		cmd[i][0] = '\0';
	}
	
	logs = fopen(LOG_FILE, "w");
	if(logs == NULL){printf("  \033[%smLe fichier de log (%s) n'a pas pu etre ouvert.\033[0m\n", errorColor, LOG_FILE);}
	
	if(argc > 1){debut = 1;}
	
	printWelcome(stdout);
	
	while(1){
		litShellCommande(cmd, &debut, exec, argc, argv, logs);
		
		     if(exec == 1)									 { shellExecReal(cmd, work_img, &exec);	}
		else if(strcmp(cmd[0], "scenario"    ) == 0 || strcmp(cmd[0], "s" ) == 0){ shellScenario(cmd);				}
		else if(strcmp(cmd[0], "initialise"  ) == 0 || strcmp(cmd[0], "i" ) == 0){ shellInitialise(work_img);			}
		else if(strcmp(cmd[0], "exec"        ) == 0 || strcmp(cmd[0], "e" ) == 0){ shellExec(&exec);				}
		else if(strcmp(cmd[0], "script"      ) == 0 || strcmp(cmd[0], "sc") == 0){ shellScript(cmd, work_img);		}
		else if(strcmp(cmd[0], "carac"       ) == 0 || strcmp(cmd[0], "c" ) == 0){ shellCarac(cmd, work_img);			}
		else if(strcmp(cmd[0], "usedImages"  ) == 0 || strcmp(cmd[0], "u" ) == 0){ shellUnusedImages(work_img);		}
		else if(strcmp(cmd[0], "listeImages" ) == 0 || strcmp(cmd[0], "li") == 0){ shellListeImages();				}
		else if(strcmp(cmd[0], "listeScripts") == 0 || strcmp(cmd[0], "ls") == 0){ shellListeScripts();				}
		else if(strcmp(cmd[0], "help"        ) == 0 || strcmp(cmd[0], "h" ) == 0){ shellHelp(cmd);				}
		else if(strcmp(cmd[0], "exit"        ) == 0 || strcmp(cmd[0], "q" ) == 0){ break;						}
		else												 { shellUnknow(cmd);				}
		
		for(i=0; i<NB_MAX_PARAM; i++){ cmd[i][0] = '\0'; }
	}
	
	for(i=0; i<NB_MAX_PARAM; i++){
		if(cmd[i] != NULL){free(cmd[i]);}
	}
	
	if(cmd != NULL){free(cmd);}
	
	fclose(logs);
	
	printf("\nProgramme termine avec succes\n\n");
	
	#ifdef WIN32
		getchar();
	#endif
	
	return 0;
}

