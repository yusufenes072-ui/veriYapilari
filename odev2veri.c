#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
    char text[50];
    struct Word* next;
} Word;


void pushWord(Word** top, char* text) {
    Word* newWord = (Word*)malloc(sizeof(Word));

    if (newWord == NULL) {
        printf("Bellek ayrilamadi!\n");
        return;
    }

    strcpy(newWord->text, text);

    newWord->next = *top;
    *top = newWord;

    printf("Eklendi: %s\n", text);
}

void popWord(Word** top) {

    if (*top == NULL) {
        printf("Geri alinacak kelime yok!\n");
        return;
    }

    Word* temp = *top;

    printf("Geri alindi: %s\n", temp->text);

    *top = (*top)->next;

    free(temp);
}

void showWords(Word* top) {

    if (top == NULL) {
        printf("Liste bos!\n");
        return;
    }

    Word* temp = top;

    printf("Metin: ");

    while (temp != NULL) {
        printf("%s", temp->text);

        if (temp->next != NULL)
            printf(" ");

        temp = temp->next;
    }

    printf("\n");
}

void freeStack(Word** top) {

    while (*top != NULL) {
        Word* temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}


int main() {

    Word* top = NULL;

    int choice;
    char text[50];

    do {

        printf("\n===== UNDO SISTEMI =====\n");
        printf("1. Add\n");
        printf("2. Undo\n");
        printf("3. Show\n");
        printf("0. Cikis\n");
        printf("> ");

        scanf("%d", &choice);
        getchar(); 

        switch (choice) {

            case 1:

                printf("Eklenecek kelime: ");
                scanf("%49s", text);

                pushWord(&top, text);

                break;


            case 2:

                popWord(&top);

                break;


            case 3:

                showWords(top);

                break;


            case 0:

                printf("Programdan cikiliyor...\n");

                break;


            default:

                printf("Gecersiz secim!\n");
        }

    } while (choice != 0);


    freeStack(&top);

    return 0;
}
