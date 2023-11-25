
# init_score

init_score 

```c
void init_score(void) {
```
snprintf este o fucntie care functioneaza similar cu printf dar in loc sa trimita rezultatul la consola, il stocheaza in bufferul catre care trimite pointerul din primul argument (in cazul asta score_filename). Aici se decide numele fisierului in care se va stoca scorul. 

```c
	snprintf(score_filename, sizeof score_filename, "%s/.tetris_score", getenv("HOME"));
```
In continuare se apeleaza functia load_score urmata de inregistrarea unui handler suplimentar pentru atexit, si anume funtia save_score. 

```c
	load_score();
	atexit(save_score);
}
```

# load_score

Incarca scorul dintr-un fisier text care este definit in functia init_score

```c

static void load_score(void) {
```

Declara file handle-ul pentru a deschide fisierul

```c
	FILE *score_fp;
```
Incearca deschiderea fisierului si testeaza valoarea returnata de functia fopen. Daca valoarea returnata este 0 (adevarat) atunci citeste din fisier continutul variabilei high_score si apoi il inchide folosind functia fclose. In cazul in care valoarea returnata nu este 0, deschiderea fisierului a esuat si se imprima o eroare la standard error. 


```c
	if ((score_fp = fopen(score_filename, "r"))) {
		if (fscanf(score_fp, "%d", &high_score) != 1)
			high_score = 0;
		fclose(score_fp);
	} else {
		/* open fail for other reason than non existing file */
		if (errno != ENOENT)
			perror("error opening high score file in read mode");
	}
}
```

# save_score

```c
static void save_score(void) {
```

Declara file handle-ul pentru a deschide fisierul

```c
	FILE *score_fp;
```

Incearca deschiderea fisierului si testeaza valoarea returnata de functia fopen. Daca valoarea returnata este 0 (adevarat) atunci scrie in fisier continutul variabilei high_score si apoi il inchide folosind functia fclose. In cazul in care valoarea returnata nu este 0, deschiderea fisierului a esuat si se imprima o eroare la standard error. 

```c
	if ((score_fp = fopen(score_filename, "w"))) {
		fprintf(score_fp, "%d\n", high_score);
		fclose(score_fp);
	} else {
		perror("error opening high score file in write mode");
	}
}

```