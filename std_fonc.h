#ifndef _STD_FONC_H_
#define _STD_FONC_H_

int imax(int a, int b);
int imin(int a, int b);
int isint(char * s); /* oui:0, non:1 */
int ispath(char * s); /* oui:0, non:1 */
void emptyBuffer();
int fichierExist(char * filename); /* oui:0, non:1 */
void tri_bulle(int * tab, int t_long);
int mediane(int * tab, int t_long);

#endif /* _STD_FONC_H_ */

