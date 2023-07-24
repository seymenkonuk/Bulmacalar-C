/*
Girilen Kibrit Çöpü Problemini Çözer
*/
#ifndef KIBRITCOPU_H
#define KIBRITCOPU_H
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

const char* kibritCopuGirdiAl();                                      // Kullanýcýyý uygun formatta girdi girmeye zorlar. Girilen deðeri geriye döndürür.
int tekHamledeCoz(const char girdi[], bool tumCozumlerMi);            // "girdi"deki bulmacayý çözer.
int cokHamledeCoz(int hamle, const char girdi[], bool tumCozumlerMi); // "girdi"deki bulmacayý n adýmda çözer.
bool denklemDogruMu(const char denklem[]);                            // girilen denklemin doðru olup olmadýðýný bulur.

const char* kibritCopuGirdiAl() {
    char girdi[1000]; char karakter; int uzunluk = 0;
    while (1) {
        karakter = getch();
        if (uzunluk % 2 == 0 && karakter >= '0' && karakter <= '9') {
            printf("%c", karakter);
            girdi[uzunluk] = karakter;
            uzunluk++;
        }
        else if (uzunluk % 2 == 1 && (karakter == '+' || karakter == '-' || karakter == '=')) {
            printf("%c", karakter);
            girdi[uzunluk] = karakter;
            uzunluk++;
        } else if (karakter == '\r' && uzunluk >= 3 && uzunluk % 2 == 1) {
            printf("\n");
            girdi[uzunluk] = '\0';
            const char* deger = girdi;
            return deger;
        } else if (uzunluk > 0 && karakter == 8) { // backspace
            printf("%c %c", 8, 8);
            uzunluk--;
        }
    }
}

int tekHamledeCoz(const char girdi[], bool tumCozumlerMi) {
    int i, j, k, uzunluk, deger = 0;
    for (uzunluk = 0; girdi[uzunluk] != '\0'; uzunluk++); uzunluk++;
    
    char anlam[13] =      {'0', '1', '2', '3',  '4','5',  '6',  '7', '8',   '9',  '+', '-',  '='};
    char cikart[13][4] =   {"",  "",  "",  "",   "", "",   "5",  "1", "069", "35", "-", "",   "-"};
    char ekle[13][4] =     {"8", "7", "",  "9",  "", "69", "8",  "",  "",    "8",  "",  "+=", ""};
    char degistir[13][4] = {"69", "", "3", "25", "", "3",  "09", "",  "",    "06", "=", "",   "+"};
    
    // Ayný Karakterdeki Çöpün Yerini Deðiþtirirsek
    for (i=0; girdi[i] != '\0'; i++) {
        // Girdinin Kopyasýný Oluþtur
        char denklem[uzunluk]; for (j=0; j<uzunluk; j++) denklem[j] = girdi[j];
        // O Karakterin Sayýsal Karþýlýðýný Bul
        for (j=0; anlam[j] != girdi[i]; j++);
        // O Karakterin Deðiþebileceði Tüm Ýhtimalleri Dene
        for (k=0; degistir[j][k] != '\0'; k++) {
            denklem[i] = degistir[j][k];
            // Denklem Doðruysa Yazdýr
            if (denklemDogruMu(denklem) == 1) {
                printf("%s\n", denklem); deger++;
                if (!tumCozumlerMi) return -1;
            }
        }
    }
    
    // Bir Karakterden Alýp Diðerine Eklersek (i den al j ye koy)
    for (i=0; girdi[i] != '\0'; i++) {
        for (j=0; girdi[j] != '\0'; j++) {
            if (i==j) continue; // Kendinden alýp kendine koymak olmaz.
            // Girdinin Kopyasýný Oluþtur
            char denklem[uzunluk]; for (k=0; k<uzunluk; k++) denklem[k] = girdi[k];
            // O Karakterlerin Sayýsal Karþýlýklarýný Bul
            int ki; for (ki=0; anlam[ki] != girdi[i]; ki++);
            int kj; for (kj=0; anlam[kj] != girdi[j]; kj++);
            // Tüm Ýhtimalleri Dene
            int m, n;
            for (m=0; cikart[ki][m] != '\0'; m++) {
                denklem[i] = cikart[ki][m];
                for (n=0; ekle[kj][n] != '\0'; n++) {
                    denklem[j] = ekle[kj][n];
                    // Denklem Doðruysa Yazdýr
                    if (denklemDogruMu(denklem) == 1) {
                        printf("%s\n", denklem); deger++;
                        if (!tumCozumlerMi) return -1;
                    }
                }
            }
        }
    }
    if (deger == 0) printf("\nCOZUM YOK!");
    return deger;
}

