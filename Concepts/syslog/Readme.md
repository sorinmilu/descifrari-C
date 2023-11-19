# Syslog

## Ce este syslog?

Syslog este in primul rand un protocol definit în RFC 3164 (cu o versiune actualizată în RFC 5424) care permite dispozitivelor diferite dintr-o rețea să trimită mesaje de log către un server sau colector centralizat de syslog.

Pe sistemele de operare de tip Unix, "syslog" se referă și la o facilitate de sistem care oferă o modalitate pentru aplicații și procese de sistem să trimită mesaje de log. Aceste mesaje de log sunt, în mod obișnuit, stocate în fișiere centralizat.

În contextul programării și administrării sistemelor, "syslog" este adesea folosit pentru a descrie infrastructura de logging furnizată de sistemul de operare. Aceasta include funcții precum syslog() în limbajul de programare C, care permit aplicațiilor să genereze mesaje de log.

In protocolul syslog, fiecare mesaj este trimit catre o **Facilitate** si este caracterizat de un **Nivel de prioritate**

### Facilitati

Facilitățile reprezintă categorii sau subsisteme care ajută la clasificarea sursei sau a tipului de mesaje de log. Aceastea oferă o modalitate de a identifica originea mesajelor de log, facilitând gestionarea și filtrarea acestora. Fiecare mesaj de log este asociat cu o facilitate specifică, indicând subsistemul sau componenta care a generat mesajul.

Facilitățile syslog sunt reprezentate de constante în antetul <syslog.h> în limbajul de programare C. Iată câteva facilități syslog comune:

<dl>

<dt>LOG_AUTH (Authorization System) - Numerical Value: 4</dt>

<dd>Utilizat pentru mesaje legate de autorizare și securitate, cum ar fi evenimentele de autentificare.</dd>

<dt>LOG_AUTHPRIV (Private Authorization Messages) - Numerical Value: 10</dt>

<dd>Similar cu LOG_AUTH, dar furnizează un flux separat pentru mesaje de autorizare mai sensibile sau private.</dd>

<dt>LOG_CRON (Clock Daemon - cron) - Numerical Value: 9</dt>

<dd>Utilizat pentru mesaje generate de daemonul cron.</dd>

<dt>LOG_DAEMON (System Daemons) - Numerical Value: 3</dt>

<dd>Utilizat pentru mesaje de la daemoni de sistem care nu au valori separate ale facilității.</dd>

<dt>LOG_KERN (Kernel) - Numerical Value: 0</dt>

<dd>Utilizat pentru mesaje de la nucleul sistemului de operare</dd>

<dt>LOG_LPR (Line Printer) - Numerical Value: 6</dt>

<dd>Mesaje legate de printing</dd>

<dt>LOG_MAIL (Mail System) - Numerical Value: 2</dt>

<dd>Mesaje legate de sistemul de transport al e-mailului</dd>

<dt>LOG_SYSLOG (Internal Syslog Messages) - Numerical Value: 5</dt>

<dd>Mesaje legate de systemul de log in sine</dd>

<dt>LOG_USER (User-Level Messages) - Numerical Value: 1</dt>

<dd>Alte mesaje provenite de la programe care ruleaza in userspace</dd>

<dt>LOG_LOCAL0 to LOG_LOCAL7 (Local Use) - Numerical Values: 16 to 23</dt>

<dd>Rezervate pentru utilizare locală, permitând aplicațiilor sau utilizatorilor să definească propriile facilități.V
</dl>


### Prioritati

În cadrul sistemului de logging, nivelurile de prioritate (log levels) sunt utilizate pentru a clasifica mesajele de log în funcție de gravitatea și importanța acestora. Iată o descriere a nivelurilor de log în limba română:

<dl>
<dt>Emergency (LOG_EMERG):</dt>

