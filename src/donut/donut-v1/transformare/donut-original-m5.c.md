
```c
#include <stdio.h>
#include <string.h>
#include <math.h>

int k;
int main() {
```

In aceasta etapa identificam doua variabile extrem de importante in cod - dimensiunile ecranului. Ecranul pe care se deseneaza torul in miscare este o matrice bidimensionala de caractere care contine un numar oarecare de linii si un numar oarecare de coloane. Acestea sunt prezente in cod. Cel mai probabil valoarea 80 este numarul de coloane si 22 este numarul de linii. Astfel, inlocuim locurile unde apare 80 cu variabila `srcw` (screen width) iar locurile unde apare 22 cu `scrh` (screen height). 


```c
  int scrw = 80;
  int scrh = 20;
```

De asemenea, observam ca dimensionarea celor doi vectori (z si b) este facuta cu valoarea 1760 care este produsul dintre 80 si 22. Deducem ca 1760 reprezinta dimensiunea unor vectori care vor stoca informatii despre ecran. declaram o variabila separata care sa tina produsul dintre latimea si inaltimea ecranului si o utilizam ca element de dimensionare a vectorilor. 

```c
  int vector = scrw * scrh;
  float z[vector];
  char b[vector];

```

```c
  float A = 0, B = 0, i, j;

  printf("\x1b[2J");
  for (;;) {


```
utilizam variabila "vector" si pentru a completa instructiunile memset

```c
    memset(b, 32, vector);
    memset(z, 0, vector * 4);
```


```c
    for (j = 0; 6.28 > j; j += 0.07) {
      for (i = 0; 6.28 > i; i += 0.02) {
        float c = sin(i);
        float d = cos(j);
        float e = sin(A);
        float f = sin(j);
        float g = cos(A);
        float h = d + 2;
        float D = 1 / (c * h * e + f * g + 5);
        float l = cos(i);
        float m = cos(B); 
        float n = sin(B);
        float t = c * h * g - f * e;

```

Calculele din urmatoarele doua instructiuni contin numerele 40 si 11 - putem trage concluzia ca exista o simetrie a calculelor care se fac si ca acestea au nevoie de jumatate din dimensiunile ecranului. Inlocuim 40 cu `scrw/2` si 20 cu `scrh/2`

```c
        int x = scrw/2 + 30 * D * (l * h * m - t * n);
        int y = scrh/2 + 15 * D * (l * h * n + t * m);
        int o = x + scrw * y;
```

```c
        int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);

```
Conditia if contine elemente care pot fi inlocuite cu `scrw` si `scrh`. 

```c
        if (scrh > y && y > 0 && x > 0 && scrw > x && D > z[o]) {
          z[o] = D;
          b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
        }
      } 
    }
    printf("\x1b[H");
    for (k = 0; k <= vector; k++) { 
 ```

instructiunea putchar contine de asemenea latimea ecranului si poate fin inlocuita cu `scrw`. 

 ```c
      putchar(k % scrw ? b[k] : 10);
 
    }
    A += 0.04;
    B += 0.02;
  }
}