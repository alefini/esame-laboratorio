#include "../globali.h"
#include "gestione_personaggio.h"
#include "gestione_ambiente.h"
#include "../gestione_storia.h"

#include <stdlib.h>
#include <string.h>

int get_id_oggetto(oggetto obj) {
	return obj.ID;
}

char * get_nome_oggetto(oggetto obj) {
	char *support = calloc(10, sizeof(char));
	strcpy(support, obj.nome);
	return support;
}

bool get_afferrabile_oggetto(oggetto obj) {
	return obj.afferrabile;
}

tipo_oggetto get_tipo_oggetto(oggetto obj) {
	return obj.tipo;
}

void set_id_oggetto(oggetto * obj, int number) {
	obj->ID = number;
	return;
}

void set_nome_oggetto(oggetto *obj, char* nome) {
	strcpy(obj->nome, nome);
	return;
}

void set_afferrabile_oggetto(oggetto *obj, bool aff) {
	obj->afferrabile = aff;
	return;
}

void set_tipo_oggetto(oggetto *obj, char type) {
	obj->tipo = type;
}

void set_punti_vita_cibo(cibo * food, int hp) {
	food->punti_vita = hp;
}

int get_punti_vita_cibo(cibo food) {
	return food.punti_vita;
}

void set_danno_arma(arma * weapon, int danno) {
	weapon->danno = danno;
	return;
}

void set_durezza_arma(arma * weapon, int durezza) {
	weapon->durezza = durezza;
	return;
}

int get_danno_arma(arma weapon)
{
  return weapon.danno;
}

int get_durezza_arma(arma weapon)
{
  return weapon.durezza;
}

char * get_nome_oggetto_guardabile(oggetto_guardabile obj_look) {
	char *support = calloc(10, sizeof(char));
	strcpy(support, obj_look.nome);
	return support;
}

void set_nome_oggetto_guardabile(oggetto_guardabile * obj_look, char * element) {
	strcpy(obj_look->nome, element);
	return;
}

void set_number_id_oggetto_guardabile(oggetto_guardabile * obj_look, int number) {
	obj_look->number_id = number;
}

int get_number_id_oggetto_guardabile(oggetto_guardabile obj_look) {
	return obj_look.number_id;
}

int get_id_oggetto_guardabile(oggetto_guardabile obj_look, int pos) {
	return obj_look.elenco_id[pos];
}

void set_id_oggetto_guardabile(oggetto_guardabile * obj_look, int pos, int element) {
	obj_look->elenco_id[pos] = element;
	return;
}

int impugnare_arma(personaggio *pg, char * nome_arma) {

  int i = 0, esito = 0;
  bool trovato = false;

	oggetto empty;
	set_id_oggetto(&empty, 0);
	set_nome_oggetto(&empty, "vuoto");
	set_afferrabile_oggetto(&empty, false);

  while (get_id_oggetto(get_slot_inventario_personaggio(*pg, i)) != 0 && trovato== false) {
			
    if (strcmp(get_nome_oggetto(get_slot_inventario_personaggio(*pg, i)), nome_arma) == 0) {

			if(get_tipo_oggetto(get_slot_inventario_personaggio(*pg, i)) == 'a') {
				set_weapon_personaggio(pg, get_slot_inventario_personaggio(*pg, i));
				set_slot_inventario_personaggio(pg, i, empty);
			} else esito = -10;
			
      trovato = true;
    }
    i = i + 1;
  }
  if (trovato == false) {
		esito = -6;
	}
  
	return esito;
}

