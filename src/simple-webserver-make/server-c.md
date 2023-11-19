
# Include

Sectiunea include contine headerele necesare pentru functiile executate de program

```c
#include <stdio.h>   
//Funcții standard de intrare/ieșire pentru citirea și scrierea fișierelor și consolei.
#include <stdlib.h>  
//Funcții standard din biblioteca C, inclusiv alocare de memorie, generare de numere aleatoare și utilități generale.
#include <unistd.h> 
//Constante și tipuri simbolice standard, inclusiv funcții pentru apeluri de sistem și manipularea fișierelor.
#include <errno.h> 
//Antet pentru numere de eroare și constante asociate. Este utilizat pentru gestionarea erorilor raportate de apelurile de sistem.
#include <string.h> 
//Funcții de manipulare a șirurilor de caractere, inclusiv operații precum copierea, concatenarea și compararea.
#include <fcntl.h>
// Opțiuni de control pentru fișiere, utilizate pentru manipularea proprietăților descriptorilor de fișiere.
#include <signal.h>
// Funcții și macrocomenzi pentru gestionarea semnalelor trimise unui program.
#include <sys/types.h>
// Tipuri și structuri de sistem utilizate în apelurile de sistem.
#include <sys/socket.h>
// Definiții și structuri pentru funcțiile și operațiunile legate de socket-uri. Esențial pentru programarea în rețea.
#include <netinet/in.h>
// Structuri și constante pentru familia de adrese de internet, utilizate în aplicațiile de rețea.
#include <arpa/inet.h>
// Funcții pentru manipularea adreselor IP și conversia între ordinea de octeți a rețelei și gazdă.
```

# Variabile globale

```c
#define BUFSIZE 8096
#define ERROR 42
#define SORRY 43
#define LOG   44
```

```c
struct {
	char *ext;
	char *filetype;
} extensions [] = {
	{"gif", "image/gif" },  
	{"jpg", "image/jpeg"}, 
	{"jpeg","image/jpeg"},
	{"png", "image/png" },  
	{"zip", "image/zip" },  
	{"gz",  "image/gz"  },  
	{"tar", "image/tar" },  
	{"htm", "text/html" },  
	{"html","text/html" },  
	{"php", "image/php" },  
	{"cgi", "text/cgi"  },  
	{"asp","text/asp"   },  
	{"jsp", "image/jsp" },  
	{"xml", "text/xml"  },  
	{"js","text/js"     },
   {"css","test/css"   }, 

	{0,0} };
```

```c
void log(int type, char *s1, char *s2, int num)
{
	int fd ;
	char logbuffer[BUFSIZE*2];

	switch (type) {
	case ERROR: (void)sprintf(logbuffer,"ERROR: %s:%s Errno=%d exiting pid=%d",s1, s2, errno,getpid()); break;
	case SORRY: 
		(void)sprintf(logbuffer, "<HTML><BODY><H1>Web Server Sorry: %s %s</H1></BODY></HTML>\r\n", s1, s2);
		(void)write(num,logbuffer,strlen(logbuffer));
		(void)sprintf(logbuffer,"SORRY: %s:%s",s1, s2); 
		break;
	case LOG: (void)sprintf(logbuffer," INFO: %s:%s:%d",s1, s2,num); break;
	}	
	
	if((fd = open("server.log", O_CREAT| O_WRONLY | O_APPEND,0644)) >= 0) {
		(void)write(fd,logbuffer,strlen(logbuffer)); 
		(void)write(fd,"\n",1);      
		(void)close(fd);
	}
	if(type == ERROR || type == SORRY) exit(3);
}
```

