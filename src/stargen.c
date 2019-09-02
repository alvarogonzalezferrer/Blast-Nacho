// -------------------------------------------------------- 
// stargen.c 
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Generador de paisajes estelares
// -------------------------------------------------------- 
#ifndef STARGEN_C
#define STARGEN_C

// -------------------------------------------------------- 
// Crea un paisaje estelar en bmp
// -------------------------------------------------------- 
void hace_paisaje_estelar(BITMAP *bmp)
{
 // Set de color actual
 int col[3];
 int i = 0, i1 = 0, c = 0, x = 0, y = 0, xd = 0, yd = 0; // vars utiles...

 clear(bmp);

 // Funcion interna auxiliar, que setea los colores de la funcion padre
 void elegir_set_colores()
 {
     // Setear colores
     switch ( random()% 7 )
     {
     case 0:
         col[0] = makecol(128,128,128);
         col[1] = makecol(192,192,192);
         col[2] = makecol(255,255,255);
         break;
    
     case 1:
         col[0] = makecol(8,128,8);
         col[1] = makecol(8,192,8);
         col[2] = makecol(8,255,8);
         break;

     case 2:
         col[0] = makecol(128,128,128);
         col[1] = makecol(128,128,192);
         col[2] = makecol(128,128,255);
         break;

     case 3:
         col[0] = makecol(128,28,28);
         col[1] = makecol(192,92,92);
         col[2] = makecol(255,55,55);
         break;

     case 4:
         col[0] = makecol(247,255,29);
         col[1] = makecol(247,128,29);
         col[2] = makecol(247,64,29);
         break;

     case 5:
         col[0] = makecol(128,0,100);
         col[1] = makecol(64,0,100);
         col[2] = makecol(32,0,100);
         break;

     default:
         col[0] = makecol(128,128,128);
         col[1] = makecol(192,192,192);
         col[2] = makecol(255,255,255);
     }
 } // fin elegir_set_colores()


  // Funcion interna auxiliar: 'pincel'
  // en la var global i esta el radio, y en i1 el incremento de radio
  void pincel(BITMAP *bmp, int x, int y, int densidad)
       {
       int j;

       for (j=0; j < random()%densidad+1; j++)
              {
              if (random()%100 > 85)
                 circlefill(bmp, x + (random()%(i*2))-i, y + (random()%(i*2))-i, 1, col[random()%3]);
              else
                 putpixel(bmp, x + (random()%(i*2))-i, y + (random()%(i*2))-i, col[random()%3] );
              }

       // radio:
         i += i1;
         if (i < 5) { i = 5; i1 = abs(i1); }
         if (i > 50) { i = 50; i1 = -abs(i1); }
       };




elegir_set_colores();

 // Estrellas normales

 for (i = 0; i < random()%1000+500; i++)
        {
        c = col[random()%3];
        x = random() % bmp->w;
        y = random() % bmp->h;

        putpixel(bmp, x, y, c);

        // tipo de estrella
        if (random()%100 > 85)
                  circlefill(bmp, x,y,1,c);

        } // fin for estrellas normales



  // Constelaciones (COOL!)
  for (c = 0; c < random()%3+1; c++)
  {
      // radio inicial del pincel
      i = random()%20+5;

      // mov del radio
      if (random() % 2 == 1)
       i1 = 1;
      else
       i1 = -1; 

     // posicion / direccion
     switch (random()%4)
     {
     case 0:
        x = 0;
        y = 0;
        xd = random()%15 + 1;
        yd = random()%15 + 1;
     break;

     case 1:
        x = bmp->w;
        y = bmp->h;
        xd = -1 * ( random()%15 + 1);
        yd = -1 * ( random()%15 + 1);
     break;

     case 2:
        x = 0;
        y = bmp->h;
        xd = random()%10 + 1;
        yd = -1 * (random()%15 + 1);
     break;

     case 3:
        x = bmp->w;
        y = 0;
        xd = -1 * (random()%15 + 1);
        yd = random()%15 + 1;
     break;
     }

     elegir_set_colores();

     while ( (x >= 0) && (x <= bmp->w) && (y >= 0) && (y <= bmp->h) )
     {
         // Trazar
            x += xd;
            y += yd;
         pincel(bmp, x, y, random()%15+5);
     }
  } // fin constelaciones


// Planetas o algo asi...

   for (c =0; c < random()%3; c++)
      {
      // radio inicial del pincel
      i = random()%20+5;

      // mov del radio
      if (random() % 2 == 1)
       i1 = 1;
      else
       i1 = -1; 
       elegir_set_colores();
       do_ellipse(bmp, random()%bmp->w, random()%bmp->h, random()% bmp->w/2 + 50, random()% bmp->w/2 + 50, random()%3+1, pincel);
       }
}

// ver tambien: do_arc, spline, etc

#endif
