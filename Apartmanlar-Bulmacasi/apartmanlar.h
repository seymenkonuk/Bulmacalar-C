/*
Apartmanlar Bulmacalar�n�n ��z�m�n� G�sterir
NOT: girdi alma eklenecek
NOT: tahtaya say� ekleme eklenecek
*/
#ifndef APARTMANLAR_H
#define APARTMANLAR_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Apartmanlar Bulmacalar�n�n ��z�m�n� G�sterir
int cozApartmanlarBulmacasi(int uzunluk, int ust[uzunluk], int sag[uzunluk], int alt[uzunluk], int sol[uzunluk], bool tumCozumlerMi);

int cozApartmanlarBulmacasi(int uzunluk, int ust[uzunluk], int sag[uzunluk], int alt[uzunluk], int sol[uzunluk], bool tumCozumlerMi) {
    int i, j, m, n, sonuc = 0;
    // Tahtay� Olu�tur ve S�f�rla
    int tahta[uzunluk][uzunluk]; for (i=0; i<uzunluk; i++) for (j=0; j<uzunluk; j++) tahta[i][j] = 0;
    
    i=0; j=0;
    while (1) {
        tahta[i][j]++;
        // Limit D���na ��kt�
        if (tahta[i][j] > uzunluk) {
            tahta[i][j] = 0;
            j--;
            if (j==-1) {
                j=uzunluk-1; i--;
                if (i==-1) {
                    // T�m �htimallere Bakt�m
                    if (sonuc == 0) printf("Cozum Bulunamadi!");
                    return sonuc;
                }
            }
            continue;
        }
        
        // i. Sat�rda Ayn� Say� Birden Fazla Kez Kullan�lm�� M�
        int dogruMu = 1;
        for (m=0; m<j; m++) {
            if (tahta[i][m] == tahta[i][j]) {
                dogruMu = 0;
                break;
            }
        }
        // j. S�tunda Ayn� Say� Birden Fazla Kez Kullan�lm�� M�
        if (dogruMu == 1) {
            for (m=0; m<i; m++) {
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
            if (sonGozuken < uzunluk) {
                int bosSayisi = uzunluk - (j + 1);
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
            if (sonGozuken < uzunluk) {
                int bosSayisi = uzunluk - (i + 1);
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
            if (j==uzunluk-1) { // T�m Sat�r Girildiyse Kontrol Et
            // Di�er 2 kontrol i�in de benzer �art yaz�labilirdi ama yava�lard�
            // �imdi tersten daha zor olabilir diye b�yle bir �art yaz�yorum
                int gozukenAdet = 0, sonGozuken = 0;
                for (m=uzunluk-1; m>=0; m--) {
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
            if (i==uzunluk-1) { // T�m S�tun Girildiyse Kontrol Et
                int gozukenAdet = 0, sonGozuken = 0;
                for (m=uzunluk-1; m>=0; m--) {
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
            if (j == uzunluk) {
                j=0; i++;
                if (i==uzunluk) {
                    // Do�ru Buldum
                    sonuc++;
                    system("cls");
                    for (m=0; m<uzunluk; m++) {
                        for (n=0; n<uzunluk; n++)
                            printf("%d ", tahta[m][n]);
                        printf("\n");
                    }
                    printf("\n");
                    
                    if (!tumCozumlerMi) return -1;
                    // Di�er ��z�mleri Bulmak i�in
                    getch(); 
                    i=uzunluk-1; j=uzunluk-1;
                }
            }
        }
    }
}
#endif