```c
void web(int fd, int hit)
{
	int j, file_fd, buflen, len;
	long i, ret;
	char * fstr;
	static char buffer[BUFSIZE+1];

	ret =read(fd,buffer,BUFSIZE); 
	if(ret == 0 || ret == -1) {
		log(SORRY,"failed to read browser request","",fd);
	}
	if(ret > 0 && ret < BUFSIZE)	
		buffer[ret]=0;	
	else buffer[0]=0;

	for(i=0;i<ret;i++)	
		if(buffer[i] == '\r' || buffer[i] == '\n')
			buffer[i]='*';
	log(LOG,"request",buffer,hit);

	if( strncmp(buffer,"GET ",4) && strncmp(buffer,"get ",4) )
		log(SORRY,"Only simple GET operation supported",buffer,fd);

	for(i=4;i<BUFSIZE;i++) { 
		if(buffer[i] == ' ') { 
			buffer[i] = 0;
			break;
		}
	}

	for(j=0;j<i-1;j++) 	
		if(buffer[j] == '.' && buffer[j+1] == '.')
			log(SORRY,"Parent directory (..) path names not supported",buffer,fd);

	if( !strncmp(&buffer[0],"GET /\0",6) || !strncmp(&buffer[0],"get /\0",6) ) 
		(void)strcpy(buffer,"GET /index.html");

	buflen=strlen(buffer);
	fstr = (char *)0;
	for(i=0;extensions[i].ext != 0;i++) {
		len = strlen(extensions[i].ext);
		if( !strncmp(&buffer[buflen-len], extensions[i].ext, len)) {
			fstr =extensions[i].filetype;
			break;
		}
	}
	if(fstr == 0) log(SORRY,"file extension type not supported",buffer,fd);

	if(( file_fd = open(&buffer[5],O_RDONLY)) == -1) 
		log(SORRY, "failed to open file",&buffer[5],fd);

	log(LOG,"SEND",&buffer[5],hit);

	(void)sprintf(buffer,"HTTP/1.0 200 OK\r\nContent-Type: %s\r\n\r\n", fstr);
	(void)write(fd,buffer,strlen(buffer));

	while (	(ret = read(file_fd, buffer, BUFSIZE)) > 0 ) {
		(void)write(fd,buffer,ret);
	}
#ifdef LINUX
	sleep(1);
#endif
	exit(1);
}
```

Inceputul functiei main care declara variabilele importante printre care structurile in care se vor gasi adresele socketurilor clientului si serverului.

```c
int main(int argc, char **argv)
{
	int i, port, pid, listenfd, socketfd, hit;
	size_t length;
	static struct sockaddr_in cli_addr; 
	static struct sockaddr_in serv_addr;
```

Se verifica argumentele primite de program la lansare. In mod normal, argumentele sunt doua, primulk este portul, cel de-al doilea este directorul de unde trebuie citite fisierele care vor fi servite. Lista argumentelor de la linia de comanda este pasata catre functia main (**argv) impreuna cu numarul acestora (argc). Citirea unui argument se face prin apelarea matricii argv: argv[index]. argv[0] este de fiecare data numele programului. 


```c
	if( argc < 3  || argc > 3 || !strcmp(argv[1], "-?") ) {

```

In cazul in care este necesar (fie numarul de argumente este gresit, fie primul argument este -? ceea ce declanseaza afisarea mesajului de ajutor)

```c
		(void)printf("usage: server [port] [server directory] &"
	"\tExample: server 80 ./ &\n\n"
	"\tOnly Supports:");
		for(i=0;extensions[i].ext != 0;i++)
			(void)printf(" %s",extensions[i].ext);

		(void)printf("\n\tNot Supported: directories / /etc /bin /lib /tmp /usr /dev /sbin \n"
		    );
		exit(0);
	}
```
In continuare se verifica daca directorul care se trimite ca argument la pornirea serverului este unul dintre directoarele de sistem. Acest lucru nu este permis. In cazul in care se intampla, se imprima un mesaj de eroare si programul se opreste. instructiunea `exit(3)`. Argumentul 3 (ca orice alta valoare mai mare decat zero) arata ca programul s-a incheiat cu o eroare. Daca programul se termina normal, se va rula exit(0). Lista directoarelor de sistem este cea de pe sistemele de operare de tip Linux.  

