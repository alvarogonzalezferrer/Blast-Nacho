// -------------------------------------------------------- 
// jugador.h 
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Rutinas que mueven, controlan, dibujan el jugador
// y sus disparos
// --------------------------------------------------------
#ifndef JUGADOR_H
#define JUGADOR_H

#define JUG_DEAD     -100 // punto en el cual muere realmente (luego de -1, se muere agonizando)

#define MAX_SHOOT_JUG  15   // cantidad maxima de disparos
#define RATE_SHOOT     20   // 70 = 1 segundo
#define JVDX           10  // velocidad de los disparos en pixels

#define JVX            10   // velocidad X / 10
#define JVMX           80   // velocidad maxima X

#define JVY            10   // velocidad Y / 10
#define JVMY           80   // velocidad maxima Y

#define FRICCION       2    // Friccion

// Estructura del jugador
struct {
 // Estas coordenadas estan desplazada 1 decima (10 = 1.0)
 int x, y; // posicion
 int dx, dy; // direccion 

 int energia; // energia
 int last_shoot; // timer para el ultimo disparo (sincroniza con retrace_count)

 unsigned long puntaje; // puntaje

} jug; // jugador

// Disparos del jugador
struct {
  int x, y;
  int libre; // TRUE = disparo libre
} dispjug[MAX_SHOOT_JUG];

int disparolibre = 0; // disparo libre, -1 = ninguno

// Prototipos de funciones

void init_jugador();
void teclado_jugador();
void mover_jugador();
void dibujar_jugador(BITMAP *bmp);
void agregar_disparo_jug();
void mover_disparo_jug();
void dibujar_disparos_jugador(BITMAP *bmp);
#endif
