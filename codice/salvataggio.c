#include <stdlib.h>
#include "globali.h"
#include "gestione/gestione_personaggio.h"
#include "gestione/gestione_oggetto.h"
#include "gestione_storia.h"
#include "analizzatore_lessicale.h"

void salvataggio_partita(ambiente stanza, personaggio pg) {
	char pathname_storia_corrente[20] = "storia.txt";
	char pathname_storia_salvataggio[40] = "salvataggi/storia_salvataggio.txt";
	char prelievo[MAX_CARATT];
	FILE *file_current, *file_salvataggio;

	//salvataggio storia
	if((file_current = fopen(pathname_storia_corrente, "r")) != NULL && (file_salvataggio = fopen(pathname_storia_salvataggio, "w")) != NULL) {

		while(!feof(file_current)){

			fgets(prelievo, MAX_CARATT, file_current);
			fprintf(file_salvataggio, "%s", prelievo);

		}

	} else printf("Impossibile aprire il file");
	fclose(file_current);
	fclose(file_salvataggio);

	//salvataggio personaggio
	char pathname_personaggio_salvataggio[40] = "salvataggi/personaggio_salvataggio.txt";
	int count = 0;
	if((file_current = fopen(pathname_personaggio_salvataggio, "w")) != NULL) {
		fprintf(file_current, "%d\n", get_posizione_personaggio(pg));
		fprintf(file_current, "%d\n", get_punti_vita_personaggio(pg));

		if(pg.weapon.ID) {
			fprintf(file_current, "&%d %s %d %d\n", get_id_oggetto(get_weapon_personaggio(pg)), get_nome_oggetto(get_weapon_personaggio(pg)), get_danno_arma(get_weapon_personaggio(pg).oggetto_speciale.weapon), get_durezza_arma(get_weapon_personaggio(pg).oggetto_speciale.weapon));
		}

		while(pg.inventario[count].ID != 0 && count < MAX_SLOTS) {
			fprintf(file_current, "%c%d %s ", '*', get_id_oggetto(get_slot_inventario_personaggio(pg, count)), get_nome_oggetto(get_slot_inventario_personaggio(pg, count)));

			if(get_afferrabile_oggetto(get_slot_inventario_personaggio(pg, count)) == true) {
				fprintf(file_current, "%s ", "true");
			} else fprintf(file_current, "%s ", "false");

			if(get_tipo_oggetto(get_slot_inventario_personaggio(pg, count))) {

				if(get_tipo_oggetto(get_slot_inventario_personaggio(pg, count)) == weapon) {
					fprintf(file_current, "%c %d %d", 'a', get_danno_arma(get_slot_inventario_personaggio(pg, count).oggetto_speciale.weapon), get_durezza_arma(get_slot_inventario_personaggio(pg, count).oggetto_speciale.weapon));
				} else if (get_tipo_oggetto(get_slot_inventario_personaggio(pg, count))== food) {
					fprintf(file_current, "%c %d", 'c', get_punti_vita_cibo(get_slot_inventario_personaggio(pg, count).oggetto_speciale.food));
				} else if (get_tipo_oggetto(get_slot_inventario_personaggio(pg, count)) == key) {

					if(get_apertura_apribile(get_slot_inventario_personaggio(pg, count).oggetto_speciale.key) == true) {
						fprintf(file_current, " k true ");
					} else fprintf(file_current, " k false ");

					fprintf(file_current, "%d", get_id_chiave_da_usare(get_slot_inventario_personaggio(pg, count).oggetto_speciale.key));

				}

			}

			fprintf(file_current, "\n");
			count = count + 1;
		}

	} else printf("Impossibile aprire il file");
	fclose(file_current);

	return;
}