```c
	if( !strncmp(argv[2],"/"   ,2 ) || !strncmp(argv[2],"/etc", 5 ) ||
	    !strncmp(argv[2],"/bin",5 ) || !strncmp(argv[2],"/lib", 5 ) ||
	    !strncmp(argv[2],"/tmp",5 ) || !strncmp(argv[2],"/usr", 5 ) ||
	    !strncmp(argv[2],"/dev",5 ) || !strncmp(argv[2],"/sbin",6) ){
		(void)printf("ERROR: Bad top directory %s, see server -?\n",argv[2]);
		exit(3);
	}
```

Orice program are un director de lucru, de obicei directorul din care este lansat executabilul (nu tot timpul). O solicitare de deschidere a unui fisier cu o cale relativa (care nu incepe la radacina sistemului de fisiere) se presupune a fi relativa la directorul de lucru. Pentru a servi fisierele html, programul trebuie sa schimbe directorul de lucru in cel care a fost oferit ca parametru de intrare. Aceasta se face cu ajutorul instructiunii chdir, care returneaza adevarat (daca operatia a reusit) sau fals (daca operatia a esuat). Operatia poate esua daca directorul tinta nu exista, daca utilizatorul curent nu are drepturi de executie, etc. In cazul in care nu se poate face schimbarea in directorul tinta, programul se opreste cu eroare.   

```c
	if(chdir(argv[2]) == -1){ 
		(void)printf("ERROR: Can't Change to directory %s\n",argv[2]);
		exit(4);
	}
```

Urmatorul set de instructiuni porneste programul ca proces de tip daemon. Un proces de tip daemon se detaseaza de orice consola si poate rula indefinit in sistemul de operare pana cand logica sa interioara il determina sa se opreasca sau primeste un semnal de oprire de la sistemul de operare. Etapele sunt: 

 - procesul se copiaza pe el insusi intr-un alt proces identic (`fork()`)
 - procesul parinte dispare
 - procesul copil executa o serie de operatii necesare pentru detasarea completa

Instructiunea `fork()` separa procesul curent in doua procese identice, un proces "copil" care va primi un nou ID de la sistemul de operare. In cazul in care operatia reuseste, `fork()` va returna id-ul procesului copil care va fi mai mare decat 0 si deci adevarat intr-o instructiune conditionala. `if(fork() != 0)` verifica succesul operatiei si daca acesta se confirma, in acest moment vor exista doua procese identice, procesul parinte si noul proces copil. Pentru a finaliza detasarea procesului copil, procesul parinte trebuie sa se incheie, cea ce se intampla cu instructiunea `return 0;` In acest moment, procesul copil devine unic iar parintele dispare. 

```c
	if(fork() != 0)
		return 0; 
```

Urmatoarele instructuni se executa de catre procesul copil (toate, de aici inainte).

Un proces de tip daemon nu poate primi comenzi de la tastatura, de aceea se bazeaza pe alte mecanisme pentru semnalizare. Unul dintre aceste mecanisme este reprezentat de "semnale" care pot fi trimise de catre sistemul de operare. Fiecare astfel de semnal trebuie conectat cu o functie interna a programului, daca dorim executia anumitor operatii la rpomirea acelui semnal. De exemplu, exista programe de tip server care folosesc un anumit semnal (de obicei SIGHUP) pentru a reincarca informatia din fisierele de configurare, fara sa trebuiasca repornite. 

Cele doua instructiuni care urmeaza au ca efect ignorarea semnalelor SIGCLD si SIGHUP prin conectarea lor cu macro-ul SIG_IGN care determina ignorarea acestor semnale. `(void)` din fata celor doua instructiuni converteste fortat orice valoare returnata intr-o valoare goala. Acest typecast se face pentru a informa compilatorul ca nu suntem interesati in ce va returna functia respectiva si nu dorim sa primim eventualele mesaje de atentionare (warnings) cuy privire la aceste valori. 
 
