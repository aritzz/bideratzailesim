/*
 * bideratzea.c
 *
 * bideratzailearen funtzio laguntzaileak
 *
 *
 */

#include "bideratzea.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/*
 * hasieraketa
 */

void hasieratu_sarea(Sarea *sarea)
{
	sarea->bideratze_erregistroa = 0;
	sarea->distantzia = 0;
	sarea->iturburu_bektorea = (int *) malloc(sizeof(int)*sarea->n);
	sarea->helburu_bektorea = (int *) malloc(sizeof(int)*sarea->n);
	sarea->bideratze_erregistro_bektorea = (int *) malloc(sizeof(int)*sarea->n);

	for (int i=0; i< sarea->n; i++)
	{
		sarea->iturburu_bektorea[i] = 0;
		sarea->helburu_bektorea[i] = 0;
		sarea->bideratze_erregistro_bektorea[i] = 0;

	}
}

/*
 * Kalkulatu bektorea dagokion oinarrian
 */
void kalkulatu_bektorea(Sarea *sarea, int mota)
{
	int oinarria = sarea->k;
	int bihurketa, emaitza=0, hondarra=0;
	int bektorea[sarea->n];
	int posizioa = (sarea->n) -1;


	// Hautatu zein nahi den kalkulatu
	if (mota == 0)
		bihurketa = sarea->iturburua;
	else if (mota == 1)
		bihurketa = sarea->helburua;
	else
		bihurketa = sarea->bideratze_erregistroa;

	// bektorea hasieratu
    for (int i=0; i<=posizioa; i++)
    	bektorea[i] = 0;

    posizioa = 0;

	// bihurketarik ez du behar oinarria baino txikiagoa delako
	if (bihurketa < oinarria)
	   bektorea[posizioa] = bihurketa;
	else
	{


	  do
	  {
		  // Zerbait arraroa pasa da
		  if (posizioa >= sarea->n)
			  break;

		  // Oinarri aldaketa egin
		  hondarra=bihurketa%oinarria;
		  emaitza=bihurketa/oinarria;
		  bektorea[posizioa]=hondarra;
		  bihurketa=emaitza;
		  posizioa++;

		  if (emaitza < oinarria)
			  bektorea[posizioa] = emaitza;


	  } while (emaitza >= oinarria);
	}

	// buelta eman
	buelta_eman(bektorea, sarea->n);

#ifdef DEBUG
	printf("Debug kalkulatu_bektorea (%d): ", mota);
	for (int i=0; i<(sarea->n); i++)
			printf("%d", bektorea[i]);
	printf("\n");

#endif


	// Motaren arabera bektorea eguneratu

	if (mota == 0)
	{

		for (int i=0; i<(sarea->n); i++)
			sarea->iturburu_bektorea[i] = bektorea[i];
	}

	else if (mota == 1)
	{

		for (int i=0; i<(sarea->n); i++)
			sarea->helburu_bektorea[i] = bektorea[i];
	}
	else
	{

		for (int i=0; i<(sarea->n); i++)
			sarea->bideratze_erregistro_bektorea[i] = bektorea[i];
	}


}

/*
 * buelta_eman: array baten alderantzizkoa itzultzen du
 */
void buelta_eman(int *pointer, int n)
{
   int *s, c, d;

   s = (int*)malloc(sizeof(int)*n);

   if (s == NULL)
      exit(EXIT_FAILURE);

   for ( c = n - 1, d = 0 ; c >= 0 ; c--, d++ )
      *(s+d) = *(pointer+c);

   for ( c = 0 ; c < n ; c++ )
      *(pointer+c) = *(s+c);

   free(s);
}

int kendu_bat(int balioa, int oinarria)
{
	if ((balioa -1) == -1)
		return oinarria-1;
	else
		return balioa-1;
}

int gehitu_bat(int balioa, int oinarria)
{
	if ((balioa +1) == oinarria)
		return 0;
	else
		return balioa+1;
}

/*
 * kopiatu bektorea
 */

