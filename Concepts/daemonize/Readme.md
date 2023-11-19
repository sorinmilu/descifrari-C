# Daemonize

Scurt program care demonstreaza tehnicile necesare pentru a transforma un program intr-un daemon. 

Un program de tip daemon este un program care ruleaza fara sa fie sub controlul utilizatorului. Se mai numesc si "background processes". Un sinonim din lumea Windows pentru astfel de procese este serviciu (service). 

Aceste programe sunt lansate din consola ca orice alt program si inainte de a incepe actiunea proprie, trebuie sa treaca printr-o succesiune obligatorie de pasi care il vor transforma in daemon. Acestia sunt demonstrati in programul daemon_example. Pe scurt: 

 - procesul se copiaza pe el insusi intr-un alt proces identic (`fork()`)
 - procesul parinte dispare
 - procesul copil executa o serie de operatii necesare pentru detasarea completa

Optional, procesul poate scrie informatii utile intr-un jurnal de sistem sau intr-un fisier (consola nu mai este disponibila). 

Procesul poate de asemenea sa defineasca propriile functii care se vor executa la primirea semnalelor din partea sistemului de operare. Semnalele sunt in principal urmatoarele: 

<dl>
<dt>SIGHUP (1): </dt>
<dd>Semnalul de hang-up. Trimis către un proces pentru a-l informa că terminalul (sau conexiunea) de la care a fost pornit a fost închis.</dd>

<dt>SIGINT (2):  </dt>
<dd>Semnalul de întrerupere. Trimis către un proces pentru a-l întrerupe sau termina în mod normal, de obicei prin apăsarea combinației de taste Ctrl+C în terminal.</dd>

<dt>SIGQUIT (3):  </dt>
<dd>Semnalul de renunțare. Trimis către un proces pentru a-i cere să se oprească și să producă un raport de stare înainte de a se încheia.</dd>

<dt>SIGILL (4):  </dt>
<dd>Semnalul de instrucțiune ilegală. Trimis către un proces când detectează o instrucțiune de procesor nevalidă sau un alt comportament neașteptat.</dd>

<dt>SIGTRAP (5):  </dt>
<dd>Semnalul de urmărire. Trimis către un proces sau debugger pentru a semnala evenimente speciale, cum ar fi oprirea unui breakpoint.</dd>

<dt>SIGABRT (6):  </dt>
<dd>Semnalul de avortare. Trimis către un proces pentru a-l forța să se termine imediat; acest semnal este de obicei generat de o apelare explicită către abort().</dd>

<dt>SIGBUS (7): </dt>
 <dd>Semnalul de eroare la nivel de autobuz. Trimis către un proces când se întâmpină o eroare la nivelul sistemului de autobuz al computerului.</dd>

<dt>SIGFPE (8): </dt>
 <dd>Semnalul de eroare în virgulă mobilă. Trimis către un proces când are loc o eroare în calculul în virgulă mobilă, cum ar fi împărțirea la zero.</dd>

<dt>SIGKILL (9):  </dt>
<dd>Semnalul de ucidere. Trimis către un proces pentru a-l forța să se termine imediat; nu poate fi prins sau ignorat.</dd>

<dt>SIGUSR1 (10): </dt>
 <dd>Semnalul utilizatorului 1. Folosit pentru a trimite informații personalizate sau comenzi către un proces.</dd>

<dt>SIGSEGV (11):  </dt>
<dd>Semnalul de segmentare. Trimis către un proces atunci când încearcă să acceseze memorie în afara spațiului său de adresă.</dd>

<dt>SIGUSR2 (12):  </dt>
<dd>Semnalul utilizatorului 2. Similar cu SIGUSR1, folosit pentru a trimite informații personalizate sau comenzi către un proces.</dd>

<dt>SIGPIPE (13):  </dt>
<dd>Semnalul de conductă. Trimis către un proces care încearcă să scrie pe o conductă (pipe) sau un socket fără să aibă un proces destinatar.</dd>

