#include <stdio.h>
#include <string.h>
#include <math.h>

#define PI 3.141
#define TWPI 2 * PI

int k;
int main() {
  int scrw = 80;
  int scrh = 20;
  int vector = scrw * scrh;
  int depth = 5;  //controleaza distanta intre "camera" si obiect
  int screendepth = 6;
  int scalex = 20;
  int scaley = 15;


  float A = 0, B = 0, i, j;

  float z[vector];
  char b[vector];

  printf("\x1b[2J");
  for (;;) {
    memset(b, 32, vector);
    memset(z, 0, vector * 4);
    for (j = 0; TWPI > j; j += 0.07) {
      for (i = 0; TWPI > i; i += 0.02) {
        float c = sin(i);
        float d = cos(j);
        float e = sin(A);
        float f = sin(j);
        float g = cos(A);
        float h = d + screendepth;
        float D = 1 / (c * h * e + f * g + depth);
        float l = cos(i);
        float m = cos(B); 
        float n = sin(B);
        float t = c * h * g - f * e;

        int x = scrw/2 + scalex * D * (l * h * m - t * n);
        int y = scrh/2 + scaley * D * (l * h * n + t * m);
        int o = x + scrw * y;
        int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
        if (scrh > y && y > 0 && x > 0 && scrw > x && D > z[o]) {
          z[o] = D;
          b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
        }
      } 
    }
    printf("\x1b[H");
    for (k = 0; k <= vector; k++) { 
      putchar(k % scrw ? b[k] : 10);
    }
    A += 0.04;
    B += 0.02;
  }
}