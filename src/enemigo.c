// -------------------------------------------------------- 
// enemigo.c 
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Rutinas que mueven, controlan, dibujan el enemigo
// y sus disparos
// -------------------------------------------------------- 
#ifndef ENEMIGO_C
#define ENEMIGO_C

// -------------------------------------------------------- 
// Inicializa el enemigo y sus disparos
// Solo coloca vivos 'vivos' enemigos (permite hacer mas niveles)
// -------------------------------------------------------- 
void init_enemigo(int vivos)
{
 int i = 0;

 proximo_nivel = FALSE;

 for (i = 0; i < MAX_ENE; i++)
    {
     ene[i].y = (random()%480)*10; // pantalla virtual = 640x480
     ene[i].dx = ene[i].dy = 0;
     ene[i].x = ((random()%320)+320)*10; 

     ene[i].energia = ENE_DEAD;  // todos muertos
     ene[i].last_shoot = 0;
     ene[i].last_move = 0;
    }

  for (i = 0; i < vivos; i++) ene[i].energia = 100; // vivos

 // Disparos
 disparolibre_ene = 0;
 for (i = 0; i < MAX_SHOOT_ENE; i++)  dispene[i].libre = TRUE;

}

// --------------------------------------------------------
// Interpretar IA enemiga
// -------------------------------------------------------- 
void IA_enemigo()
{
int i = 0, m = 1;
for (i = 0; i < MAX_ENE; i++)
   {
     if (ene[i].energia > ENE_DEAD )
     {
      // solo dispara si esta vivo
      if (ene[i].energia > 0 ) if (random()%100 < 25) agregar_disparo_ene(i); // disparar

         if ((ene[i].dx == 0) || (ene[i].dy == 0))
            {
              if (random()%100 < 50)
                  m = -1;
              else
                  m = 1;

              ene[i].dx = m*(random()% EVMX);
              ene[i].dy = m*(random()% EVMY);
            }
     }
   }
}

// --------------------------------------------------------
// Mover enemigo
// -------------------------------------------------------- 
void mover_enemigo()
{
// Notar que todas las coordenadas estan simuladas con / 10,
// entonces, debo transportar todo *10
int i = 0,  todos_muertos = TRUE;
static int tim1; // timer interno

for (i = 0; i < MAX_ENE; i++)
   {
     if (ene[i].energia > ENE_DEAD ) // luego de < 0, auto-explota hasta abajo
     {
         todos_muertos = FALSE; // al menos uno vivo

         if (ene[i].energia < 1) // agonizar y dar puntaje
            {
            ene[i].energia -= random()%2+1;

                if (abs(tim1 - retrace_count) > 3) // temporizar razonable...
                {
                 // sumar puntos, con mensaje
                 // sumar_puntaje_mensaje(ene[i].x,ene[i].y, random()%100+30, &jug.puntaje);
                 jug.puntaje += random()%100+30;

                tim1 = retrace_count;
                // sonido explosion
                play_sample(explosion_snd, al_azar(200,255), al_azar(64, 192), 1000 + al_azar(-500, 500), 0);

                agregar_explosion(ene[i].x / 10 + al_azar(-10,10) + enemigo_bmp[0]->w/2,
                                  ene[i].y / 10 + al_azar(-10,10) + enemigo_bmp[0]->h/2,
                                  random()%25+10,
                                  random()%35+35+abs(ene[i].energia),
                                  explosion_bmp);

                agregar_particulas(ene[i].x/10+ al_azar(-10,10)+ enemigo_bmp[0]->w/2,
                                   ene[i].y/10+ al_azar(-10,10)+ enemigo_bmp[0]->h/2,
                                   random()%25+20+abs(ene[i].energia),
                                   random()%10+10,
                                   3,
                                   particula_color,
                                   particula_color); 
                }
            } // fin agonizar

         ene[i].x += ene[i].dx;
         ene[i].y += ene[i].dy;

         if (ene[i].x < 3200) {   ene[i].x = 3200; ene[i].dx = 0; }
         if (ene[i].x > 6400 - enemigo_bmp[0]->w*10) { ene[i].x = 6400 - enemigo_bmp[0]->w*10; ene[i].dx = 0; }
         if (ene[i].y < 0)   { ene[i].y = 0; ene[i].dy = 0; }
         if (ene[i].y > 4800 - enemigo_bmp[0]->h*10) { ene[i].y = 4800 - enemigo_bmp[0]->h*10; ene[i].dy = 0; }

        if (ene[i].dx > 0) // FRICCION_ENE
           {
            ene[i].dx -= FRICCION_ENE;
            if (ene[i].dx < 0) ene[i].dx = 0;
           }

        if (ene[i].dx < 0) // FRICCION_ENE
           {
            ene[i].dx += FRICCION_ENE;
            if (ene[i].dx > 0) ene[i].dx = 0;
           }

        if (ene[i].dy > 0) // FRICCION_ENE
           {
            ene[i].dy -= FRICCION_ENE;
            if (ene[i].dy < 0) ene[i].dy = 0;
           }

        if (ene[i].dy < 0) // FRICCION_ENE
           {
            ene[i].dy += FRICCION_ENE;
            if (ene[i].dy > 0) ene[i].dy = 0;
           }
     }

   } // fin for

if (todos_muertos) proximo_nivel = TRUE; // pasar nivel, todos muertos!

}
// --------------------------------------------------------
// Dibuja el enemigo en el BMP (debe tener 640x480)
// --------------------------------------------------------
void dibujar_enemigo(BITMAP *bmp)
{
 BITMAP *bmp2 = NULL;

int i = 0;
for (i = 0; i < MAX_ENE; i++)
   {
     if (ene[i].energia > ENE_DEAD)
     {
         // elegir el da¤o
         bmp2 = enemigo_bmp[0];
         if (ene[i].energia < 75 ) bmp2 = enemigo_bmp[1];
         if (ene[i].energia < 50 ) bmp2 = enemigo_bmp[2];
         if (ene[i].energia < 25 ) bmp2 = enemigo_bmp[3];
 
         draw_sprite(bmp, bmp2, ene[i].x / 10, ene[i].y / 10);
     }
   }
}

