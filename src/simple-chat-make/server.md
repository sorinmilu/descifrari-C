# Includerea bibliotecilor

```c
#include <stdio.h> // Bibliotecă standard pentru I/O
#include <unistd.h> // Pentru funcții POSIX, cum ar fi close()
#include <stdlib.h> // Pentru funcții generale, cum ar fi exit()
#include <string.h> // Pentru manipularea șirurilor de caractere
#include <sys/types.h> // Definește tipuri de date utilizate în socket-uri
// #include <sys/socket.h> 
// #include <netinet/in.h>
#include <netdb.h> // Bibliotecă pentru lucrul cu rețele - de obicei include si cele doua biblioteci de mai sus, comentate. 
```

# Constantele generale
```c
// Definim dimensiuni și constante
#define MSG_SIZE 90 // Dimensiunea maximă a unui mesaj
#define MAX_CLIENTS 95 // Numărul maxim de clienți care pot conecta simultan
#define MYPORT 7400 // Portul implicit al serverului
```

Functie pentru inchiderea unui client. File descriptors trebuie mutati cu o poztitie mai jos, pentru a mentine continutiatea. 

```c
// Funcție pentru închiderea unui client și actualizarea stării
void exitClient(int fd, fd_set *readfds, char fd_array[], int *num_clients) {
    int i; // Index pentru iterare

    close(fd); // Închide socket-ul clientului
    FD_CLR(fd, readfds); // Elimină descriptorul din setul de citire

    // Caută și șterge clientul din lista de descriptori
    for (i = 0; i < (*num_clients) - 1; i++) 
        if (fd_array[i] == fd) 
            break; // Găsește poziția clientului

    // Reorganizează lista pentru a elimina clientul
    for (; i < (*num_clients) - 1; i++) 
        fd_array[i] = fd_array[i + 1]; // Suprascrie pozițiile

    (*num_clients)--; // Scade numărul de clienți activi
}
```

# Functia principala

```c
// Funcția principală a serverului
int main(int argc, char *argv[]) {
    int i = 0; // Variabilă de iterare
```

## Initializarea variabilelor principale

```c
    int port; // Variabilă pentru portul serverului
    int num_clients = 0; // Numărul curent de clienți conectați
    int server_sockfd, client_sockfd; // Socket-uri pentru server și clienți
    struct sockaddr_in server_address; // Structura adresei serverului
    int addresslen = sizeof(struct sockaddr_in); // Lungimea structurii de adresă
    int fd; // Descriptor curent al socket-ului
    char fd_array[MAX_CLIENTS]; // Listă pentru descriptorii clienților
    fd_set readfds, testfds; // Seturi de descriptori pentru citire și testare
    char msg[MSG_SIZE + 1]; // Buffer pentru mesaje primite/trimise
    char kb_msg[MSG_SIZE - 10]; // Mesaje citite de la tastatură
    int result; // Variabilă pentru a stoca rezultatul operațiilor I/O
```

## Prelucrarea informatiei de la linia de comanda

```c
    // Verifică argumentele liniei de comandă pentru setarea portului
    if (argc == 1 || argc == 3) { // Dacă sunt argumente valide
        if (argc == 3) { // Dacă există 3 argumente
            if (!strcmp("-p", argv[1])) { // Verifică dacă parametrul este -p
                sscanf(argv[2], "%i", &port); // Extrage portul din argument
            } else {
                printf("Parametru invalid.\nUtilizare: chat [-p PORT] HOSTNAME\n"); // Mesaj de eroare
                exit(0); // Încheie execuția
            }
        } else port = MYPORT; // Dacă nu e specificat, folosește portul implicit
```

## Pornirea serverului

### Initializarea, configurarea si lansarea socketului

```c
        printf("\n*** Serverul pornește (scrie \"quit\" pentru a opri): \n"); // Mesaj pentru pornirea serverului
        fflush(stdout); // Golim buffer-ul de ieșire

        server_sockfd = socket(AF_INET, SOCK_STREAM, 0); // Creăm socket-ul pentru server
        server_address.sin_addr.s_addr = htonl(INADDR_ANY); // Acceptă conexiuni de la orice adresă
        server_address.sin_port = htons(port); // Setează portul
        bind(server_sockfd, (struct sockaddr *)&server_address, addresslen); // Leagă socket-ul de adresa IP
        listen(server_sockfd, 1); // Setează socket-ul în modul de ascultare
```

### Initializarea setului de filedescriptors. 

