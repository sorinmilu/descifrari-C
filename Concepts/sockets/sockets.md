## Socket

### Generalitati

Mecanismul de tip socket (soclu) în sistemele de operare este utilizat pentru a permite comunicația între procese. Uncaz particular este socketul de retea care permite comunicarea intre procese aflate pe doua computere diferite, prin itnermediul protocoalelor de retea. Socketurile oferă un mod standardizat de transmitere a datelor între dispozitive sau procese software pe aceeași mașină sau între mașini diferite. Socketurile de acest tip permit transmiterea de informatie bidirectionala intre procese. Deschiderea unui socket ocupa un port - un numar intreg (de regula 16 biti fara semn) aflat intr-un interval limitat de valori, de obicei intre 0 si 65536. Porturile intre 0 si 1024 sunt standardizate pentru protocoale cunoscute, porturile aflate intre 1024 si 49151 sunt utilizate pentru protocoale secundare iar cele dintre 49152 si 65536 sunt numite porturi efemere si sunt utilizate pentru conexiunile client. 

O conexiune intre doua procese deschide cate un port pe fiecare dintre computerele respective. De obicei uynul dintre programe este un server care deschide un port cunoscut si asteapta conexiuni de la client iar celalalt este client care se conecteaza pe portul cunoscut al serverului deschizand local un port efemer. 

Ex: coneciune HTTP: server:80 <-> client:49154

### Instructiuni de interes intalnite in cod


`server_sockfd = socket(AF_INET, SOCK_STREAM, 0);` : creaza un nou socket. AF_INET specifica faptul ca adresa IP este de tip IPv4, SOCK_STREAM specifica tipul de socket (conexiune de tip stream, TCP, SCTP, QUIC). Ultimul parametru reprezinta protocolul, valoarea 0 inseamna default ceea ce pentru SOCK_STREAM este TCP. 


`server_address.sin_addr.s_addr = htonl(INADDR_ANY);` seteaza adresa 0.0.0.0 ca adresa pe care asculta socketul. htonl converteste ordinea octetilor din cea locala (a computerului - de obicei little endian) in cea de retea (care este diferita, de cele mai multe ori big-endian - din motive istorice). Inversul aceste functii este ntohl

`server_address.sin_port = htons(port);` : seteaza portul pe care va asculta socketul. htons este aceeasi cu htonl dar opereaza pe un short, nu pe un long

`bind(server_sockfd, (struct sockaddr *)&server_address, addresslen);` - Funcția bind asociază un socket cu o anumită adresă, astfel încât să poată fi folosit pentru a asculta conexiuni de la adresa respectivă. Dupa o operatie bind de succes, socketul este deschis si pregatit pentru instructiunea listen. 

 - server_sockfd: Acesta este descriptorul de fișier al socket-ului care urmează să fie asociat cu o adresă.

 - (struct sockaddr *)&server_address: Aceasta este o conversie de tip care transformă adresa serverului (server_address), declarată ca o structură de tipul struct sockaddr, într-un pointer la struct sockaddr. Această conversie este necesară pentru că funcția bind așteaptă un pointer la o structură de tip struct sockaddr ca al doilea argument.

 - addresslen: Acesta este parametrul care specifică dimensiunea adresei specificate, exprimată în octeți. Această dimensiune depinde de tipul de adresă folosit (IPv4 sau IPv6, de exemplu).


`listen(server_sockfd, 1);` porneste ascultarea pe socketul deschis. 

`client_sockfd = accept(server_sockfd, NULL, NULL);` : accepta o conexiune de la un socket client si returneaza file descriptorul corespunzator acesteia. In mod normal, acest file descriptor va fi adaugat la un set de file descriptori (vezi mai jos). ultimii doi parametrii (care sunt NULL) ar fi putut fi pointeri catre structuri care tin informatii despre adresa clientului respectiv lungimea acesteia (IPv4, IPv6). 