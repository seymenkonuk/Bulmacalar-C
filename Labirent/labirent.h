/*
Labirent Çözer
*/
#ifndef LABIRENT_H
#define LABIRENT_H
#define HASSASIYET 1000
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lib/rastgele.h" // https://github.com/seymenkonuk/Rastgele-C commit 1
#include "../lib/imlec.h" // https://github.com/seymenkonuk/Imlec-Kontrol-C commit 1

enum {
    YOL, DUVAR, KONUM, GIDILMEYECEK_YOL
};

void yolGirdisiAl(int genislik, int yukseklik, int platform[yukseklik][genislik]); // Girilen Girdiyi Platforma Yazar
int labirentCoz(int genislik, int yukseklik, int platform[yukseklik][genislik]); // Labirentin En Kýsa Çýkýþ Yolunu Bulur
int yolBul(int genislik, int yukseklik, int platform[yukseklik][genislik]);      // Yol Bulma Algoritmasý

void yolGirdisiAl(int genislik, int yukseklik, int platform[yukseklik][genislik]) {
    int yonler[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};
    system("cls"); int i, j;
    for (i=0; i<genislik+2; i++) printf("%c ", 254);
    for (i=0; i<yukseklik+1; i++) printf("\n%c", 254);
    for (i=0; i<genislik+1; i++) printf(" %c", 254);
    for (i=1; i<yukseklik+1; i++) { gotoxy((genislik+1)*2, i); printf("%c", 254);}
    
    // Platformu Sýfýrla
    for (i=0; i<yukseklik; i++) for (j=0; j<genislik; j++) platform[i][j] = YOL;
    
    // Girdiyi Al
    int konumSayisi = 0, x = 0, y = 0;
    while (1) {
        gotoxy(2*x+2, y+1);
        char tus = getch();
        int yon = -1;
        
        if (tus == 'd' || tus == 'D')
            yon = 0;
        else if (tus == 's' || tus == 'S')
            yon = 1;
        else if (tus == 'a' || tus == 'A')
            yon = 2;
        else if (tus == 'w' || tus == 'W')
            yon = 3;
        else if (tus == YOL + '0') {
            if (platform[y][x] == KONUM) konumSayisi--;
            platform[y][x] = YOL;
            printf("  ");
        }
        else if (tus == DUVAR + '0') {
            if (platform[y][x] == KONUM) konumSayisi--;
            platform[y][x] = DUVAR;
            printf("%c ", 254);
        }
        else if (tus == KONUM+'0' && konumSayisi < 2) {
            if (platform[y][x] == KONUM) konumSayisi--;
            platform[y][x] = KONUM;
            printf("+ ");
            konumSayisi++;
        } else if (tus == '\r' && konumSayisi == 2) {
            gotoxy(0, yukseklik+1);
            return;
        }
        
        if (yon == -1) continue;
        
        int yeni_x = x + yonler[yon][0];
        int yeni_y = y + yonler[yon][1];
        
        if (yeni_x == -1) {
            yeni_x = genislik-1;
            yeni_y--;
        }
        
        if (yeni_x == genislik) {
            yeni_x = 0;
            yeni_y++;
        }
        
        if (yeni_y < 0) continue;
        if (yeni_y >= yukseklik) continue;
        
        x = yeni_x; y = yeni_y;
    }
}

