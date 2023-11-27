# Descifrari-C

Descifrari-C este un proiect care isi propune clarificarea unor programe de complexitate mica si medie. Sunt programe de pe internet (github in principal) care ajuta in invatarea diferitelor aspecte ale programarii in C. 

Programele se gasesc in directoare separate, fiecare dintre ele au cel putin un mod de build (fie make fie cmake, fie ambele) iar acesta este de regula specificat in numele directorului.

Fiecare program are un readme.md care descrie programul, conceptele importante care se vor intalni in program, elementele de cod, continutul Makefile-urilor... etc. 

Toate programele sunt compilate si testate in Linux, cu compilatorul gcc. 

# Motivatie

Una dintre particularitatile limbajului de programare C, in special ca prim limbaj invatat, este tranzitia de la etapa de a cunoaste sintaxa si a avea o idee despre functiile acestuia catre etapa in care se poate scrie un program mai complex. In cazul C-ului, aceasa tranzitie implica invatarea unor sintaxe si instrumente suplimentare, cum ar fi make sau cmake, invatarea modului in care un program c se poate plasa in mai multe fisiere, etc. In plus, pe langa sintaxa obisnuita, C-ul este un limbaj de sistem care sunt chiar mai dificil de urmarit datorita multitudinii de concepte noi (comunicatie pe retea, I/O, etc.). 

# Concepte importante

Programele prezentate mai jos se bazeaza pe o serie de "concepte" sau operatii tipice care sunt prezentate si separat in sectiunea Concepte unde vor fi descrise separat cu exemple elementare de cod. 

- [cum se detaseaza un program astfel incat sa ruleze in fundal](./Concepts/daemonize/)
- [cum se foloseste biblioteca ncurses](./Concepts/ncurses/)
- [cum se utilizeaza socketurile pentru comunicare pe retea](./Concepts/sockets/)
- [cum se interactioneaza cu logurile sistemului de operare](./Concepts/syslog/)

# Programe existente

Programele sunt impartite in functie de complexitatea lor. 

## Complexitate 1

- [X si 0, implementare simpla](./src/tictactoe-make/)
- [implementari diferite ale unor algoritmi de sortare](./src/sortari-cmake/)
- [calculul crc (cyclic redundancy check)](./src/crc-cmake-make/)


## Complexitate 2

 - [un server web simplu](./src/simple-webserver-make/)

## Complexitate 3

- [un program simplu de chat (client si server)](./src/simple-chat-make/)
- [tetris in consola implementat cu biblioteca ncurses](./src/tetris-make/)
- [program de inregistrare a taskurilor](./src/todo-make/)