void kopiatu_bektorea(int *nora, int *zein, int n)
{
	for (int i=0; i<n; i++)
		nora[i] = zein[i];
}

/*
 * mailak prozesatu
 */

void prozesatu_maila(Sarea *sarea)
{

	int bektore_temp[sarea->n];
	int bideratze_temp[sarea->n];
	kopiatu_bektorea(bektore_temp, sarea->iturburu_bektorea, sarea->n);

	Nodoak *aux, *aldatzekoa;

	sarea->nodoak = (struct Nodoak *) malloc (sizeof(struct Nodoak));
	sarea->nodoak->nodo_bektorea = (int *) malloc(sizeof(int)*sarea->n);

	sarea->nodoak->hurrengoa = NULL;
	kopiatu_bektorea(sarea->nodoak->nodo_bektorea, sarea->iturburu_bektorea, sarea->n);

	aldatzekoa = sarea->nodoak;


	// bideratze erregistroa: helburua-iturburua
	for (int i=0; i<sarea->n; i++)
	{
				int bideratze_puntua;
				bideratze_puntua = sarea->helburu_bektorea[i] - sarea->iturburu_bektorea[i];
				if (bideratze_puntua < 0)
					bideratze_puntua = sarea->k - abs(bideratze_puntua);

				sarea->bideratze_erregistro_bektorea[i] = bideratze_puntua;
	}
	kopiatu_bektorea(bideratze_temp, sarea->bideratze_erregistro_bektorea, sarea->n);


	// nodoen kalkulua

	for (int i=sarea->n-1; i>=0; i--)
	{
		while (sarea->bideratze_erregistro_bektorea[i] != 0)
		{
			if (sarea->bideratze_erregistro_bektorea[i] < 0) {
				sarea->bideratze_erregistro_bektorea[i]++;
				bektore_temp[i] = kendu_bat(bektore_temp[i], sarea->k);
			}
			else {
				sarea->bideratze_erregistro_bektorea[i]--;
				bektore_temp[i] = gehitu_bat(bektore_temp[i], sarea->k);
			}

			// Nodoa prestatu eta kopiatu
						aux = (struct Nodoak *) malloc (sizeof(struct Nodoak));
						aux->nodo_bektorea = (int *) malloc(sizeof(int)*sarea->n);
						aux->hurrengoa = NULL;
						kopiatu_bektorea(aux->nodo_bektorea, bektore_temp, sarea->n);
						aldatzekoa->hurrengoa = aux;
						aldatzekoa = aldatzekoa->hurrengoa;
		}
	}

	kopiatu_bektorea(sarea->bideratze_erregistro_bektorea, bideratze_temp, sarea->n);
	sarea->distantzia = eman_distantzia(sarea);
}

/*
 * toruak prozesatu
 */

