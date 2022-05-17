#include <stdlib.h>

#include "globali.h" 
#include "gestione/gestione_tabella_simboli.h"
#include "gestione/gestione_personaggio.h"
#include "gestione/gestione_oggetto.h"
#include "gestione_storia.h"
#include "salvataggio.h"

void gestione_errore (int result);

char * scan(char* input, int offset) {
	
	char *token = calloc(10, sizeof(char));	//inizializza lo spazio di memoria dinamica

	*token = '\0';
	int count = 0;

	while(input[offset] != ' ' && input[offset] != '\n' && offset < strlen(input)) {
		token[count] = input[offset];
		count = count + 1;
		offset = offset + 1;
	}

	return token;
}

char * check_parola_chiave (char * token) {
	
	char * symbol = malloc(10 * sizeof(char));
	strcpy(symbol, "EMP");

	int count = 0;
	while (count < get_number_tab_simboli(keywords)) {

		if(strcmp(token, get_parola_tab_simboli(keywords, count)) == 0) {
			strcpy(symbol, get_simbolo_tab_simboli(keywords, count));
		}

		count = count + 1;	
	}

	return symbol;
}

void analizzare_comando(char * input) {

	int count = 0;
	set_number_tab_simboli(ident, 0);
	char *token = malloc(20 * sizeof(char));

	token = strtok(input, " \n");

	while(token) {

		int count_1 = 0, stato_corrente = 0, stato_pozza = 2;
		
		while(count_1 < strlen(token) && stato_corrente != stato_pozza) {

			if(token[count_1] >= 'a' && token[count_1] <= 'z') {
				if(stato_corrente == 0 || stato_corrente == 1) {
					stato_corrente = 1;
				}
			} else {
				stato_corrente = stato_pozza;
			}

			count_1 = count_1 + 1;
		}

		if(stato_corrente != stato_pozza) {		//parola corretta
			
			set_parola_tab_simboli(ident, get_number_tab_simboli(ident), token);

			if(strcmp(check_parola_chiave(token), "EMP") != 0) {
				
				set_simbolo_tab_simboli(ident, get_number_tab_simboli(ident), check_parola_chiave(token));

			} else {

				set_simbolo_tab_simboli(ident, get_number_tab_simboli(ident), "OBJ");

			}

		} else {											//parola scorretta - con dentro numeri

			set_parola_tab_simboli(ident, get_number_tab_simboli(ident), "0");
			set_simbolo_tab_simboli(ident, get_number_tab_simboli(ident), "0");

		}

		set_number_tab_simboli(ident, get_number_tab_simboli(ident) + 1);

		token = strtok(NULL, " \n");
	}

	return;
}

