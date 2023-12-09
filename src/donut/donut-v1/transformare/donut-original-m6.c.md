
In aceasta etapa identificam variabilele care sunt importante pentru proiectia pe ecran. 

```c
#include <stdio.h>
#include <string.h>
#include <math.h>
```

```c
int k;
int main() {
  int scrw = 80;
  int scrh = 20;
  int vector = scrw * scrh;

  ```
  
  ```c
  int depth = 5; 
  int screendepth = 2;
  int scalex = 20;
  int scaley = 15;
  float angle_increment_y = 0.04;
  float angle_increment_x = 0.06;
  char shade[] = ".,-~:;=!*#$@";
  ```
  
  
  ```c
  float angle_y = 0, angle_x = 0, i, j;

  float z[vector];
  char b[vector];

  printf("\x1b[2J");
  for (;;) {
    memset(b, 32, vector);
    memset(z, 0, vector * 4);
    for (j = 0; 6.28 > j; j += 0.07) {
      for (i = 0; 6.28 > i; i += 0.02) {
        float c = sin(i);
        float d = cos(j);
        float e = sin(angle_y);
        float f = sin(j);
        float g = cos(angle_y);
        float h = d + screendepth;
        float D = 1 / (c * h * e + f * g + depth);
        float l = cos(i);
        float m = cos(angle_x); 
        float n = sin(angle_x);
        float t = c * h * g - f * e;

        int x = scrw/2 + scalex * D * (l * h * m - t * n);
        int y = scrh/2 + scaley * D * (l * h * n + t * m);
        int o = x + scrw * y;
        int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
        if (scrh > y && y > 0 && x > 0 && scrw > x && D > z[o]) {
          z[o] = D;
          b[o] = shade[N > 0 ? N : 0];
        }
      } 
    }
    printf("\x1b[H");
    for (k = 0; k <= vector; k++) { 
      putchar(k % scrw ? b[k] : 10);
    }
    angle_y += angle_increment_y;
    angle_x += angle_increment_x;
  }
}