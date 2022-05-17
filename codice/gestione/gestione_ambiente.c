#include <stdlib.h>
#include "../globali.h"

//gestione destinazione
int get_id_destinazione(direzione dir) {
	return dir.id_destinazione;
}

char get_punto_cardinale(direzione dir) {
	return dir.punto_cardinale;
}

void set_id_destinazione(direzione * dir, int dest) {
	dir->id_destinazione = dest;
	return;
}

void set_punto_cardinale(direzione * dir, char pc) {
	dir->punto_cardinale = pc;
}

bool get_apertura_direzione(direzione dir) {
	return dir.apertura;
}

void set_apertura_direzione(direzione * dir, bool apertura) {
	dir->apertura = apertura;
	return;
}

int get_id_chiave_direzione(direzione dir) {
	return dir.id_chiave;
}

void set_id_chiave_direzione(direzione * dir, int chiave) {
	dir->id_chiave = chiave;
	return;
}


//gestione stanza
int get_id_ambiente (ambiente stanza) {
	return stanza.id;
}

void set_id_ambiente (ambiente * stanza, int id) {
	stanza->id = id;
	return;
}

char * get_descrizione_ambiente(ambiente stanza) {
	return stanza.descrizione;
}

void set_descrizione_ambiente(ambiente * stanza, char * desc) {
	stanza->descrizione = malloc(500 * sizeof(char));
	strncpy(stanza->descrizione, desc, 200);
	return;
}

oggetto get_oggetto_ambiente (ambiente stanza, int pos) {
	return stanza.elenco_oggetti[pos];
}

void set_oggetto_ambiente (ambiente * stanza, int pos, oggetto obj) {
	stanza->elenco_oggetti[pos] = obj;
	return;
}

direzione get_direzione_ambiente (ambiente stanza, int pos) {
	return stanza.direzioni_possibili[pos];
}

void set_direzione_ambiente (ambiente * stanza, int pos, direzione dir) {
	stanza->direzioni_possibili[pos] = dir;
	return;
}

//oggetto guardabile -stanza
oggetto_guardabile get_oggetto_guardabile_ambiente(ambiente stanza, int pos) {
	return stanza.looked[pos];
}

void set_oggetto_guardabile_ambiente(ambiente * stanza, int pos, oggetto_guardabile obj_look) {
	stanza->looked[pos] = obj_look;
	return;
}

//contatori
void set_count_obj_ambiente(ambiente * stanza, int number) {
	stanza->count_obj = number;
	return;
}

int get_count_obj_ambiente(ambiente stanza) {
	return stanza.count_obj;
}

void set_count_dir_ambiente(ambiente * stanza, int number) {
	stanza->count_dir = number;
	return;
}

int get_count_dir_ambiente(ambiente stanza) {
	return stanza.count_dir;
}

void set_count_look_ambiente(ambiente * stanza, int number) {
	stanza->count_look = number;
	return;
}

int get_count_look_ambiente(ambiente stanza) {
	return stanza.count_look;
}