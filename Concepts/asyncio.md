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