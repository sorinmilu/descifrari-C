#include <stdio.h>
#include <ctype.h>


int main() {
    char buffer[500];
    FILE *fisier = fopen("input1.txt", "r");
    int sum = 0;
    if (fisier == NULL){
        fprintf(stderr, "Fisierul nu a fost gasit.");
        return 1;
    }
    while (fscanf(fisier, "%s", buffer)==1){
        int p=-1;
        int u=-1;

        for (int i=0; buffer[i]!='\0'; i++ ){
            if (isdigit(buffer[i])){
                //printf("%d ;", buffer[i]-'0');
                if (p==-1){
                    p = buffer[i]-'0';
                }
                u = buffer[i]-'0';
            }
        }
        sum = sum + (p*10+u);
        //printf("selectate: %d %d", p, u);
        //printf(" \n");

    }
    printf("Totalul este: %d", sum);
    fclose(fisier);
    return 0;
}
