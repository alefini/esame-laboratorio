#ifndef ANALIZZATORE_LESSICALE_H
#define ANALIZZATORE_LESSICALE_H

char* scan(char* input, int offset);
void analizzare_comando(char *input);
char * check_parola_chiave (char * token);
void eseguire_comando (tabella_simboli * tab, personaggio * pg);

#endif