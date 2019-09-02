// -------------------------------------------------------- 
// jugador.c 
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Rutinas que mueven, controlan, dibujan el jugador
// y sus disparos
// -------------------------------------------------------- 
#ifndef JUGADOR_C
#define JUGADOR_C

// -------------------------------------------------------- 
// Inicializa el jugador y sus disparos
// -------------------------------------------------------- 
void init_jugador()
{
 jug.puntaje = 0;

 jug.y = 2400; // pantalla virtual = 640x480
 jug.dx = jug.dy = jug.x = 0; 

 jug.energia = 100; 
 jug.last_shoot = 0;

 // Disparos
 int i = 0;
 disparolibre = 0;
 for (i = 0; i < MAX_SHOOT_JUG; i++)  dispjug[i].libre = TRUE;

}

// --------------------------------------------------------
// Interpretar teclado
// -------------------------------------------------------- 
void teclado_jugador()
{
 if (key[KEY_LEFT])  jug.dx -= JVX;
 if (key[KEY_RIGHT]) jug.dx += JVX;
 if (key[KEY_UP])    jug.dy -= JVY;
 if (key[KEY_DOWN])  jug.dy += JVY;

 if (key[KEY_SPACE]) agregar_disparo_jug();
}

// --------------------------------------------------------
// Mover jugador
// -------------------------------------------------------- 
void mover_jugador()
{
// Notar que todas las coordenadas estan simuladas con / 10,
// entontes, debo transportar todo *10
static int tim1; // timer interno


         if (jug.energia < 1) // agonizar
            {
            jug.energia -= random()%2;
                if (abs(tim1 - retrace_count) > 3) // temporizar razonable...
                {
                tim1 = retrace_count; 
                // sonido explosion
                play_sample(explosion_snd, al_azar(128,255), 128, 1000 + al_azar(-500, 500), 0);

                // mensaje de dolor del NACHO! - DEBUG: esto es muy espefico, remover si se va a portar el engine
                if (random()%100 < 5) agregar_mensaje_dolor_nacho(jug.x +  random()%25+10 , jug.y + random()%25+10);

                agregar_explosion(jug.x / 10 + al_azar(-10,10) + enemigo_bmp[0]->w/2,
                                  jug.y / 10 + al_azar(-10,10) + enemigo_bmp[0]->h/2,
                                  random()%25+10,
                                  random()%35+35+abs(jug.energia),
                                  explosion_bmp);

                agregar_particulas(jug.x/10+ al_azar(-10,10)+ enemigo_bmp[0]->w/2,
                                   jug.y/10+ al_azar(-10,10)+ enemigo_bmp[0]->h/2,
                                   random()%25+20+abs(jug.energia),
                                   random()%10+10,
                                   3,
                                   particula_color,
                                   particula_color); 
                }
            } // fin agonizar


jug.x += jug.dx;
jug.y += jug.dy;

if (jug.x < 0)    jug.x = 0;
if (jug.x > 3200 - jugador_bmp[0]->w*10) jug.x = 3200 - jugador_bmp[0]->w*10;
if (jug.y < 0)    jug.y = 0;
if (jug.y > 4800 - jugador_bmp[0]->h*10) jug.y = 4800 - jugador_bmp[0]->h*10;


  if (jug.dx > 0) // friccion
     {
      jug.dx -= FRICCION;
      if (jug.dx < 0) jug.dx = 0;
     }

  if (jug.dx < 0) // friccion
     {
      jug.dx += FRICCION;
      if (jug.dx > 0) jug.dx = 0;
     }

  if (jug.dy > 0) // friccion
     {
      jug.dy -= FRICCION;
      if (jug.dy < 0) jug.dy = 0;
     }

  if (jug.dy < 0) // friccion
     {
      jug.dy += FRICCION;
      if (jug.dy > 0) jug.dy = 0;
     }

}
// --------------------------------------------------------
// Dibuja el jugador en el BMP (debe tener 640x480)
// --------------------------------------------------------
void dibujar_jugador(BITMAP *bmp)
{
 BITMAP *bmp2 = NULL;

 // elegir el da¤o
 bmp2 = jugador_bmp[0];
 if (jug.energia < 75 ) bmp2 = jugador_bmp[1];
 if (jug.energia < 50 ) bmp2 = jugador_bmp[2];
 if (jug.energia < 25 ) bmp2 = jugador_bmp[3];
 
 draw_sprite(bmp, bmp2, jug.x / 10, jug.y / 10);
}

// --------------------------------------------------------
// Agrega un disparo del jugador
// -------------------------------------------------------- 
void agregar_disparo_jug()
{

 if (abs(jug.last_shoot - retrace_count) < RATE_SHOOT) return; // no es tiempo de tirar...
 if (disparolibre < 0) return; // no hay disparo libre
 
 jug.last_shoot = retrace_count;
 
 dispjug[disparolibre].x = jug.x / 10 + jugador_bmp[0]->w;
 dispjug[disparolibre].y = jug.y / 10 + jugador_bmp[0]->h/2;
 dispjug[disparolibre].libre = FALSE;
 disparolibre = -1;

 // sonido de disparo aqui
 play_sample(laser1_snd, 200, 128, 1000 + al_azar(-500, 500), 0);
}

