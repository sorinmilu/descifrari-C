# Sort Algos in C

[https://github.com/ismdeep/sort-algos-c](https://github.com/ismdeep/sort-algos-c)


Proiectul initial contine trei seturi diferite de implementari ale unui set de algoritmi de sortare. Proiectul contine de asemenea o serie de functii care permit compararea duratei rularii fiecarui algoritm in parte. 

Cele trei implementari utilizeaza acelasi set de algoritmi de sortare prezentati in trei modalitati diferite de implementare ale mecanismului de sortare: 

- sort-algos-int-with-func.c foloseste implementari ale algoritmilor de sortare lipsite de functii aditionale
- sort-algos.c este similar
- sort-algos-int.c nu foloseste functii de comparare

Dincolo de implementarea algoritmilor (care este interesanta) ceea ce este util la acest proiect este studiul structurii distribuirii codului in fisiere. Pentru a exemplifca, am adaugat doua proiecte aditionale in care implementarea sort-algos-int.c este distribuita diferit in fisiere: 


[sortari-onefile-cmake](../sortari-cmake/sortari-onefile-cmake/) este un proiect in care absolut toate functiile utilizate in proiectul initial sunt plasate intr-un singur fisier. 

[sortari-onedir-cmake](../sortari-cmake/sortari-onedir-cmake/) este un proiect in care functiile sunt separate in mai multe fisiere sursa iar definitiile acestora intr-un fisier de tip header (.h). 


```bash

mkdir build
cd build
cmake ../
make

```