void caricare_partita(personaggio * pg) {

	char file_storia_salvataggio[35] = "salvataggi/storia_salvataggio.txt";
	FILE *file_salvataggio;
	char file_storia_caricare[30] = "storia.txt";
	FILE *file_caricare;

	char support[MAX_CARATT];
	//caricamento storia
	if((file_salvataggio = fopen(file_storia_salvataggio, "r")) != NULL && (file_caricare = fopen(file_storia_caricare, "w")) != NULL) {

		while(!(feof(file_salvataggio))) {

			fgets(support, MAX_CARATT, file_salvataggio);
			fprintf(file_caricare, "%s", support);

		}

	} else printf("Impossibile aprire il file");
	fclose(file_caricare);
	fclose(file_salvataggio);

	inizializzazione_inventario(pg);

	char file_dati_pg[40] = "salvataggi/personaggio_salvataggio.txt";
	//caricamento dati pg
	if((file_salvataggio = fopen(file_dati_pg, "r")) != NULL) {
		char *token = calloc(10, sizeof(char));
		int count_inv = 0;

		fgets(support, MAX_CARATT, file_salvataggio);			//prelievo posizione
		token = scan(support, 0);
		set_posizione_personaggio(pg, convert_sequence_char_to_int(token));

		fgets(support, MAX_CARATT, file_salvataggio);			//prelievo punti vita
		token = scan(support, 0);
		set_punti_vita_personaggio(pg, convert_sequence_char_to_int(token));

		while(!feof(file_salvataggio)) {						//prelievo arma + inventario

			int count = 1;
			fgets(support, MAX_CARATT, file_salvataggio);
			oggetto temp;

			if(support[0] == '&') {
				bool id_flag = false, nome_flag = false, danno_flag = false, durezza_flag = false;

				set_afferrabile_oggetto(&temp, true);
				set_tipo_oggetto(&temp, 'a');

				//inizio scansione arma
				while(support[count]) {
					token = scan(support, count);

					if(id_flag == false) {
						set_id_oggetto(&temp, convert_sequence_char_to_int(token));
						id_flag = true;
					} else if(nome_flag == false) {
						set_nome_oggetto(&temp, token);
						nome_flag = true;
					} else if(danno_flag == false) {
						set_danno_arma(&temp.oggetto_speciale.weapon, convert_sequence_char_to_int(token));
						danno_flag = true;
					} else if(durezza_flag == false) {
						set_durezza_arma(&temp.oggetto_speciale.weapon, convert_sequence_char_to_int(token));
						durezza_flag = true;
					}

					if(durezza_flag == true) {
						set_weapon_personaggio(pg, temp);
					}

					int lenght = 0 + strlen(token);
					*token = '\0';
					count = count + 1 + lenght;

				} //fine scansione arma

			} else if(support[0] == '*') {
				bool id_flag = false, nome_flag = false, aff_flag = false, tipo_flag = false, par1_flag = false, par2_flag = false;

				//inizio scansione oggetto trovato
				while(support[count]) {
					token = scan(support, count);

					if(id_flag == false) {

						set_id_oggetto(&temp, convert_sequence_char_to_int(token));
						id_flag = true; 

					} else if(nome_flag == false) {
								
						set_nome_oggetto(&temp, token);
						nome_flag = true;

					} else if(aff_flag == false) {

						if(strcmp(token, "true") == 0) {
							set_afferrabile_oggetto(&temp, true);
						} else {
							set_afferrabile_oggetto(&temp, false);
						}

						aff_flag = true;
					} else if(tipo_flag == false) {

						if(strcmp(token, "a") == 0) {
							set_tipo_oggetto(&temp, weapon);
						} else if(strcmp(token, "c") == 0) {
							set_tipo_oggetto(&temp, food);
						} else if(strcmp(token, "k") == 0) {
							set_tipo_oggetto(&temp, key);
						} 

						tipo_flag = true;
					} else if(par1_flag == false) {
								
						if(get_tipo_oggetto(temp) == weapon) {

							set_danno_arma(&temp.oggetto_speciale.weapon, convert_sequence_char_to_int(token));

						} else if(get_tipo_oggetto(temp) == food) {

							set_punti_vita_cibo(&temp.oggetto_speciale.food, convert_sequence_char_to_int(token));

						} else if(get_tipo_oggetto(temp) == key) {
								
							if(strcmp(token, "true") == 0) {
								set_apertura_apribile(&temp.oggetto_speciale.key, true);
							} else if(strcmp(token, "false") == 0) {
								set_apertura_apribile(&temp.oggetto_speciale.key, false);
							}
									
						}
							
						par1_flag = true;
					}	else if(par2_flag == false) {

						if(get_tipo_oggetto(temp) == weapon) {
							set_durezza_arma(&temp.oggetto_speciale.weapon, convert_sequence_char_to_int(token));
						} else if(get_tipo_oggetto(temp) == key) {
							set_id_chiave_da_usare(&temp.oggetto_speciale.key, convert_sequence_char_to_int(token));
						}

						par2_flag = true;
					}

					if(aff_flag == true) {
						set_slot_inventario_personaggio(pg, count_inv, temp);
					}

					int lenght = 0 + strlen(token);
					*token = '\0';
					count = count + 1 + lenght;
				} // fine scansione oggetto trovato

				count_inv = count_inv + 1;

			}  // fine oggetto trovato
			
			support[0] = '\0';
			set_tipo_oggetto(&temp, 'z');

		}

		descrivere_ambiente(get_posizione_personaggio(*pg));

	} else printf("Impossibile aprire il file");

	return;
}