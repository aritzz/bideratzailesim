/*
 * bideratzea.h
 *
 * bideratzailearen funtzio laguntzaileak eta datu-egiturak
 */


// debug behar baldin bada
// #define DEBUG 1


// Datu egiturak
typedef struct Nodoak {
   int nodo_zenbakia;
   int *nodo_bektorea;
   struct Nodoak *hurrengoa;
} Nodoak;

typedef struct Sareak {
   int n;
   int k;
   int eraztunak;
   int iturburua;
   int helburua;
   int bideratze_erregistroa;
   int distantzia;
   int max;
   char mota_izena[50];
   int *iturburu_bektorea;
   int *helburu_bektorea;
   int *bideratze_erregistro_bektorea;
   Nodoak *nodoak;
} Sarea;


// funtzioen deklarazioa
void kalkulatu_bektorea(Sarea *sarea, int mota);
void kalkulatu_bideratzea(Sarea *nodoa);
void kalkulatu_nodoak(Nodoak *nodoa);
void inprimatu_sarea(Sarea *sarea);
void buelta_eman(int *pointer, int n);
int eman_distantzia(Sarea *sare);
void hasieratu_sarea(Sarea *sarea);

