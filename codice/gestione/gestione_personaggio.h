#ifndef GESTIONE_PERSONAGGIO_H
#define GESTIONE_PERSONAGGIO_H

#include "../globali.h"

void set_punti_vita_personaggio(personaggio *pg, int hp);
void set_slot_inventario_personaggio(personaggio *pg, int pos, oggetto obj);
void set_weapon_personaggio(personaggio *pg, oggetto weapon);
int get_punti_vita_personaggio(personaggio pg);
oggetto get_slot_inventario_personaggio(personaggio pg, int pos);
oggetto get_weapon_personaggio(personaggio pg);
void set_posizione_personaggio(personaggio * pg, int element);
int get_posizione_personaggio(personaggio pg);

void ordinare_inventario(personaggio *pg);
int controllare_inventario(personaggio pg);
int prendere_oggetto(personaggio *pg, char * name_object);
int lasciare_oggetto(personaggio *pg, char *nome_oggetto);
int muovere_personaggio(personaggio * pg, char dir);
int guardare_oggetto(ambiente stanza, char * nome_obj); 

void stampare_inventario(personaggio pg);

void inizializzazione_inventario(personaggio *pg);
void inizializzazione_personaggio(personaggio *pg);

#endif