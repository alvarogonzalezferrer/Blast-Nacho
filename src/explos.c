// -------------------------------------------------------- 
// explos.c 
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Engine de explosiones / humo / pedazos
// Como el sprite que las representa se puede cambiar dinamicamente
// el efecto es re-cool!
// --------------------------------------------------------
#ifndef EXPLOS_C
#define EXPLOS_C

// -------------------------------------------------------- 
// Reinicia las explosiones
// -------------------------------------------------------- 
void reset_explosiones()
{
int i;
    for (i=0; i< MAX_EXPLO; i++)
        explo[i].vidaact = -1; // muerta...

explo_libre = 0;
}

// -------------------------------------------------------- 
// Agrega una explosion
// En x,y con vida, de size, y con spr de imagen
// -------------------------------------------------------- 
void agregar_explosion(int x, int y, int vida, int size, BITMAP *spr)
{
int i; // cache
if (explo_libre < 0) return; // no hay explosion libre
i = explo_libre; // para ahorrarme escritura

explo[i].x = x;
explo[i].y = y;
explo[i].vidaorg = explo[i].vidaact = vida;
explo[i].sizeorg = explo[i].sizeact = size;
explo[i].spr = spr;
explo[i].ang = itofix(al_azar(0,255));
explo[i].frame = retrace_count;

explo_libre = -1;
}

// -------------------------------------------------------- 
// Mover explosiones
// --------------------------------------------------------
void mover_explosiones()
{
int i;
explo_libre = -1;

    for (i=0; i< MAX_EXPLO; i++)
    {
        if (explo[i].vidaact >0)
           {
            explo[i].vidaact--; // descontar vida
            if (abs(explo[i].frame - retrace_count) > EXPLO_VEL) // avanza frame
               {
               explo[i].ang =  fixadd(explo[i].ang, itofix(1));
               if (fixtoi(explo[i].ang) > 255) explo[i].ang = itofix(1);
               }
           }
           else
           {
           explo_libre = i;
           }
    }
}
// -------------------------------------------------------- 
// Dibuja explosiones en bmp
// --------------------------------------------------------
void dibujar_explosiones(BITMAP *bmp)
{
int i, x, y;
fixed escala;

explo_libre = -1;

    for (i=0; i< MAX_EXPLO; i++)
    {
        if (explo[i].vidaact >0)
           {
             // calcular tama¤o actual
             explo[i].sizeact = explo[i].vidaact * explo[i].sizeorg;
             if (explo[i].sizeact > 0) // evita / por 0
                      explo[i].sizeact /= explo[i].vidaorg;
                   else
                      explo[i].sizeact = 1;
                      
             if (explo[i].sizeact < 1) explo[i].sizeact = 1;

             // calcular centro
             x = explo[i].x - explo[i].sizeact / 2;
             y = explo[i].y - explo[i].sizeact / 2;
             // calcular escala (asume que el spr es cuadrado!)
             escala = ftofix( (float)(explo[i].sizeact) / (float)(explo[i].spr->w));
             // dibujar
             rotate_scaled_sprite(bmp,
                                  explo[i].spr,
                                  x, y,
                                  explo[i].ang,
                                  escala);
           }
           else
           {
           explo_libre = i;
           }
    }
    
}

#endif