// --------------------------------------------------------
// Agrega un disparo del enemigo 'i'
// -------------------------------------------------------- 
void agregar_disparo_ene(int i)
{
 if (ene[i].energia < 1) return; // enemigo muerto
 
 if (abs(ene[i].last_shoot - retrace_count) < ERATE_SHOOT) return; // no es tiempo de tirar...
 if (disparolibre_ene < 0) return; // no hay disparo libre
 
 ene[i].last_shoot = retrace_count;
 
 dispene[disparolibre_ene].x = ene[i].x / 10;
 dispene[disparolibre_ene].y = ene[i].y / 10 + enemigo_bmp[0]->h/2;
 dispene[disparolibre_ene].libre = FALSE;
 disparolibre_ene = -1;

 // sonido de disparo aqui
 play_sample(laser2_snd, 200, 128, 1000 + al_azar(-500, 500), 0);
}

// --------------------------------------------------------
// Mover disparos del enemigo
// -------------------------------------------------------- 
void mover_disparo_ene()
{
 int i = 0;

 // solucion ineficiente, pero rapida de programar, hay mejores formas
 disparolibre_ene = -1;
 for (i = 0; i < MAX_SHOOT_ENE; i++)
     {
       if (dispene[i].libre)
          {
            disparolibre_ene = i;
          }
          else
          {
            dispene[i].x -= EVDX;
            // verificar si le pego al jugador
            
            if (( dispene[i].x < jug.x / 10 + jugador_bmp[0]->w ) &&
                ( dispene[i].x > jug.x / 10 ) &&
                ( dispene[i].y + shoot_enemigo_bmp->h/2 < jug.y / 10 + jugador_bmp[0]->h ) &&
                ( dispene[i].y + shoot_enemigo_bmp->h/2 > jug.y / 10 ) )
                {
                    jug.energia -= random()%3+1; // restar energia (1..3)

                    // explosion aqui - sonido
                    play_sample(explosion_snd, 200, 128, 1000 + al_azar(-500, 500), 0);
                    
                         agregar_explosion(dispene[i].x,
                                           dispene[i].y,
                                           random()%25+10,
                                           random()%25+25,
                                           explosion_bmp);

                    // sonido grito de dolor
                    play_sample(grito_jugador_snd[random()%4], 255, 128, 1000, 0);

                    // particulas
                         agregar_particulas(dispene[i].x,
                                            dispene[i].y,
                                            random()%25+10,
                                            random()%10+10,
                                            al_azar(1,3),
                                            particula_color,
                                            particula_color); 
                    dispene[i].x = -666; // elminar disparo

                    // mensaje de dolor del NACHO! - DEBUG: esto es muy espefico, remover si se va a portar el engine
                    if (random()%100 < 15) agregar_mensaje_dolor_nacho(jug.x +  random()%25+10 , jug.y + random()%25+10);
                }

            if (dispene[i].x < 0)
               {
                dispene[i].libre = TRUE;
                disparolibre_ene = i;
               }
          } // fin ver si esta libre
     } // fin for
}

// --------------------------------------------------------
// Dibujar disparos del enemigo en bmp (640x480)
// -------------------------------------------------------- 
void dibujar_disparos_enemigo(BITMAP *bmp)
{
 int i = 0;

 // solucion ineficiente, pero rapida de programar, hay mejores formas
 disparolibre_ene = -1;
 for (i = 0; i < MAX_SHOOT_ENE; i++)
     {

       if (dispene[i].libre)
            disparolibre_ene = i;
          else
            draw_sprite(bmp, shoot_enemigo_bmp, dispene[i].x, dispene[i].y);

     } // fin for
}

#endif
