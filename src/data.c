// -------------------------------------------------------- 
// data.c 
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Carga datos del programa
// -------------------------------------------------------- 

#ifndef DATA_C
#define DATA_C
// -------------------------------------------------------- 
// Carga los datos, y los cachea tambien.
// LLAMAR EN MODO GRAFICO PARA QUE LOS DATOS CARGUEN OK...
// Si falla, levanta un error y termina.
// Si todo OK, va mostrando el progreso de la carga (que cheto!)
// -------------------------------------------------------- 
void cargar_datos()
{
    DATAFILE *p = NULL; // puntero de busqueda
    int i; // para el for
    char buf[256]; // nombre del sprite

    if (datfile != NULL) // si ya esta cargado, descargar
       {
       unload_datafile(datfile);
       datfile = NULL;
       }

       // ---------
       // RUTINA AUXILIAR DE CALLBACK que muestra '.' en pantalla
       // a medida que carga los objetos...
       int xt = 0, yt = 0; // coordenadas x,y del punto...
       yt = text_height(font) * 2; // comenzar en la 2nda linea
       int colt;
       colt = makecol(255,255,255); // blanco...
       void cargar_callback(DATAFILE *d)
         {
           textout(screen,font,">", xt, yt, colt);
           xt += text_length(font,">");
           if (xt > SCREEN_W * 0.9) { xt = 0; yt += text_height(font); }
         }
       // ---------
       
    // intentar cargar el archivo de disco
    datfile = load_datafile_callback("game.dat", cargar_callback);

    // Si no existe, cargar el interno
    if (datfile == NULL) datfile = load_datafile("#");

    // si no existe game over
    if (datfile == NULL) levantar_error("ERROR: Imposible cargar datos del programa!");

    // cachear bitmaps y paleta

    // busca la paleta (metodo de busqueda aproximada)
    p = fuzzy_find_datafile_object_type(datfile, "PALETA_VGA", DAT_PALETTE);
    if (p == NULL) levantar_error("ERROR FATAL: no existe la paleta_vga!!!");
    paleta_vga = (PALETTE *)p->dat;

     // Font
        p = fuzzy_find_datafile_object_type(datfile, "font_game", DAT_FONT);
        if (p == NULL)
             levantar_error("ERROR FATAL: font_game faltante!\n");
        else
             font_game = p->dat;



    // Fondo (anulado, lo genero en forma dinamica)
//    p = fuzzy_find_datafile_object_type(datfile, "fondo_bmp", DAT_BITMAP);
//    if (p == NULL)
//         levantar_error("ERROR FATAL: falta el fondo 640x480!\n");
//    else
//         fondo_bmp = p->dat;

    // sprites

    // enemigo
    for (i = 0; i < 4; i++)
    {
        sprintf(buf,"enemigo_bmp_%d", i);
        p = fuzzy_find_datafile_object_type(datfile, buf, DAT_BITMAP);
        if (p == NULL)
             levantar_error("ERROR FATAL: sprite enemigo faltante!\n");
        else
             enemigo_bmp[i] = p->dat;
    }

    // disparo enemigo
        p = fuzzy_find_datafile_object_type(datfile, "shoot_enemigo_bmp", DAT_BITMAP);
        if (p == NULL)
             levantar_error("ERROR FATAL: shoot_enemigo_bmp faltante!\n");
        else
             shoot_enemigo_bmp = p->dat;

    // jugador
    for (i = 0; i < 4; i++)
    {
        sprintf(buf,"jugador_bmp_%d", i);
        p = fuzzy_find_datafile_object_type(datfile, buf, DAT_BITMAP);
        if (p == NULL)
             levantar_error("ERROR FATAL: sprite jugador faltante!\n");
        else
             jugador_bmp[i] = p->dat;
    }

    // disparo jugador
        p = fuzzy_find_datafile_object_type(datfile, "shoot_jugador_bmp", DAT_BITMAP);
        if (p == NULL)
             levantar_error("ERROR FATAL: shoot_jugador_bmp faltante!\n");
        else
             shoot_jugador_bmp = p->dat;
    

     // Explosion
        p = fuzzy_find_datafile_object_type(datfile, "explosion_bmp", DAT_BITMAP);
        if (p == NULL)
             levantar_error("ERROR FATAL: sprite explosion faltante!\n");
        else
             explosion_bmp = p->dat;

     // Premios
     for (i = 0; i < 4; i++)
     {
        sprintf(buf,"premio_bmp_%d", i);
        p = fuzzy_find_datafile_object_type(datfile, buf, DAT_BITMAP);
        if (p == NULL)
             levantar_error("ERROR FATAL: premio faltante!\n");
        else
             premio_bmp[i] = p->dat;
     }


    // Sonidos
        p = fuzzy_find_datafile_object_type(datfile, "laser1_snd", DAT_SAMPLE);
        if (p == NULL)
             levantar_error("ERROR FATAL: sonido laser1_snd faltante!\n");
        else
             laser1_snd = p->dat;

             // prioridad
             laser1_snd->priority = 32;

        p = fuzzy_find_datafile_object_type(datfile, "laser2_snd", DAT_SAMPLE);
        if (p == NULL)
             levantar_error("ERROR FATAL: sonido laser2_snd faltante!\n");
        else
             laser2_snd = p->dat;

             // prioridad
             laser2_snd->priority = 16;

        p = fuzzy_find_datafile_object_type(datfile, "explosion_snd", DAT_SAMPLE);
        if (p == NULL)
             levantar_error("ERROR FATAL: sonido explosion_snd faltante!\n");
        else
             explosion_snd = p->dat;

             // prioridad mayor a los lasers (def = 128)
             explosion_snd->priority = 72;

    // GRITOS del jugador
    for (i = 0; i < 4; i++)
    {
        sprintf(buf,"grito_jugador_snd_%d", i);
        p = fuzzy_find_datafile_object_type(datfile, buf, DAT_SAMPLE);
        if (p == NULL)
             levantar_error("ERROR FATAL: grito_jugador_snd faltante!\n");
        else
             grito_jugador_snd[i] = p->dat;

             grito_jugador_snd[i]->priority = 132; // prioridad
    }

    // GRITOS del enemigo
    for (i = 0; i < 4; i++)
    {
        sprintf(buf,"grito_enemigo_snd_%d", i);
        p = fuzzy_find_datafile_object_type(datfile, buf, DAT_SAMPLE);
        if (p == NULL)
             levantar_error("ERROR FATAL: grito_enemigo_snd faltante!\n");
        else
             grito_enemigo_snd[i] = (SAMPLE *)p->dat;

             grito_enemigo_snd[i]->priority = 128; // prioridad
    }

    // Premios
    for (i = 0; i < 4; i++)
    {
        sprintf(buf,"premio_snd_%d", i);
        p = fuzzy_find_datafile_object_type(datfile, buf, DAT_SAMPLE);
        if (p == NULL)
             levantar_error("ERROR FATAL: premio_snd faltante!\n");
        else
             premio_snd[i] = (SAMPLE *)p->dat;

             premio_snd[i]->priority = 132; // prioridad
    }

    // Crear mapa RGB
    create_rgb_table(&rgb_table, *((PALETTE*)paleta_vga) , NULL);
    rgb_map = &rgb_table;
    // Todo bien negrita...
}
#endif
