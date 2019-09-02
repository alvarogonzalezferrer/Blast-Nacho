// -------------------------------------------------------- 
// premio.c
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Premios - por ahora, solo energia y puntos
// --------------------------------------------------------
#ifndef PREMIO_C
#define PREMIO_C

// -------------------------------------------------------- 
// Reinicia las premios
// -------------------------------------------------------- 
void reset_premios()
{
int i;
    for (i=0; i< MAX_PREMIO; i++)
         premio[i].vida = -1; // premio libre

premio_libre = 0;
}

// -------------------------------------------------------- 
// Agrega una premio
// En x,y (pixel) con spr de imagen y con sumar_puntos, sumar_energia
// -------------------------------------------------------- 
void agregar_premio(int x, int y, BITMAP *spr, SAMPLE *snd, int sumar_puntos, int sumar_energia)
{
int i; // cache
if (premio_libre < 0) return; // no hay premio libre
i = premio_libre; // para ahorrarme escritura

    premio[i].x = x * 100;
    premio[i].y = y * 100; 
    premio[i].dx = al_azar(-400,-100);
    premio[i].dy = al_azar(200,-200);
    premio[i].vida = PREMIO_VIDA;
    premio[i].spr = spr;
    premio[i].snd = snd;
    premio[i].ang = itofix(al_azar(0,255));
    premio[i].frame = retrace_count;
    premio[i].sumar_puntos = sumar_puntos;
    premio[i].sumar_energia = sumar_energia;

premio_libre = -1;
}

// -------------------------------------------------------- 
// Mover premios, y otorga el punto, si colisiona con el jugador
// --------------------------------------------------------
void mover_premios()
{
int i;
premio_libre = -1;

    for (i=0; i< MAX_PREMIO; i++)
    {
        if (premio[i].vida >0)
           {
            premio[i].vida--; // descontar vida
            premio[i].x += premio[i].dx;
            premio[i].y += premio[i].dy;
            if (premio[i].x < -500) premio[i].vida = 0;
            if (premio[i].y < -500) premio[i].vida = 0;
            if (premio[i].x > 64500) premio[i].vida = 0;
            if (premio[i].y > 48500) premio[i].vida = 0;

            if (abs(premio[i].frame - retrace_count) > PREMIO_VEL) // avanza frame
               {
                   premio[i].ang =  fixadd(premio[i].ang, itofix(1));
                   if (fixtoi(premio[i].ang) > 255) premio[i].ang = itofix(1);
               }

            // verificar si choco al jugador, otorgar premio
            if ((premio[i].x / 100 >= jug.x / 10) &&
                (premio[i].y / 100 >= jug.y / 10) &&
                (premio[i].x / 100 <= jug.x / 10 + jugador_bmp[0]->w) &&
                (premio[i].y / 100 <= jug.y / 10 + jugador_bmp[0]->h))
                {
                    premio[i].vida = -1;
                    jug.energia += premio[i].sumar_energia;

                        // sumar puntos, con mensaje
                        sumar_puntaje_mensaje(premio[i].x / 10,premio[i].y / 10, premio[i].sumar_puntos, &jug.puntaje);

                    if (jug.energia > 100) // si toma de mas, darle puntos en vez de energia
                    {
                        jug.puntaje += (jug.energia - 100) * 10;
                        jug.energia = 100;
                    }

                    // DEBUG: poner chispas o algo

                    // sonido de premio
                    if (premio[i].snd != NULL) play_sample(premio[i].snd, al_azar(128,255), 128, 1000 + al_azar(-500, 500), 0);
                }
           }
           else
           {
           premio_libre = i;
           }
    }
}
// -------------------------------------------------------- 
// Dibuja premios en bmp
// --------------------------------------------------------
void dibujar_premios(BITMAP *bmp)
{
int i;

premio_libre = -1;

    for (i=0; i< MAX_PREMIO; i++)
    {
        if (premio[i].vida >0)
           {
             // dibujar
                    rotate_sprite(bmp,
                                  premio[i].spr,
                                  premio[i].x / 100, premio[i].y / 100,
                                  premio[i].ang);
           }
           else
           {
               premio_libre = i;
           }
    }
}

#endif