void eseguire_comando (tabella_simboli * tab, personaggio * pg) {
	int esito = 0;

	if(strcmp(get_simbolo_tab_simboli(tab, 0),  "TKE") == 0) { 								//prendi
		esito = prendere_oggetto(pg, get_parola_tab_simboli(tab, 1));

		printf("Oggetto preso\n");

	} else if(strcmp(get_simbolo_tab_simboli(tab, 0),  "LVE") == 0) {					//lascia
		esito = lasciare_oggetto(pg, get_parola_tab_simboli(tab, 1));

		if(esito == 0) {
			printf("Oggetto lasciato\n");
		}

	} else if(strcmp(get_simbolo_tab_simboli(tab, 0),  "VAI") == 0) {					//vai

		char direction;
		if(strcmp(get_parola_tab_simboli(tab, 1), "nord") == 0) {
			direction = 'n';
		} else if(strcmp(get_parola_tab_simboli(tab, 1), "est") == 0) {
			direction = 'e';
		} else if(strcmp(get_parola_tab_simboli(tab, 1), "sud") == 0) {
			direction = 's';
		} else if(strcmp(get_parola_tab_simboli(tab, 1), "ovest") == 0) {
			direction = 'o';
		} else if(strcmp(get_parola_tab_simboli(tab, 1), "su") == 0) { 
			direction = 'a';
		} else if(strcmp(get_parola_tab_simboli(tab, 1), "giu") == 0) {
			direction = 'b';
		} else {
			esito = -2;
		}

		if(esito != -2) {
			esito = muovere_personaggio(pg, direction);
		} 

	} else if(strcmp(get_simbolo_tab_simboli(tab, 0),  "LOK") == 0) {					//guarda

		if(strcmp(get_parola_tab_simboli(tab, 1),  "arma") == 0) {
			
			if(get_id_oggetto(get_weapon_personaggio(*pg))) {
				printf("Stai impugnando %s, danno: %d, durezza:%d\n", get_nome_oggetto(get_weapon_personaggio(*pg)), get_danno_arma(get_weapon_personaggio(*pg).oggetto_speciale.weapon), get_durezza_arma(get_weapon_personaggio(*pg).oggetto_speciale.weapon));
			} else esito = -10;

		} else if(strcmp(get_parola_tab_simboli(tab, 1),  "uomo") == 0 && get_posizione_personaggio(*pg) == 14) {
			 indovino_indovinello();
		} else esito = guardare_oggetto(stanza_attuale, get_parola_tab_simboli(tab, 1));

	} else if(strcmp(get_simbolo_tab_simboli(tab, 0),  "OPN") == 0) {					//apri

		if(strcmp(get_parola_tab_simboli(tab, 1), "porta") == 0) {

			char direction;
			if(strcmp(get_parola_tab_simboli(tab, 2), "nord") == 0) {
				direction = 'n';
			} else if(strcmp(get_parola_tab_simboli(tab, 2), "est") == 0) {
				direction = 'e';
			} else if(strcmp(get_parola_tab_simboli(tab, 2), "sud") == 0) {
				direction = 's';
			} else if(strcmp(get_parola_tab_simboli(tab, 2), "ovest") == 0) {
				direction = 'o';
			} else esito = -2;

			if(esito != -2) {
				esito = aprire_porta(&stanza_attuale, pg, direction);
			}

			if(esito == 0) {
				printf("Porta aperta\n");
			}

		} else {
			esito = aprire_oggetto(pg, get_parola_tab_simboli(tab, 1));

			if(esito == 0) {
				printf("Oggetto aperto\n");
			}
		}

	} else if(strcmp(get_simbolo_tab_simboli(tab, 0),  "EAT") == 0) {					//mangia
		esito = mangiare_cibo(pg,  get_parola_tab_simboli(tab, 1));

		if(esito == 0) {
			printf("Hai mangiato\n");
		}

	} else if(strcmp(get_simbolo_tab_simboli(tab, 0),  "SLT") == 0) {					//salute

		printf("Hai %d punti vita\n", get_punti_vita_personaggio(*pg));

	} else if(strcmp(get_simbolo_tab_simboli(tab, 0),  "INV") == 0) {					//inventario
		printf("Inventario:\n");
		stampare_inventario(*pg);

	} else if(strcmp(get_simbolo_tab_simboli(tab, 0),  "HEL") == 0) {					//aiuto

		printf("\nCiao piccolo giocatore, ti serve aiuto?\n\nEccoti alcuni comandi di base:\n\n-Digita il comando 'vai (nord, sud, est, ovest, su, giù)' per spostarti nella direzione desiderata.\n\n-Digita il comando 'guarda (nome oggetto da guardare)' per osservare meglio l'oggetto desiderato.\n\n-Digita il comando 'prendi (nome oggetto, spada ad esempio)' per inserire l'oggetto nell'inventario, inoltre per utilizzare le armi bisogna digitare il comando 'impugna (nome oggetto, spada ad esempio)' ovviamente l'oggetto deve essere presente nel tuo inventario.\n\n-Digita il comando 'lascia (nome oggetto da lasciare)' per liberare l'inventario dall'oggetto selezionato.\n\nDurante un combattimento i comandi disponibili sono: attacca, difendi per eseguire l'azione desiderata.\n\n-Digita il comando 'mangia' (nome cibo, mela ad esempio) per recuperare alcuni HP.\n\nDigita il comando 'salute o s' per vedere i tuoi HP rimanenti.\n\n-Digita il comando 'apri porta + (direzione)' per aprire una porta chiusa.\n\n-Digita il comando 'inventario o inv' per visualizzare tutti gli oggetti presenti nell'inventario.\n\n-Digita il comando 'salva' per salvare la partita e 'carica' per caricare l'ultimo salvataggio.\n\n-Digita il comando 'aiuto o h' per visualizzare la lista di tutti i comandi disponibili.\n");

	} else if(strcmp(get_simbolo_tab_simboli(tab, 0),  "SLV") == 0) {
		salvataggio_partita(stanza_attuale, *pg);
		printf("Salvataggio effettuato\n");
	} else if(strcmp(get_simbolo_tab_simboli(tab, 0),  "LOA") == 0) {
		caricare_partita(pg);
		printf("Partita caricata\n");
	} else if(strcmp(get_simbolo_tab_simboli(tab, 0),  "IMP") == 0) {
		esito = impugnare_arma(pg, get_parola_tab_simboli(tab, 1));
	} else {
		esito = -1;
	} 

	gestione_errore(esito);

	return;
}

void gestione_errore (int result) {

	if(result == -1) {
		printf("Non ho capito\n");
	} else if(result == -2) {
		printf("Non ho capito la direzione\n");
	} else if(result == -3) {
		printf("Direzione non consentita\n");
	} else if(result == -4) {
		printf("Punti vita massimi\n");
	} else if(result == -5) {
		printf("Non penso che si possa mangiare...\n");
	} else if(result == -6) {
			printf("Oggetto non presente in inventario\n");
	} else if(result == -7) {
		printf("Non vedi nulla del genere\n");
	} else if(result == -8) {
		printf("Inventario pieno\n");
	} else if(result == -9) {
		printf("Non trovi nulla di interessante\n");
	} else if(result == -10) {
		printf("non stai impugnando nulla\n");
	} else if(result == -11) {
		printf("La porta è chiusa\n");
	} else if(result == -12) {
		printf("Non hai la chiave giusta\n");
	} else if(result == -13) {
		printf("È già aperto\n");
	}

  return;
  
}