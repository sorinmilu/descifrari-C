#include <stdio.h>
#include <string.h>
#include <math.h>

int k;
double sin(), cos();

```c
int main() {
  float A = 0, B = 0, i, j;
  float z[1760];
  char b[1760];
  printf("\x1b[2J");

```
Bucla principala 
```c

  for (;;) {
```

reprezinta o bucla infinita. Se poate inlocui cu ceva de genul: `while (1 == 1)`

`while (1 == 1)` poate observa ca while este mai lenta decat for datorita evaluarii expresiei de egalitate


```c
    memset(b, 32, 1760);
    memset(z, 0, 7040);
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

        int x = 40 + 30 * D * (l * h * m - t * n);
        int y = 12 + 15 * D * (l * h * n + t * m);
        int o = x + 80 * y;
        int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
        if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
          z[o] = D;
 ```

Selectia caracterului de shading


 ```c
       b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
 ```

este echivalenta cu: 

      ```c
      char shade[] = ".,-~:;=!*#$@";

      int shchar = 0;

      if (N > 0) {
        shchar = N;
      }

      b[o] = shade[shchar];

      ```





        }
      } 
    }
    printf("\x1b[H");
    for (k = 0; 1761 > k; k++) { 
      putchar(k % 80 ? b[k] : 10);
    }
    A += 0.04;
    B += 0.02;
  }
}