void prozesatu_torua(Sarea *sarea)
{

	int bektore_temp[sarea->n];
	int bideratze_temp[sarea->n];

	kopiatu_bektorea(bektore_temp, sarea->iturburu_bektorea, sarea->n);

	Nodoak *aux, *aldatzekoa;

	sarea->nodoak = (struct Nodoak *) malloc (sizeof(struct Nodoak));
	sarea->nodoak->nodo_bektorea = (int *) malloc(sizeof(int)*sarea->n);

	sarea->nodoak->hurrengoa = NULL;
	kopiatu_bektorea(sarea->nodoak->nodo_bektorea, sarea->iturburu_bektorea, sarea->n);

	aldatzekoa = sarea->nodoak;


	// bideratze erregistroa: helburua-iturburua
	for (int i=0; i<sarea->n; i++)
	{
				int bideratze_puntua;
				bideratze_puntua = sarea->helburu_bektorea[i] - sarea->iturburu_bektorea[i];

				if (bideratze_puntua > sarea->k/2)
					bideratze_puntua = bideratze_puntua - sarea->k;

				if (bideratze_puntua < -(sarea->k)/2)
					bideratze_puntua = bideratze_puntua + sarea->k;

				sarea->bideratze_erregistro_bektorea[i] = bideratze_puntua;
	}
	kopiatu_bektorea(bideratze_temp, sarea->bideratze_erregistro_bektorea, sarea->n);


	// nodoen kalkulua

	for (int i=sarea->n-1; i>=0; i--)
	{
		while (sarea->bideratze_erregistro_bektorea[i] != 0)
		{
			if (sarea->bideratze_erregistro_bektorea[i] < 0) {
				sarea->bideratze_erregistro_bektorea[i]++;
				bektore_temp[i] = kendu_bat(bektore_temp[i], sarea->k);
			}
			else {
				sarea->bideratze_erregistro_bektorea[i]--;
				bektore_temp[i] = gehitu_bat(bektore_temp[i], sarea->k);
			}

			// Nodoa prestatu eta kopiatu
			aux = (struct Nodoak *) malloc (sizeof(struct Nodoak));
			aux->nodo_bektorea = (int *) malloc(sizeof(int)*sarea->n);
			aux->hurrengoa = NULL;
			kopiatu_bektorea(aux->nodo_bektorea, bektore_temp, sarea->n);
			aldatzekoa->hurrengoa = aux;
			aldatzekoa = aldatzekoa->hurrengoa;
		}
	}
	kopiatu_bektorea(sarea->bideratze_erregistro_bektorea, bideratze_temp, sarea->n);

	sarea->distantzia = eman_distantzia(sarea);

}
/*
 * eman bektoreko zenbakia oinarrian
 */

int bektorea_zenbakira(int *bektorea, int n, int oinarria)
{
	int akum =0;
	for (int i=n-1, j=0;i>=0;i--, j++)
		akum += bektorea[i]*pow(oinarria, j);

	return akum;
}



/*
 * hiperkuboak prozesatu
 */
void prozesatu_hiperkuboa(Sarea *sarea)
{
	Nodoak *aux, *aldatzekoa;

	sarea->nodoak = (struct Nodoak *) malloc (sizeof(struct Nodoak));
	sarea->nodoak->nodo_bektorea = (int *) malloc(sizeof(int)*sarea->n);
	int bektore_temp[sarea->n];

	sarea->nodoak->hurrengoa = NULL;
	kopiatu_bektorea(sarea->nodoak->nodo_bektorea, sarea->iturburu_bektorea, sarea->n);

	kopiatu_bektorea(bektore_temp, sarea->iturburu_bektorea, sarea->n);

	aldatzekoa = sarea->nodoak;

	for (int i=(sarea->n)-1; i>=0; i--)
		sarea->bideratze_erregistro_bektorea[i] = sarea->helburu_bektorea[i] ^ sarea->iturburu_bektorea[i];


	for (int i=(sarea->n)-1; i>=0; i--)
		{
			/*
			 * Bideratze erregistroa 1 baldin bada eta iturburukoa ere bai,
			 * zero bihurtu. Bestela, alderantziz
			 */

			if (sarea->bideratze_erregistro_bektorea[i] == 1) {
				if (sarea->iturburu_bektorea[i] == 1)
					bektore_temp[i] = 0;
				else
					bektore_temp[i] = 1;


			// Nodoa prestatu eta kopiatu
			aux = (struct Nodoak *) malloc (sizeof(struct Nodoak));
			aux->nodo_bektorea = (int *) malloc(sizeof(int)*sarea->n);
			aux->hurrengoa = NULL;
			kopiatu_bektorea(aux->nodo_bektorea, bektore_temp, sarea->n);
			aldatzekoa->hurrengoa = aux;
			aldatzekoa = aldatzekoa->hurrengoa;
			}
		}

	sarea->distantzia = eman_distantzia(sarea);

}

/*
 * Kalkulatu bideratze-helbidea
 */