<dt>SIGALRM (14): </dt>
 <dd>Semnalul de alarmă. Trimis către un proces atunci când expiră un temporizator de alarmă.</dd>

<dt>SIGTERM (15):  </dt>
<dd>Semnalul de terminare. Trimis către un proces pentru a-l întrerupe sau a-l termina în mod normal.</dd>

</dl>

# Programul daemon_example.c

Programul incepe prin a defini functiile care se vor executa automat cand va primi anumite semnalke de la sistemul de operare. Acestea vor trebui apoi asociate cu semnalele respective. Trebuie mentionat ca `sigkill_handler` nu functioneaza - semnalul SIGKILL nu ajunge de fapt pana la proces. 

```c
void cleanup() {
    syslog(LOG_INFO, "Daemon is shutting down.");
    // Perform any cleanup tasks here.
    closelog();
}

void sigkill_handler(int signum) {
    // This does not work - sigkill is handledx
    syslog(LOG_INFO, "Oh, you killed me.");
}

void sighup_handler(int signum) {
    syslog(LOG_INFO, "I shall live forever!!");
}
``


Deschidem logul

```c
int main() {
    // Open syslog (from syslog.h)
    openlog("daemon_example", LOG_PID | LOG_NDELAY, LOG_DAEMON);
```

Programul asociaza functiile respective cu fiecare semnal in parte

```c
    signal(SIGTERM, cleanup);
    signal(SIGKILL, sigkill_handler);
    signal(SIGHUP, sighup_handler);
```

Procesul se copiaza in procesul client cu ajutorul instructiunii "fork" dupa care verifica succesul operatiei

```c
    pid_t pid = fork();
    if (pid < 0) {
        syslog(LOG_ERR, "Error forking");
        exit(EXIT_FAILURE);
    }
```

Daca pid > 0 inseamna ca procesul copil a inceput sa functioneze - e timpul sa scapam de procesul parinte. Acesta inchide logul si se opreste.

```c
    if (pid > 0) {
        syslog(LOG_INFO, "Daemon PID: %d", pid);
        closelog();
        exit(EXIT_SUCCESS);
    }

```

`umask(0);` este folosit pentru a seta masca de creare a modului de fișiere la zero. Această mască afectează permisiunile implicite ale fișierelor și directoarelor nou-create. Prin setarea la zero, se permite procesului daemon să aibă control complet asupra permisiunilor fișierelor pe care le creează.

```c

    // Child process (daemon)
    umask(0); // Unmask the file mode
```

Programul copil creaza o noua sesiune (un nou grup de procese). Sunt situatii in care o noua sesiune nu este necesara si programul poate prelua grupul parintelui cu ajutorul instructiunii `setpgrp()`. 

```c
    // Create a new session and become the leader of the session
    if (setsid() == -1) {
        syslog(LOG_ERR, "Error creating session");
        exit(EXIT_FAILURE);
    }
```

Urmatoarele instructiuni continua detasarea (daemonizarea) procesului. Se modifica directorul curent cu / (pentrum a detasa procesul de directorul sau de lucru), se inchid file descriptorii deschisi (aici doar STDIN, STDOUT, STDERR). Numerele acestor file-descriptors se pot prlua din macro-urile STDIN_FILENO STDOUT_FILENO, STDERR_FILENO definite in unistd.h. 


```c
    // Change the current working directory to root
    if (chdir("/") == -1) {
        syslog(LOG_ERR, "Error changing directory");
        exit(EXIT_FAILURE);
    }

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
```

Urmatoarele instructiuni au efectul de a redirecta toti file descriptorii catre /dev/null

```c
    // Redirect standard file descriptors to /dev/null
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_WRONLY);
    open("/dev/null", O_RDWR);
```

Bucla while urmatoare reprezinta ansamblul de operatii pe care programuyl le executa in timp ce ruleaza. In mod normal, aceasta bucla este semnificativ mai consistenta. 

```c
    // Main daemon logic
    while (1) {
        syslog(LOG_INFO, "Daemon is active.");
        sleep(LOG_INTERVAL);
    }

    return 0;
}

```