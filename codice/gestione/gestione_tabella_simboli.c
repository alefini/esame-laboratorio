#include "../globali.h"

char * get_parola_tab_simboli(tabella_simboli * tab, int pos) {
	return tab[pos].parola;
}

void set_parola_tab_simboli(tabella_simboli * tab, int pos, char * element) {
	strcpy(tab[pos].parola, element);
	return;
}

char * get_simbolo_tab_simboli(tabella_simboli * tab, int pos) {
	return tab[pos].simbolo;
}

void set_simbolo_tab_simboli(tabella_simboli * tab, int pos, char * element) {
	strcpy(tab[pos].simbolo, element);
	return;
}

int get_number_tab_simboli(tabella_simboli * tab) {
	return tab->number;
}

void set_number_tab_simboli(tabella_simboli * tab, int element) {
	tab->number = element;
	return;
}

void stampa_tabella_simboli (tabella_simboli * tab) {
	int count = 0;
	
	while(count < get_number_tab_simboli(tab)) {
		printf("parola: %s, simbolo: %s\n", get_parola_tab_simboli(tab, count), get_simbolo_tab_simboli(tab, count));
		count = count + 1;
	}

}