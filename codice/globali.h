#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#ifndef GLOBALI_H
#define GLOBALI_H

#define MAX_SLOTS 10
#define MAX_HEALTH 100
#define MAX_CARATT 500
#define MAX_DIREZIONI 6
#define MAX_KEYWORD 50

typedef enum {
	food = 'c',
	weapon = 'a',
	key = 'k'
} tipo_oggetto;

typedef struct {
  int danno;
  int durezza;
} arma;

typedef struct {
  int punti_vita;
} cibo;

typedef struct { 
  bool apertura;
  int id_chiave;
} oggetto_apribile;

typedef struct {
	cibo food;
	arma weapon;
	oggetto_apribile key;
} special_obj;

typedef struct {
  int ID;
	char nome[20]; 
  bool afferrabile;
	tipo_oggetto tipo;
	special_obj oggetto_speciale;
} oggetto;

typedef struct {
	char nome[20];
	int number_id;
	int elenco_id[MAX_SLOTS];
} oggetto_guardabile;

typedef struct {
	int id_destinazione;
	char punto_cardinale; 
	bool apertura;
	int id_chiave;
} direzione;

typedef struct {
  int id;
	char *descrizione;
  int count_obj;
	oggetto elenco_oggetti[MAX_SLOTS];
	int count_dir;
  direzione direzioni_possibili[MAX_DIREZIONI];
	int count_look;
	oggetto_guardabile looked[MAX_SLOTS]; 
} ambiente;

typedef struct { 
	int posizione;
  int punti_vita;
  oggetto inventario[MAX_SLOTS];
  oggetto weapon;
} personaggio;

typedef struct {
	int punti_vita;
	oggetto weapon;  
} nemico;

typedef struct {
	char parola[20];
	char simbolo[4];
	int number;
} tabella_simboli;

tabella_simboli keywords[MAX_KEYWORD];
tabella_simboli ident[MAX_KEYWORD];
personaggio james;
ambiente stanza_attuale;

#endif