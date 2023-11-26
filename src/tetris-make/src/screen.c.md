


# Functii

## Main

Functia main este foarte redusa, initializeaza seedul numerelor aleatoare, initializeaza scorul, porneste bucla principala care va rula continuu pana la finalul programului

```c
int main(void) {
	srand((unsigned) time(NULL));
	init_score();
	start_new_game();
	main_loop();
}

```

