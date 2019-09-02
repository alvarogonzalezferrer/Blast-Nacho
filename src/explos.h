// -------------------------------------------------------- 
// explos.h
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Engine de explosiones / humo / pedazos
// -------------------------------------------------------- 
#ifndef EXPLOS_H
#define EXPLOS_H

// cantidad maxima de explosiones
#define MAX_EXPLO   100

// timer
#define EXPLO_VEL    2

// estructura de explosiones
struct {
    int x, y; // posicion
    int sizeorg; // tama¤o original
    int sizeact; // tama¤o actual
    int vidaorg; // tiempo de vida original
    int vidaact; // vida actual
    BITMAP *spr; // sprite que usa
    fixed ang; // angulo de giro
    int frame; // timer para medir el giro
} explo[MAX_EXPLO];

int explo_libre = 0; // explosion libre

// Prototipos
void reset_explosiones();
void agregar_explosion(int x, int y, int vida, int size,BITMAP *spr);
void dibujar_explosiones(BITMAP *bmp);
void mover_explosiones();
#endif
