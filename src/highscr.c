// -------------------------------------------------------- 
// highscr.c 
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Tabla de altos puntajes
// -------------------------------------------------------- 
#ifndef HIGHSCR_C
#define HIGHSCR_C

#include <stdlib.h> // preciso qsort


char puntostr[30]; // string de puntaje
char nombrejug[10]; // nombre del jugador

// Dialogo de ingresar nombre 
DIALOG entrar_nombre_GUI[] =
    { 
    // (dialog proc)     (x)   (y)   (w)   (h) (fg)(bg)(key (fl)(d1)(d2)(dp)(dp2)(dp3)
    { d_shadow_box_proc,  0 , 0 ,    120 , 50 , 15 , 0 , 0 , 0 , 0 , 0 ,NULL,NULL,NULL},
    { d_text_proc,        5 , 2 ,    110 , 8 ,  15 , 0 , 0 , 0 , 0 , 0 ,"Hiciste un alto puntaje!",NULL,NULL},
    { d_text_proc,        5 , 10 ,   110 , 8 ,  15 , 0 , 0 , 0 , 0 , 0 ,puntostr,NULL,NULL},
    { d_text_proc,        5 , 20 ,   110 , 8 ,  15 , 0 , 0 , 0 , 0 , 0 ,"Ingresa tu nombre!",NULL,NULL},
    { d_edit_proc,        5 , 35 ,   110 , 8 ,  15 , 0 , 0 , D_EXIT , 9 , 0 ,nombrejug,NULL,NULL},
    { NULL,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL  }
}; /* entrar_nombre */


// -------------------------------------------------------- 
// Helper para ordenar la tabla
// -------------------------------------------------------- 
int qsort_helper_puntajetbl(const void *e1, const void *e2)
{
  // ordena de mayor a menor, es decir, el mayor quedara en 0
  return ((const PUNTAJETBL *)e2)->puntaje - ((const PUNTAJETBL *)e1)->puntaje;
}


// -------------------------------------------------------- 
// Salva la tabla a disco
// -------------------------------------------------------- 
void salvar_tabla()
{
  FILE *fp;

  // no existe, crear default
  if ( (fp = fopen(HIGH_FILE, "wb")) == NULL) return; // demasiado error...

  // escribir a disco (1 solo, porque sizeof devuelve el tama¤o de todos... shit)
  fwrite(&puntajetbl, sizeof(puntajetbl), 1, fp);

fflush(fp);
fclose(fp);
}

// -------------------------------------------------------- 
// Esta rutina auxiliar crea la tabla de puntajes
// -------------------------------------------------------- 
void crear_tabla_default()
{
  int i;  
  // tabla imaginaria
  for (i=0; i<11; i++)
      {
         puntajetbl[i].puntaje = random()%((11-i+1)*1500) + ((11-i+1)*1500);


         sprintf(puntajetbl[i].nombrejug, "Kronoman"); // debug: nombre sencillo...

        /******** DEBUG: funciona OK, pero esta deshabilitado por mi egocentrismo...
         switch (random()%5)
         {
         case 0:
            sprintf(puntajetbl[i].nombrejug, "Kronoman");
         break;
         case 1:
            sprintf(puntajetbl[i].nombrejug, "Nacho");
         break;
         case 2:
            sprintf(puntajetbl[i].nombrejug, "Viky");
         break;
         case 3:
            sprintf(puntajetbl[i].nombrejug, "Eddy");
         break;
         case 4:
            sprintf(puntajetbl[i].nombrejug, "Super");
         break;
         }
       ******************* deshabilitado hasta aqui *******/
      }

  salvar_tabla();
}

// --------------------------------------------------------
// Carga la tabla de disco
// Si no existiera la tabla o fuera invalida, la crea
// -------------------------------------------------------- 
void cargar_tabla_puntaje()
{
FILE *fp;

// ver si la tabla es valida
if (file_size(HIGH_FILE) != sizeof(puntajetbl))
   {
   crear_tabla_default(); // crearla nuevamente
   }

    // abrir tabla
    if ( (fp = fopen(HIGH_FILE, "rb")) == NULL) {
       // si fallo, crear
       crear_tabla_default();
    // reabrir en modo lectura para continuar abajo
      if ( (fp = fopen(HIGH_FILE, "rb")) == NULL) return; // demasiados errores
    }; // fin crear tabla

    // leer tabla de puntaje
    fread(&puntajetbl, sizeof(puntajetbl), 1, fp);
    fclose(fp); // no la preciso mas...
}

