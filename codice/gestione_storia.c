#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "globali.h"
#include "analizzatore_lessicale.h"
#include "gestione/gestione_oggetto.h"
#include "gestione/gestione_ambiente.h"
#include "gestione/gestione_nemico.h"
#include "gestione/gestione_combattimento.h"
#include "gestione_storia.h"

// ^id_stanza
// *OGGETTI
// %direzioni

void inizializzazione_oggetti_ambienti();

void descrivere_ambiente(int room_number) {

	char pathname[20] = "storia.txt", prelievo[MAX_CARATT];
	FILE *file_storia;
	bool trovato = false;
	nemico enemy;
	
	if((file_storia = fopen(pathname, "r")) != NULL) {
		rewind(file_storia);

		while(!feof(file_storia) && trovato == false) {

			char *token = malloc(20 * sizeof(char));

			fgets(prelievo, MAX_CARATT, file_storia);

			if(prelievo[0] == '^') {
				token = scan(prelievo, 1);

				if(convert_sequence_char_to_int(token) == room_number) {
					set_id_ambiente(&stanza_attuale, room_number);
					trovato = true;
				}

				*token = '\0';
			}

			if(trovato == true) {

				inizializzazione_oggetti_ambienti();
				set_count_obj_ambiente(&stanza_attuale, 0);
				set_count_dir_ambiente(&stanza_attuale, 0);
				set_count_look_ambiente(&stanza_attuale, 0);

				//printf("\033[0;0H\033[2J");

				while(prelievo[0] != '_') {

					fgets(prelievo, MAX_CARATT, file_storia);

					if(prelievo[0] != '/' && prelievo[0] != '&' && prelievo[0] != '$' && prelievo[0] != '*' && prelievo[0] != '%' && prelievo[0] != '_') {

						set_descrizione_ambiente(&stanza_attuale, prelievo);
						printf("%s", prelievo);
					
					} else if(prelievo[0] == '&') {							//nemico

						int count = 1;
						bool hp_flag = false, danno_flag = false, durezza_flag = false;
						oggetto wpn_enemy;
						while(prelievo[count]) {
							token = scan(prelievo, count);
							int number = convert_sequence_char_to_int(token);

							if(hp_flag == false) {
								set_punti_vita_nemico(&enemy, number);
								hp_flag = true;
							} else if(get_punti_vita_nemico(enemy) > 0) {

								if(danno_flag == false) {
									set_danno_arma(&wpn_enemy.oggetto_speciale.weapon, number);
									danno_flag = true;
								} else if(durezza_flag == false) {
									set_durezza_arma(&wpn_enemy.oggetto_speciale.weapon, number);
									durezza_flag = true;
								}

								if(danno_flag == true && durezza_flag == true) {
									set_arma_nemico(&enemy, wpn_enemy);

									fgets(prelievo, MAX_CARATT, file_storia);

									if(prelievo[0] == '$') {
										printf("%s", prelievo);
										combattimento(&james, &enemy);
									}
									
								}

							}

							int lenght = 0 + strlen(token);
							count = count + 1 + lenght;
						}

					} else if(prelievo[0] == '/') {							//guarda
						oggetto_guardabile temp;
						int count = 1;
						set_number_id_oggetto_guardabile(&temp, 0);
						
						bool nome_flag = false;

						while(prelievo[count]) {
							token = scan(prelievo, count);

							if(nome_flag == false) {
								set_nome_oggetto_guardabile(&temp, token);
								nome_flag = true;	
							} else {
								set_id_oggetto_guardabile(&temp, get_number_id_oggetto_guardabile(temp), convert_sequence_char_to_int(token));
								set_number_id_oggetto_guardabile(&temp, get_number_id_oggetto_guardabile(temp) + 1);
							}

							int lenght = 0 + strlen(token);
							count = count + 1 + lenght;
						}

						set_oggetto_guardabile_ambiente(&stanza_attuale, get_count_look_ambiente(stanza_attuale), temp);
						set_count_look_ambiente(&stanza_attuale, get_count_look_ambiente(stanza_attuale) + 1);

					} else if(prelievo[0] == '*') {							//oggetto
						bool id_flag = false, nome_flag = false, aff_flag = false, tipo_flag = false, par1_flag = false, par2_flag = false;
						oggetto temp;
						int count = 1;

						while(prelievo[count]) {
							token = scan(prelievo, count);

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

							int lenght = 0 + strlen(token);
							*token = '\0';
							count = count + 1 + lenght;
						}

						set_oggetto_ambiente(&stanza_attuale, get_count_obj_ambiente(stanza_attuale), temp);
						set_count_obj_ambiente(&stanza_attuale, get_count_obj_ambiente(stanza_attuale) + 1);
						set_tipo_oggetto(&temp, 'z');

					} else if(prelievo[0] == '%') {					//direzioni possibili
						bool id_flag = false, dir_flag = false, apertura_flag = false, id_chiave_flag = false;
						int count = 1;
						direzione temp;

						while(prelievo[count]) {
							token = scan(prelievo, count);

							if(id_flag == false) {
								set_id_destinazione(&temp, convert_sequence_char_to_int(token));
								id_flag = true;
							} else if(dir_flag == false) {
								set_punto_cardinale(&temp, *token);
								dir_flag = true;
							} else if(apertura_flag == false) {

								if(strcmp(token, "true") == 0) {
									set_apertura_direzione(&temp, true);
								} else if(strcmp(token, "false") == 0){
									set_apertura_direzione(&temp, false);
								}

								apertura_flag = true;
							} else if(id_chiave_flag == false) {
								set_id_chiave_direzione(&temp, convert_sequence_char_to_int(token));
								id_chiave_flag = true;
							}

							int lenght = 0 + strlen(token);
							*token = '\0';
							count = count + 1 + lenght;
						}

						set_direzione_ambiente(&stanza_attuale, get_count_dir_ambiente(stanza_attuale), temp);
						set_count_dir_ambiente(&stanza_attuale, get_count_dir_ambiente(stanza_attuale) + 1);
					}

					*token = '\0';
				}

			}

			free(token);
		}
		
	} else printf("Impossibile aprire il file");

	fclose(file_storia);
}

