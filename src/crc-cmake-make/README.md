https://github.com/malinengineer/crc/tree/master

===
# CRC

Cyclic Redundancy Check (CRC) este o tehnică de detecție a erorilor folosită în comunicații digitale și stocarea datelor. Este un algoritm de control al erorilor care implică adăugarea unui număr specific de biți la un set de date, iar receptorul utilizează același algoritm pentru a verifica integritatea datelor primite.

Bitii adaugati reprezinta restul impartirii binare a mesajului initial la care se adauga un numar de biti suplimentari la un anumit numar binar special ales. Acest set de biti se adauga la finalul mesajului. 

Restul impartirii unui numar la un alt numar se afla tot timpul in intervalul 0 - divizor. 



# compilare simpla: 

```bash
gcc -Wall main.c crc.c -o main
```

## makefile pentru compilarea simpla:

----------------------------------------
```makefile
CC = gcc
CFLAGS = -Wall -g

SRC = main.c crc.c
OBJ = $(SRC:.c=.o)
TARGET = crcbin

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)
```
---------------------------------------

# compilarea cu biblioteca dinamica: 

crc.c va deveni o biblioteca dinamica numita libcrc.so

1. Compilarea sursei crc.c in fisier obiect

trebuie folosit flagul -fPIC care genereaza cod independent de pozitie, necesar pentru incarcarea
obiectelor la runtime. La finalul comenzii rezulta un fisier crc.o

```bash
gcc -c -fPIC crc.c -o crc.o
```
2. transformarea fisierului obiect in biblioteca dinamica

```bash
gcc -shared -o libcrc.so crc.o
```
la finalul comenzii rezulta un fisier libcrc.so

3. compilarea fisierului principal astfel incat sa incarce biblioteca dinamica la rulare

Flagul -L face compilatorul sa caute biblioteca dinamica in directorul curent iar
flagul libcrc face compilatorul sa "lege" programul compilat de aceasta biblioteca dinamica

```bash
gcc -o main main.c -L. -lcrc
```
la finalul comenzii rezulta un fisier executabil main. La executia lui, acesta va cauta biblioteca dinamica intr-un director din lista sistemului (/usr/lib, /lib, etc.). Pentru a adauga directorul curent la aceasta lista, se ruleaza comanda:  

```bash
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
```
## makefile pentru compilarea dinamica

https://www.topbug.net/blog/2019/10/28/makefile-template-for-a-shared-library-in-c-with-explanations/



```makefile
CC = gcc  # C compiler
CFLAGS = -fPIC -Wall  # C flags
LDFLAGS = -shared   # linking flags
EXEFLAGS = -L. -lcrc
RM = rm -f   # rm command
TARGET_LIB = libcrc.so  # target lib
EXECUTABLE = main
SRCS = crc.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET_LIB) $(EXECUTABLE)

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(EXECUTABLE): main.o $(LIBRARY)
	$(CC) -o $@ $< $(EXEFLAGS)

clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)

```
### Detalii Makefile

Fisierul Makefile are doua tinte: libraria si executabilul. Comenzile de compilare ale acestora sunt 
specificate in sectiunile $(LIBRARY) si $(EXECUTABLE), sectiuni in care fiecare variabila va fi inlocuita cu variabilele definite mai sus

    **CC**: compilatorul cu care se va executa compilarea.
    **CFLAGS** : flagurile compilatorului -Wall pentru atentionari.
    **LDFLAGS** : flagurile linkerului.
    **EXEFLAGS** : flagurile executabilului
    **SRC** : denumirea codului sursa (crc.c).
    **OBJ** : denumirea fisierului obiect (crc.o).
    **LIBRARY** : denumirea bibliotecii care trebuie creata (libcrc.so).
    **EXECUTABLE** : denumirea fisierului executabil rezultat in urma compilarii

# Cmake

CMake este un sistem de generare a Makefile-urilor și de administrare a procesului de compilare al proiectelor software. Este proiectat pentru a facilita dezvoltarea și administrarea proiectelor complexe, oferind un limbaj independent de platformă pentru descrierea configurării și a procesului de compilare. 

Utilizarea CMake presupune scrierea unui fișier CMakeLists.txt în directorul rădăcină al proiectului, care descrie resursele, dependențele și pașii de compilare. Apoi, se poate utiliza comanda cmake pentru a genera fișierele de configurare și apoi make sau alte unelte similare pentru a compila proiectul.

## CmakeLists.txt pentru compilarea dinamica

```cmake
cmake_minimum_required(VERSION 3.12)
project(MyProject C)

set(CMAKE_C_STANDARD 11)

# Flaguri pentru compilator
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wall")

# fisierele sursa
set(SRCS crc.c main.c)

# Bibliotecile dinamice
add_library(libcrc SHARED ${SRCS})

# Executabilul principal
add_executable(crc_main main.c)

# Legarea executabilului principal de biblioteca distribuita
target_link_libraries(crc_main PRIVATE libcrc)

# seteaza numele bibliotecii distribuite
set_target_properties(libcrc PROPERTIES OUTPUT_NAME "crc")

# Numele executabilului principal
set_target_properties(crc_main PROPERTIES OUTPUT_NAME "crc_main")

# Directoarele in care vor fi instalate fisierele
install(TARGETS libcrc DESTINATION lib)
install(TARGETS crc_main DESTINATION bin)

# Instalarea fisierelor de tip header 
install(FILES crc.h DESTINATION include)

```

Utilizarea CmakeLists.txt presupune urmatoarele comenzi:

Se creaza un director special pentru compilare
```bash
mkdir build
```

Se muta in directorul respectiv
```bash
cd build
```

Se lanseaza comanda cmake urmata de directorul in care se gasesc sursele (in cazul nostru directorul parinte, ..).
```bash
cmake ..
```
Comanda cmake lansata anterior a generat un fisier Makefile care poate fi lansat folosing comanda make
```bash
make
```