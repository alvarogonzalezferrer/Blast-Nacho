//--------------------------------------------------------
// partic.c
// Efectos de particulas
// (c) 2002, Kronoman
//--------------------------------------------------------

#ifndef PARTIC_C
#define PARTIC_C

//--------------------------------------------------------
// GLOBALES
//--------------------------------------------------------

// SISTEMA DE PARTICULAS
int cantidad_particulas = 0; // cantidad de particulas

// NOTAR QUE EL TIPO 'fixed' pertenece a Allegro
// es para usar punto flotante falso, o sea un 'float' entero ;D
// usar itofix, etc para convertir
static struct {
 fixed x;   // posicion x particula 0-1000
 fixed y;   // posicion y particula 0-1000
 fixed dx;  // direccion x (punto flotante)
 fixed dy;  // direccion y (punto flotante)
 int vida;  // vida que le queda a la particula, al llegar a 0 es liberada
 int color; // color 0-255
 int tipo;  // tipo de particula
} particula[MAX_PARTICULAS]; // desde 0 a MAX_PARTICULAS - 1


//--------------------------------------------------------
// reset_particulas()
// esto 'resetea' el sistema de particulas
// llamar cada vez que termina el juego
// de lo contrario habra particulas al empezar a jugar de nuevo
//--------------------------------------------------------
void reset_particulas()
{
int i1; // para el for

cantidad_particulas = 0; // cantidad de particulas
for (i1=1; i1 < MAX_PARTICULAS; i1++)
{
 particula[i1].x = 0;
 particula[i1].y = 0;
 particula[i1].dx = 0;
 particula[i1].dx = 0;
 particula[i1].vida = 0;
 particula[i1].color = 0;
 particula[i1].tipo = 0;
}

} // fin reset_particulas()
//--------------------------------------------------------

//--------------------------------------------------------
// Dibuja las particulas en bmp
//--------------------------------------------------------
void dibujar_particulas(BITMAP *bmp)
{
int i1; // para el for

// notar que no comprueba si estan dentro de pantalla
// de eso se encargan las rutinas de graficos
// seria al pedo - gastar 2 comprobaciones
for (i1=1; i1 < cantidad_particulas; i1++)
{

if (particula[i1].vida < 1) particula[i1].tipo = -1; // particula muerta

if (particula[i1].tipo == 0)
            putpixel (bmp,
                     fixtoi(particula[i1].x),
                     fixtoi(particula[i1].y),
                     particula[i1].color);

if (particula[i1].tipo == 1)
            circlefill (bmp,
                      fixtoi(particula[i1].x),
                      fixtoi(particula[i1].y), 1,
                      particula[i1].color);

if (particula[i1].tipo == 2)
                line (bmp,
                      fixtoi(particula[i1].x),
                      fixtoi(particula[i1].y),
                      fixtoi(fadd(particula[i1].x, particula[i1].dx)),
                      fixtoi(fadd(particula[i1].y, particula[i1].dy)),
                      particula[i1].color);

if (particula[i1].tipo == 3)
                rectfill (bmp,
                          fixtoi(particula[i1].x)-1,
                          fixtoi(particula[i1].y)-1,
                          fixtoi(particula[i1].x)+1,
                          fixtoi(particula[i1].y)+1,
                          particula[i1].color);

if (particula[i1].tipo == 4) // multiple (LENTO!)
            {
            putpixel (bmp,
                     fixtoi(particula[i1].x) + random()%20 - 10,
                     fixtoi(particula[i1].y) + random()%20 - 10,
                     particula[i1].color);
            putpixel (bmp,
                     fixtoi(particula[i1].x) + random()%20 - 10,
                     fixtoi(particula[i1].y) + random()%20 - 10,
                     particula[i1].color);
            putpixel (bmp,
                     fixtoi(particula[i1].x) + random()%20 - 10,
                     fixtoi(particula[i1].y) + random()%20 - 10,
                     particula[i1].color);
            putpixel (bmp,
                     fixtoi(particula[i1].x) + random()%20 - 10,
                     fixtoi(particula[i1].y) + random()%20 - 10,
                     particula[i1].color);
            putpixel (bmp,
                     fixtoi(particula[i1].x) + random()%20 - 10,
                     fixtoi(particula[i1].y) + random()%20 - 10,
                     particula[i1].color);
            putpixel (bmp,
                     fixtoi(particula[i1].x) + random()%20 - 10,
                     fixtoi(particula[i1].y) + random()%20 - 10,
                     particula[i1].color);
            }

// nota: fadd(x,y) es igual a x+y, pero con fixed... :^)

} // fin for
// LISTO!

} // fin dibujar_particulas
//--------------------------------------------------------



