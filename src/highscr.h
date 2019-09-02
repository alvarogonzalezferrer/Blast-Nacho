// -------------------------------------------------------- 
// highscr.h 
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Tabla de altos puntajes
// -------------------------------------------------------- 
#ifndef HIGHSCR_H
#define HIGHSCR_H

#define HIGH_FILE  "nachotop.dat" // archivo donde guardar el top 10

// tabla de puntajes (10+1)
typedef struct PUNTAJETBL {
   char nombrejug[10];
   unsigned long puntaje;
} PUNTAJETBL;

PUNTAJETBL puntajetbl[11];

int qsort_helper_puntajetbl(const void *e1, const void *e2);

void salvar_tabla();

void crear_tabla_default();

void cargar_tabla_puntaje();

void check_alto_puntaje(unsigned long puntaje);

void mostrar_altos_puntajes();

#endif
