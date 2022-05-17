#include "../globali.h"
#include "gestione_oggetto.h"
#include "gestione_ambiente.h"
#include "../gestione_storia.h"

void set_punti_vita_personaggio(personaggio *pg, int hp) {
	pg->punti_vita = hp;
}

void set_slot_inventario_personaggio(personaggio *pg, int pos, oggetto obj) {
	pg->inventario[pos] = obj;
}

void set_weapon_personaggio(personaggio *pg, oggetto weapon) {
	pg->weapon = weapon;
}

int get_punti_vita_personaggio(personaggio pg) {
	return pg.punti_vita;
}

oggetto get_slot_inventario_personaggio(personaggio pg, int pos) {
	return pg.inventario[pos];
}

oggetto get_weapon_personaggio(personaggio pg) {
	return pg.weapon;
}

void set_posizione_personaggio(personaggio * pg, int element) {
	pg->posizione = element;
}

int get_posizione_personaggio(personaggio pg) {
	return pg.posizione;
}

void inizializzazione_inventario(personaggio *pg) {
	int count = 0;

	oggetto empty;
	set_id_oggetto(&empty, 0);
	set_nome_oggetto(&empty, "vuoto");
	set_afferrabile_oggetto(&empty, false);

	while(count < MAX_SLOTS) {
		set_slot_inventario_personaggio(pg, count, empty);
		count = count + 1;
	} 

	return;
}

void inizializzazione_personaggio(personaggio *pg) {
	set_posizione_personaggio(pg, 1);
	set_punti_vita_personaggio(pg, MAX_HEALTH);
	inizializzazione_inventario(pg);
}

int controllare_inventario(personaggio pg) {
	int count = 0, pos = -1;

	while(count < MAX_SLOTS && pos == -1) {
		
		if(strcmp(get_nome_oggetto(get_slot_inventario_personaggio(pg, count)), "vuoto") == 0) {
			pos = count;
		}

		count = count + 1;
	}

	return pos;
}

void stampare_inventario(personaggio pg)
{
  int i=0;
  while(i< MAX_SLOTS)
  {
    if(strcmp(get_nome_oggetto(get_slot_inventario_personaggio(pg, i)), "vuoto")!= 0)
    {
      printf("%s ", get_nome_oggetto(get_slot_inventario_personaggio(pg, i)));
    }
    i = i + 1;
  }
  printf("\n");

  return;
}

void ordinare_inventario(personaggio *pg) {

	oggetto empty;
	set_id_oggetto(&empty, 0);
  set_nome_oggetto(&empty, "vuoto");
  set_afferrabile_oggetto(&empty, false);
	
	int count = 0;
	while(count < MAX_SLOTS) {

		if(get_id_oggetto(get_slot_inventario_personaggio(*pg, count)) == 0) {

			int count_1 = count + 1;
			while(count_1 < MAX_SLOTS) {

				if(get_id_oggetto(get_slot_inventario_personaggio(*pg, count_1)) != 0) {
					set_slot_inventario_personaggio(pg, count, get_slot_inventario_personaggio(*pg, count_1));
					set_slot_inventario_personaggio(pg, count_1, empty);
					count_1 = MAX_SLOTS;
				}

				count_1 = count_1 + 1;
			}

		}

		count = count + 1;
	}
}

int prendere_oggetto(personaggio *pg, char * name_object) {
	
	oggetto object;
	int count = 0, pos, esito = 0;
	bool afferrabile = false, trovato = false;

	direzione dir;
	set_id_destinazione(&dir, 16);
	set_punto_cardinale(&dir, 'b');

	while(count < get_count_obj_ambiente(stanza_attuale) && trovato == false) {

		if(strcmp(name_object, get_nome_oggetto(get_oggetto_ambiente(stanza_attuale, count))) == 0) {
			object = get_oggetto_ambiente(stanza_attuale, count);
			afferrabile = get_afferrabile_oggetto(object);
      trovato = true;
		}

		count = count + 1;
	}

  pos = controllare_inventario(*pg);

  if (pos != -1 && afferrabile != false)
  {
    set_slot_inventario_personaggio(pg, pos, object);
		remove_object_from_file(get_id_oggetto(object));

		if(strcmp(name_object, "libro") == 0 && get_posizione_personaggio(*pg) == 15) {
			open_door_from_file(dir, get_posizione_personaggio(*pg));
			printf("\nLa libreria comincia a vibrare ed a muoversi verso ovest, rivelando un passaggio segreto che va verso il basso\n");
		}

		descrivere_ambiente(get_posizione_personaggio(*pg));
  }
  else if (pos == -1)
  {
    esito = -8;
  }
  else esito = -7;

  return esito;
}

int lasciare_oggetto(personaggio *pg, char *nome_oggetto) {
  int i = 0, esito = 0;
  bool trovato = false;

	oggetto empty;
	set_id_oggetto(&empty, 0);
  set_nome_oggetto(&empty, "vuoto");
  set_afferrabile_oggetto(&empty, false);
	
  while (i < MAX_SLOTS && trovato == false) {

    if (strcmp(get_nome_oggetto(get_slot_inventario_personaggio(*pg, i)), nome_oggetto) == 0)
    {
			insert_object_into_file(get_slot_inventario_personaggio(*pg, i), get_posizione_personaggio(*pg));
			descrivere_ambiente(get_posizione_personaggio(*pg));
      set_slot_inventario_personaggio(pg, i, empty);
			ordinare_inventario(pg);
      trovato = true;
    }

    i = i + 1;
  }
  if (trovato == false)
  {
    esito = -6;
  }

  return esito;
}

int muovere_personaggio(personaggio * pg, char dir) {

	int	count = 0, esito = -3;
	while (count < get_count_dir_ambiente(stanza_attuale)) {
		direzione temp = get_direzione_ambiente(stanza_attuale, count);

		if(get_punto_cardinale(temp) == dir) {

			if(get_apertura_direzione(temp)) {
				esito = 0;
				set_posizione_personaggio(pg, get_id_destinazione(temp));
			} else esito = -11;
			
		}

		count = count + 1;
	}

	if(esito == 0) {
		descrivere_ambiente(get_posizione_personaggio(*pg));
	}

	return esito;
}

int guardare_oggetto(ambiente stanza, char * nome_obj) {
	int esito = -7, count = 0;

	if(get_count_look_ambiente(stanza) > 0) {
			
		while(count < get_count_look_ambiente(stanza)) {

			if(strcmp(nome_obj, get_nome_oggetto_guardabile(get_oggetto_guardabile_ambiente(stanza, count))) == 0) {

				esito = 0;
				printf("Hai trovato: ");
				int count_1 = 0;
				while(count_1 < get_number_id_oggetto_guardabile(get_oggetto_guardabile_ambiente(stanza, count))) {

					int id_oggetto = get_id_oggetto_guardabile(&stanza.looked[count], count_1);

					int count_2 = 0;
					while(count_2 < get_count_obj_ambiente(stanza)) {

						if(id_oggetto == get_id_oggetto(get_oggetto_ambiente(stanza, count_2))) {  
							printf("%s ", get_nome_oggetto(get_oggetto_ambiente(stanza, count_2)));
						}

						count_2 = count_2 + 1;
					}

					count_1 = count_1 + 1;
				}
				printf("\n");
				
			}

			count = count + 1;
		}

	} else esito = -9; 


	return esito;
}