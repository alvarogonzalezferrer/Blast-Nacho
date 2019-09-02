
'crea campo de estrellas rudimentario en vga
'qbasic
'por krono 2000
'quedan bastante buenos.
'cosas a hacer
'mejorar para color de 16 bits y vb
'ajustar los nombres de las variables, que son una mierda
'optimizar
'mejorarlo mas! fractals y planetas!! ya!
SCREEN 12

DO
CLS

'grilla de juego [no visible, obviamente]

'FOR a = 0 TO 639 STEP 10
'        LINE (a, 0)-(a, 480), 8
'NEXT
'FOR a = 0 TO 479 STEP 10
'        LINE (0, a)-(640, a), 8
'NEXT

'FOR b = 0 TO 479 STEP 10
'FOR a = 0 TO 639 STEP 10
'PSET (a, b), 8
'NEXT
'NEXT

'-------------------------------------------------------------------------



'---------------------
'estrellas 'normales'

RANDOMIZE TIMER

c = INT(RND * 300) + 300
setdecolor = INT(RND * 3) + 1
FOR a = 1 TO c
z = INT(RND * 3) + 1
IF setdecolor = 1 THEN
        IF z = 1 THEN z = 7
        IF z = 2 THEN z = 2
        IF z = 3 THEN z = 3
END IF
IF setdecolor = 2 THEN
        IF z = 1 THEN z = 11
        IF z = 2 THEN z = 9
        IF z = 3 THEN z = 1
END IF
IF setdecolor >= 3 THEN
        IF z = 1 THEN z = 7
        IF z = 2 THEN z = 8
        IF z = 3 THEN z = 15
END IF
x = INT(RND * 640) + 1
y = INT(RND * 480) + 1

IF INT(RND * 20) + 1 < 19 THEN
        PSET (x, y), z
ELSE
       PSET (x, y), z
        CIRCLE (x, y), 1, z
END IF
NEXT

'-------------------------------------------------------------------------
'especie de efecto de 'nebulosa' que sale del borde
'lo dibuja con un 'pincel' circular tipo sprite
'realizar entre 1 y x por escenario


FOR jj = 1 TO INT(RND * 3) + 1

'kit de color a usar
setdecolor = INT(RND * 5) + 1

'iniciar posicion y movimiento
SELECT CASE INT(RND * 4) + 1
CASE 1
        x = 0
        y = 0
        xd = INT(RND * 10) + 1
        yd = INT(RND * 10) + 1
CASE 2
        x = 640
        y = 480
        xd = -INT(RND * 10) - 1
        yd = -INT(RND * 10) - 1
CASE 3
        x = 0
        y = 480
        xd = INT(RND * 10) + 5
        yd = -INT(RND * 10) - 5

CASE 4
        x = 640
        y = 0
        xd = -INT(RND * 10) - 5

        yd = INT(RND * 10) + 5
END SELECT

'radio inicial del 'pincel'

r = INT(RND * 20) + 5
'movimiento del radio
IF INT(RND * 2) + 1 = 1 THEN m = 1 ELSE m = -1

DO

x = x + xd 'mover pincel
y = y + yd

'dibujar cada fase
k = INT(RND * 10) + 1'iteraciones de esta fase [densidad de puntos]
FOR ww = 1 TO k
'CIRCLE (x, y), r, 1
'elegir pos de los puntos
'dentro del circulo

xp = INT(RND * r * 2) + (x - r)
yp = INT(RND * r * 2) + (y - r)

z = INT(RND * 3) + 1
IF setdecolor = 1 THEN
        IF z = 1 THEN z = 10
        IF z = 2 THEN z = 2
        IF z = 3 THEN z = 3
END IF
IF setdecolor = 2 THEN
        IF z = 1 THEN z = 11
        IF z = 2 THEN z = 9
        IF z = 3 THEN z = 1
END IF
IF setdecolor = 3 THEN
        IF z = 1 THEN z = 7
        IF z = 2 THEN z = 8
        IF z = 3 THEN z = 15
END IF
IF setdecolor = 4 THEN
        IF z = 1 THEN z = 14
        IF z = 2 THEN z = 13
        IF z = 3 THEN z = 12
END IF
IF setdecolor = 5 THEN
        IF z = 1 THEN z = 4
        IF z = 2 THEN z = 5
        IF z = 3 THEN z = 6
END IF

PSET (xp, yp), z
IF INT(RND * 20) + 1 > 18 THEN
       CIRCLE (xp, yp), 1, z
END IF


NEXT

'cambiar tama¤o del radio
r = r + m
IF r < 5 THEN r = 5: m = 1
IF r > 50 THEN r = 50: m = -1