// -------------------------------------------------------- 
// chequea si hizo un alto puntaje
// si lo hizo, pide nombre, y salva el puntaje
// -------------------------------------------------------- 
void check_alto_puntaje(unsigned long puntaje)
{
int i;
int hizohg = FALSE;

cargar_tabla_puntaje(); // cargar tabla

// limpiar el puntaje 11, donde mantendre el puntaje del jugador
puntajetbl[10].puntaje = puntaje;

// ver si el puntaje del jugador supera alguno, sino, volver
hizohg = FALSE;
for (i=0; i<10; i++)
    {
    if (puntaje > puntajetbl[i].puntaje) hizohg = TRUE;
    }

if (hizohg == FALSE) return; // no hizo alto puntaje, salir

// pedir nombre del puntaje nuevo
    sprintf(puntostr, "%010ld", puntaje);
   nombrejug[0] = '\0';

// Hacer dialogo
    entrar_nombre_GUI[0].w = text_length(font, "Hiciste un alto puntaje!") * 1.05;
    centre_dialog(entrar_nombre_GUI);
    set_dialog_color(entrar_nombre_GUI, makecol(255,255,255), makecol(0,0,0));
    gui_fg_color = makecol(255,255,255);
    gui_bg_color = makecol(0,0,0);
    clear_keybuf();
    do_dialog(entrar_nombre_GUI, 4);

// colocar nombre
sprintf(puntajetbl[10].nombrejug, "%s", nombrejug);

// ordenar (el que queda ultimo, en la proxima vez, sera descartado)
qsort(puntajetbl, 11, sizeof(PUNTAJETBL), qsort_helper_puntajetbl);

// salvar a disco
salvar_tabla();

// listo
}

// -------------------------------------------------------- 
// Muestra la tabla de altos puntajes
// Si existe altopuntaje_bmp lo muestra de fondo estirado a la pantalla
// --------------------------------------------------------
void mostrar_altos_puntajes()
{
int i, y; // para el for
 DATAFILE *p = NULL; // puntero de busqueda
 BITMAP *bmp = NULL; // doble buffer
 BITMAP *bmpD = NULL; // bmp data de disco o fondo


// doble buffer
bmp = create_bitmap(640, 480);
clear(bmp);
clear(screen);

set_palette( *((PALETTE*)paleta_vga) ); // tengo que hacer esto porque es un puntero, y no una matriz

 // Tomar imagen (si no hay, seguir... sorry)
        p = fuzzy_find_datafile_object_type(datfile, "altopuntaje_bmp", DAT_BITMAP);
        if (p == NULL)
             {
             // no hay imagen, poner unas estrellas
              hace_paisaje_estelar(bmp);
             }
        else
             {
             bmpD = (BITMAP *)p->dat;
             // Enviar a buffer
             stretch_blit(bmpD, bmp, 0, 0, bmpD->w, bmpD->h, 0, 0, bmp->w, bmp->h);
             }

// poner titulo
text_mode(-1);

textout_centre(bmp, font_game, "Los diez mejores pilotos son...", bmp->w/2, 2, makecol(255,255,255));

// mostrar los 10 primeros (el 11avo se descarta)
y = text_height(font_game)*1.05; // dejar 105% de espacio
for (i=0; i<10; i++)
 {
  textprintf(bmp, font_game, 2, y, makecol(255,255,255),"%2d",i+1);
  textprintf_centre(bmp, font_game, (bmp->w * 0.9) / 2, y, makecol(255,255,255), "%10s",puntajetbl[i].nombrejug);
  textprintf_right(bmp, font_game, bmp->w, y, makecol(255,255,255), "%010ld",puntajetbl[i].puntaje);
  y += (bmp->h*0.75) / 10; // tomar el 75% de pantalla
 }

// Enviar a pantalla y liberar
stretch_blit(bmp, screen, 0, 0, bmp->w, bmp->h, 0, 0, SCREEN_W, SCREEN_H);
destroy_bitmap(bmp);

  // Esperar por tecla
 textout_centre(screen, font, "<< Presione una tecla >>", SCREEN_W/2, SCREEN_H - text_height(font), makecol(255,255,255) );

 clear_keybuf();
 readkey();
 clear_keybuf();

}

#endif
