#ifndef GESTIONE_AMBIENTE_H
#define GESTIONE_AMBIENTE_H

//gestione direzione
int get_id_destinazione(direzione dir);
char get_punto_cardinale(direzione dir);
void set_id_destinazione(direzione * dir, int dest);
void set_punto_cardinale(direzione * dir, char pc);
bool get_apertura_direzione(direzione dir);
void set_apertura_direzione(direzione * dir, bool apertura);
int get_id_chiave_direzione(direzione dir);
void set_id_chiave_direzione(direzione * dir, int chiave);

//gestione ambiente
int get_id_ambiente (ambiente stanza);
void set_id_ambiente (ambiente * stanza, int id);
char * get_descrizione_ambiente(ambiente stanza);
void set_descrizione_ambiente(ambiente * stanza, char * desc);
oggetto get_oggetto_ambiente (ambiente stanza, int pos);
void set_oggetto_ambiente (ambiente * stanza, int pos, oggetto obj);
direzione get_direzione_ambiente (ambiente stanza, int pos);
void set_direzione_ambiente (ambiente * stanza, int pos, direzione dir);
oggetto_guardabile get_oggetto_guardabile_ambiente(ambiente stanza, int pos);
void set_oggetto_guardabile_ambiente(ambiente * stanza, int pos, oggetto_guardabile obj_look);

void set_count_obj_ambiente(ambiente * stanza, int number);
int get_count_obj_ambiente(ambiente stanza);
void set_count_dir_ambiente(ambiente * stanza, int number);
int get_count_dir_ambiente(ambiente stanza);
void set_count_look_ambiente(ambiente * stanza, int number);
int get_count_look_ambiente(ambiente stanza);

#endif