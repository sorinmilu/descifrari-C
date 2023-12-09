
# O prima analiza a codului

#include <stdio.h>
#include <string.h>
#include <math.h>

int k;

Aceasta linie nu este necesara, se poate elimina. 
```
double sin(), cos();
```

Inceputul functiei main (singura functie existenta in program). Se declara cateva variabile de tip float si doi vectori, z si b. 

```c
int main() {
  float A = 0, B = 0, i, j;
  float z[1760];
  char b[1760];
```

Urmatoarea instructiune are ca efect golirea ecranului intr-o consola. Declaratia este compusa din `\x1b` care reprezinta caracterul escape (valoare hexazecimala 0x1B). Trimiterea acestui caracter catre consola o determina sa nu afiseze nimic ci sa astepte o instructiune de tip CSI (Control Sequence Introducer)

`[H` este codul de tip CSI care trimite cursorul in pozitia cea mai din stanga-sus. 


```c  
  printf("\x1b[2J");

```
Bucla principala 
```c

  for (;;) {
```

reprezinta o bucla infinita. Se poate inlocui cu ceva de genul: `while (1 == 1)`

`while (1 == 1)` poate observa ca while este mai lenta decat for datorita evaluarii expresiei de egalitate


memset initializeaza cei doi vectori astfel incat sa contina toate elementele egale cu zero. 
memset opereaza cu octeti, nu stie ce fel de date se gasesc in memorie, astfel, pentru vectorul z este necesara initializarea unui numar de octeti de 4 ori mai mare (presupunand ca un float este stocat in 4 octeti).


```c
    memset(b, 32, 1760);
    memset(z, 0, 7040);
```

Urmeaza doua cicluri for care cicleaza dupa variabilele i si j.  

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

        int x = 40 + 30 * D * (l * h * m - t * n);
        int y = 12 + 15 * D * (l * h * n + t * m);
        int o = x + 80 * y;
        int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);

```

Urmatoarele instructiuni completeaza datele din vectorii z si b in conditiile in care valorile calculate mai sus se inscriu in lista de conditii. 

Setarea valorii care este plasata in vectorul b este tipica pentru ASCII ART - reprezinta selectia unui caracter de tip shading care simuleaza umbrele prin utilizarea caracterelor mai mult sau mai putin dense pe ecran. 

Selectia caracterului de shading se foloseste de posibilitatea de a indexa un vector direct initializat impreuna cu posibilitatea de a utiliza un operator ternar ca index. 


```c
        if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
          z[o] = D;
          b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
        }

```

Urmatoarele paranteze inchid cele doua cicluri de calcul. 

```c
      } 
    }
```

Urmatoarea instructiune are ca efect golirea ecranului intr-o consola. Declaratia este compusa din `\x1b` care reprezinta caracterul escape (valoare hexazecimala 0x1B). Trimiterea acestui caracter catre consola o determina sa nu afiseze nimic ci sa astepte o instructiune de tip CSI (Control Sequence Introducer)

`[H` este codul de tip CSI care trimite cursorul in pozitia cea mai din stanga-sus. 

```c
    printf("\x1b[H");
```

urmatorul ciclu for este cel care afiseaza pe ecran ce se gaseste in matricea b

```c
    for (k = 0; 1761 > k; k++) { 
      putchar(k % 80 ? b[k] : 10);
    }
```

Urmatoarele intructiuni incrementeaza valorile variabilelor A si B. Noile valori vor fi utilizate in urmatoarea executie a ciclului `for` infinit de mai sus. 

```c
    A += 0.04;
    B += 0.02;
  }
}
```