bool denklemDogruMu(const char denklem[]) {
    int eskiSonuc, sonuc = 0, i, ilkMi = 1; char sonoperator = '+';
    // Sayýlarý Hesapla
    for (i=0; denklem[i] != '\0'; i++) {
        if (i % 2 == 0) { // Sayýya Bakýyorsak
            int sayi = denklem[i] - 48;
            if (sonoperator == '-')
                sayi = 0 - sayi;
            sonuc += sayi;
        } else { // Operatöre Bakýyorsak
            sonoperator = denklem[i];
            if (denklem[i] == '=') {
                // Bir Önceki ile Eþit Deðilse Denklem Yanlýþtýr
                if (ilkMi == 0 && eskiSonuc != sonuc) return false;
                sonoperator = '+';
                eskiSonuc = sonuc;
                sonuc = 0;
                ilkMi = 0;
            }
        }
    }
    return ilkMi == 0 && eskiSonuc == sonuc;
}

int cokHamledeCoz(int hamle, const char girdi[], bool tumCozumlerMi) {
    char anlam[13] = {'0', '1', '2', '3', '4','5', '6', '7', '8', '9', '+', '-', '='};
    int i, j, deger = 0;
    int uzunluk; for (uzunluk=0; girdi[uzunluk] != '\0'; uzunluk++); uzunluk++;
    char denklem[uzunluk]; denklem[uzunluk-1] = '\0';
    
    int rakamcopyerler[10][7] = {
        {1,1,1,1,1,1,0},
        {0,1,1,0,0,0,0},
        {1,1,0,1,1,0,1},
        {1,1,1,1,0,0,1},
        {0,1,1,0,0,1,1},
        {1,0,1,1,0,1,1},
        {1,0,1,1,1,1,1},
        {1,1,1,0,0,0,0},
        {1,1,1,1,1,1,1},
        {1,1,1,1,0,1,1}
    };
    int operatorcopyerler[3][3] = {
        {1,1,0},
        {1,0,0},
        {1,0,1}
    };
    
    // Denklemin Ýlk Halini Oluþtur
    int denklemS[uzunluk-1]; 
    for (i=0; i<uzunluk-1; i++) 
        if (i%2 == 0)
            denklemS[i] = 0;
        else
            denklemS[i] = 10;
    
    // Tüm Ýhtimalleri Dene
    while (1) {
        // Sayýlara Göre Denklemi Oluþtur
        for (i=0; i<uzunluk-1; i++) denklem[i] = anlam[denklemS[i]];
        
        // Denklem Kaç Hamlede Bu Denkleme Dönüþtürülebilir
        int bos = 0, dolu = 0;
        for (i=0; i<uzunluk-1; i++) {
            int ki; for (ki=0; anlam[ki] != girdi[i]; ki++);
            int kj; for (kj=0; anlam[kj] != denklem[i]; kj++);
            if (i % 2 == 0) {
                for (j=0; j<7; j++) {
                    if (rakamcopyerler[ki][j] != rakamcopyerler[kj][j]) {
                        if (rakamcopyerler[ki][j] == 1)
                            bos++;
                        else
                            dolu++;
                    }
                }
            } else {
                for (j=0; j<3; j++) {
                    if (operatorcopyerler[ki-10][j] != operatorcopyerler[kj-10][j]) {
                        if (operatorcopyerler[ki-10][j] == 1)
                            bos++;
                        else
                            dolu++;
                    }
                }
            }
        }
        
        if (bos == dolu) // Ayný sayýda çöp var // Çöp Yok Edilmemiþ veya Eklenmemiþ
            if (bos <= hamle && !(bos == 0 && hamle == 1)) // Hamlede O Kadar Deðiþiklik Yapýlabilir
                if (denklemDogruMu(denklem) == 1) { // Denklem Doðruysa Yazdýr
                    printf("%s\n", denklem); deger++;
                    if (!tumCozumlerMi) return -1;
                }
        
        denklemS[uzunluk-2]++; // En Saðý Bir Arttýr
        int hangi;
        // Limit Dýþýna Çýkýldýysa Bir Solundakini Arttýr, Kendisini Sýfýrla / Baþa Döndür
        for (hangi = uzunluk - 2; hangi >= 0; hangi--) { 
            if (hangi % 2 == 0 && denklemS[hangi] == 10) {
                denklemS[hangi] = 0;
                if (hangi-1 == -1) {// En Soldaki Limit Dýþýna Çýktýysa Bitir
                    if (deger == 0) printf("\nCOZUM YOK!");
                    return deger;
                }
                denklemS[hangi-1] += 1;
            } else if (hangi % 2 == 1 && denklemS[hangi] == 13) {
                denklemS[hangi] = 10;
                denklemS[hangi-1] += 1;
            } else break;
        }
    }
}
#endif