LOOP UNTIL x < 0 OR x > 640 OR y < 0 OR y > 480 'hasta que se salga de pantalla

NEXT jj 'hacer proxima nebulosa
'-------------------------------------------------------------------------
'dibujar los 'planetas'
'anda medio mal, tratar que no se superpongan!!
c = INT(RND * 10) + 5'cantidad

FOR jj = 1 TO c
x = INT(RND * 63) + 1
x = x * 10'ajustar a grilla de 64

y = INT(RND * 47) + 1
y = y * 10'ajustar a grilla de 48

r = INT(RND * 7) + 3

'limpiar para pintar
CIRCLE (x, y), r, 1
PAINT (x, y), 1, 1
CIRCLE (x, y), r, 2
PAINT (x, y), 2, 2
CIRCLE (x, y), r, 3
PAINT (x, y), 3, 3
setdecolor = INT(RND * 5) + 1
z = INT(RND * 3) + 1
IF setdecolor = 1 THEN
        IF z = 1 THEN z = 10
        IF z = 2 THEN z = 2
        IF z = 3 THEN z = 3
END IF
IF setdecolor = 2 THEN
        IF z = 1 THEN z = 11
        IF z = 2 THEN z = 9
        IF z = 3 THEN z = 1
END IF
IF setdecolor = 3 THEN
        IF z = 1 THEN z = 7
        IF z = 2 THEN z = 8
        IF z = 3 THEN z = 15
END IF
IF setdecolor = 4 THEN
        IF z = 1 THEN z = 14
        IF z = 2 THEN z = 13
        IF z = 3 THEN z = 12
END IF
IF setdecolor = 5 THEN
        IF z = 1 THEN z = 4
        IF z = 2 THEN z = 5
        IF z = 3 THEN z = 6
END IF



'hacer
CIRCLE (x, y), r, z
PAINT (x, y), z, z

'renderizar [mas o menos]
PSET (x, y), z 'setear el punto inicial de partida

FOR kk = 1 TO INT(RND * 50) + 20

z = INT(RND * 3) + 1
IF setdecolor = 1 THEN
        IF z = 1 THEN z = 10
        IF z = 2 THEN z = 2
        IF z = 3 THEN z = 3
END IF
IF setdecolor = 2 THEN
        IF z = 1 THEN z = 11
        IF z = 2 THEN z = 9
        IF z = 3 THEN z = 1
END IF
IF setdecolor = 3 THEN
        IF z = 1 THEN z = 7
        IF z = 2 THEN z = 8
        IF z = 3 THEN z = 15
END IF
IF setdecolor = 4 THEN
        IF z = 1 THEN z = 14
        IF z = 2 THEN z = 13
        IF z = 3 THEN z = 12
END IF
IF setdecolor = 5 THEN
        IF z = 1 THEN z = 4
        IF z = 2 THEN z = 5
        IF z = 3 THEN z = 6
END IF

'elegir pos de los puntos
'dentro del circulo

xp = INT(RND * r * 2) + (x - r)
yp = INT(RND * r * 2) + (y - r)

'calcular largo desde el radio
h = (SQR(ABS(xp - x) ^ 2 + ABS(yp - y) ^ 2))
IF h < r THEN
        'esta dentro del circulo, dibujar
        LINE -(xp, yp), z
END IF
NEXT kk


'otro modo de renderizar
'elegir entre el anterior o este
'este es mejor para colores de 16 bits [degrade]

FOR kk = r TO 1 STEP -1
z = INT(RND * 3) + 1
IF setdecolor = 1 THEN
        IF z = 1 THEN z = 10
        IF z = 2 THEN z = 2
        IF z = 3 THEN z = 3
END IF
IF setdecolor = 2 THEN
        IF z = 1 THEN z = 11
        IF z = 2 THEN z = 9
        IF z = 3 THEN z = 1
END IF
IF setdecolor = 3 THEN
        IF z = 1 THEN z = 7
        IF z = 2 THEN z = 8
        IF z = 3 THEN z = 15
END IF
IF setdecolor = 4 THEN
        IF z = 1 THEN z = 14
        IF z = 2 THEN z = 13
        IF z = 3 THEN z = 12
END IF
IF setdecolor = 5 THEN
        IF z = 1 THEN z = 4
        IF z = 2 THEN z = 5
        IF z = 3 THEN z = 6
END IF

'CIRCLE (x, y), kk, z

NEXT kk





NEXT jj


'-------------------------------------------------------------------------

SLEEP 0 'esperar por tecla
LOOP WHILE INKEY$ <> CHR$(27) 'hacer nuevo escenario

SYSTEM

