#include <stdlib.h>
#include <stdio.h>
#include <time.h> 

#include "../globali.h"
#include "gestione_personaggio.h"
#include "gestione_nemico.h"
#include "gestione_oggetto.h"
#include "../gestione_storia.h"

void attaccare_nemico(nemico * enemy, arma arma_pg)
{
  int punti_attuali = get_punti_vita_nemico(*enemy) - get_danno_arma(arma_pg);
	set_punti_vita_nemico(enemy, punti_attuali);
}

void difendere_nemico(nemico *enemy)
{
	set_durezza_arma(&enemy->weapon.oggetto_speciale.weapon, get_durezza_arma(enemy->weapon.oggetto_speciale.weapon) - 1);
}

void attaccare_personaggio(personaggio *pg, arma arma_enemy)
{
  int punti_attuali = get_punti_vita_personaggio(*pg) - get_danno_arma(arma_enemy);
	set_punti_vita_personaggio(pg, punti_attuali);
}

void difendere_personaggio(personaggio *pg)
{
	set_durezza_arma(&pg->weapon.oggetto_speciale.weapon, get_durezza_arma(pg->weapon.oggetto_speciale.weapon) - 1);
}

void combattimento (personaggio *pg , nemico *enemy)
{
  srand(time(NULL));
  int precisione, esito = 0;
	char risposta[20];
	printf("\nCOMINCIA IL COMBATTIMENTO\n\n");

	arma arma_pg = get_weapon_personaggio(*pg).oggetto_speciale.weapon;
	arma arma_enemy = get_arma_nemico(*enemy).oggetto_speciale.weapon;

  do {

    printf ("Scegli la tua mossa, attacchi o difendi ? : ");
    scanf("%s", risposta);
		printf("\033[0;0H\033[2J");
    
    int casuale = rand()%100;

		if(strcmp(risposta, "attacca") == 0) {

			if(casuale >= 50) {			//nemico attacca
				
				precisione = rand()%100;
				if(precisione >= 25) {

					printf("Riesci a colpire il nemico ma ");

					attaccare_nemico(enemy, arma_pg);

				} else printf("Non riesci a colpire il nemico ma ");

				precisione = rand()%100;
				if(precisione >= 25) {
					printf("il suo colpo va comunque a segno, ferendoti...\n");

					attaccare_personaggio(pg, arma_enemy);

				} else printf("lui non riesce a prenderti!\n"); 
				
			} else {																			 			//nemico difende

				int precisione = rand()%100;	
				if(precisione >= 25) {
					printf("Colpisci il nemico ");

					if(get_durezza_arma(get_arma_nemico(*enemy).oggetto_speciale.weapon) > 0) {

						printf("ma lui riesce a parare il tuo colpo rimandendo illeso...\n");

						difendere_nemico(enemy);

					} else {
						printf("e lo prendi in pieno!\n");

						attaccare_nemico(enemy, arma_pg);
					}
					
				} else printf("Hai mancato il colpo !!!\n");
				
			}

		} else if(strcmp(risposta, "difendi") == 0) {

			if(casuale >= 50) {			//nemico attaccare

				precisione = rand()%100;
				if(precisione >= 25) {

					printf("Il nemico cerca di colpirti ma ");

					if(get_durezza_arma(get_weapon_personaggio(*pg).oggetto_speciale.weapon) > 0) {

						printf("riesci a difenderti !!!\n");
						difendere_personaggio(pg); 

					} else {

						printf("non riesci a difenderti in tempo...\n");
						attaccare_personaggio(pg, arma_enemy);

					}	

				} else printf("Il nemico manca il colpo\n");

			} else {			//nemico difende
				printf("Vi difendete entrambi\n");
			}

		}
    else printf("Comando non riconosciuto\n");

		printf("HP di James: %d, HP del nemico: %d\n", get_punti_vita_personaggio(*pg), get_punti_vita_nemico(*enemy));
		printf("Durezza dell'arma di James: %d, Durezza dell'arma del nemico: %d\n", get_durezza_arma(get_weapon_personaggio(*pg).oggetto_speciale.weapon), get_durezza_arma(get_arma_nemico(*enemy).oggetto_speciale.weapon));

  } while (get_punti_vita_personaggio(*pg) > 0 && get_punti_vita_nemico(*enemy) > 0);

  if (get_punti_vita_personaggio(*pg) <= 0)
  {
    printf("\nSei morto\n");
  }
  else if (get_punti_vita_nemico(*enemy) <= 0)
  { 
    remove_enemy_from_file(get_posizione_personaggio(*pg));
  }

  return;
}