int mangiare_cibo(personaggio *pg, char * nome_cibo)
{
  int hp = get_punti_vita_personaggio(*pg), esito = 0;
	bool trovato = false;

	oggetto empty;
	set_id_oggetto(&empty, 0);
	set_nome_oggetto(&empty, "vuoto");
	set_afferrabile_oggetto(&empty, false);

  if (hp == 100)
  {
    esito = -4;
  }
  else
  {
		int count = 0;
		while(count < MAX_SLOTS && trovato == false) {

			if(strcmp(nome_cibo, get_nome_oggetto(get_slot_inventario_personaggio(*pg, count))) == 0) {

				if(get_tipo_oggetto(get_slot_inventario_personaggio(*pg, count)) == food) {

					set_punti_vita_personaggio(pg, get_punti_vita_cibo(get_slot_inventario_personaggio(*pg, count).oggetto_speciale.food) + get_punti_vita_personaggio(*pg));
					
					set_slot_inventario_personaggio(pg, count, empty);

					if(get_punti_vita_personaggio(*pg) > MAX_HEALTH) {
						set_punti_vita_personaggio(pg, MAX_HEALTH);
					}

				} else {
					esito = -5;
				}

				trovato = true;
			} 

			count = count + 1;
		}

		if(trovato == false) {
			esito = -6;
		}

  }

	return esito;
}

//gestione oggetti apribili
void set_apertura_apribile(oggetto_apribile *obj, bool apertura)
{
  obj->apertura = apertura;
  return;
}

bool get_apertura_apribile(oggetto_apribile obj)
{
  return obj.apertura;
}

void set_id_chiave_da_usare(oggetto_apribile *obj, int id_key)
{
  obj->id_chiave = id_key;
  return;
}

int get_id_chiave_da_usare(oggetto_apribile obj) {
	return obj.id_chiave;
}

int aprire_oggetto(personaggio *pg, char * name_obj) {
  bool trovato = false;
  int i = 0, esito = 0;

	oggetto empty;
	set_id_oggetto(&empty, 0);
	set_nome_oggetto(&empty, "vuoto");
	set_afferrabile_oggetto(&empty, false);

	oggetto temp;

	while(i < get_count_obj_ambiente(stanza_attuale) && trovato == false) {

		if(strcmp(get_nome_oggetto(get_oggetto_ambiente(stanza_attuale, i)), name_obj) == 0) {
			temp = get_oggetto_ambiente(stanza_attuale, i);

			if(get_tipo_oggetto(temp) == key) {

				if(get_apertura_apribile(temp.oggetto_speciale.key) == false) {

					int j = 0;
					while(j< MAX_SLOTS && trovato == false) {

						if(get_id_oggetto(get_slot_inventario_personaggio(*pg, j)) == get_id_chiave_da_usare(temp.oggetto_speciale.key)) {
							set_apertura_apribile(&temp.oggetto_speciale.key, true);		//imposto oggetto Aperto
							set_slot_inventario_personaggio(pg, j, empty);							//elimino la chiave
							trovato = true;
						}

						j = j + 1;
					}

				} else esito = -13; 		//oggetto già aperto

				if(trovato == false) {
					esito = -12;					//oggetto non trovato
				}

			} else {
				esito = -14;						//oggetto non di tipo key
			}

		}

		i = i + 1;
	}

  return esito;
}

int aprire_porta(ambiente * stanza, personaggio * pg, char point) {
	int esito = 0, i = 0;
	bool trovato_1 = false, trovato_2 = false;		//trovato_1 stanza trovato_2 chiave

	while(i < get_count_dir_ambiente(*stanza) && trovato_1 == false) {

		direzione dir = get_direzione_ambiente(*stanza, i);

		if(get_punto_cardinale(dir) == point) {
			trovato_1 = true;

			if(get_apertura_direzione(dir) == false) {

				if(get_id_chiave_direzione(dir) == 0) {
					set_apertura_direzione(&stanza->direzioni_possibili[i], true);
					open_door_from_file(dir, get_posizione_personaggio(*pg));
					trovato_2 = true;
				} else {

					int j = 0;
					while(get_id_oggetto(get_slot_inventario_personaggio(*pg, j)) != 0 && trovato_2 == false) {

						if(get_id_oggetto(get_slot_inventario_personaggio(*pg, j)) == get_id_chiave_direzione(dir)) {
							set_apertura_direzione(&stanza->direzioni_possibili[i], true);
							open_door_from_file(dir, get_posizione_personaggio(*pg));
							trovato_2 = true;
						}

						j = j + 1;
					}

				}			

			} else esito = -13;			//oggetto già aperto

		}

		i = i + 1;

	}

	if(esito == 0) {
		if(trovato_1 == false) {
			esito = -3;
		} else if(trovato_2 == false) {
			esito = -12;
		}
	}

	return esito;
}  