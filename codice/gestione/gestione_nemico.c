#include "../globali.h"

void set_punti_vita_nemico(nemico * enemy, int hp) {
	enemy->punti_vita = hp;
	return;
}

int get_punti_vita_nemico(nemico enemy) {
	return enemy.punti_vita;
}

void set_arma_nemico(nemico * enemy, oggetto weapon) {
	enemy->weapon = weapon;
	return;
}

oggetto get_arma_nemico(nemico enemy) {
	return enemy.weapon;
}