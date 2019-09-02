// Numeros aleatorios
// azar.c
// (c) 2002, Kronoman

#ifndef AZAR_C
#define AZAR_C

//----------------------------------------------------------- 
//Funcion al_azar
//Pasarle dos numeros, y devuelve uno al azar entre ellos
// pueden ser negativos o positivos
// SIEMPRE pasar el menor primero y el mayor despues
// El generador de numeros aleatorios debe estar previamente iniciado
//-----------------------------------------------------------
int al_azar(int num1, int num2)
{
int i1;
// si estan al reves, dar vuelta 
if (num1 > num2)
{
    i1 = num2;
    num2 = num1;
    num1 = i1;
}

    i1 = num2 - num1 + 1;
    i1 = (random() % i1) + num1;
    return i1;
}
//----------------------------------------------------------- 


#endif
