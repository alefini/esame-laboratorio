#ifndef GESTIONE_OGGETTO_H
#define GESTIONE_OGGETTO_H

#include "../globali.h"

//oggetto generale
int get_id_oggetto(oggetto obj);
char * get_nome_oggetto(oggetto obj);
bool get_afferrabile_oggetto(oggetto obj);
tipo_oggetto get_tipo_oggetto(oggetto obj);
void set_id_oggetto(oggetto * obj, int number);
void set_nome_oggetto(oggetto *obj, char* nome);
void set_afferrabile_oggetto(oggetto *obj, bool aff);
void set_tipo_oggetto(oggetto *obj, char type);
//cibo
void set_punti_vita_cibo(cibo *food, int hp);
int get_punti_vita_cibo(cibo food);
int mangiare_cibo(personaggio *pg, char * nome_cibo);
//arma
void set_danno_arma(arma *weapon, int danno);
void set_durezza_arma(arma *weapon, int durezza);
int get_danno_arma(arma weapon);
int get_durezza_arma(arma weapon);

int impugnare_arma(personaggio *pg, char * nome_arma);
//oggetto_apribile
void set_apertura_apribile(oggetto_apribile *obj, bool apertura);
void set_id_chiave_da_usare(oggetto_apribile *obj, int id_key);
bool get_apertura_apribile(oggetto_apribile obj);
int get_id_chiave_da_usare(oggetto_apribile obj);
int aprire_oggetto(personaggio *pg, char * name_obj);
int aprire_porta(ambiente * stanza, personaggio * pg, char point);
//gestione_oggetti_guardabili
char * get_nome_oggetto_guardabile(oggetto_guardabile obj_look);
void set_nome_oggetto_guardabile(oggetto_guardabile * obj_look, char * element);
int get_id_oggetto_guardabile(oggetto_guardabile * obj_look, int pos);
void set_id_oggetto_guardabile(oggetto_guardabile * obj_look, int pos, int element);
void set_number_id_oggetto_guardabile(oggetto_guardabile * obj_look, int number);
int get_number_id_oggetto_guardabile(oggetto_guardabile obj_look);

#endif