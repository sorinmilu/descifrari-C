# Chat - client / server

Sursa: [Simple chat client-server](https://github.com/dtolj/simple-chat-client-server)

# Descriere

Un mic sistem de chat care cuntine un program de tip server si un program de tip client. 

# Concepte utilizate in program:

## Socket

### Generalitati

Mecanismul de tip socket (soclu) în sistemele de operare este utilizat pentru a permite comunicația între procese. Uncaz particular este socketul de retea care permite comunicarea intre procese aflate pe doua computere diferite, prin itnermediul protocoalelor de retea. Socketurile oferă un mod standardizat de transmitere a datelor între dispozitive sau procese software pe aceeași mașină sau între mașini diferite. Socketurile de acest tip permit transmiterea de informatie bidirectionala intre procese. Deschiderea unui socket ocupa un port - un numar intreg (de regula 16 biti fara semn) aflat intr-un interval limitat de valori, de obicei intre 0 si 65536. Porturile intre 0 si 1024 sunt standardizate pentru protocoale cunoscute, porturile aflate intre 1024 si 49151 sunt utilizate pentru protocoale secundare iar cele dintre 49152 si 65536 sunt numite porturi efemere si sunt utilizate pentru conexiunile client. 

O conexiune intre doua procese deschide cate un port pe fiecare dintre computerele respective. De obicei uynul dintre programe este un server care deschide un port cunoscut si asteapta conexiuni de la client iar celalalt este client care se conecteaza pe portul cunoscut al serverului deschizand local un port efemer. 

Ex: coneciune HTTP: server:80 <-> client:49154

### Instructiuni de interes intalnite in cod


`server_sockfd = socket(AF_INET, SOCK_STREAM, 0);` : creaza un nou socket. AF_INET specifica faptul ca adresa IP este de tip IPv4, SOCK_STREAM specifica tipul de socket (conexiune de tip stream, TCP, SCTP, QUIC). Ultimul parametru reprezinta protocolul, valoarea 0 inseamna default ceea ce pentru SOCK_STREAM este TCP. 


`server_address.sin_addr.s_addr = htonl(INADDR_ANY);` seteaza adresa 0.0.0.0 ca adresa pe care asculta socketul. htonl converteste ordinea octetilor din cea locala (a computerului - de obicei little endian) in cea de retea (care este diferita, de cele mai multe ori big-endian - din motive istorice). Inversul aceste functii este ntohl

`server_address.sin_port = htons(port);` : seteaza portul pe care va asculta socketul. htons este aceeasi cu htonl dar opereaza pe un short, nu pe un long

`bind(server_sockfd, (struct sockaddr *)&server_address, addresslen);` - conecteaza socketul la o adresa locala. Operatia este obligatorie pentru servere. Dupa o operatie bind de succes, socketul este deschis si pregatit pentru instructiunea listen. 

`listen(server_sockfd, 1);` porneste ascultarea pe socketul deschis. 

`client_sockfd = accept(server_sockfd, NULL, NULL);` : accepta o conexiune de la un socket client si returneaza file descriptorul corespunzator acesteia. In mod normal, acest file descriptor va fi adaugat la un set de file descriptori (vezi mai jos). ultimii doi parametrii (care sunt NULL) ar fi putut fi pointeri catre structuri care tin informatii despre adresa clientului respectiv lungimea acesteia (IPv4, IPv6). 


## I/O asincron si multiplexare

Anumite programe au nevoie sa accepte input pe canale multiple, atunci cand acesta este primit. In cazul acestui program, serverul trebuie sa monitorizeze conexiunile cu mai multi clienti in acelasi timp si sa reactioneze la mesajele sosite de la fiecare dintre ele. Aceste conexiuni sunt deschise prin intermediul socketurilor care sunt reprezentate pentru operatia de citire/scriere prin intermediul unor pseudo-fisiere. Problema se reduce (cel putin pe sistemele de operare de tip UNIX) la nevoia unui mecanism care sa permita unui program sa monitorizeze mai multe fisiere in acelasi timp si sa reactioneze la oricare input adaugat in oricare din aceste fisiere. 

Nu se poate utiliza o metoda cum ar fi "read" pentru aceasta pentru ca "read" blocheaza programul pana cand exista intrare in acel file descriptor, orice input pe alt file descriptor nu va fi bagat in seama. S-ar putea utiliza un mod non-blocant si o metoda de polling pe fiecare file descriptor in parte dar aceasta tehnica este foarte ineficienta. 

O solutie mai buna este functia "select". Aceasta blocheaza programul pana la aparitia unui input pe un set de file-descriptori sau pana la expirarea unui cronometru, indiferent care eveniment apare primul. Aceasta posibilitate este declarata in headerul sys/types.h.

Setul de file-descriptori pentru functia select este specificat ca obiecte de tipul fd_set. Operarea unui astfel de fd_set se face cu ajutorul unor macro-uri. 

Succesiunea operatiilor cu un set de file-descriptori este urmatoarea: 

1. Initializare - declara si initializeaza un set de file-descriptori
2. Multiplexare - foloseste un apel de sistem de multiplexare (select, poll) pentru a astepta evenimente pe oricare dintre file-descriptorii din set. 
3. Reactie la eveniment - Verifica file-descriptorii pentru a vedea care sunt gata pentru scriere sau citire si apoi produce operatia de I/O corespunzatoare sau executa functiile de callback asociate
4. Repetare - repeta procesul intr-o bucla infinita pentru a monitoriza continuu setul 


`char fd_array[MAX_CLIENTS];`

`fd_set readfds` declara variabila readfds ca fiind de tipul fd_set. fd_set este o structura opaca pusa la dispozitie de sistemul de operare. 

`FD_ZERO(&readfds);`:  Aceasta linie initializeaza setul de file-descriptors (readfs) ca set gol. Sterge toti descriptorii existenti in setul respectiv.  

`FD_SET(server_sockfd, &readfds);`: Aceasta linie adauga file-descriptorul server_sockfd la setul de file-descriptors readfs. Aceasta implica ca programul este interesat in monitorizarea socketului respectiv pentru eventualitatea in care este gata de citire.

`FD_SET(0, &readfds);`: Aceasta linie adauga descriptorul 0 la setul readfs. File descriptorul 0 reprezinta standard input (stdin). Aceasta arata ca programul curent doreste si monitorizarea stdin (tastatura). 
    
`select(FD_SETSIZE, &testfds, NULL, NULL, NULL);` : porneste operatia de monitorizare a setului de file-descriptors. Operatia va bloca executia programului pana cand unul sau mai multi dintre file-descriptori primeste un input. FD_SETSIZE reprezinta dimensiunea setului de file-descriptors, &testfds este un pointer catre setul de file-descriptors testfds care va fi monitorizat la citire. urmatorii trei parametrii care sunt NULL reprezinta eventuale seturi de file-descriptori monitorizati la disponibilitatea de scriere, erori sau timeouts. La aparitia unui eveniment de "ready for read" programul se va multa la instructiunea urmatoare. 

`for (fd = 0; fd < FD_SETSIZE; fd++) {` : parcurge setul de file-descriptors

`if (FD_ISSET(fd, &testfds)) {` : foloseste FD_ISSET pentru a vedea daca fd este gata de citire

`if (fd == server_sockfd) {` : daca activitatea este pe server_sockfd (socketul serverului) inseamna ca avem o conexiune noua


`FD_SET(client_sockfd, &readfds);`  Adauga file descriptorul client_sockfd la setul fd
`fd_array[num_clients]=client_sockfd;` Adauga file descriptrul si la arrayul fd_array


`else if (fd == 0)  {` : avem activitate pe fd = 0 - tastatura

`else if(fd) {` : fd este definit, inseamna ca avem un mesaj venit de la clientul reprezentat de fd (fd este determinat de parcurgerea setului de file-descriptors). 


