/*
Apartmanlar Bulmacalarýnýn Çözümünü Gösterir
*/

#ifndef APARTMANLAR_H
#define APARTMANLAR_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lib/tahta.h"

void girdiAlApartmanlarBulmacasi(int boyut, int ust[boyut], int sag[boyut], int alt[boyut], int sol[boyut], int platform[boyut][boyut]);
int cozApartmanlarBulmacasi(int boyut, int ust[boyut], int sag[boyut], int alt[boyut], int sol[boyut], int platform[boyut][boyut], bool tumCozumlerMi);

void girdiAlApartmanlarBulmacasi(int boyut, int ust[boyut], int sag[boyut], int alt[boyut], int sol[boyut], int platform[boyut][boyut]) {
    int i, j;
    // Tahta Oluþtur ve Köþeleri Sil
    tahtaOlustur(boyut+2, boyut+2, 2);
    gotoxy(0,0); printf("   ");
    gotoxy(0,1); printf(" ");
    gotoxy((boyut+2)*4-2,0); printf("   ");
    gotoxy((boyut+2)*4, 1); printf(" ");
    gotoxy(0, (boyut+2)*2); printf("   ");
    gotoxy(0, (boyut+2)*2-1); printf(" ");
    gotoxy((boyut+2)*4-2, (boyut+2)*2); printf("   ");
    gotoxy((boyut+2)*4, (boyut+2)*2-1); printf("   ");
    tahtaGit(2,1);
    
    // Girdiyi Sýfýrla
    for (i=0; i<boyut; i++) ust[i] = 0;
    for (i=0; i<boyut; i++) sag[i] = 0;
    for (i=0; i<boyut; i++) alt[i] = 0;
    for (i=0; i<boyut; i++) sol[i] = 0;
    for (i=0; i<boyut; i++) for (j=0; j<boyut; j++) platform[i][j] = 0;
    
    // Girdiyi Al
    while (1) {
        char tus = getch();
        bool hata = false; // Hareket Sonucunda Köþelere Mi Gidiyor
        
        if (tus == 'w' || tus == 'W') {
            if  (konumy == 2 && (konumx == 1 || konumx == boyut+2))
                hata = true;
        } else if (tus == 'a' || tus == 'A') {
            if  (konumx == 2 && (konumy == 1 || konumy == boyut+2))
                hata = true;
        } else if (tus == 's' || tus == 'S') {
            if  (konumy == boyut+1 && (konumx == 1 || konumx == boyut+2))
                hata = true;
        } else if (tus == 'd' || tus == 'D') {
            if  (konumx == boyut+1 && (konumy == 1 || konumy == boyut+2))
                hata = true;
        } else if (tus == '\r') {
            gotoxy(0, (boyut+2)*2+1);
            return;
        } else if (tus >= '0' && tus <= '9') {
            if (tus == '0')
                printf(" ");
            else
                printf("%c", tus);
            if (konumx == 1) {
                sol[konumy-2] = tus - '0';
            } else if (konumx == boyut+2) {
                sag[konumy-2] = tus - '0';
            } else if (konumy == 1) {
                ust[konumx-2] = tus - '0';
            } else if (konumy == boyut+2) {
                alt[konumx-2] = tus - '0';
            } else {
                platform[konumy-2][konumx-2] = tus - '0';
            }
        }
        
        if (!hata) tahtaKontrol(tus, 0);
    }
}

