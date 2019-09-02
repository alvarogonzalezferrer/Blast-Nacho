// -------------------------------------------------------- 
// mensaje.h 
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Sistema de mensajes en pantalla de NachoBlast
// -------------------------------------------------------- 
#ifndef MENSAJE_H
#define MENSAJE_H

// cantidad maxima de mensajes en pantalla a la vez
#define MAX_MSG   10


// Estructura de mensajes
struct {
    // Estas coordenadas estan desplazada 1 decima (10 = 1.0)
    int x, y; // posicion (centrado sobre eje x, y = arriba)
    int dx, dy; // direccion (se actualiza cada 1/70 de segundo)

    FONT *fnt; // font que usa
    int vida; // vida del mensaje restante en 1/70 de segundo (70 = 1 segundo)
    int color; // color del mensaje
    char txt[80]; // texto del mensaje

    int timer1; // timer interno para medir el desgaste

} msg[MAX_MSG];

int msg_libre = 0; // mensaje libre

// Prototipos
void reset_mensajes();
void agregar_mensaje(int x, int y, int vida, int dx, int dy, FONT *fnt, char *txt, int color);
void mover_mensajes();
void dibujar_mensajes(BITMAP *bmp);
void agregar_mensaje_dolor(int x, int y);
void agregar_mensaje_dolor_nacho(int x, int y);
void sumar_puntaje_mensaje(int x, int y, int sumar, unsigned long *punt);
#endif
