#ifndef GESTIONE_STORIA_H
#define GESTIONE_STORIA_H

#include "globali.h"

void descrivere_ambiente(int number_room);
void remove_object_from_file(int id_object);
void insert_object_into_file(oggetto obj, int id_number);
void inizializzazione_file();
void remove_enemy_from_file (int pos);
void open_door_from_file(direzione dir, int pos);

void indovino_indovinello ();

int convert_sequence_char_to_int(char *sequence);

#endif