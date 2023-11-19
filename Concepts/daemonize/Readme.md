# Daemonize

Scurt program care demonstreaza tehnicile necesare pentru a transforma un program intr-un daemon. 

Un program de tip daemon este un program care ruleaza fara sa fie sub controlul utilizatorului. Se mai numesc si "background processes". Un sinonim din lumea Windows pentru astfel de procese este serviciu (service). 

Aceste programe sunt lansate din consola ca orice alt program si inainte de a incepe actiunea proprie, trebuie sa treaca printr-o succesiune obligatorie de pasi care il vor transforma in daemon. Acestia sunt demonstrati in programul daemon_example. Pe scurt: 

- procesul se copiaza pe el insusi intr-un alt proces identic (`fork()`)
 - procesul parinte dispare
 - procesul copil executa o serie de operatii necesare pentru detasarea completa

Optional, procesul poate scrie informatii utile intr-un jurnal de sistem sau intr-un fisier (consola nu mai este disponibila). 