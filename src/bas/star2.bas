'Mascara de estrellas para dibujar en photoshop
SCREEN 12
FOR i = 1 TO 1000
x = INT(RND * 640) + 1
y = INT(RND * 480) + 1

PSET (x, y), 15

    IF RND < .1 THEN
        LINE (x - 2, y)-(x + 2, y), 15
        LINE (x, y - 2)-(x, y + 2), 15
    END IF
NEXT
SLEEP

