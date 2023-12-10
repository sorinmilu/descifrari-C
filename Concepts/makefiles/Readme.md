# Make

Make este un sistem de automatizare a compilarii si constructiei unor programe si biblioteci din cod sursa. Pentru aceasta, make cauta si citeste o serie de fisiere numite Makefile care contin intructiuni cu privire la ordinea si instrumentele necesare compilarii si linkeditarii programelor. 

Make a fost creat de [Stuart Feldman](https://en.wikipedia.org/wiki/Stuart_Feldman) in 1976 la Bell Labs. 

Make poate fi utilizat si pentru alte operatii. 

Un Makefile contine un set de reguli care au forma: 


```bash
tinta: elemente dependente
    comenzi
```

urmatorul exemplu va produce un program numit server pe baza fisierului sursa server.c cu ajutorul comenzii `gcc -Wall -o server server.c`. 

```bash
server: server.c
	gcc -Wall -o server server.c

```

Makefile-urile folosesc de multe ori variabile pentru a le face mai flexibile. Un exemplu: 

```bash
CC = gcc
CFLAGS = -Wall -Wextra

server: server.c
	$(CC) $(CFLAGS) -o server server.c
```
Nu toate tintele reprezinta programe care vor rezulta in urma procesului de compilare. Tintele care nu intra in aceasta categorie se numesc "Tinte false". Exemple frecvente de tine talse sunt tinta *all* care contruieste toate tintele ulterioare sau *clean* care sterge toate fisierele rezultate in urma procesului de constructie dar lasa sursele neatinse. 

```bash

CC = gcc
CFLAGS = -Wall -Wextra

all: server client

server: server.c
	$(CC) $(CFLAGS) -o server server.c

client: client.c
	$(CC) $(CFLAGS) -o client client.c

.PHONY: clean

clean:
	rm -f server client

```
 Un exemplu putin mai complex in care rezultatul final va fi un executabil numit edit compus din mai multe fisiere obiect (determinate de existenta mai multe fisiere sursa). 

 ```bash

 edit : main.o kbd.o command.o display.o insert.o search.o files.o utils.o
        cc -o edit main.o kbd.o command.o display.o insert.o search.o files.o utils.o

main.o : main.c defs.h
        cc -c main.c
kbd.o : kbd.c defs.h command.h
        cc -c kbd.c
command.o : command.c defs.h command.h
        cc -c command.c
display.o : display.c defs.h buffer.h
        cc -c display.c
insert.o : insert.c defs.h buffer.h
        cc -c insert.c
search.o : search.c defs.h buffer.h
        cc -c search.c
files.o : files.c defs.h buffer.h command.h
        cc -c files.c
utils.o : utils.c defs.h
        cc -c utils.c
clean :
        rm edit main.o kbd.o command.o display.o insert.o search.o files.o utils.o
 
 ```


[Documentatia gmake](https://devdocs.io/gnu_make/) 