int cozApartmanlarBulmacasi(int boyut, int ust[boyut], int sag[boyut], int alt[boyut], int sol[boyut], int platform[boyut][boyut], bool tumCozumlerMi) {
    int i, j, m, n, sonuc = 0;
    // Tahtayý Oluþtur ve Sýfýrla
    int tahta[boyut][boyut]; 
    for (i=0; i<boyut; i++) 
        for (j=0; j<boyut; j++) 
                tahta[i][j] = platform[i][j];
    
    // Hile Kontrolü
    for (i=0; i<boyut; i++)
        for (j=0; j<boyut; j++) {
            if (platform[i][j] == 0) continue;
            for (m=j+1; m<boyut; m++)
                if (platform[i][j] == platform[i][m]) {
                    printf("Hatali Girdi Girdin!"); return -2;
                }
        }
    for (j=0; j<boyut; j++)
        for (i=0; i<boyut; i++) {
            if (platform[i][j] == 0) continue;
            for (m=i+1; m<boyut; m++)
                if (platform[i][j] == platform[m][j]) {
                    printf("Hatali Girdi Girdin!"); return -2;
                }
        }
    // Verilen Sayýlarda Apartman Gözükebilir Mi Kontrolü de Yapýlabilir
    
    i=0; j=0; int yon = 1;
    while (1) {
        // j Deðeri Geriden Limit Dýþýna Çýktýysa
        if (j==-1) {
            j = boyut-1; i--;
            if (i==-1) {
                // Tüm Ýhtimallere Baktým
                if (sonuc == 0) printf("Cozum Bulunamadi!");
                return sonuc;
            }
        }
        
        // j Deðeri Ýleriden Limit Dýþýna Çýktýysa
        if (j == boyut) {
            j=0; i++;
            if (i==boyut) {
                // Doðru Buldum
                sonuc++;
                
                // Tahta Yoksa Tahta Oluþtur
                if (sonuc == 1) {
                    system("cls");
                    tahtaOlustur(boyut+2, boyut+2, 2);
                    gotoxy(0,0); printf("   ");
                    gotoxy(0,1); printf(" ");
                    gotoxy((boyut+2)*4-2,0); printf("   ");
                    gotoxy((boyut+2)*4, 1); printf(" ");
                    gotoxy(0, (boyut+2)*2); printf("   ");
                    gotoxy(0, (boyut+2)*2-1); printf(" ");
                    gotoxy((boyut+2)*4-2, (boyut+2)*2); printf("   ");
                    gotoxy((boyut+2)*4, (boyut+2)*2-1); printf("   ");
                }
                // Tahtaya Sonucu Doðru Formatta Yaz
                for (m=1; m<=boyut; m++) {
                    for (n=1; n<=boyut; n++) {
                        tahtaGit(n+1, m+1);
                        printf("%d ", tahta[m-1][n-1]);
                    }
                }
                for (m=0; m<boyut; m++) {
                    tahtaGit(m+2, 1);
                    if (ust[m] == 0) continue;
                    printf("%d", ust[m]);
                }
                for (m=0; m<boyut; m++) {
                    tahtaGit(1, m+2);
                    if (sol[m] == 0) continue;
                    printf("%d", sol[m]);
                }
                for (m=0; m<boyut; m++) {
                    tahtaGit(boyut+2, m+2);
                    if (sag[m] == 0) continue;
                    printf("%d", sag[m]);
                }
                for (m=0; m<boyut; m++) {
                    tahtaGit(m+2, boyut+2);
                    if (alt[m] == 0) continue;
                    printf("%d", alt[m]);
                }
                printf("\n\n");
                
                if (!tumCozumlerMi) return -1;
                // Diðer Çözümleri Bulmak için
                getch(); 
                i=boyut-1; j=boyut-1;
                yon = -1; continue;
            }
        }
        
        // O Hücreye Kullanýcý Sayý Girmediyse
        if (platform[i][j] == 0) {
            tahta[i][j]++;
            yon = 1;
        } else {
            j+=yon;
            continue;
        }
        
        // Limit Dýþýna Çýktý
        if (tahta[i][j] > boyut) {
            tahta[i][j] = 0;
            j--;
            yon = -1;
            continue;
        }
        
        // i. Satýrda Ayný Sayý Birden Fazla Kez Kullanýlmýþ Mý
        int dogruMu = 1;
        for (m=0; m<boyut; m++) {
            if (m==j) continue;
            if (tahta[i][m] == tahta[i][j]) {
                dogruMu = 0;
                break;
            }
        }
        // j. Sütunda Ayný Sayý Birden Fazla Kez Kullanýlmýþ Mý
        if (dogruMu == 1) {
            for (m=0; m<boyut; m++) {
                if (m==i) continue;
                if (tahta[m][j] == tahta[i][j]) {
                    dogruMu = 0;
                    break;
                }
            }
        }
        // i. Satýrda Ýstenen Kadar Apartman Gözüküyor Mu?
        // Örnek: istenen 4, satýr 1 2 0 0, 2 adet gözüküyor ama 2 adet boþ var, doðruMu = 1 kalmaya devam etmeli
        // Örnek: istenen 1, satýr 1 2 0 0, 0 lar olmasýna raðmen bu satýrýn hatalý olduðu kesin
        if (dogruMu == 1 && sol[i] > 0) {
            int enAzGozuken = 0, sonGozuken = 0;
            int enFazlaKacTaneGozukebilir;
            for (m=0; m<=j; m++) {
                if (tahta[i][m] > sonGozuken) {
                    sonGozuken = tahta[i][m];
                    enAzGozuken++;
                }
            }
            if (sonGozuken < boyut) {
                int bosSayisi = boyut - (j + 1);
                enFazlaKacTaneGozukebilir = enAzGozuken + bosSayisi;
                enAzGozuken++;
            } else {
                enFazlaKacTaneGozukebilir = enAzGozuken;
            }
            int istenen = sol[i];
            if (enAzGozuken > istenen || istenen > enFazlaKacTaneGozukebilir) dogruMu = 0;
        }
        // j. Sutunda Ýstenen Kadar Apartman Gözüküyor Mu?
        if (dogruMu == 1 && ust[j] > 0) {
            int enAzGozuken = 0, sonGozuken = 0;
            int enFazlaKacTaneGozukebilir;
            for (m=0; m<=i; m++) {
                if (tahta[m][j] > sonGozuken) {
                    sonGozuken = tahta[m][j];
                    enAzGozuken++;
                }
            }
            if (sonGozuken < boyut) {
                int bosSayisi = boyut - (i + 1);
                enFazlaKacTaneGozukebilir = enAzGozuken + bosSayisi;
                enAzGozuken++;
            } else {
                enFazlaKacTaneGozukebilir = enAzGozuken;
            }
            int istenen = ust[j];
            if (enAzGozuken > istenen || istenen > enFazlaKacTaneGozukebilir) dogruMu = 0;
        }
        // i. satýr tersten doðru mu
        if (dogruMu == 1 && sag[i] > 0) {
            if (j==boyut-1) { // Tüm Satýr Girildiyse Kontrol Et
            // Diðer 2 kontrol için de benzer þart yazýlabilirdi ama yavaþlardý
            // Þimdi tersten daha zor olabilir diye böyle bir þart yazýyorum
                int gozukenAdet = 0, sonGozuken = 0;
                for (m=boyut-1; m>=0; m--) {
                    if (tahta[i][m] > sonGozuken) {
                        sonGozuken = tahta[i][m];
                        gozukenAdet++;
                    }
                }
                int istenen = sag[i];
                if (gozukenAdet != istenen) dogruMu = 0;
            }
        }
        // j. sütun tersten doðru mu
        if (dogruMu == 1 && alt[j] > 0) {
            if (i==boyut-1) { // Tüm Sütun Girildiyse Kontrol Et
                int gozukenAdet = 0, sonGozuken = 0;
                for (m=boyut-1; m>=0; m--) {
                    if (tahta[m][j] > sonGozuken) {
                        sonGozuken = tahta[m][j];
                        gozukenAdet++;
                    }
                }
                int istenen = alt[j];
                if (gozukenAdet != istenen) dogruMu = 0;
            }
        }
        
        // Doðruysa
        if (dogruMu == 1) {
            j++;
            continue;
        }
    }
}
#endif
