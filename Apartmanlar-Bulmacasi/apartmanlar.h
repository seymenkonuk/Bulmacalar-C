/*
Apartmanlar Bulmacalarýnýn Çözümünü Gösterir
NOT: girdi alma eklenecek
NOT: tahtaya sayý ekleme eklenecek
*/
#ifndef APARTMANLAR_H
#define APARTMANLAR_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Apartmanlar Bulmacalarýnýn Çözümünü Gösterir
int cozApartmanlarBulmacasi(int uzunluk, int ust[uzunluk], int sag[uzunluk], int alt[uzunluk], int sol[uzunluk], bool tumCozumlerMi);

int cozApartmanlarBulmacasi(int uzunluk, int ust[uzunluk], int sag[uzunluk], int alt[uzunluk], int sol[uzunluk], bool tumCozumlerMi) {
    int i, j, m, n, sonuc = 0;
    // Tahtayý Oluþtur ve Sýfýrla
    int tahta[uzunluk][uzunluk]; for (i=0; i<uzunluk; i++) for (j=0; j<uzunluk; j++) tahta[i][j] = 0;
    
    i=0; j=0;
    while (1) {
        tahta[i][j]++;
        // Limit Dýþýna Çýktý
        if (tahta[i][j] > uzunluk) {
            tahta[i][j] = 0;
            j--;
            if (j==-1) {
                j=uzunluk-1; i--;
                if (i==-1) {
                    // Tüm Ýhtimallere Baktým
                    if (sonuc == 0) printf("Cozum Bulunamadi!");
                    return sonuc;
                }
            }
            continue;
        }
        
        // i. Satýrda Ayný Sayý Birden Fazla Kez Kullanýlmýþ Mý
        int dogruMu = 1;
        for (m=0; m<j; m++) {
            if (tahta[i][m] == tahta[i][j]) {
                dogruMu = 0;
                break;
            }
        }
        // j. Sütunda Ayný Sayý Birden Fazla Kez Kullanýlmýþ Mý
        if (dogruMu == 1) {
            for (m=0; m<i; m++) {
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
        // i. satýr tersten doðru mu
        if (dogruMu == 1 && sag[i] > 0) {
            if (j==uzunluk-1) { // Tüm Satýr Girildiyse Kontrol Et
            // Diðer 2 kontrol için de benzer þart yazýlabilirdi ama yavaþlardý
            // Þimdi tersten daha zor olabilir diye böyle bir þart yazýyorum
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
        // j. sütun tersten doðru mu
        if (dogruMu == 1 && alt[j] > 0) {
            if (i==uzunluk-1) { // Tüm Sütun Girildiyse Kontrol Et
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
        
        // Doðruysa
        if (dogruMu == 1) {
            j++;
            if (j == uzunluk) {
                j=0; i++;
                if (i==uzunluk) {
                    // Doðru Buldum
                    sonuc++;
                    system("cls");
                    for (m=0; m<uzunluk; m++) {
                        for (n=0; n<uzunluk; n++)
                            printf("%d ", tahta[m][n]);
                        printf("\n");
                    }
                    printf("\n");
                    
                    if (!tumCozumlerMi) return -1;
                    // Diðer Çözümleri Bulmak için
                    getch(); 
                    i=uzunluk-1; j=uzunluk-1;
                }
            }
        }
    }
}
#endif