void kalkulatu_bideratzea(Sarea *sarea)
{
	// kontrolatu kalkulua egiten hasi baino lehen
	sarea->max = pow(sarea->k, sarea->n);

	if ((sarea->iturburua > sarea->max) || (sarea->helburua > sarea->max)) {
		printf("Helmuga edo iturburua heinetik kanpo.");
		exit(EXIT_FAILURE);
	}

	if (sarea->eraztunak == 1) // eraztuna edo torua
		{
			if (sarea->n==1)
				strcpy(sarea->mota_izena, "eraztun");
			else
				strcpy(sarea->mota_izena, "toru");

			prozesatu_torua(sarea);
		}
	else // hiperkuboa edo maila
		if ((sarea->k==2) && (sarea->n>1)) //hiperkuboa
		{
			prozesatu_hiperkuboa(sarea);
			strcpy(sarea->mota_izena, "hiperkubo");
		}
		else {
			prozesatu_maila(sarea);
			strcpy(sarea->mota_izena, "maila");
		}
}

/*
 * Distantzia
 */

int eman_distantzia(Sarea *sare)
{

	int dim = 0;

	// gure bektore itsusia sartu
	for (int i=0; i<sare->n; i++)
		dim += abs(sare->bideratze_erregistro_bektorea[i]);

	return dim;

}

/*
 * Bektore itsusia, politean bihurtuko dugu
 */

void eman_bektore_polita(int *bektorea, int tamaina, char *bektorepolita)
{

	char temp[10];
	// hasieratu
	strcpy(bektorepolita, "[");

	// gure bektore itsusia sartu
	for (int i=0; i<tamaina; i++)
	{
		sprintf(temp, "%d", bektorea[i]);
		strcat(bektorepolita, temp);
		if (i != tamaina-1)
			strcat(bektorepolita, ", ");
	}

	// bukatu
	strcat(bektorepolita, "]");

}

void inprimatu_nodoak(Nodoak *nodo, int n, int oinarria)
{
	char bektorepolita[4*(n)];
	struct Nodoak *aux;
	      int i;

	      i=0;
	      aux = nodo;
	      while (aux!=NULL) {
	    		eman_bektore_polita(aux->nodo_bektorea, n, bektorepolita);
	            printf("\t\t%d %s\n", bektorea_zenbakira(aux->nodo_bektorea, n, oinarria), bektorepolita);
	            aux = aux->hurrengoa;
	            i++;
	      }
}

/*
 * Inprimatu datuak
 */
void inprimatu_sarea(Sarea *sarea)
{
	char bektorepolita[4*(sarea->n)];

#ifdef DEBUG
	printf("Debug inprimatu_sarea iturburua (%d): ", sarea->n);
	for (int i=0; i<(sarea->n); i++)
			printf("%d", sarea->iturburu_bektorea[i]);
	printf("\n");
	printf("Debug inprimatu_sarea helburua (%d): ", sarea->n);
		for (int i=0; i<(sarea->n); i++)
				printf("%d", sarea->helburu_bektorea[i]);
		printf("\n");
#endif

	printf("###########################################################\n");
	printf("## %d dimentsioko %s bat kalkulatuko da\n", sarea->n, sarea->mota_izena);
	printf("## %d nodo ditu dimentsioko\n", sarea->k);
	printf("###########################################################\n\n");
	eman_bektore_polita(sarea->iturburu_bektorea, sarea->n, bektorepolita);
	printf("Iturburua: %d\t%s\n", sarea->iturburua, bektorepolita);
	eman_bektore_polita(sarea->helburu_bektorea, sarea->n, bektorepolita);
	printf("Helburua: %d\t%s\n", sarea->helburua, bektorepolita);
	eman_bektore_polita(sarea->bideratze_erregistro_bektorea, sarea->n, bektorepolita);
	printf("Bideratze-erregistroa: \t%s\n", bektorepolita);
	printf("Distantzia: \t%d\n", sarea->distantzia);
	printf("Nodoak: \n");
	inprimatu_nodoak(sarea->nodoak, sarea->n, sarea->k);
	printf("\n######################## Bukaera ##########################\n###########################################################\n");

}
