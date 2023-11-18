# Sursa

[https://github.com/emacdona/tictactoe](https://github.com/emacdona/tictactoe)

# Descriere

Programul implementeaza un joc de tip X si 0 in consola, fara jucator automat. Implementarea consta dintr-o biblioteca care contine functii pentru manipularea tablei de joc, numita board (board.c - board.h) si dintr-un fisier principal, main.c.

# Comentarii despre cod

# main.c

main.c este fisierul principal care contine doar functia main. Functia declara o matrice de stare numita board: `char board[3][3];` care va contine starea jocului in orice moment. Aceasta matrice va fi transmisa catre toate functiile care sunt implicate in derularea jocului. Functia main apeleaza apoi ` initBoard(board);` care va pune cate un spatiu in fiecare dintre cele 9 celule (3 linii si 3 coloane) ale matricei de stare. 

Apoi, functia main porneste o bucla while infinita cu ajutorul instructiunii ` while(1){` (1 este mereu adevarat) care se va executa pe toata durata jocului. Variabila turn, initializata cu 0 mentine jucatorul al carui rand este sa mute (0 sau 1) 

Comanda `system("clear");` goleste consola, urmata de apelul functiei `drawBoard(board);`. Aceasta functie va parcurge matricea de stare board si va afisa conmtinutul acesteia impreuna cu separatoarele | si --- cu ajutorul instructiunii

```
printf(" %c %c", charAt(board, col, row), (col == 2) ? '\n' : '|');
```

Comanda de golire a consolei `system("clear");` se gaseste in interiorul buclei infinite ceea ce determina redesenarea ecranului dupa fiecare mutare. 

Functia `charAt(board, col, row)` este tot parte din biblioteca board - aceasta returneaza caracterul aflat la pozitia col, row. Constructia ` (col == 2) ? '\n' : '|'` este un conditional ternar care va afisa fie newline (\n), daca coloana este 2 (adica cea de-a treia, finalul randului) fie separatorul de coloana |. 

Functia main apeleaza o alta functie din board.c: `state(board)`. Aceasta functie returneaza "starea" jocului, in realitate starea jocului dupa terminarea acestuia (1 - castigator, -1 - remiza, 0 - jocul nu s-a terminat). In cazul in care se returneaza una dintre valorile 1 sau -1 inseamna ca jocul s-a terminat iar functia va returna 0 terminand programul. In caz contrar, se executa urmatoarea succesiune de instructiuni: 

```
      printf("\n(turn #%i) To which square would you (player %c) like to move? ", turn, player);
      fgets(input, 3, stdin);
      moveTo = atoi(input);

      if (mv(board, moveTo, player))
         turn++;

      printf("\n");

```

care tiparesc mesajul de solicitare a urmatoarei mutari (printf), preia valoarea (fgets), converteste valoarea la numar intreg (atoi) apoi executa functia `mv(board, moveTo, player)` (care se gaseste tot in board) urmarind cu ajutorul instructiunii if daca aceasta confirma validitatea mutarii. Daca mutarea este valida, se va incrementa variabila turn.   

Mutarea asteptata de la utilizator este un numar de pozitie (un numar intreg aflat intre 1 si 9) care identifica pozitia in matrice prin parcurgerea acesteia de la stanga la dreapta si de sus in jos: 

1 | 2 | 3 
----------
4 | 5 | 6 
----------
7 | 8 | 9


# Board

Fisierul board.h contine definitiile functiilor implementate in biblioteca board. 

```
#ifndef __board_h__
#define __board_h__

void drawBoard(char board[3][3]);
void initBoard(char board[3][3]);
char charAt(char board[3][3], int x, int y);
int movexy(char board[3][3], int x, int y, char c);
int mv(char board[3][3], int x, char c);
int isMoveLegal(char board[3][3], int x, int y);
int state(char board[3][3]);

#endif

```
## drawBoard (char board[3][3])

deseneaza tabela de joc care consta intr-o succesiune de caractere | ca separator de coloane si --- ca separator de linii. Desenul se face prin parcurgerea matricii de stare board cu ajutorul a doua cicluri for. 

## initBoard (char board[3][3])

initBoard parcurge matricea de joc cu ajutorul a doua cicluri for setand toate elementele acesteia ca fiind un spatiu. 

## charAt (char board[3][3], int x, int y)

functia charAt returneaza caracterul aflat in matricea de joc pe pozitia x, y. Functia verifica coordonatele transmise pentru a vedea daca sunt valide (se afla intre 0 si 2) cu ajutorul instructiunii: `if( x > 2 || x < 0 || y > 2 || y < 0)`. 

## movexy(char board[3][3], int x, int y, char c)

movexy este o functie care pozitioneaza in matricea de joc mutarea curenta. Inainte de a seta elementul de la pozitia x, y aceasta foloseste functia isMoveLogal pentru a verifica daca mutarea este legala. In cazul in care aceasta este legala, functia va returna 1 dupa ce pozitioneaza caracterul c in pozitia x,y din matrice cu ajutorul instructiunii `board[x][y] = c;`. In cazul in care mutarea nu este legala, functia returneaza 0. 

## mv(char board[3][3], int x, char c)

mv este o fucntie utilitara care preia mutarea de la utilizator, sub forma unui numar intre 1 si 9, calculeaza pe baza acestui numar cele doua coordonate pe care le asteapta functia movexy, cu ajutorul formulelor (x - 1) % 3 (care da indexul coloanei), (x - 1) / 3 (care da indexul randului)

## isMoveLegal(char board[3][3], int x, int y)

Functia contine o singura linie: `return charAt(board, x, y) == ' ';` care apeleaza functia charAt (care returneaza caracterul aflat la pozitia x si y), Instructiunea returneaza rezultatul compararii intre ceea ce returneaza charAt si spatiu. Altfel spus, mutarea este legala daca la acea pozitie in matrice se gaseste un spatiu (adica pozitia este libera). 

## state(char board[3][3])

Functia inspecteaza tabela de joc (board) si determina (cu ajutorun unei succesiuni de cicluri for si comparatii) daca vreuna dintre coloane, linie sau diagonala contine acelasi caracter (x sau 0). Daca acestu lucru se intampla, functia va returna 1 (exista un castigator). Daca nu avem un castigator, exista doua variante: fie tabela mai contine spatii goale (ceea ce se verifica cu ajutorul unei noi parcurgeri a matricii) - caz in care se returneaza 0 (jocul continua) fie se returneaza -1 (jocul este remiza). 

# Constructia

Constructia este facuta cu ajutorul unui fisier Makefile care are urmatorul continut: 

```
CC = gcc
CFLAGS = -Wall -g
SRC = main.c board.c
OBJ = $(SRC:.c=.o)
TARGET = ttt

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)

```

Makefile are o sectiune introductiva in care se definesc o serie de variabile in acelasi stil in care se definesc in limbajele de shell. Sunt definite compilatorul (CC) optiunile care se vor folosi in timpul compilarii (CFLAGS), lista fisierelor care vor fi compilate (SRC) lista obiectelor in care acestea vor fi compilate (OBJ) si numele final al programului care va rezulta in urma compilarii (TARGET). Aceste variabile vor fi utilizate in sectiunile urmatoare ale makefile-ului. Definirea acestora in headerul Makefile-ului este doar o chestiune de preferinta - fisierul ar fi functionat si in cazul in care continutul acestora ar fi fost pozitionat direct in sectiunile active ale Makefile in locul variabilelor. 

Linia `OBJ = $(SRC:.c=.o)` foloseste o substitutie (permisa de specificatiile sistemului make) care inlocuieste .c cu .o in variabila SRC. Astfel, obj devine `OBJ = main.o board.o`. 

Makefile are trei tinte: 

```
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
```
care va fi inlocuita cu

```
ttt: main.o board.o
	gcc -Wall -g -o ttt main.o board.o
```

Aceasta tinta este prima in lista, deci este tinta care va fi compilata in cazul in care make este apelat fara argumente. Dar inainte de executia acestei tinte, avand in vedere ca aceasta contine main.o si board.o care inca nu exista, make va cauta in regulile urmatoare tinte care le creaza. Aceasta este tina urmatoare: 

```
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
```
care va fi inlocuita cu

```
main.o board.o: %.o: %.c
	gcc -Wall -g -c -o $@ $<
```

Tinta clean va fi executata doar in cazul in care este apelata direct (make clean) si va sterge toate fisierele compilate pentru a putea relua compilarea. 

# Makefile original

Makefile aflat in proiectul original este putin mai explicit: 

```
CFLAGS = -g -O0

ttt: main.o board.o
	$(CC) $(CFLAGS) -o $@ main.o board.o 

main.o: main.c board.h
	$(CC) $(CFLAGS) -c -o $@ main.c

board.o: board.c board.h
	$(CC) $(CFLAGS) -c -o $@ board.c 

clean:
	rm -rf ttt *.o
```