//--------------------------------------------------------
// void mover_particulas()
// Rutina que MUEVE las particulas 
// y libera la memoria de las particulas que ya no se usan
// para permitir el uso de nuevas
// llamar cuando actualiza la logica del juego
//-------------------------------------------------------- 
void mover_particulas()
{
int i1, i2; // para el for, etc

i2 = cantidad_particulas;

for (i1=1; i1<cantidad_particulas; i1++)
{
// uso fadd porque son numeros fixed
// igual los podes sumar con +, pero no comprueba el overflow
//particula[i1].x +=  particula[i1].dx;
//particula[i1].y +=  particula[i1].dy;

particula[i1].x = fadd(particula[i1].x, particula[i1].dx);
particula[i1].y = fadd(particula[i1].y, particula[i1].dy);

// DEBUG: agregar gravedad y viento aqui...

// Gravedad
particula[i1].dy = fadd(particula[i1].dy, ftofix(gravedad));

// Viento
particula[i1].dx = fadd(particula[i1].dx, ftofix(viento));


particula[i1].vida--;

if (particula[i1].vida < 1)
    {
    // particula muerta, cambiar con la ultima viva el lugar
    // y eliminar
     particula[i1] = particula[i2];
     i2--;
     if (i2<0) i2=0;
    }
} // fin for
cantidad_particulas = i2;
// LISTO!
} // fin mover_particulas
//--------------------------------------------------------

//--------------------------------------------------------
//void agregar_particulas(int x, int y, int vida, cantidad
//                           int tipo, int colorr1,
//                           int colorr2)
//
// Esta rutina agrega particulas
// en la  posicion 'x,y' de duracion 'vida', de 'cantidad'
// de 'tipo', y en un rango de color de 'colorr1' a 'colorr2'
// 'tipo' puede ser:
// 0 = puntos
// 1 = circulos
// 2 = lineas
// 3 = cuadrados
// 4 = multiple (se dibuja varias veces al azar la misma) (OJO! 6x lentas pero super cool!)
// 5 = al azar
// 6 = combinar 1 y 0...
// 7 = combinar 0,1,2
//
// ATENTO: esto debe ser:
// color1 < colorr2 
//
//--------------------------------------------------------

void agregar_particulas(int x, int y, int vida,
                        int cantidad, int tipo, int colorr1,
                        int colorr2)
{
int i1, i2; // para el for, etc

if (cantidad_particulas>MAX_PARTICULAS-1) return;

// crear hasta el maximo posible de particulas
if (cantidad_particulas + cantidad > MAX_PARTICULAS-1)
                          cantidad = MAX_PARTICULAS - 1 - cantidad_particulas;

if (tipo == 5) tipo = random () % 5;

for (i1=cantidad_particulas; i1<cantidad_particulas + cantidad; i1++)
{
particula[i1].x = itofix(x);
particula[i1].y = itofix(y);

// elegir color
i2 = al_azar(colorr1, colorr2);
particula[i1].color = i2;

// velocidad
particula[i1].dx = ftofix((float)(al_azar(-500, 500)) / 100);
particula[i1].dy = ftofix((float)(al_azar(-500, 750)) / 100);

particula[i1].vida = vida;

particula[i1].tipo = tipo;

// combinar 1 y 0...
if (tipo==6) particula[i1].tipo = random () % 2;

// combinar 0,1,2
if (tipo==7) particula[i1].tipo = random () % 3;


} // fin for

cantidad_particulas = cantidad_particulas + cantidad;
// comprobacion de seguridad
if (cantidad_particulas>MAX_PARTICULAS-1) cantidad_particulas=MAX_PARTICULAS-1;

// LISTO!
} // fin agregar_particulas 
//--------------------------------------------------------
#endif
