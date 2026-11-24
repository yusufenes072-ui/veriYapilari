
#include <stdio.h>

#define N 6
#define O 4

char dersler[N] = {'d0', 'd1', 'd2', 'd3', 'd4', 'd5'};

int ogrenciler[O][N] = {
    {1, 1, 0, 0, 1, 0},
    {1, 0, 1, 0, 1, 0},
    {0, 0, 1, 1, 0, 1},
    {0, 0, 0, 1, 1, 1}
};

int graf[N][N];

void grafOlustur() {
    int i, j, k;

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            graf[i][j] = 0;

    for (i = 0; i < O; i++) {
        for (j = 0; j < N; j++) {
            if (ogrenciler[i][j] == 1) {
                for (k = j + 1; k < N; k++) {
                    if (ogrenciler[i][k] == 1) {
                        graf[j][k] = 1;
                        graf[k][j] = 1;
                    }
                }
            }
        }
    }
}

void grafYazdir() {
    int i, j;

    printf("\nKomsuluk Matrisi:\n");

    printf("   ");
    for (i = 0; i < N; i++)
        printf("%c  ", dersler[i]);

    printf("\n");

    for (i = 0; i < N; i++) {
        printf("%c  ", dersler[i]);

        for (j = 0; j < N; j++)
            printf("%d  ", graf[i][j]);

        printf("\n");
    }
}

void welchPowell() {
    int derece[N], sira[N], renk[N];
    int i, j, k, temp;
    int renkSayisi = 0;

    for (i = 0; i < N; i++) {
        derece[i] = 0;
        sira[i] = i;
        renk[i] = 0;

        for (j = 0; j < N; j++)
            derece[i] += graf[i][j];
    }

    for (i = 0; i < N - 1; i++) {
        for (j = i + 1; j < N; j++) {
            if (derece[sira[i]] < derece[sira[j]]) {
                temp = sira[i];
                sira[i] = sira[j];
                sira[j] = temp;
            }
        }
    }

    printf("\nDugum Dereceleri:\n");

    for (i = 0; i < N; i++)
        printf("%c: %d\n", dersler[i], derece[i]);

    printf("\nDereceye Gore Siralama:\n");

    for (i = 0; i < N; i++)
        printf("%c ", dersler[sira[i]]);

    printf("\n\nWelch-Powell Renklendirmesi:\n");

    for (i = 0; i < N; i++) {
        if (renk[sira[i]] == 0) {
            renkSayisi++;
            renk[sira[i]] = renkSayisi;

            for (j = i + 1; j < N; j++) {
                int dugum = sira[j];
                int uygun = 1;

                if (renk[dugum] == 0) {
                    for (k = 0; k < N; k++) {
                        if (renk[k] == renkSayisi &&
                            graf[dugum][k] == 1) {
                            uygun = 0;
                            break;
                        }
                    }

                    if (uygun)
                        renk[dugum] = renkSayisi;
                }
            }
        }
    }

    for (i = 1; i <= renkSayisi; i++) {
        printf("\nSinav %d: ", i);

        for (j = 0; j < N; j++) {
            if (renk[j] == i)
                printf("%c ", dersler[j]);
        }
    }

    printf("\n\nMinimum Sinav Oturumu: %d\n", renkSayisi);
}

int main() {

    printf("ILK SINAV TAKVIMI\n");

    grafOlustur();
    grafYazdir();
    welchPowell();

    printf("\n\nDINAMIK GUNCELLEME\n");

    ogrenciler[3][4] = 0;

    printf("Ogrenci-4 d4 dersini birakti.\n");

    grafOlustur();
    grafYazdir();
    welchPowell();

    return 0;
}

