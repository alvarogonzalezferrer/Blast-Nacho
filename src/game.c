// -------------------------------------------------------- 
// Blast Krono(r)
// 
// game.c
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Engine del juego 
// -------------------------------------------------------- 
#ifndef GAME_C
#define GAME_C

#define FPSQ  30   // cantidad de actualizaciones x seg que quiero (1,2,4,5,6,10,12,15..60)
                   // default: 60
                   // SOLO usar divisores de 60 y <= 60!

// Contador para mantener la velocidad del juego constante...
volatile int contador_vel = 0;

// -------------------------------------------------------- 
// Auxiliar interna, que se ejecuta en un timer para mantener la velocidad
// -------------------------------------------------------- 
void incrementar_contador_vel()
{
   contador_vel += 60 / FPSQ;
}

END_OF_FUNCTION(incrementar_contador_vel);

// -------------------------------------------------------- 
// Auxiliar que confirma la salida (para no sobrecargar el loop)
// -------------------------------------------------------- 
void confirmar_salida()
{
                  // confirmar salida
                  
                   key[KEY_ESC] = FALSE;
                   clear_keybuf();
                  
                  // Mensaje GUI
                  gui_fg_color = makecol(255,255,255);
                  gui_bg_color = makecol(0,0,0);
                  switch (alert3("Finalizar juego", "Accion a tomar?", NULL, "Cancelar", "Salir", "Reiniciar", 0, 0, 0) )
                      {
                     // case 1: // cancelo...
                     // break;

                      case 2: // salir al DOS
                           game_over = TRUE;
                           salir_del_juego = TRUE;
                      break;
                      case 3: // reiniciar juego, game over
                            game_over = TRUE;
                            salir_del_juego = FALSE;

                      break;
                      default:
                      // nunca debe llegar aca
                      break;

                      };

                  contador_vel = 0; // evitar frame skip...

                  clear_keybuf();
                  key[KEY_ESC] = FALSE;
}

// -------------------------------------------------------- 
// Comienzo del juego - llamar aqui para comenzar a jugar
// -------------------------------------------------------- 
void comenzar_juego()
{
  int nivel_actual = 2; // cantidad de enemigos a pelear (nivel)
  char msg_level[40]; // mensaje del nivel...

  // Setear el timer para mantener las fps correctas
  LOCK_VARIABLE(contador_vel);
  LOCK_FUNCTION(incrementar_contador_vel);

  // Instala el timer a 60 fps...
  install_int_ex(incrementar_contador_vel, BPS_TO_TIMER(FPSQ));

  // Setea el comienzo
  game_over = FALSE;

  // Buffer de pantalla virtual de 640x480
  // se dibuja en ese tama¤o, y luego se reduce a la resolucion actual
  pantalla = create_bitmap(640,480);

  // Fondo de la pantalla
  fondo_bmp = create_bitmap(640,480);


  init_jugador();   // inicia jugador

  particula_color = makecol(240,240,0);

while (!game_over) // loop de niveles
 {
  // fondo dinamico
  hace_paisaje_estelar(fondo_bmp);

  // devolver algo de energia al jugador
  jug.energia += random()%25 + 25;
  if (jug.energia > 100) jug.energia = 100;

  // reposicionar jugador
  jug.x = 200;
  jug.y = 3200;
  jug.dx = 0;
  jug.dy = 0;

  init_enemigo(nivel_actual); // enemigos (parametro = cantidad enemigos)

  reset_explosiones(); // resetear explosiones
  reset_particulas(); // resetear particulas
  reset_premios(); // resetear premios

  fade_out(2);

  clear(pantalla);
  clear(screen);

  set_palette( *((PALETTE*)paleta_vga) ); // tengo que hacer esto porque es un puntero, y no una matriz

  reset_mensajes();

  sprintf(msg_level,"Nivel %i", nivel_actual - 1);
  agregar_mensaje(3200, 2200,110, 0, -25, font_game, msg_level, makecol(255,255,0) );
  
  // -------------------------------------------------------- 
  while ((!game_over) && (!proximo_nivel)) // loop de juego, 'proximo_nivel' en enemigos.h
   {
        while (contador_vel > 0)
          {
              actualizar_logica();
              contador_vel--;

              // Chequear teclas vitales (ESC y F7 para salir del juego)
              if (key[KEY_ESC] ) confirmar_salida(); // ESC finaliza y sale al DOS

              // TRUCO: presionar N+A+C+H+O para pasar de nivel!
              if (key[KEY_N] &&
                  key[KEY_A] &&
                  key[KEY_C] &&
                  key[KEY_H] &&
                  key[KEY_O]) proximo_nivel = TRUE;

              if (key[KEY_F7]  ) { jug.energia = -1; } // F7 comete suicidio

              // si se le acabo la energia, finalizar
              if (jug.energia < JUG_DEAD) game_over = TRUE; // moriste macho...
          }
        actualizar_pantalla();
   }
   // -------------------------------------------------------- 

   if (proximo_nivel) { nivel_actual++; proximo_nivel = 0; } // pasar nivel
   if (nivel_actual > MAX_ENE) game_over = TRUE; // GANO!!! verificar luego, debug

 } // fin loop de niveles

   // mostrar pantalla ganador / perdedor
   if (nivel_actual > MAX_ENE) // gano
     pantalla_winner();
   else
     pantalla_perdedor();

   // chequear alto puntaje (top 10)
   check_alto_puntaje(jug.puntaje);

   // mostrar alto puntaje
   mostrar_altos_puntajes();

   fade_out(2);

   // Liberar memoria
   destroy_bitmap(pantalla);
   destroy_bitmap(fondo_bmp);

} // fin comenzador del juego

