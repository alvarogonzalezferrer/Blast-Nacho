// -------------------------------------------------------- 
// Blast Krono(r)
// 
// game.h
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Engine del juego
// -------------------------------------------------------- 
#ifndef GAME_H
#define GAME_H

BITMAP *pantalla = NULL; // buffer de 640x480 en donde se dibuja el juego
                         // y luego, se vuelca a pantalla

int game_over = FALSE; // indica si termino el juego

// -------------------------------------------------------- 
// Cache de graficos 
// -------------------------------------------------------- 

// Color de particulas...
int particula_color = 0; // cachear luego

// Paleta del juego
PALETTE *paleta_vga = NULL; 

// Fondo
BITMAP *fondo_bmp = NULL; // 640x480

// Enemigo (enemigo_bmp_0..enemigo_bmp_3)
BITMAP *enemigo_bmp[4]; // enemigo da¤o (0..3) (0,25,50,75)

BITMAP *shoot_enemigo_bmp = NULL; // disparos enemigo

// Jugador
BITMAP *jugador_bmp[4]; // jugador da¤o  (0..3) (0,25,50,75)

BITMAP *shoot_jugador_bmp = NULL; // disparos jugador

// Explosiones 
BITMAP *explosion_bmp = NULL;

// Humo - DEBUG, sin hacer
// BITMAP humo_bmp = NULL;

// Premios [energia, moneda, billete, diamante]
BITMAP *premio_bmp[4];

// Tipo de letra
FONT *font_game = NULL;

// Sonidos

// Laser jugador
SAMPLE *laser1_snd = NULL;

// Laser enemigos
SAMPLE *laser2_snd = NULL;

// Explosion
SAMPLE *explosion_snd = NULL;

// Gritos jugador
SAMPLE *grito_jugador_snd[4];

// Gritos enemigo
SAMPLE *grito_enemigo_snd[4];

// Premios
SAMPLE *premio_snd[4];

// -------------------------------------------------------- 
// Prototipos
// -------------------------------------------------------- 
void confirmar_salida();
void comenzar_juego(); // comienza el juego
void actualizar_logica();  // logica del juego
void actualizar_pantalla(); // pantalla del juego

#endif
