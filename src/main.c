// -------------------------------------------------------- 
// Blast Krono(r)
// 
// main.c
// -------------------------------------------------------- 
// Copyright (c) 2002, Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Juego de navecitas hecho un dia de lluvia muy aburrido
// Historia: Kronomans del espacio invaden la tierra.
// Tu mision: detenerlos.
// DJGPP + Allegro 4.0.0
// Freeware
// Funciona en 640x480 o 320x200 x 256 colores
// -------------------------------------------------------- 

#ifndef MAIN_C
#define MAIN_C

// -------------------------------------------------------- 
// Inclusiones
// -------------------------------------------------------- 
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "allegro.h"

// Inclusiones propias

// *.h
#include "error.h"
#include "datafind.h"
#include "azar.h"
#include "partic.h"
#include "main.h"
#include "game.h"
#include "data.h"
#include "jugador.h"
#include "enemigo.h"
#include "explos.h"
#include "premio.h"
#include "stargen.h"
#include "palwhite.h"
#include "gui.h"
#include "highscr.h"
#include "historia.h"
#include "mensaje.h"

// *.c
#include "error.c"
#include "datafind.c"
#include "partic.c"
#include "azar.c"
#include "game.c"
#include "data.c"
#include "jugador.c"
#include "enemigo.c"
#include "explos.c"
#include "premio.c"
#include "stargen.c"
#include "gui.c"
#include "highscr.c"
#include "historia.c"
#include "mensaje.c"
// --------------------------------------------------------
// Comienzo
// -------------------------------------------------------- 
int main(int argc, char *argv[] )
{

    int i1; // para el for de los parametros
    int rx = 640, ry = 480; // para permitir que el usuario elija la resolucion
    int snd = TRUE; // quiere sonido
allegro_init(); // inicializa Allegro (nunca falla, al menos hasta v4.0.0)

// Inicia numeros aleatorios
srandom(time(NULL));

    // --------------------------------------------------------
    // Interpretar parametros
    // -------------------------------------------------------- 
    for (i1=1; i1<argc; i1++) {

    // -safe (modo seguro)
      if (stricmp(argv[i1], "-safe") == 0) { rx = 320; ry = 200; snd = FALSE; }

    // -320x200 (320x200)
      if (stricmp(argv[i1], "-320x200") == 0) { rx = 320; ry = 200; }

    // -320x240 (320x240)
      if (stricmp(argv[i1], "-320x240") == 0) { rx = 320; ry = 240; }

    // -800x600 (800x600)
      if (stricmp(argv[i1], "-800x600") == 0) { rx = 800; ry = 600; }

    // -1024x768 (1024x768)
      if (stricmp(argv[i1], "-1024x768") == 0) { rx = 1024; ry = 768; }

    // -nosound - sin sonido
      if (stricmp(argv[i1], "-nosound") == 0) { snd=FALSE; }

    // ayuda
      if (stricmp(argv[i1],"-h")==0 || stricmp(argv[i1],"-?") == 0 || stricmp(argv[i1],"--h") == 0 || stricmp(argv[i1],"/?") == 0)
         {
        printf("NachoBlast: Problemas y soluciones, parametros del juego:\n");
        printf("Antes de nada, el juego precisa al menos una PC 386 con DOS 2.0 o superior,\ny al menos 1 mb de memoria RAM, ademas de una placa de video VGA (320x200x256c)\n");
        printf("Los siguientes parametros pueden ayudarle a resolver problemas del juego:\n");
        printf("Uso: nachoblast.exe [parametros]; ejemplo nachoblast.exe -nosound\n");
        printf("\nParametro       Efecto\n");
        printf("-?              Muestra esta ayuda\n");
        printf("-safe           Coloca el juego en modo 'seguro'.\n");
        printf("                Es decir, coloca el juego en baja resolucion (320x200)\n");
        printf("                y sin sonido, con lo cual, funciona bien incluso en PCs viejas.\n");
        printf("-nosound        Desactiva TOTALMENTE el SONIDO, ideal en caso de que el\n");
        printf("                programa funcione lento, o se trabe al no reconocer\n");
        printf("                su placa de sonido.-\n");
        printf("-320x200        Coloca el video en modo VGA 320x200; ideal para placas de\n");
        printf("                video antiguas, lentas, o que no tienen soporte VESA.-\n");
        printf("-320x240        Coloca el video en modo X de VGA 320x240.-\n");
        printf("-800x600        Coloca el video en modo SVGA 800x600.-\n");
        printf("                Requiere una placa de video VESA 2.0 o superior\n");
        printf("-1024x768       Coloca el video en modo SVGA 1024x768.-\n");
        printf("                Requiere una placa de video VESA 2.0 o superior\n");
        printf("NOTA: el modo de video por default del juego es 640x480 VESA; y el sonido\n");
        printf("intenta ser autodetectado (se recomienda una placa Sound Blaster genuina).-\n");

         exit(0);
         }
    } // fin for


// intentar modo de video 640x480
if (set_gfx_mode(GFX_AUTODETECT, rx, ry, 0, 0) != 0)
  {
    if (set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0) != 0)
       {
       // intentar 320x200
       if (set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0) != 0)
          {
          // error
          set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
          allegro_message("ERROR\nModo de video invalido!: \n%s\n", allegro_error);
          exit(1);
          }
       }
  }
// Instalar teclado y timers y mouse
if (install_timer() != 0) levantar_error("ERROR: Fallo el inicio del temporizador!");
if (install_keyboard() != 0) levantar_error("ERROR: Imposible acceder al teclado!");
// DEBUG: no hay mouse, no lo preciso...


clear(screen);
textout(screen, font,"Espere... iniciando programa...",0,0, makecol(255,255,255));
textout(screen, font,"Si el juego se detiene aqui, intente reiniciarlo con el parametro -nosound.",0,SCREEN_H - text_height(font)*2 , makecol(255,255,255));
textout(screen, font,"Utilize el parametro -h para mas informacion. Ej: nachoblast -h",0,SCREEN_H - text_height(font), makecol(255,255,255));


// SONIDO
reserve_voices(8, 0); // 8 voces de sonido

// volumen por voz (def: 2, maximo volumen: 0)
set_volume_per_voice(1); // puede causar distorsion, ojo! causa DISTORSION!

if (snd)
   {
   if (install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL) == -1)
     { levantar_error("ERROR: no se puede configurar el sonido.\nPara desactivarlo use el parametro -nosound!");}
   }
else
  { install_sound(DIGI_NONE, MIDI_NONE, NULL); } // sin sonido

  // volumen al mango
  set_volume(255,-1);

// Cargar datos
cargar_datos();

salir_del_juego = FALSE;


while (!salir_del_juego)
{
    fade_out(4);

    // mostrar historia
    mostar_historia();
    
    fade_out(4);

    // Mostrar portada
    mostrar_portada();

    fade_out(4);

    // Mostrar instrucciones
    mostrar_ayuda();

    // Iniciar juego
    comenzar_juego();
}


// Finalizar
set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);

mensaje_al_salir();


// printf("(c) 2002, Kronoman - Hecho en la Republica Argentina\nEn memoria de mi querido padre\nPrograma freeware (GRATIS!)\n");
// printf("Gracias por jugar! - Programa gratuito - Copielo a sus amigos!\n");

return 0;
}


#endif
