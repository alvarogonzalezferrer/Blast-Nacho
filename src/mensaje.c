// -------------------------------------------------------- 
// mensaje.c 
// -------------------------------------------------------- 
// Copyright (c) Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Sistema de mensajes en pantalla de NachoBlast
// -------------------------------------------------------- 
#ifndef MENSAJE_C
#define MENSAJE_C

// --------------------------------------------------------
// Reinicia los mensajes
// -------------------------------------------------------- 
void reset_mensajes()
{
int i;
    for (i=0; i< MAX_MSG; i++)
        msg[i].vida = -1; // muerto

msg_libre = 0;
}


// -------------------------------------------------------- 
// Agrega un mensaje
// En x,y con vida, con movimiento dx,dy, con font fnt, y texto txt, y color
// NOTA: Estas coordenadas estan desplazada 1 decima (10 = 1.0)
// -------------------------------------------------------- 
void agregar_mensaje(int x, int y, int vida, int dx, int dy, FONT *fnt, char *txt, int color)
{
int i; // cache
if (msg_libre < 0) return; // no hay explosion libre
i = msg_libre; // para ahorrarme escritura

msg[i].x = x;
msg[i].y = y;
msg[i].dx = dx;
msg[i].dy = dy;
msg[i].vida = vida;
msg[i].fnt = fnt;

sprintf(msg[i].txt,"%s",txt);

msg[i].color = color;
msg[i].timer1 = retrace_count;

msg_libre = -1;
}

// -------------------------------------------------------- 
// Mover mensajes
// --------------------------------------------------------
void mover_mensajes()
{
int i;
msg_libre = -1;

    for (i=0; i< MAX_MSG; i++)
    {
        if (msg[i].vida > 0)
           {
            if (abs(msg[i].timer1 - retrace_count) >= 1)
                {
                msg[i].vida--; // descontar vida
                    // mover mensaje
                    msg[i].x += msg[i].dx;
                    msg[i].y += msg[i].dy;
                    msg[i].timer1 = retrace_count;
                }
           }
           else
           {
               msg_libre = i;
           }
    }
}

// -------------------------------------------------------- 
// Dibujar mensajes
// --------------------------------------------------------
void dibujar_mensajes(BITMAP *bmp)
{
 int i;

msg_libre = -1;

    text_mode(-1);

    for (i=0; i< MAX_MSG; i++)
    {
       if (msg[i].vida > 0)
       {
         textprintf_centre(bmp, msg[i].fnt, msg[i].x / 10,msg[i].y / 10, msg[i].color, "%s", msg[i].txt);
       }
       else
       {
       msg_libre = i;
       }
    }
}

// --------------------------------------------------------
// Macro para agregar onomatopeyas de dolor de enemigos... ;^P
// --------------------------------------------------------
void agregar_mensaje_dolor(int x, int y)
{
char msg[25];
int col;
col = makecol(255,255,255);

switch (random()%6)
   {
   case 0:
        col = makecol(255,255,0);
   break;
   case 1:
        col = makecol(0,255,255);
   break;
   case 2:
        col = makecol(255,0,255);
   break;
   case 3:
        col = makecol(255,64,64);
   break;
   default:
    col = makecol(255,255,255);
   break;
   };

switch (random()%10)
   {
   case 0:
       sprintf(msg,"Argh!");
   break;
   case 1:
       sprintf(msg,"Ohh!");
   break;

   case 2:
       sprintf(msg,"Skirk!");
   break;

   case 3:
       sprintf(msg,"Arghh");
   break;

   case 4:
       sprintf(msg,"Auch!");
   break;

   case 5:
       sprintf(msg,"Ouch!");
   break;

   case 6:
       sprintf(msg,"Aumm!");
   break;

   case 7:
       sprintf(msg,"Oorgh!");
   break;

   default:
       sprintf(msg,"Ouch!");
   break;
   };

agregar_mensaje(x,y,random()%15+15,0, -(random()%10+3),font_game, msg, col);


}

// --------------------------------------------------------
// Macro para agregar onomatopeyas de dolor del Nacho!
// --------------------------------------------------------
void agregar_mensaje_dolor_nacho(int x, int y)
{
char msg[25];
int col;
col = makecol(255,255,255);

switch (random()%6)
   {
   case 0:
        col = makecol(255,255,0);
   break;
   case 1:
        col = makecol(0,255,255);
   break;
   case 2:
        col = makecol(255,0,255);
   break;
   case 3:
        col = makecol(255,64,64);
   break;
   default:
    col = makecol(255,255,255);
   break;
   };

switch (random()%10)
   {
   case 0:
       sprintf(msg,"Puta comadre!");
   break;
   case 1:
       sprintf(msg,"Sopanca!");
   break;

   case 2:
       sprintf(msg,"Sopacaca!");
   break;

   case 3:
       sprintf(msg,"Las catalinas!");
   break;

   case 4:
       sprintf(msg,"Chem, boludito!");
   break;

   case 5:
       sprintf(msg,"Evan!");
   break;

   case 6:
       sprintf(msg,"Adam!");
   break;

   case 7:
       sprintf(msg,"Que locura!");
   break;

   default:
       sprintf(msg,"Ouch!");
   break;
   };

agregar_mensaje(x,y,random()%15+15,0, -(random()%10+3),font_game, msg, col);
}


// --------------------------------------------------------
// Macro para agregar el mensaje de suma de puntaje
// NOTA: ademas, SUMA el puntaje a punt
// --------------------------------------------------------
void sumar_puntaje_mensaje(int x, int y, int sumar, unsigned long *punt)
{
char msg[25];
int col;
col = makecol(255,255,255);

if (sumar == 0) return; // evitar al dope...

// si hay un puntero para sumar...
if (punt != NULL ) *punt += sumar;

switch (random()%6)
   {
   case 0:
        col = makecol(255,255,0);
   break;
   case 1:
        col = makecol(0,255,255);
   break;
   case 2:
        col = makecol(255,0,255);
   break;
   case 3:
        col = makecol(255,64,64);
   break;
   default:
    col = makecol(255,255,255);
   break;
   };

if (sumar > 0)
    sprintf(msg,"+%i", sumar);
else
    sprintf(msg,"-%i", abs(sumar));

agregar_mensaje(x,y,random()%15+15,0, -(random()%10+5),font_game, msg, col);
}

#endif