```c
	(void)signal(SIGCLD, SIG_IGN); 
	(void)signal(SIGHUP, SIG_IGN); 
```

In continuare, procesul copil a mostenit de la procesul parinte tot, inclusiv eventualele fisiere deschise. Cel putin stream-urile standard (STDIN, STDERR si STDOUT) sunt in continuare deschise, ca file descriptors. Astfel, se foloseste close() pentru a inchide toate aceste file descriptors. 0,1 si 2 sunt STDIN, STDOUT si STDERR.  

```c	
	for(i=0;i<32;i++)
		(void)close(i);	
```

Functia setgrp fara argumente va atribui un nou "process group id" procesului copil, detasandu-l complet de parintele care intre timp a disparut. Grupul procesului este un identificator suplimentar in sistemele de operare de tip Unix care permite gruparea proceselor similare pentru operatii de management comune. `setptrp()` este ultima etapa din detasara unui proces de tip daemon. 

```c
	(void)setpgrp();	
```

Procesul semnaleaza pornirea prin trimiterea unui mesaj care va fi scris in log. Mesajul contine primul argument al programului (argv[1]) care este portul pe care asculta serverul, impreuna cu pid-ul serverului (obtinut cu instructiunea getpid()).

```c
	log(LOG,"http server starting",argv[1],getpid());
```

Urmatorul set de instructiuni transforma procesul (care deocamdata este un simplu daemon) intr-un server. Pentru aceasta, programul va declara un [socket](../Doc-Concepts/sockets.md) si va astepta conexiuni de la clienti. `listenfd = socket(AF_INET, SOCK_STREAM,0)` deschide un socket de retea de tip IPv4 (AF_INET) stream cu protocolul default (TCP). Dupa declararea socketului se vor specifica cateva proprietati ale acestuia: `serv_addr.sin_addr.s_addr = htonl(INADDR_ANY)` face socketul sa asculte pe toate interfetele existente in sistemul de operare iar `serv_addr.sin_port = htons(port)` seteaza portul pe care va asculta serverul. 

Functia bind() asociaza socketul declarat (listenfd) cu o anumita matrice de adrese ((struct sockaddr *)&serv_addr) 

Functia listen deschide propriu-zis socketul (pana acum doar i-am stabilit proprietatile), fiind pregatita sa accepte pana la 64 de conexiuni. 


```c
	if((listenfd = socket(AF_INET, SOCK_STREAM,0)) <0)
		log(ERROR, "system call","socket",0);
	port = atoi(argv[1]);
	if(port < 0 || port >60000)
		log(ERROR,"Invalid port number try [1,60000]",argv[1],0);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);
	if(bind(listenfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) <0)
		log(ERROR,"system call","bind",0);
	if( listen(listenfd,64) <0)
		log(ERROR,"system call","listen",0);
```

Urmatoarea secventa de linii de cod reprezinta propriu-zis partea de server web. Ca orice daemon, exista o bucla infinita care asteapta conextiuni de la client. `if((socketfd = accept(listenfd, (struct sockaddr *)&cli_addr, &length)) < 0)` verifica aparitia unei astfel de conexiuni. 

Daca conexiunea este stabilta procesul curent va crea un proces copil care va apela functia web . 


```c
	for(hit=1; ;hit++) {
		length = sizeof(cli_addr);
		if((socketfd = accept(listenfd, (struct sockaddr *)&cli_addr, &length)) < 0)
			log(ERROR,"system call","accept",0);

		if((pid = fork()) < 0) {
			log(ERROR,"system call","fork",0);
		}
		else {
			if(pid == 0) {
				(void)close(listenfd);
				web(socketfd,hit);
			} else {
				(void)close(socketfd);
			}
		}
	}
}
```
