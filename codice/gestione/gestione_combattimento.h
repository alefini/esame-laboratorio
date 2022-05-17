#ifndef GESTIONE_COMBATTIMENTO_H
#define GESTIONE_COMBATTIMENTO_H

void attaccare_nemico(nemico *enemy, arma arma_pg);
void difendere_nemico(nemico *enemy);
void attaccare_personaggio(personaggio *pg, arma arma_enemy);
void difendere_personaggio(personaggio *pg);
void combattimento (personaggio *pg , nemico *enemy);

#endif