'intento de perspectiva
SCREEN 12

ratio = .5                'ratio inicial
stepr = (1 - ratio) / 640  'salto de ratio
y = 0

DO
x = 320
x1 = x - (x * ratio / 2)
x2 = x + (x * ratio / 2)
FOR x = x1 TO x2
    PSET (x, y), 15
NEXT
y = y + 1
ratio = ratio + stepr
IF y > 439 THEN EXIT DO


LOOP

