#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char ad[50];
    char durum[20];
} Hasta;

/* KUYRUK (QUEUE) */
Hasta kuyruk[MAX];
int on = 0, arka = 0;

int kuyrukBosMu() {
    return on == arka;
}

int kuyrukDoluMu() {
    return arka == MAX;
}

void enqueue(Hasta h) {
    if (kuyrukDoluMu()) {
        printf("Kuyruk dolu!\n");
        return;
    }

    strcpy(h.durum, "bekliyor");
    kuyruk[arka++] = h;
    printf("%s kuyruga eklendi.\n", h.ad);
}
int i;
Hasta dequeue() {
    Hasta bos = {0, "", ""};

    if (kuyrukBosMu()) {
        printf("Kuyruk bos!\n");
        return bos;
    }

    return kuyruk[on++];
}

void kuyrukListele() {
    if (kuyrukBosMu()) {
        printf("Bekleyen hasta yok.\n");
        return;
    }

    printf("\n--- Bekleyen Hastalar ---\n");
    for (i = on; i < arka; i++) {
        printf("ID: %d | Ad: %s | Durum: %s\n",
               kuyruk[i].id,
               kuyruk[i].ad,
               kuyruk[i].durum);
    }
}

/* YIGIN (STACK) */
Hasta yigin[MAX];
int ust = -1;

int yiginBosMu() {
    return ust == -1;
}

int yiginDoluMu() {
    return ust == MAX - 1;
}

void push(Hasta h) {
    if (yiginDoluMu()) {
        printf("Yigin dolu!\n");
        return;
    }

    strcpy(h.durum, "muayenede");
    yigin[++ust] = h;
    printf("%s muayeneye alindi.\n", h.ad);
}

Hasta pop() {
    Hasta bos = {0, "", ""};

    if (yiginBosMu()) {
        printf("Muayene yigini bos!\n");
        return bos;
    }

    return yigin[ust--];
}

void yiginListele() {
    if (yiginBosMu()) {
        printf("Muayenedeki hasta yok.\n");
        return;
    }

    printf("\n--- Muayenedeki Hastalar ---\n");
    for (i = ust; i >= 0; i--) {
        printf("ID: %d | Ad: %s | Durum: %s\n",
               yigin[i].id,
               yigin[i].ad,
               yigin[i].durum);
    }
}

/* BAGLI LISTE (TAMAMLANAN HASTALAR) */
typedef struct Dugum {
    Hasta hasta;
    struct Dugum *sonraki;
} Dugum;

Dugum *bas = NULL;
Dugum *son = NULL;

void gecmiseEkle(Hasta h) {
    Dugum *yeni = malloc(sizeof(Dugum));

    if (yeni == NULL) {
        printf("Bellek ayrilamadi!\n");
        return;
    }

    strcpy(h.durum, "tamamlandi");
    yeni->hasta = h;
    yeni->sonraki = NULL;

    if (bas == NULL) {
        bas = son = yeni;
    } else {
        son->sonraki = yeni;
        son = yeni;
    }

    printf("%s muayeneyi tamamladi.\n", h.ad);
}

void gecmisListele() {
    Dugum *gecici = bas;

    if (gecici == NULL) {
        printf("Tamamlanan hasta kaydi yok.\n");
        return;
    }

    printf("\n--- Tamamlanan Hastalar ---\n");

    while (gecici != NULL) {
        printf("ID: %d | Ad: %s | Durum: %s\n",
               gecici->hasta.id,
               gecici->hasta.ad,
               gecici->hasta.durum);

        gecici = gecici->sonraki;
    }
}

/* HASTANE ISLEMLERI */
void muayeneyeAl() {
    if (kuyrukBosMu()) {
        printf("Bekleyen hasta bulunmuyor!\n");
        return;
    }

    if (yiginDoluMu()) {
        printf("Muayene yigini dolu!\n");
        return;
    }

    Hasta h = dequeue();
    push(h);
}

void muayeneyiTamamla() {
    if (yiginBosMu()) {
        printf("Muayenede hasta bulunmuyor!\n");
        return;
    }

    Hasta h = pop();
    gecmiseEkle(h);
}

void bellekTemizle() {
    Dugum *gecici = bas;

    while (gecici != NULL) {
        Dugum *sil = gecici;
        gecici = gecici->sonraki;
        free(sil);
    }

    bas = son = NULL;
}

int main() {
    int secim;
    int sonrakiID = 1;
    Hasta h;

    do {
        printf("\n===== HASTANE HASTA TAKIP SISTEMI =====\n");
        printf("1. Yeni hasta kaydet\n");
        printf("2. Hastayi muayeneye al\n");
        printf("3. Muayeneyi tamamla\n");
        printf("4. Bekleyen hastalari listele\n");
        printf("5. Muayenedeki hastalari listele\n");
        printf("6. Tamamlanan hastalari listele\n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");

        if (scanf("%d", &secim) != 1) {
            printf("Gecersiz giris!\n");
            break;
        }

        switch (secim) {
            case 1:
                if (kuyrukDoluMu()) {
                    printf("Kuyruk dolu!\n");
                    break;
                }

                h.id = sonrakiID++;

                printf("Hasta adi: ");
                scanf(" %49[^\n]", h.ad);

                strcpy(h.durum, "bekliyor");
                enqueue(h);
                break;

            case 2:
                muayeneyeAl();
                break;

            case 3:
                muayeneyiTamamla();
                break;

            case 4:
                kuyrukListele();
                break;

            case 5:
                yiginListele();
                break;

            case 6:
                gecmisListele();
                break;

            case 0:
                printf("Program sonlandiriliyor.\n");
                break;

            default:
                printf("Hatali secim!\n");
        }

    } while (secim != 0);

    bellekTemizle();
    return 0;
}
