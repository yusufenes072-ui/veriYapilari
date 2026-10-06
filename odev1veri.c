#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char name[50];
    struct Song* next;
    struct Song* prev;
} Song;


void addSongToEnd(Song** head, char* name) {
    Song* newSong = (Song*)malloc(sizeof(Song));

    if (newSong == NULL) {
        printf("Bellek ayrilamadi!\n");
        return;
    }

    strcpy(newSong->name, name);

    if (*head == NULL) {
        newSong->next = newSong;
        newSong->prev = newSong;
        *head = newSong;

        printf("'%s' listeye eklendi.\n", name);
        return;
    }

    Song* last = (*head)->prev;

    newSong->next = *head;
    newSong->prev = last;

    last->next = newSong;
    (*head)->prev = newSong;

    printf("'%s' listeye eklendi.\n", name);
}

void removeSong(Song** head, char* name) {
    if (*head == NULL) {
        printf("Liste bos!\n");
        return;
    }

    Song* current = *head;

    do {
        if (strcmp(current->name, name) == 0) {

            if (current->next == current) {
                *head = NULL;
            }
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;

                if (current == *head) {
                    *head = current->next;
                }
            }

            free(current);

            printf("'%s' listeden silindi.\n", name);
            return;
        }

        current = current->next;

    } while (current != *head);

    printf("'%s' listede bulunamadi.\n", name);
}

void playNext(Song** current) {
    if (*current == NULL) {
        printf("Liste bos!\n");
        return;
    }

    *current = (*current)->next;

    printf("Calan sarki: %s\n", (*current)->name);
}

void playPrevious(Song** current) {
    if (*current == NULL) {
        printf("Liste bos!\n");
        return;
    }

    *current = (*current)->prev;

    printf("Calan sarki: %s\n", (*current)->name);
}

void showSongs(Song* head, Song* current) {
    if (head == NULL) {
        printf("Liste bos!\n");
        return;
    }

    Song* temp = head;

    printf("\n--- Sarkilar ---\n");

    do {
        if (temp == current)
            printf(">> %s  [CALANIYOR]\n", temp->name);
        else
            printf("   %s\n", temp->name);

        temp = temp->next;

    } while (temp != head);

    printf("----------------\n");
}

void freeList(Song** head) {
    if (*head == NULL)
        return;

    Song* current = (*head)->next;

    while (current != *head) {
        Song* temp = current;
        current = current->next;
        free(temp);
    }

    free(*head);
    *head = NULL;
}


int main() {
    Song* head = NULL;
    Song* current = NULL;

    int choice;
    char name[50];

    do {
        printf("\n===== MUZIK CALAR =====\n");
        printf("1. Sarki ekle\n");
        printf("2. Sarki sil\n");
        printf("3. Sonraki sarki\n");
        printf("4. Onceki sarki\n");
        printf("5. Sarkilari listele\n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &choice);
        getchar(); // Enter karakterini temizle

        switch (choice) {

            case 1:
                printf("Sarki adi: ");
                fgets(name, sizeof(name), stdin);

                name[strcspn(name, "\n")] = '\0';

                addSongToEnd(&head, name);

                if (current == NULL)
                    current = head;

                break;


            case 2:
                printf("Silinecek sarki: ");
                fgets(name, sizeof(name), stdin);

                name[strcspn(name, "\n")] = '\0';

                if (current != NULL &&
                    strcmp(current->name, name) == 0) {

                    if (current->next == current) {
                        current = NULL;
                    }
                    else {
                        current = current->next;
                    }
                }

                removeSong(&head, name);

                break;


            case 3:
                playNext(&current);
                break;


            case 4:
                playPrevious(&current);
                break;


            case 5:
                showSongs(head, current);
                break;


            case 0:
                printf("Programdan cikiliyor...\n");
                break;


            default:
                printf("Gecersiz secim!\n");
        }

    } while (choice != 0);

    freeList(&head);

    return 0;
}
