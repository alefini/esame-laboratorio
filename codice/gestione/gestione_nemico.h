#ifndef GESTIONE_NEMICO_H
#define GESTIONE_NEMICO_H

void set_punti_vita_nemico(nemico * enemy, int hp);
int get_punti_vita_nemico(nemico enemy);
void set_arma_nemico(nemico * enemy, oggetto weapon);
oggetto get_arma_nemico(nemico enemy);

#endif