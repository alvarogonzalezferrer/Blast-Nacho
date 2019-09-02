// -------------------------------------------------------- 
// premio.h
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Premios - por ahora, solo energia y puntos
// -------------------------------------------------------- 
#ifndef PREMIO_H
#define PREMIO_H

// cantidad maxima de premios
#define MAX_PREMIO   5
#define PREMIO_VIDA  150 // duracion del premio
#define PREMIO_VEL   2 // timer para girar el premio

// estructura de premios
struct {
    int x, y; // posicion ( / 100 para saber: 100 = 1.00)
    int dx, dy; // direccion x,y  (100 =  1.00)
    int vida; // vida actual
    BITMAP *spr; // sprite que usa
    SAMPLE *snd; // sonido que toca al agarrarlo
    fixed ang; // angulo de giro
    int frame; // timer para medir el giro

    int sumar_energia; // cuanto le suma a la energia (puede ser 0)
    int sumar_puntos; // cuanto le suma a los puntos (puede ser 0)

} premio[MAX_PREMIO];

int premio_libre = 0; // premio libre

// Prototipos
void reset_premios();
void agregar_premio(int x, int y, BITMAP *spr, SAMPLE *snd, int sumar_puntos, int sumar_energia);
void mover_premios();
void dibujar_premios(BITMAP *bmp);

#endif
