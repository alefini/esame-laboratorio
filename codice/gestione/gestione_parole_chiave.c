#include <stdlib.h>

#include "../globali.h"
#include "../analizzatore_lessicale.h"
#include "gestione_tabella_simboli.h"

void inizializzazione_parole_chiave() {

	char pathname[20] = "parole_chiave.txt";
	FILE *fp;
	int count_1 = 0;
	char *support = malloc(10 * sizeof(char));

	if((fp = fopen(pathname, "r")) != NULL) {

		while(!feof(fp)) {
			fgets(support, 100, fp);
			int check = 0, count = 0;

			while(count < strlen(support)) {

				char * token = malloc(10 * sizeof(char));
				token = scan(support, count);

				if(check == 0) {
					
					set_parola_tab_simboli(keywords, count_1, token);
					
					check = 1;

				} else if (check == 1) {

					set_simbolo_tab_simboli(keywords, count_1, token);
					set_number_tab_simboli(keywords, get_number_tab_simboli(keywords)+1);

					count_1 = count_1 + 1;
					check = 0;
				}

				int lenght = 0 + strlen(token);
				*token = '\0';
				count = count + 1 + lenght;
			}

			*support = '\0';
		}

	} else printf("Impossibile aprire il file");

	return;
}