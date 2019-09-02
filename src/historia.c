// -------------------------------------------------------- 
// historia.c 
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Este modulo muestra la historia del juego
// en una pantalla scrolling...
// Tambien muestra el mensaje ATF de despedida en modo texto
// -------------------------------------------------------- 

#ifndef HISTORIA_C
#define HISTORIA_C

#include <conio.h> // necesario luego

void mostar_historia()
{

 char txt[150][80]; // lineas de texto (maximo 150)
 int cant = 0; // cantidad de texto
 int i = 0,x = 0,y = 0, c = 0 ; // para el for, scroll, etc
 char *txd; // datos de texto
 BITMAP *bmp = NULL; // buffer
 BITMAP *fnd = NULL; // fondo
 DATAFILE *p; // busqueda de info binaria
 int timer1; // temporizador...
 
 clear(screen);

 set_palette( *((PALETTE*)paleta_vga) ); // tengo que hacer esto porque es un puntero, y no una matriz

 bmp = create_bitmap(640,480);
 fnd = create_bitmap(640,480);

 clear(bmp);
 clear(fnd);

 hace_paisaje_estelar(fnd);

 // Tomar texto (si no hay, seguir... sorry)
        p = fuzzy_find_datafile_object(datfile, "historia_txt");
        if (p == NULL)
             return; // ERROR: no hay texto
        else
             txd = (char *)p->dat;

 // Abrir para leer y cargar en RAM
 // Como el dato es binario, recorro byte x byte buscando salto de linea (13)...
 x = 0;
 for (i=0; i < p->size; i++)
     {
       if (txd[i] != 13 && x < 79)
          {
            if (txd[i] >= 32) { txt[cant][x] = txd[i]; } // poner desde espacio en adelante...
            if (txd[i] < 32) { txt[cant][x] = ' '; } // reemplazar chars raros por espacios...
            x++;
          }
       else
           {
            txt[cant][x] = '\0'; // finalizar la linea
            cant++; x = 0;
           };
           
       if (cant > 150) return; // error, muchas lineas...
     };

 y = -480; // scroll de y del texto
 c =  makecol(255,255,255); // color del texto
 timer1 = retrace_count; // tomar tiempo...
 clear_keybuf();
 // loop principal, da una vuelta (puede cancelarse con una tecla...)
 while (!keypressed() && y < (cant * text_height(font_game)) )
   {
    // dibujar en el doble buffer el texto...
    blit(fnd, bmp, 0,0,0,0,bmp->w, bmp->h);
    
    text_mode(-1);

    for (i=0; i < cant; i ++)
        textprintf_centre(bmp, font_game, bmp->w/2, (i * text_height(font_game)) - y, c, "%s", txt[i]);

    // enviar a pantalla
    stretch_blit(bmp, screen, 0, 0, bmp->w, bmp->h, 0, 0, SCREEN_W, SCREEN_H);

//  textprintf(screen, font, 0,0, c, "y:%i", y); // DEBUG!

  if (text_height(font_game) / 8 < 1) // avanzar 1/x altura de font
      y++;
  else
      y += text_height(font_game) / 8;  


    while (abs(retrace_count - timer1) < 7); // pausar 70 = 1 segundo
    timer1= retrace_count;
   }; // fin while

 clear_keybuf();
}


// --------------------------------------------------------
// Mensaje de despedida - Creditos...
// LLAMAR EN MODO TEXTO
// MUESTRA EL MENSAJE ATF (GENERADO POR MI EDITOR ATF)
// QUE ES ASI [BYTE DE LETRA][BYTE COLOR]
// DONDE COLOR ES EL COLOR FG (4 bits bajos) Y BG (4 bits altos)
// Mapa de bits del color:
//     ---- XXXX = foreground color
//     -XXX ---- = background color
//     X--- ---- = 1=blink 0=steady
//
// Objeto: SALIR_ATF
// El mensaje comienza a partir del byte 16, el resto 0..15 son cabecera al dope
// -------------------------------------------------------- 
void mensaje_al_salir()
{
  DATAFILE *p; // busqueda de info binaria
  char *txd; // datos de texto
  int i; // para el for
  int y = 0, x = 0;

        p = fuzzy_find_datafile_object(datfile, "SALIR_ATF");
        if (p == NULL)
             return; // ERROR: no hay texto
        else
             txd = (char *)p->dat;

 // de byte 16 al final
 for (i=16; i < p->size - 2; i+=2)
     {
      textattr( (int)txd[i+1] ); // con esto queda joya el color
      cprintf("%c", txd[i]);
        x++;
        if (x>79) { x = 0; y++; };
        if (y > 21) break; // evitar que se salga de pantalla
     };

cprintf("\r");

// clear_keybuf();
//    while (!keypressed());
// clear_keybuf();

}



#endif