void inizializzazione_oggetti_ambienti() {

	oggetto empty;
	set_id_oggetto(&empty, 0);
	set_nome_oggetto(&empty, "empty");
	set_afferrabile_oggetto(&empty, false);

	int count = 0;
	while(count <= MAX_SLOTS) {
		set_oggetto_ambiente(&stanza_attuale, count, empty);
		count = count + 1;
	}

	return;
}

int convert_sequence_char_to_int(char *sequence) {
	int count = strlen(sequence)-1;
	int number = 0, moltiplicator = 1;

	while(count >= 0) {
		number = ((sequence[count] - '0') * moltiplicator) + number;

		moltiplicator = moltiplicator * 10;
		count = count - 1;
	}

	return number;
}

void inizializzazione_file() {
	char pathname_write[30] = "storia.txt";
	FILE *file_write;
	char pathname_read[30] = "storia_originale.txt";
	FILE *file_read;

	char prelievo[MAX_CARATT];

	if((file_read = fopen(pathname_read, "r")) != NULL && (file_write = fopen(pathname_write, "w")) != NULL) {

		while(!feof(file_read)) {

			fgets(prelievo, MAX_CARATT, file_read);
	
			fprintf(file_write, "%s", prelievo);

		}
	}

	fclose(file_read);
	fclose(file_write);
}

void remove_object_from_file(int id_object) {
	char pathname_write[30] = "storia_support.txt";
	FILE *file_write;
	char pathname_read[30] = "storia.txt";
	FILE *file_read;

	char prelievo[MAX_CARATT];
	char *token = calloc(10, sizeof(char));

	if((file_read = fopen(pathname_read, "r")) != NULL && (file_write = fopen(pathname_write, "w")) != NULL) {

		while(!feof(file_read)) {

			fgets(prelievo, MAX_CARATT, file_read);

			if(prelievo[0] == '*') {
				token = scan(prelievo, 1);
				int number = convert_sequence_char_to_int(token);

				if(number != id_object) {
					fprintf(file_write, "%s", prelievo);
				}

				*token = '\0';

			} else fprintf(file_write, "%s", prelievo);
	
		}


	} else printf("Impossibile aprire il file");

	fclose(file_read);
	fclose(file_write);

	remove(pathname_read);
	rename(pathname_write, pathname_read);
}

void insert_object_into_file(oggetto obj, int id_number) {

	char pathname_storia[30] = "storia.txt";
	FILE *file_storia;
	char pathname_support[30] = "support_storia.txt";
	FILE *file_support;
	char support[MAX_CARATT];
	char *token = calloc(10, sizeof(char));

	if((file_storia = fopen(pathname_storia, "r")) != NULL && (file_support = fopen(pathname_support, "w")) != NULL) {

		while(!feof(file_storia)) {

			fgets(support, MAX_CARATT, file_storia);
			
			if(support[0] == '^') {
				token = scan(support, 1);
				
				if(convert_sequence_char_to_int(token) == id_number) {
					
					while (support[0] != '*' && support[0] != '%') {
						fprintf(file_support, "%s", support);
						fgets(support, MAX_CARATT, file_storia);
					}
					
					fprintf(file_support, "*%d %s ", get_id_oggetto(obj), get_nome_oggetto(obj));

					if(get_afferrabile_oggetto(obj) == true) {
						fprintf(file_support, "true");
					} else fprintf(file_support, "false");

					if(get_tipo_oggetto(obj)) {

						if(get_tipo_oggetto(obj) == weapon) {
							fprintf(file_support, " a %d %d", get_danno_arma(obj.oggetto_speciale.weapon), get_durezza_arma(obj.oggetto_speciale.weapon));
						} else if(get_tipo_oggetto(obj) == food) {
							fprintf(file_support, " c %d", get_punti_vita_cibo(obj.oggetto_speciale.food));
						} else if(get_tipo_oggetto(obj) == key) {

							if(get_apertura_apribile(obj.oggetto_speciale.key) == true) {
								fprintf(file_support, " k true ");
							} else {
								fprintf(file_support, " k false ");
							}

							fprintf(file_support, "%d", get_id_chiave_da_usare(obj.oggetto_speciale.key));

						}

					}

					fprintf(file_support, "\n%s", support);

				} else fprintf(file_support, "%s", support); 

				*token = '\0';

			} else fprintf(file_support, "%s", support);
 
		}

	} else printf("Impossibile aprire il file"); 
	fclose(file_storia);
	fclose(file_support);

	remove(pathname_storia);
	rename(pathname_support, pathname_storia);

	return;
}

