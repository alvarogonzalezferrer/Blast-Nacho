// -------------------------------------------------------- 
// enemigo.h 
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Rutinas que mueven, controlan, dibujan el enemigo
// y sus disparos
// --------------------------------------------------------
#ifndef ENEMIGO_H
#define ENEMIGO_H

#define ENE_DEAD     -100 // punto en el cual muere realmente (luego de -1, se muere agonizando)

#define MAX_ENE        10   // maxima cantidad de enemigos en pantalla ( y de niveles!)
#define MAX_SHOOT_ENE   5   // cantidad maxima de disparos
#define ERATE_SHOOT    55   // 70 = 1 segundo
#define EVDX            7  // velocidad de los disparos en pixels

#define EVX            15   // velocidad X / 10
#define EVMX          100   // velocidad maxima X

#define EVY            15   // velocidad Y / 10
#define EVMY          100   // velocidad maxima Y

#define FRICCION_ENE    1    // Friccion

int proximo_nivel = FALSE; // pasar a proximo nivel?

// Estructura del enemigo
struct {
 // Estas coordenadas estan desplazada 1 decima (10 = 1.0)
 int x, y; // posicion
 int dx, dy; // direccion 

 int energia; // energia
 int last_shoot; // timer para el ultimo disparo (sincroniza con retrace_count)
 int last_move; // timer para la IA

} ene[MAX_ENE]; // enemigo

// Disparos del enemigo
struct {
  int x, y;
  int libre; // TRUE = disparo libre
} dispene[MAX_SHOOT_ENE];

int disparolibre_ene = 0; // disparo libre, -1 = ninguno

// Prototipos de funciones

void init_enemigo(int vivos);
void IA_enemigo();
void mover_enemigo();
void dibujar_enemigo(BITMAP *bmp);
void agregar_disparo_ene(int i);
void mover_disparo_ene();
void dibujar_disparos_enemigo(BITMAP *bmp);
#endif
