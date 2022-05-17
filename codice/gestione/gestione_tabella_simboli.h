#ifndef GESTIONE_TABELLA_SIMBOLI_H
#define GESTIONE_TABELLA_SIMBOLI_H

char * get_parola_tab_simboli(tabella_simboli * tab, int pos);
void set_parola_tab_simboli(tabella_simboli * tab, int pos, char * element);
char * get_simbolo_tab_simboli(tabella_simboli * tab, int pos);
void set_simbolo_tab_simboli(tabella_simboli * tab, int pos, char * element);
int get_number_tab_simboli(tabella_simboli * tab);
void set_number_tab_simboli(tabella_simboli * tab, int element);

void stampa_tabella_simboli (tabella_simboli * tab);

#endif