<dd>Mesaje de acest nivel indică o stare critică a sistemului, care necesită intervenție imediată. De obicei, acestea sunt evenimente care pot duce la nefuncționarea majoră a sistemului.</dd>

<dt>Alert (LOG_ALERT):</dt>

<dd> Mesaje care indică o condiție care trebuie tratată imediat. Similar cu nivelul de urgență, dar poate fi utilizat pentru situații în care intervenția este necesară, dar nu imediată.</dd>

<dt>Critical (LOG_CRIT):</dt>

<dd> Mesaje care semnalează o situație critică, care necesită atenție imediată. Acestea indică o problemă semnificativă care afectează funcționarea normală a sistemului.</dd>

<dt>Error (LOG_ERR):</dt>

<dd> Mesaje care indică o eroare în execuția unei operații sau a unei aplicații. Acestea semnalează o condiție care necesită corectare, dar care nu este critică pentru funcționarea generală a sistemului.</dd>

<dt>Warning (LOG_WARNING):</dt>

<dd> Mesaje care semnalează o condiție potențial problematică sau avertizează asupra unui comportament neașteptat. Acestea nu sunt erori, dar indică situații care ar putea duce la probleme ulterioare.</dd>

<dt>Notice (LOG_NOTICE):</dt>

<dd> Mesaje care furnizează informații de notificare sau de interes general. Acestea sunt de obicei utilizate pentru a raporta evenimente normale sau stări de funcționare a sistemului.</dd>

<dt>Info (LOG_INFO):</dt>

<dd> Mesaje de informație generală despre activitatea sistemului. Acestea pot include detalii despre operațiile normale și starea generală a aplicațiilor.</dd>

<dt>Debug (LOG_DEBUG):</dt>

<dd> Mesaje de diagnosticare și depanare utilizate în timpul dezvoltării sau a depanării aplicațiilor. Acestea furnizează informații detaliate care ajută la identificarea și rezolvarea problemelor.</dd>
</dl>

Folosirea corespunzătoare a nivelurilor de log este importantă pentru a facilita monitorizarea, depanarea și gestionarea sistemelor și aplicațiilor. Fiecare nivel are un scop specific în comunicarea evenimentelor și stărilor sistemului.

Sistemele linux moderne folosesc **systemd-journald** pe post de facilitate centralizata de logging. 

## Programul syslog.c

Scurt program care demonstreaza interactiunea cu jurnalele de sistem, prin intermediul bibliotecii syslog.h. Programul porneste, initializeaza si utilizeaza biblioteca syslog pentru a trimite mesaje in locul sistemului de operare

Openlog initializeaza o serie de variabile globale definite in syslog.c care vor fi utilizate mai tarziu de celelalte functii din syslog pentru a trimite mesaje. "log_example" de pilda reprezinta numele programului care va aparea in fiecare linie de log. LOG_PID este un flag care determina aparitia id-ului de proces in toate liniile din log, LOG_NDELAY este de asemenea un flag 

```c
    openlog("log_example", LOG_PID | LOG_NDELAY, LOG_USER);
```

Transmiterea diferitelor mesaje, cu diferite prioritati. Fiecare mesaj transmis implica deschiderea unei conexiuni catre demonul care se ocupa de protocolul syslog. 

```c
    syslog(LOG_INFO, "This is an informational message.");
    syslog(LOG_WARNING, "This is a warning message.");
    syslog(LOG_ERR, "This is an error message.");
```

Setlogtmask modifica nivelul de prioritate incepand de la care mesajele catre syslog vor fi logate. 

```c
    // Change logging priority dynamically
    setlogmask(LOG_UPTO(LOG_WARNING));  // Log messages up to warning level

```

Mai multe mesaje trimise

```c
    // Log messages after changing priority
    syslog(LOG_INFO, "This message should not be logged.");
    syslog(LOG_WARNING, "This is another warning message.");

```

Closelog curata o serie de resurse care au fost alocate la openlog

```c

    closelog();
    return 0;
}


```