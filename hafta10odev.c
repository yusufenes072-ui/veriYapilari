#include <stdio.h>

#define N 5

int graf[N][N] = {
    {0, 1, 0, 1, 0},
    {1, 0, 1, 0, 1},
    {0, 1, 0, 0, 0},
    {1, 0, 0, 0, 1},
    {0, 1, 0, 1, 0}
};

int ziyaret[N] = {0};

char sehirler[N] = {'A', 'B', 'C', 'D', 'E'};

void BFS(int baslangic) {
    int kuyruk[N];
    int on = 0, arka = 0;

    ziyaret[baslangic] = 1;
    kuyruk[arka++] = baslangic;

    printf("BFS Dolasimi: ");

    while (on < arka) {
        int dugum = kuyruk[on++];

        printf("%c ", sehirler[dugum]);

        for (int i = 0; i < N; i++) {
            if (graf[dugum][i] == 1 && ziyaret[i] == 0) {
                ziyaret[i] = 1;
                kuyruk[arka++] = i;
            }
        }
    }

    printf("\n");
}

void DFS(int dugum) {
    ziyaret[dugum] = 1;

    printf("%c ", sehirler[dugum]);

    for (int i = 0; i < N; i++) {
        if (graf[dugum][i] == 1 && ziyaret[i] == 0) {
            DFS(i);
        }
    }
}

int main() {

    printf("BFS Algoritmasi:\n");
    BFS(0);

    for (int i = 0; i < N; i++) {
        ziyaret[i] = 0;
    }

    printf("\nDFS Algoritmasi:\n");
    DFS(0);

    printf("\n");

    return 0;
}
