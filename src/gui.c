// -------------------------------------------------------- 
// gui.c 
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Interfase del juego (portada, info, opciones, etc)
// -------------------------------------------------------- 
#ifndef GUI_C
#define GUI_C

// -------------------------------------------------------- 
// Portada introductoria
// Muestra la portada, toca el sonido de portada, y
// espera por una tecla...
// La paleta y DATs deben estar ya cacheadas
// --------------------------------------------------------
void mostrar_portada()
{
 DATAFILE *p = NULL; // puntero de busqueda
 BITMAP *bmp = NULL;
 SAMPLE *snd = NULL;

  clear(screen);

  set_palette( *((PALETTE*)paleta_vga) ); // tengo que hacer esto porque es un puntero, y no una matriz

 // Tomar imagen (si no hay, seguir... sorry)
        p = fuzzy_find_datafile_object_type(datfile, "portada_bmp", DAT_BITMAP);
        if (p == NULL)
             return; // ERROR: no hay portada
        else
             bmp = (BITMAP *)p->dat;

 // Enviar a pantalla
 stretch_blit(bmp, screen, 0, 0, bmp->w, bmp->h, 0, 0, SCREEN_W, SCREEN_H);

 // Tocar sonido
        p = fuzzy_find_datafile_object_type(datfile, "portada_snd", DAT_SAMPLE);
        if (p != NULL) // si hay, tocar, sino, ignorar
           {
             // esperar un poco mas de un segundo, para dar tiempo a que todo se calme... ;^D
             int tt1 = retrace_count;
             while (abs(retrace_count - tt1) < 100);

             // tocar
             snd = (SAMPLE *)p->dat;
             snd->priority = 255;
             play_sample(snd, 255, 128, 1000, 0);
           }

 // Esperar por tecla
    text_mode(-1);
    textout_centre(screen, font, "<< Presione una tecla >>", SCREEN_W/2, SCREEN_H - text_height(font), makecol(255,255,255) );

    clear_keybuf();
    readkey();
    clear_keybuf();
}

// -------------------------------------------------------- 
// Ayuda (explica como jugar)
// La paleta y DATs deben estar ya cacheadas
// --------------------------------------------------------
void mostrar_ayuda()
{
 DATAFILE *p = NULL; // puntero de busqueda
 BITMAP *bmp = NULL;

  clear(screen);

  set_palette( *((PALETTE*)paleta_vga) ); // tengo que hacer esto porque es un puntero, y no una matriz

 // Tomar imagen (si no hay, seguir... sorry)
        p = fuzzy_find_datafile_object_type(datfile, "ayuda_bmp", DAT_BITMAP);
        if (p == NULL)
             return; // ERROR: no hay portada
        else
             bmp = (BITMAP *)p->dat;

 // Enviar a pantalla
 stretch_blit(bmp, screen, 0, 0, bmp->w, bmp->h, 0, 0, SCREEN_W, SCREEN_H);

 // Esperar por tecla
    text_mode(-1);
    textout_centre(screen, font, "<< Presione una tecla >>", SCREEN_W/2, SCREEN_H - text_height(font), makecol(255,255,255) );

    clear_keybuf();
    readkey();
    clear_keybuf();

}

// -------------------------------------------------------- 
// Pantalla de ganador
// La paleta y DATs deben estar ya cacheadas
// --------------------------------------------------------
void pantalla_winner()
{
 DATAFILE *p = NULL; // puntero de busqueda
 BITMAP *bmp = NULL;
 SAMPLE *snd = NULL;

  clear(screen);

  set_palette( *((PALETTE*)paleta_vga) ); // tengo que hacer esto porque es un puntero, y no una matriz

 // Tomar imagen (si no hay, seguir... sorry)
        p = fuzzy_find_datafile_object_type(datfile, "winner_bmp", DAT_BITMAP);
        if (p != NULL)
             {
             bmp = (BITMAP *)p->dat;
             // Enviar a pantalla
             stretch_blit(bmp, screen, 0, 0, bmp->w, bmp->h, 0, 0, SCREEN_W, SCREEN_H);
             }



// poner titulo
text_mode(-1);
textout_centre(screen, font_game, "Sos un GANADOR!", SCREEN_W/2, 2, makecol(255,255,255));


// Tocar sonido
        p = fuzzy_find_datafile_object_type(datfile, "winner_snd", DAT_SAMPLE);
        if (p != NULL) // si hay, tocar, sino, ignorar
           {
             // esperar un poco mas de un segundo, para dar tiempo a que todo se calme... ;^D
             int tt1 = retrace_count;
             while (abs(retrace_count - tt1) < 100);

             // tocar
             snd = (SAMPLE *)p->dat;
             snd->priority = 255;
             play_sample(snd, 255, 128, 1000, 0);
           }

// Esperar por tecla
    text_mode(-1);
    textout_centre(screen, font, "<< Presione una tecla >>", SCREEN_W/2, SCREEN_H - text_height(font), makecol(255,255,255) );

    clear_keybuf();
    readkey();
    clear_keybuf();
}

// --------------------------------------------------------
// Pantalla de perdedor
// La paleta y DATs deben estar ya cacheadas
// --------------------------------------------------------
void pantalla_perdedor()
{
 DATAFILE *p = NULL; // puntero de busqueda
 BITMAP *bmp = NULL;
 SAMPLE *snd = NULL;

  clear(screen);

  set_palette( *((PALETTE*)paleta_vga) ); // tengo que hacer esto porque es un puntero, y no una matriz

 // Tomar imagen (si no hay, seguir... sorry)
        p = fuzzy_find_datafile_object_type(datfile, "game_over_bmp", DAT_BITMAP);
        if (p != NULL)
             {
             bmp = (BITMAP *)p->dat;
             // Enviar a pantalla
             stretch_blit(bmp, screen, 0, 0, bmp->w, bmp->h, 0, 0, SCREEN_W, SCREEN_H);
             }



// poner titulo
text_mode(-1);
textout_centre(screen, font_game, "Fin del juego!", SCREEN_W/2, 2, makecol(255,255,255));


// Tocar sonido
        p = fuzzy_find_datafile_object_type(datfile, "game_over_snd", DAT_SAMPLE);
        if (p != NULL) // si hay, tocar, sino, ignorar
           {
             // esperar un poco mas de un segundo, para dar tiempo a que todo se calme... ;^D
             int tt1 = retrace_count;
             while (abs(retrace_count - tt1) < 100);

             snd = (SAMPLE *)p->dat;
             snd->priority = 255;
             play_sample(snd, 255, 128, 1000, 0);
           }

// Esperar por tecla
    text_mode(-1);
    textout_centre(screen, font, "<< Presione una tecla >>", SCREEN_W/2, SCREEN_H - text_height(font), makecol(255,255,255) );

    clear_keybuf();
    readkey();
    clear_keybuf();
}

#endif