```c

        FD_ZERO(&readfds); // Inițializează setul de descriptori pentru citire
        FD_SET(server_sockfd, &readfds); // Adaugă socket-ul serverului în setul de citire
        FD_SET(0, &readfds); // Adaugă intrarea standard (tastatura) în setul de citire
```

## Bucla principala a executiei

Functia select trece mai departe in momentul in care apare o comunicare pe un anumit.  

```c
        while (1) { // Loop infinit pentru gestionarea conexiunilor
            testfds = readfds; // Copiază setul de descriptori activi
            select(FD_SETSIZE, &testfds, NULL, NULL, NULL); // Așteaptă activitate pe oricare dintre descriptori

            for (fd = 0; fd < FD_SETSIZE; fd++) { // Iterează prin toți descriptorii
                if (FD_ISSET(fd, &testfds)) { // Verifică dacă există activitate pe descriptor
```

Daca apare o comunicare pe socketul de server, atunci trebuie sa acceptam o conexiune noua. Aceasta implica urmatoarele: 
- crearea unui nou file descriptor pentru noul client, folosind accept
- adaugarea file descriptorului la lista curenta
  
Daca comunicarea se face pe un client deja existent, se prelucreaza mesajul si se scrie mesajul catre toti clientii. 

```c
                    if (fd == server_sockfd) { // Dacă este socket-ul serverului
                        client_sockfd = accept(server_sockfd, NULL, NULL); // Acceptă o conexiune nouă

                        if (num_clients < MAX_CLIENTS) { // Dacă nu s-a atins limita de clienți
                            FD_SET(client_sockfd, &readfds); // Adaugă noul client în setul de citire
                            fd_array[num_clients] = client_sockfd; // Salvează descriptorul clientului
                            printf("Client %d conectat\n", num_clients++); // Afișează mesaj de conectare
                            fflush(stdout); // Golim buffer-ul

                            sprintf(msg, "M%2d", client_sockfd); // Creează mesaj de identificare
                            send(client_sockfd, msg, strlen(msg), 0); // Trimite mesajul clientului
                        } else { // Dacă limita de clienți este atinsă
                            sprintf(msg, "XPrea mulți clienți. Încearcă mai târziu.\n"); // Mesaj de respingere
                            write(client_sockfd, msg, strlen(msg)); // Trimite mesajul
                            close(client_sockfd); // Închide conexiunea
                        }
                    } else if (fd == 0) { // Dacă este activitate la tastatură
                        fgets(kb_msg, MSG_SIZE + 1, stdin); // Citește mesaj de la tastatură
                        if (strcmp(kb_msg, "quit\n") == 0) { // Dacă mesajul este "quit"
                            sprintf(msg, "XServerul se închide.\n"); // Creează mesaj pentru clienți
                            for (i = 0; i < num_clients; i++) { // Trimite mesajul tuturor clienților
                                write(fd_array[i], msg, strlen(msg));
                                close(fd_array[i]); // Închide fiecare conexiune
                            }
                            close(server_sockfd); // Închide serverul
                            exit(0); // Încheie execuția
                        } else { // Dacă mesajul este altul
                            printf("Server - trimite mesaj\n"); // Afișează pe server
                            sprintf(msg, "M%s", kb_msg); // Formatează mesajul
                            for (i = 0; i < num_clients; i++) // Trimite mesajul tuturor clienților
                                write(fd_array[i], msg, strlen(msg));
                        }
                    } else if (fd) { // Dacă există activitate pe un client
                        result = read(fd, msg, MSG_SIZE); // Citește datele de la client
                        if (result == -1) perror("Eroare la citire()"); // Mesaj de eroare la citire
                        else if (result > 0) { // Dacă există date citite
                            sprintf(kb_msg, "M%2d", fd); // Creează prefix pentru mesaj
                            msg[result] = '\0'; // Terminator pentru șir
                            strcat(kb_msg, msg + 1); // Concatenează mesajul clientului

                            for (i = 0; i < num_clients; i++) { // Trimite mesajul altor clienți
                                if (fd_array[i] != fd) 
                                    write(fd_array[i], kb_msg, strlen(kb_msg));
                            }
                            printf("%s", kb_msg + 1); // Afișează mesajul pe server

                            if (msg[0] == 'X') { // Dacă mesajul începe cu 'X', clientul se deconectează
                                exitClient(fd, &readfds, fd_array, &num_clients); // Deconectează clientul
                            }
                        }
                    } else { // Dacă un client deconectat este detectat
                        exitClient(fd, &readfds, fd_array, &num_clients); // Șterge clientul
                    }
                }
            }
        }
    }

    return 0; // Încheiere program
}
```