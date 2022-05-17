#include "gestione_storia.h"
#include "gestione/gestione_personaggio.h"
#include "gestione/gestione_parole_chiave.h"
#include "analizzatore_lessicale.h"
#include "globali.h"

#include <stdlib.h>

int main(void) {
	inizializzazione_parole_chiave();
	inizializzazione_file();

	printf("Corre l’anno 1492, l’esploratore James Boston è alla ricerca della famosa moneta di Hoysala, antica moneta di origine orientale spedita in lungo e in largo passando anche per le mani del mercante italiano Marco Polo come scritto da testimonianza nella sua opera “Il Milione”. Le ultime informazioni risalenti all’avvistamento di Hoysala portano il nostro James ai piedi del castello di Wrecked, luogo inesplorato da ormai centinaia di anni, insito di pericoli. James decide di farsi coraggio e di avventurarsi all’interno delle mura del castello…\n\n");

	inizializzazione_personaggio(&james);
	descrivere_ambiente(1);
	
	while(get_punti_vita_personaggio(james) > 0 && get_posizione_personaggio(james) != 16) {

		char *input = calloc(20, sizeof(char));
		printf("\nProssima mossa: ");
		fgets(input, 50, stdin);

		analizzare_comando(input);

		eseguire_comando(ident, &james);

		input[0] = '\0';

	}

	return 0;
}