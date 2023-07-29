/*
Apartmanlar Bulmacalar�n�n ��z�m�n� G�sterir
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
    // Tahta Olu�tur ve K��eleri Sil
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
    
    // Girdiyi S�f�rla
    for (i=0; i<boyut; i++) ust[i] = 0;
    for (i=0; i<boyut; i++) sag[i] = 0;
    for (i=0; i<boyut; i++) alt[i] = 0;
    for (i=0; i<boyut; i++) sol[i] = 0;
    for (i=0; i<boyut; i++) for (j=0; j<boyut; j++) platform[i][j] = 0;
    
    // Girdiyi Al
    while (1) {
        char tus = getch();
        bool hata = false; // Hareket Sonucunda K��elere Mi Gidiyor
        
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
    // Tahtay� Olu�tur ve S�f�rla
    int tahta[boyut][boyut]; 
    for (i=0; i<boyut; i++) 
        for (j=0; j<boyut; j++) 
                tahta[i][j] = platform[i][j];
    
    // Hile Kontrol�
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
    // Verilen Say�larda Apartman G�z�kebilir Mi Kontrol� de Yap�labilir
    
    i=0; j=0; int yon = 1;
    while (1) {
        // j De�eri Geriden Limit D���na ��kt�ysa
        if (j==-1) {
            j = boyut-1; i--;
            if (i==-1) {
                // T�m �htimallere Bakt�m
                if (sonuc == 0) printf("Cozum Bulunamadi!");
                return sonuc;
            }
        }
        
        // j De�eri �leriden Limit D���na ��kt�ysa
        if (j == boyut) {
            j=0; i++;
            if (i==boyut) {
                // Do�ru Buldum
                sonuc++;
                
                // Tahta Yoksa Tahta Olu�tur
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
                // Tahtaya Sonucu Do�ru Formatta Yaz
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
                // Di�er ��z�mleri Bulmak i�in
                getch(); 
                i=boyut-1; j=boyut-1;
                yon = -1; continue;
            }
        }
        
        // O H�creye Kullan�c� Say� Girmediyse
        if (platform[i][j] == 0) {
            tahta[i][j]++;
            yon = 1;
        } else {
            j+=yon;
            continue;
        }
        
        // Limit D���na ��kt�
        if (tahta[i][j] > boyut) {
            tahta[i][j] = 0;
            j--;
            yon = -1;
            continue;
        }
        
        // i. Sat�rda Ayn� Say� Birden Fazla Kez Kullan�lm�� M�
        int dogruMu = 1;
        for (m=0; m<boyut; m++) {
            if (m==j) continue;
            if (tahta[i][m] == tahta[i][j]) {
                dogruMu = 0;
                break;
            }
        }
        // j. S�tunda Ayn� Say� Birden Fazla Kez Kullan�lm�� M�
        if (dogruMu == 1) {
            for (m=0; m<boyut; m++) {
                if (m==i) continue;
                if (tahta[m][j] == tahta[i][j]) {
                    dogruMu = 0;
                    break;
                }
            }
        }
        // i. Sat�rda �stenen Kadar Apartman G�z�k�yor Mu?
        // �rnek: istenen 4, sat�r 1 2 0 0, 2 adet g�z�k�yor ama 2 adet bo� var, do�ruMu = 1 kalmaya devam etmeli
        // �rnek: istenen 1, sat�r 1 2 0 0, 0 lar olmas�na ra�men bu sat�r�n hatal� oldu�u kesin
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
        // j. Sutunda �stenen Kadar Apartman G�z�k�yor Mu?
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
        // i. sat�r tersten do�ru mu
        if (dogruMu == 1 && sag[i] > 0) {
            if (j==boyut-1) { // T�m Sat�r Girildiyse Kontrol Et
            // Di�er 2 kontrol i�in de benzer �art yaz�labilirdi ama yava�lard�
            // �imdi tersten daha zor olabilir diye b�yle bir �art yaz�yorum
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
        // j. s�tun tersten do�ru mu
        if (dogruMu == 1 && alt[j] > 0) {
            if (i==boyut-1) { // T�m S�tun Girildiyse Kontrol Et
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
        
        // Do�ruysa
        if (dogruMu == 1) {
            j++;
            continue;
        }
    }
}
#endif