// --------------------------------------------------------
// Mover disparos del jugador
// -------------------------------------------------------- 
void mover_disparo_jug()
{
 int i = 0, i2 = 0;

 // solucion ineficiente, pero rapida de programar, hay mejores formas
 disparolibre = -1;
 for (i = 0; i < MAX_SHOOT_JUG; i++)
     {
       if (dispjug[i].libre)
          {
            disparolibre = i;
          }
          else
          {
            dispjug[i].x += JVDX;
            // verificar si le pego a algun enemigo!!!!
            for (i2 = 0; i2 < MAX_ENE; i2++)
            {
             if (ene[i2].energia > 0 )
                {
                if (( dispjug[i].x < ene[i2].x / 10 + enemigo_bmp[0]->w ) &&
                    ( dispjug[i].x > ene[i2].x / 10 ) &&
                    ( dispjug[i].y + shoot_jugador_bmp->h/2 < ene[i2].y / 10 + enemigo_bmp[0]->h ) &&
                    ( dispjug[i].y + shoot_jugador_bmp->h/2 > ene[i2].y / 10 ) )
                    {
                        ene[i2].energia -= random()%15 + 5;
                        // ver si murio


                        if (ene[i2].energia < 1)
                        {
                        // murio
                        // explosion, sonido de muerte
                        play_sample(explosion_snd, 200, 128, 1000 + al_azar(-500, 500), 0);

                        play_sample(grito_enemigo_snd[random()%4], 255, 128, 1000, 0);

                         agregar_explosion(dispjug[i].x,
                                           dispjug[i].y,
                                           random()%25+25,
                                           random()%60+80,
                                           explosion_bmp);


                        agregar_particulas(dispjug[i].x,
                                           dispjug[i].y,
                                           random()%50+25,
                                           random()%50+25,
                                           al_azar(1,3),
                                           particula_color,
                                           particula_color); // corregir color

                         // sumar puntos, con mensaje
                         sumar_puntaje_mensaje(ene[i2].x,ene[i2].y, random()%1000+100, &jug.puntaje);

                         // soltar premio
                         switch (random()%10)
                           {
                             // Moneda 
                             case 0:
                             case 1:
                             case 2:
                                 agregar_premio(dispjug[i].x, dispjug[i].y, premio_bmp[1], premio_snd[1], random()%500+250, random()%3);
                             break;

                             // Billete
                             case 3:
                             case 4:
                             case 5:
                                 agregar_premio(dispjug[i].x, dispjug[i].y, premio_bmp[2], premio_snd[2], random()%1000+750, random()%4);
                             break;

                             // Diamante
                             case 6:
                             case 7:
                                 agregar_premio(dispjug[i].x, dispjug[i].y, premio_bmp[3], premio_snd[3], random()%2000+2000, random()%4);
                             break;

                             // Energia
                             default: 
                             agregar_premio(dispjug[i].x,
                                            dispjug[i].y,
                                            premio_bmp[0],
                                            premio_snd[0],
                                            random()%100+100,
                                            random()%12+3);
                             break;

                           } // fin switch
                        }
                        else
                        {
                        // solo lo hirio

                        // sonido explosion 
                        play_sample(explosion_snd, 180, 128, 1000 + al_azar(-500, 500), 0);
                        // grito
                        play_sample(grito_enemigo_snd[random()%4], 255, 128, 1000, 0);

                        // explosion aqui
                         agregar_explosion(dispjug[i].x,
                                           dispjug[i].y,
                                           random()%25+10,
                                           random()%25+35,
                                           explosion_bmp);

                        
                        // particulas
                             agregar_particulas(dispjug[i].x,
                                                dispjug[i].y,
                                                random()%15+15,
                                                random()%15+15,
                                                al_azar(1,3),
                                                particula_color,
                                                particula_color);  
                         // puntaje
                         jug.puntaje += random()%100+10;

                         // debug: mensaje de dolor...
                         if (random()%100 < 25) agregar_mensaje_dolor(ene[i2].x, ene[i2].y);
                        }
                        dispjug[i].x = 6666; // elminar disparo
                    }
                }
            } // fin for de enemigos

            if (dispjug[i].x > 640)
               {
                dispjug[i].libre = TRUE;
                disparolibre = i;
               }
          } // fin ver si esta libre
     } // fin for
}

// --------------------------------------------------------
// Dibujar disparos del jugador en bmp (640x480)
// -------------------------------------------------------- 
void dibujar_disparos_jugador(BITMAP *bmp)
{
 int i = 0;

 // solucion ineficiente, pero rapida de programar, hay mejores formas
 disparolibre = -1;
 for (i = 0; i < MAX_SHOOT_JUG; i++)
     {

       if (dispjug[i].libre)
            disparolibre = i;
          else
            draw_sprite(bmp, shoot_jugador_bmp, dispjug[i].x, dispjug[i].y);

     } // fin for
}

#endif
