/*
 ============================================================================
 Konputagailu Paraleloko Sistemak
 bideratze-algoritmoak

 bideratzailearen programa nagusia

 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "bideratzea.h"

int main(void) {
	Sarea bideratze_sarea;

	puts("*******************************");
	puts("\t Bideratzailea");
	puts("*******************************");
	puts("\t");
	printf("Sarearen dimentsio kopurua (n): \t");
	scanf("%d", &bideratze_sarea.n);

	printf("Sarearen nodo kopurua dimentsioko (k): \t");
	scanf("%d", &bideratze_sarea.k);

	printf("Dimentsioan, kateak (0) edo eraztunak (1) ditu?\t");
	scanf("%d", &bideratze_sarea.eraztunak);

	printf("Mezua sortzen duen nodoa:\t");
	scanf("%d", &bideratze_sarea.iturburua);

	printf("Mezua hartzen duen nodoa:\t");
	scanf("%d", &bideratze_sarea.helburua);


	hasieratu_sarea(&bideratze_sarea);
	kalkulatu_bektorea(&bideratze_sarea, 0);
	kalkulatu_bektorea(&bideratze_sarea, 1);
	kalkulatu_bideratzea(&bideratze_sarea);

	inprimatu_sarea(&bideratze_sarea);

	return EXIT_SUCCESS;
}

