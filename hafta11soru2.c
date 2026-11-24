
#include <stdio.h>

#define N 6
#define INF 999999

char dugumler[N] = {'A', 'B', 'C', 'D', 'E', 'F'};

int graf[N][N] = {
    {0,   7,   5,   INF, INF, 1},
    {7,   0,   1,   1,   3,   INF},
    {5,   1,   0,   2,   1,   INF},
    {INF, 1,   2,   0,   INF, 7},
    {INF, 3,   1,   INF, 0,   2},
    {1,   INF, INF, 7,   2,   0}
};

// Dijkstra algoritmasi
void dijkstra(int baslangic, int mesafe[], int onceki[]) {

    int ziyaret[N] = {0};
    int i, j, min, u;

    for (i = 0; i < N; i++) {
        mesafe[i] = INF;
        onceki[i] = -1;
    }

    mesafe[baslangic] = 0;

    for (i = 0; i < N; i++) {

        min = INF;
        u = -1;

        // En dusuk mesafeli dugumu bul
        for (j = 0; j < N; j++) {
            if (!ziyaret[j] && mesafe[j] < min) {
                min = mesafe[j];
                u = j;
            }
        }

        if (u == -1)
            break;

        ziyaret[u] = 1;

        // Komsu dugumlerin mesafelerini guncelle
        for (j = 0; j < N; j++) {

            if (!ziyaret[j] && graf[u][j] != INF &&
                graf[u][j] != 0) {

                if (mesafe[u] + graf[u][j] < mesafe[j]) {

                    mesafe[j] = mesafe[u] + graf[u][j];
                    onceki[j] = u;
                }
            }
        }
    }
}

// En kisa yolu yazdirma
void yolYazdir(int hedef, int onceki[]) {

    int yol[N];
    int sayac = 0;
    int i;

    while (hedef != -1) {
        yol[sayac++] = hedef;
        hedef = onceki[hedef];
    }

    for (i = sayac - 1; i >= 0; i--) {
        printf("%c", dugumler[yol[i]]);

        if (i > 0)
            printf(" -> ");
    }
}

int main() {

    int mesafe[N];
    int onceki[N];

    int i, j;
    int toplam;
    int enMerkezi = 0;
    int enDusuk = INF;

    // GOREV 1 VE 2
    printf("DIJKSTRA - EN KISA YOL ANALIZI\n");

    dijkstra(0, mesafe, onceki);

    printf("\nA Dugumunden En Kisa Yollar:\n");

    // B ve D dugumlerine giden yollar
    int hedefler[] = {1, 3};

    for (i = 0; i < 2; i++) {

        j = hedefler[i];

        printf("\nA -> %c\n", dugumler[j]);

        printf("Yol: ");
        yolYazdir(j, onceki);

        printf("\nToplam Maliyet: %d\n", mesafe[j]);
    }

    // GOREV 3
    printf("\n\nMERKEZI DUGUM ANALIZI\n");

    for (i = 0; i < N; i++) {

        dijkstra(i, mesafe, onceki);

        toplam = 0;

        printf("\nBaslangic Dugumu: %c\n", dugumler[i]);

        for (j = 0; j < N; j++) {

            toplam += mesafe[j];

            printf("%c Dugumune Mesafe: %d\n",
                   dugumler[j], mesafe[j]);
        }

        printf("Toplam Yol Maliyeti: %d\n", toplam);

        if (toplam < enDusuk) {
            enDusuk = toplam;
            enMerkezi = i;
        }
    }

    // En dusuk toplam maliyete sahip dugumleri bul
    printf("\nEN MERKEZI DUGUM(LER):\n");

    for (i = 0; i < N; i++) {

        dijkstra(i, mesafe, onceki);

        toplam = 0;

        for (j = 0; j < N; j++) {
            toplam += mesafe[j];
        }

        if (toplam == enDusuk) {
            printf("%c Dugumu - Toplam Maliyet: %d\n",
                   dugumler[i], toplam);
        }
    }

    printf("\nAnaliz tamamlandi.\n");

    return 0;
}



//SONUÇ AÇIKLAMA:

/*Bu çalýþmada C programlama dili kullanýlarak Dijkstra algoritmasý uygulanmýþtýr. Öncelikle 6 düðümden oluþan aðýrlýklý ve yönsüz grafýn komþuluk matrisi oluþturulmuþtur.

Dijkstra algoritmasý kullanýlarak A düðümünden diðer düðümlere ulaþan en kýsa yollar hesaplanmýþtýr. A düðümünden B düðümüne en kýsa yol A-F-E-C-B olup maliyeti 5'tir. A düðümünden D düðümüne en kýsa yol ise A-F-E-C-D olup maliyeti 6'dýr.

Son olarak bütün düðümler baþlangýç noktasý kabul edilerek toplam en kýsa yol maliyetleri hesaplanmýþtýr. Yapýlan analiz sonucunda C ve E düðümlerinin 11 toplam maliyetle aðýn en merkezi düðümleri olduðu belirlenmiþtir.

Sonuç olarak Dijkstra algoritmasý kullanýlarak en düþük maliyetli rotalar ve aðýn merkezi düðümleri baþarýyla tespit edilmiþtir.