int labirentCoz(int genislik, int yukseklik, int platform[yukseklik][genislik]) {
    int yonler[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    int baslangic_i, baslangic_j;
    int bitis_i, bitis_j;
    void labirentiYazdir(int platform[yukseklik][genislik]) {
        printf("\n\n");
        int i, j;
        for (i=0; i<genislik+2; i++) printf("%c ", 254);
        printf("\n");
        for (i=0; i<yukseklik; i++) {
            printf("%c ", 254);
            for (j=0; j<genislik; j++) {
                if (platform[i][j] == DUVAR) 
                    printf("%c ", 254);
                else if (platform[i][j] == YOL)
                    printf(". ");
                else if (platform[i][j] == GIDILMEYECEK_YOL)
                    printf(". ");
                else 
                    printf("+ ");
            }
            printf("%c\n", 254);
        } 
        for (i=0; i<genislik+2; i++) printf("%c ", 254);
        printf("\n");
    }
    void konumlariBul() {
        int i, j, adet = 0;
        for (i=0; i<yukseklik; i++) {
            for (j=0; j<genislik; j++) {
                if (platform[i][j] == KONUM) {
                    platform[i][j] = YOL;
                    if (adet == 0) {
                        baslangic_i = i;
                        baslangic_j = j;
                        adet = 1;
                    } else {
                        bitis_i = i;
                        bitis_j = j;
                        return;
                    }
                }
            }
        }
        
    }
    int komsuYollariSay(int i, int j, int platform[yukseklik][genislik]) {
        int komsu = 0;
        if (i-1>=0) if (platform[i-1][j] == YOL) komsu++;
        if (i+1<yukseklik) if (platform[i+1][j] == YOL) komsu++;
        if (j-1>=0) if (platform[i][j-1] == YOL) komsu++;
        if (j+1<genislik) if (platform[i][j+1] == YOL) komsu++;
        return komsu;
    }
    int rastgeleArama() {
        int i, j, k;
        int enkisacozum[yukseklik][genislik], enkisacozumadim = yukseklik*genislik+1;
        for (k=0; k<HASSASIYET; k++) {
            // Cozum Bul
            bool cozulduMu = false; int adim = 0;
            int konum_i = baslangic_i, konum_j = baslangic_j;
            
            int kopya[yukseklik][genislik];
            for (i=0; i<yukseklik; i++) for (j=0; j<genislik; j++) kopya[i][j] = platform[i][j];
            kopya[baslangic_i][baslangic_j] = KONUM;
            while (1) {
                if (konum_i == bitis_i && konum_j == bitis_j) {
                    cozulduMu = true;
                    break;
                }
                if (komsuYollariSay(konum_i, konum_j, kopya) == 0) break;
                
                int yeni_i, yeni_j;
                while (1) {
                    int yon = rastgeleAralik(0, 3);
                    yeni_i = konum_i + yonler[yon][0];
                    yeni_j = konum_j + yonler[yon][1];
                    if (yeni_i >= 0 && yeni_i < yukseklik)
                        if (yeni_j >= 0 && yeni_j < genislik)
                            if (kopya[yeni_i][yeni_j] == YOL)
                                break;
                }
                kopya[yeni_i][yeni_j] = KONUM;
                konum_i = yeni_i;
                konum_j = yeni_j;
                adim++;
            }
            
            if (cozulduMu && adim < enkisacozumadim) {
                enkisacozumadim = adim;
                for (i=0; i<yukseklik; i++) for (j=0; j<genislik; j++) enkisacozum[i][j] = kopya[i][j];
            }
        }
        if (enkisacozumadim == yukseklik*genislik+1) {
            platform[baslangic_i][baslangic_j] = KONUM;
            platform[bitis_i][bitis_j] = KONUM;
            return -1;
        }
        for (i=0; i<yukseklik; i++) for (j=0; j<genislik; j++) platform[i][j] = enkisacozum[i][j];
        return enkisacozumadim;
    }
    int duzenliArama() {
        int i, j;
        int enkisacozum[yukseklik][genislik], enkisacozumadim = yukseklik*genislik+1;
        int hareketler[yukseklik*genislik], adim = 0;
        for (i=0; i<yukseklik*genislik; i++) hareketler[i] = 0;
        int konum_i = baslangic_i, konum_j = baslangic_j;
        platform[konum_i][konum_j] = KONUM;
        while (1) {
            hareketler[adim]++;
            // 5 numaralý adým tanýmlý deðil
            if (hareketler[adim] == 5) {
                hareketler[adim] = 0;
                adim--;
                
                if (adim == -1) break;
                
                platform[konum_i][konum_j] = YOL; // O Konumu Sil
                // Eski Konumuna Dön
                konum_i = konum_i - yonler[hareketler[adim]-1][0]; 
                konum_j = konum_j - yonler[hareketler[adim]-1][1];
                continue; 
            }
            
            int yeni_i = konum_i + yonler[hareketler[adim]-1][0]; 
            int yeni_j = konum_j + yonler[hareketler[adim]-1][1];
            
            // Gidilebiliyorsa Oraya Git
            if (yeni_i >= 0 && yeni_i < yukseklik)
                if (yeni_j >= 0 && yeni_j < genislik)
                    if (platform[yeni_i][yeni_j] == YOL) {
                        adim++;
                        konum_i = yeni_i; konum_j = yeni_j;
                        platform[konum_i][konum_j] = KONUM;
                    }
            
            // Labirentin Çýkýþýna Ulaþýldýysa
            if (konum_i == bitis_i && konum_j == bitis_j) {
                
                if (adim < enkisacozumadim) {
                    enkisacozumadim = adim;
                    for (i=0; i<yukseklik; i++) for (j=0; j<genislik; j++) enkisacozum[i][j] = platform[i][j];
                }
                adim--;
                platform[konum_i][konum_j] = YOL; // O Konumu Sil
                // Eski Konumuna Dön
                konum_i = konum_i - yonler[hareketler[adim]-1][0]; 
                konum_j = konum_j - yonler[hareketler[adim]-1][1];
            }
        }
        if (enkisacozumadim == yukseklik*genislik+1) {
            platform[baslangic_i][baslangic_j] = KONUM;
            platform[bitis_i][bitis_j] = KONUM;
            return -1;
        }
        for (i=0; i<yukseklik; i++) for (j=0; j<genislik; j++) platform[i][j] = enkisacozum[i][j];
        return enkisacozumadim;
    }
    void cikmazSokaklariKapat() {
        int i, j; bool bittiMi;
        do {
            bittiMi = true;
            for (i=0; i<yukseklik; i++) {
                for (j=0; j<genislik; j++) {
                    if (platform[i][j] != YOL) continue;
                    if (i == baslangic_i && j == baslangic_j) continue;
                    if (i == bitis_i && j == bitis_j) continue;
                    if (komsuYollariSay(i, j, platform) <= 1) {
                        platform[i][j] = GIDILMEYECEK_YOL;
                        bittiMi = false;
                    }
                }
            }
        } while (!bittiMi);
    }
    konumlariBul();
    cikmazSokaklariKapat();
    int sonuc = duzenliArama();
    if (sonuc != -1) labirentiYazdir(platform);
    else printf("Cozum Bulunamadi!\n");
    return sonuc;
}

int yolBul(int genislik, int yukseklik, int platform[yukseklik][genislik]) {
    int i, j, k;
    int yonler[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    int baslangic_i, baslangic_j;
    int bitis_i, bitis_j;
    bool baslangicBulunduMu = false;
    for (i=0; i<yukseklik; i++) {
        for (j=0; j<genislik; j++) {
            if (platform[i][j] == KONUM) {
                if (baslangicBulunduMu) {
                    bitis_i = i;
                    bitis_j = j;
                } else {
                    platform[i][j] = YOL;
                    baslangic_i = i;
                    baslangic_j = j;
                    baslangicBulunduMu = true;
                }
            }
        }
    }
    
    platform[bitis_i][bitis_j] = -5;
    while (1) {
        for (i=0; i<yukseklik; i++) {
            for (j=0; j<genislik; j++) {
                if (platform[i][j] != YOL) continue;
                for (k=0; k<4; k++) {
                    int yeni_i = i + yonler[k][0];
                    int yeni_j = j + yonler[k][1];
                    if (yeni_i >= 0 && yeni_i < yukseklik)
                        if (yeni_j >= 0 && yeni_j < genislik)
                            if (platform[yeni_i][yeni_j] < 0) {
                                platform[i][j] = -k-1;
                                break;
                            }
                                
                }
            }
        }
        if (platform[baslangic_i][baslangic_j] < 0) break;
    }
    int konum_i = baslangic_i, konum_j = baslangic_j;
    while (1) {
        int yon = -platform[konum_i][konum_j]-1;
        platform[konum_i][konum_j] = KONUM;
        if (konum_i == bitis_i && konum_j == bitis_j) break;
        konum_i = konum_i + yonler[yon][0];
        konum_j = konum_j + yonler[yon][1];
    }
    for (i=0; i<yukseklik; i++)
        for (j=0; j<genislik; j++)
            if (platform[i][j] < 0)
                platform[i][j] = YOL;
    
    printf("\n\n");
    for (i=0; i<genislik+2; i++) printf("%c ", 254);
    printf("\n");
    for (i=0; i<yukseklik; i++) {
        printf("%c ", 254);
        for (j=0; j<genislik; j++) {
            if (platform[i][j] == DUVAR) 
                printf("%c ", 254);
            else if (platform[i][j] == YOL)
                printf(". ");
            else if (platform[i][j] == GIDILMEYECEK_YOL)
                printf(". ");
            else 
                printf("+ ");
        }
        printf("%c\n", 254);
    } 
    for (i=0; i<genislik+2; i++) printf("%c ", 254);
    printf("\n");
}
#endif
