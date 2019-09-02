//--------------------------------------------------------
// partic.h
// Definiciones para las rutinas de efectos visuales simples
// Huellas del tanque, particulas, etc
//--------------------------------------------------------


#ifndef PARTIC_H
#define PARTIC_H


//--------------------------------------------------------
// Prototipos
//--------------------------------------------------------

void reset_particulas();
void dibujar_particulas(BITMAP *bmp);
void mover_particulas();
void agregar_particulas(int x, int y, int vida,
                        int cantidad, int tipo,
                        int colorr1, int colorr2);
//--------------------------------------------------------
// Definiciones
//--------------------------------------------------------

// cantidad maxima de particulas
#define MAX_PARTICULAS          150

// Gravedad
float gravedad = 0.1;
// Viento
float viento = 0.0;

#endif