// -------------------------------------------------------- 
// Actualiza la logica del juego
// --------------------------------------------------------
void actualizar_logica()
{

 // Mover el jugador
 mover_jugador();

 // Mover disparos del jugador
 mover_disparo_jug();

 // Enemigo
 mover_enemigo();
 mover_disparo_ene();

 // enemigos
 IA_enemigo();

 // Particulas
 mover_particulas();

 // Explosiones
 mover_explosiones();

 // Premios
 mover_premios();

 // Mensajes
 mover_mensajes();

 // Interpretar teclado
 teclado_jugador();

 // Funcion especial - Si se presiona PAUSA o P, se produce la pausa del juego.
 if (key[KEY_PAUSE] || key[KEY_P])
     {
       key[KEY_PAUSE] = FALSE;
       key[KEY_P] = FALSE;
       clear_keybuf();
       // Mensaje GUI
       gui_fg_color = makecol(255,255,255);
       gui_bg_color = makecol(0,0,0);
       alert("Nacho Blast", "Juego en pausa", NULL, "Continuar", NULL, 0, 0);
       clear_keybuf();
       key[KEY_PAUSE] = FALSE;
       key[KEY_P] = FALSE;
       contador_vel = 0; // evitar frame skip...
     } // fin pausa

}

// --------------------------------------------------------
// Dibuja el juego en pantalla
// -------------------------------------------------------- 
void actualizar_pantalla()
{
  static int negro = -1, blanco = -1;
  int xe;
  if (negro < 0) negro = makecol(0,0,0);
  if (blanco <0) blanco = makecol(255,255,255);

  // Dibujar fondo
  blit(fondo_bmp, pantalla, 0, 0, 0, 0, fondo_bmp->w, fondo_bmp->h);

  // Premios
  dibujar_premios(pantalla);

  // Dibujar jugador
  dibujar_jugador(pantalla);
  dibujar_enemigo(pantalla);

  // Dibujar disparos jugador
  dibujar_disparos_jugador(pantalla);
  dibujar_disparos_enemigo(pantalla);

  // Particulas
  dibujar_particulas(pantalla);

  // Explosiones
  dibujar_explosiones(pantalla);

  // Mensajes
  dibujar_mensajes(pantalla);

  // Poner puntaje y energia
  xe = jug.energia;
  if (xe < 0) xe = 0;
  text_mode(-1);

// metodo viejo
//  rectfill(pantalla, 0, 0, xe, text_height(font_game), blanco);
//  textprintf(pantalla, font_game, xe+2, 0, blanco, "%3d%%", xe);
// puntaje
//  textprintf(pantalla, font_game, 2, text_height(font_game)+4, blanco, "%010ld", jug.puntaje);
// metodo nuevo
textprintf(pantalla, font_game, 0, 0, blanco, "%3d%% - %010ld ", xe, jug.puntaje);

  // Enviar doble buffer a pantalla
  if ((pantalla->w == SCREEN_W) && (pantalla->h == SCREEN_H))
      blit(pantalla, screen, 0,0,0,0,pantalla->w, pantalla->h); // copiar directo
  else // ajustar a pantalla (mas lento en pantallas grandes, mas rapido en 320x200)
      stretch_blit(pantalla, screen, 0, 0, pantalla->w, pantalla->h, 0, 0, SCREEN_W, SCREEN_H);

// si presiona F12, capturar la pantalla 640x480 a un PCX en el dir actual
if (key[KEY_F12]  ) {
    key[KEY_F12] = FALSE;
          PALETTE pal;
          char tempfname[13] = "nbXXXXXX";
          mktemp(tempfname); // nombre unico...
          tempfname[8] = '.';
          tempfname[9] = 'P';
          tempfname[10] = 'C';
          tempfname[11] = 'X';
          tempfname[12] = '\0';
          get_palette(pal);
          save_bitmap(tempfname, pantalla, pal);
          // agrego mensaje informando
          agregar_mensaje(1000, 1000, 150, -10, -10, font, "Se salvo la pantalla", makecol(255,255,255));
    }

}

#endif
