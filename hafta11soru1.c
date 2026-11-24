
#include <stdio.h>

#define N 6

int matris[N][N] = {0};

// Kenar ekleme fonksiyonu
void kenarEkle(int a, int b) {
    matris[a-1][b-1] = 1;
    matris[b-1][a-1] = 1;
}

// Komþuluk matrisini yazdýrma
void matrisiYazdir() {
    int i, j;

    printf("\nKomþuluk Matrisi:\n");

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", matris[i][j]);
        }
        printf("\n");
    }
}

// Düðüm derecelerini hesaplama
void dereceHesapla() {
    int i, j, derece, toplam = 0;

    printf("\nDugum Dereceleri:\n");

    for (i = 0; i < N; i++) {
        derece = 0;

        for (j = 0; j < N; j++) {
            derece += matris[i][j];
        }

        printf("%d. dugumun derecesi: %d\n",
               i + 1, derece);

        toplam += derece;
    }

    printf("Grafin genel derecesi: %d\n", toplam);
    printf("Ortalama dugum derecesi: %.2f\n",
           (float)toplam / N);
}

// Bipartite kontrolü (BFS)
int bipartiteKontrol() {
    int renk[N];

    int kuyruk[N];
    int bas = 0, son = 0;

    int i, j, u;

    for (i = 0; i < N; i++) {
        renk[i] = -1;
    }

    renk[0] = 0;
    kuyruk[son++] = 0;

    while (bas < son) {
        u = kuyruk[bas++];

        for (j = 0; j < N; j++) {

            if (matris[u][j] == 1) {

                if (renk[j] == -1) {
                    renk[j] = 1 - renk[u];
                    kuyruk[son++] = j;
                }

                else if (renk[j] == renk[u]) {
                    return 0;
                }
            }
        }
    }

    printf("\nDugumlerin Renkleri:\n");

    for (i = 0; i < N; i++) {
        printf("%d. dugum: %s\n",
               i + 1,
               renk[i] == 0 ? "Mavi (0)" : "Kirmizi (1)");
    }

    return 1;
}

int main() {

    // Baþlangýç kenarlarý
    kenarEkle(1, 2);
    kenarEkle(1, 4);
    kenarEkle(2, 3);
    kenarEkle(3, 4);
    kenarEkle(3, 6);
    kenarEkle(4, 5);
    kenarEkle(5, 6);

    printf("ILK GRAF\n");

    matrisiYazdir();
    dereceHesapla();

    if (bipartiteKontrol()) {
        printf("\nGraf BIPARTITE (Iki Parcali).\n");
    }
    else {
        printf("\nGraf BIPARTITE DEGILDIR.\n");
    }

    // Dinamik test: (2,4) kenarýný ekleme
    printf("\n\nDINAMIK TEST\n");

    printf("(2,4) kenari ekleniyor...\n");

    kenarEkle(2, 4);

    matrisiYazdir();
    dereceHesapla();

    if (bipartiteKontrol()) {
        printf("\nGraf BIPARTITE (Iki Parcali).\n");
    }
    else {
        printf("\nGraf BIPARTITE DEGILDIR.\n");
    }

    return 0;
}