void remove_enemy_from_file (int pos) {
	char pathname_storia[20] = "storia.txt";
	FILE *file_storia;
	char pathname_support[20] = "storia_support.txt";
	FILE *file_support;

	char support[MAX_CARATT];
	char *token = calloc(10, sizeof(char));

	if((file_storia = fopen(pathname_storia, "r")) != NULL && (file_support = fopen(pathname_support, "w")) != NULL) {

		while(!feof(file_storia)) {

			fgets(support, MAX_CARATT, file_storia);

			if(support[0] == '^') {

				token = scan (support, 1);
				fprintf(file_support, "%s", support);

				if(convert_sequence_char_to_int(token) == pos) {

					while(support[0] != '_') {

						fgets(support, MAX_CARATT, file_storia);

						if(support[0] != '$' && support[0] != '&') {
							fprintf(file_support, "%s", support);
						}

					}

				}

			} else fprintf(file_support, "%s", support);

		}

	} else printf("Impossibile aprire il file");
	
	fclose(file_storia);
	fclose(file_support);

	remove(pathname_storia);
	rename(pathname_support, pathname_storia);

	return;
}

void open_door_from_file(direzione dir, int pos) {
	char pathname_storia[40] = "storia.txt";
	FILE *file_storia;
	char pathname_support[40] = "storia_support.txt";
	FILE *file_support;

	char prelievo[MAX_CARATT];
	char *token = calloc(10, sizeof(char));

	if((file_storia = fopen(pathname_storia, "r")) != NULL && (file_support = fopen(pathname_support, "w")) != NULL) {

		while(!feof(file_storia)) {

			fgets(prelievo, MAX_CARATT, file_storia);

			if(prelievo[0] == '^') {
				token = scan(prelievo, 1);
				fprintf(file_support, "%s", prelievo);

				if(convert_sequence_char_to_int(token) == pos) {

					while(prelievo[0] != '_') {
						fgets(prelievo, MAX_CARATT, file_storia);

						if(prelievo[0] == '%') {
							*token = '\0';
							token = scan(prelievo, 1);
							if(convert_sequence_char_to_int(token) == get_id_destinazione(dir)) {
								fprintf(file_support, "%c%d %c true 0\n", prelievo[0],get_id_destinazione(dir), get_punto_cardinale(dir));
							} else fprintf(file_support, "%s", prelievo);

						} else fprintf(file_support, "%s", prelievo);

					}

				}

				*token = '\0';

			} else fprintf(file_support, "%s", prelievo);

		}

	} else printf("Impossibile aprire il file");
	fclose(file_storia);
	fclose(file_support);

	remove(pathname_storia);
	rename(pathname_support, pathname_storia);

	return;
}

void indovino_indovinello () {

	int number;
	char *answer = calloc(10, sizeof(char));

	direzione dir;
	set_id_destinazione(&dir, 15);
	set_punto_cardinale(&dir, 'n');

	printf("Lì vicino c’è un uomo anziano in ginocchio: pensi che stia pregando ma in realtà ha sentito la tua presenza e sussurra “Sei entrato in un luogo sacro, parla con me.”\n");
	printf("Un plotone di soldati è composto da 3 colonne e 15 righe. Le righe sono distanti tra loro di 2 metri. Quanto è lungo il plotone?\n");

	do {
		printf("Risposta: ");
		fgets(answer, 50, stdin);
		number = convert_sequence_char_to_int(scan(answer, 0));

		if(number == 28) {
			printf("L’uomo si gira, ti guarda e, alzando leggermente la mano, pronuncia qualcosa a te incomprensibile e punta il dito verso la porta a nord del corridoio centrale.\n");
			open_door_from_file(dir, 12);
		} else {
			printf("L'uomo ti ripete la domanda\n");
		}

	} while (number != 28);

}