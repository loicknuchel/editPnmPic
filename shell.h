#ifndef _SHELL_H_
#define _SHELL_H_

int litShellCommande(char ** cmd, int * debut, int exec, int argc, char ** argv, FILE * logs);

int shellScenario(char ** cmd);
int shellInitialise(image * work_img);
int shellExec(int * exec);
int shellExecReal(char ** cmd, image * work_img, int * exec);
int shellScript(char ** cmd, image * work_img);
int shellCarac(char ** cmd, image * work_img);
int shellUnusedImages(image * work_img);
int shellListeImages();
int shellListeScripts();
int shellHelp(char ** cmd);
int shellUnknow(char ** cmd);


#endif /* _SHELL_H_ */


