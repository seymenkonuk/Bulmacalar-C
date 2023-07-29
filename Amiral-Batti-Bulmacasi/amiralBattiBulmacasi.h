/*
Kullanýcý ile Bilgisayar Arasýnda Amiral Battý Oyunu
*/
#ifndef AMIRALBATTIBULMACASI_H
#define AMIRALBATTIBULMACASI_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lib/tahta.h"

void girdiAlAmiralBattiBulmacasi(int boyut, int yatay[boyut], int dikey[boyut], int platform[boyut][boyut], int gemiUzunluk[boyut+1]);
int cozAmiralBattiBulmacasi(int boyut, int yatay[boyut], int dikey[boyut], int platform[boyut][boyut], int gemiUzunluk[boyut+1], bool tumCozumlerMi);

void girdiAlAmiralBattiBulmacasi(int boyut, int yatay[boyut], int dikey[boyut], int platform[boyut][boyut], int gemiUzunluk[boyut+1]) {
    int i, j;
    // Tahta Oluþtur ve Sol Üst Köþeyi Sil
    tahtaOlustur(boyut+1, boyut+1, 2);
    gotoxy(0,0); printf("   ");
    gotoxy(0,1); printf(" ");
    
    // Bilgilendirme Yazýsý
    gotoxy(0, (boyut+1)*2+2);
    printf("Gemi Olmayan Alan (Deniz): 0\n");
    printf("Belli Olmayan Gemi: 1\n");
    printf("Yuvarlak Gemi: 2\n");
    printf("Kare Gemi: 3\n");
    printf("Sol Daire Gemi: 4\n");
    printf("Sag Daire Gemi: 5\n");
    printf("Ust Daire Gemi: 6\n");
    printf("Alt Daire Gemi: 7\n");
    
    // Girdiyi Sýfýrla
    for (i=0; i<boyut; i++) {tahtaGit(i+2, 1); printf("0"); yatay[i] = 0; }
    for (i=0; i<boyut; i++) {tahtaGit(1, i+2); printf("0"); dikey[i] = 0; }
    for (i=0; i<boyut; i++) for (j=0; j<boyut; j++) platform[i][j] = -1;
    
    tahtaGit(2,1);
    
    // Girdiyi Al
    while (1) {
        char tus = getch();
        bool hata = false; // Hareket Sonucunda Köþelere Mi Gidiyor
        
        if (tus == 'w' || tus == 'W') {
            if  (konumy == 2 && konumx == 1)
                hata = true;
        } else if (tus == 'a' || tus == 'A') {
            if  (konumx == 2 && konumy == 1)
                hata = true;
        } else if (tus == '\r') {
            gotoxy(0, (boyut+2)*2+1);
            break;
        } else if ((konumx==1 || konumy==1) && tus >= '0' && tus <= '9') {
            printf("%c", tus);
            if (konumx == 1) {
                dikey[konumy-2] = tus - '0';
            } else if (konumy == 1) {
                yatay[konumx-2] = tus - '0';
            }
        } else if (tus >= '0' && tus <= '7') {
            platform[konumy-2][konumx-2] = tus - '0';
            printf("%c", tus);
        } else if (tus == 8 /*backspace*/ && konumx!=1 && konumy!=1) {
            platform[konumy-2][konumx-2] = -1;
            printf(" ");
        }
        
        if (!hata) tahtaKontrol(tus, 0);
    }
    
    // Gemi Uzunluklarýný Al
    gotoxy(0, (boyut+1)*2+2+9);
    gemiUzunluk[0] = 0;
    for (i=1; i<boyut+1; i++) {
        printf("%d Uzunlugunda Kac Adet Gemi Olsun: ", i);
        scanf("%d", &gemiUzunluk[i]);
    }
}

int cozAmiralBattiBulmacasi(int boyut, int yatay[boyut], int dikey[boyut], int platform[boyut][boyut], int gemiUzunluk[boyut+1], bool tumCozumlerMi) {
    int i, j, k, m, n, sonuc=0;
    // Depoyu Oluþtur
    int depo[boyut][boyut];
    for (i=0; i<boyut; i++) 
        for (j=0; j<boyut; j++)
            if (platform[i][j] >= 1)
                depo[i][j] = 1;
            else
                depo[i][j] = platform[i][j];
        
    // Depoyu Uygun Formata Dönüþtür
    for (i=0; i<boyut; i++) 
        for (j=0; j<boyut; j++)
            if (platform[i][j] == 2) { // Yuvarlak ise Tüm Komþularý Denizdir
                int yonler[8][2]={{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};
                for (k=0; k<8; k++) {
                    int yeni_i = i+yonler[k][0];
                    int yeni_j = j+yonler[k][1];
                    if (yeni_i<0 || yeni_i>=boyut) continue;
                    if (yeni_j<0 || yeni_j>=boyut) continue;
                    depo[yeni_i][yeni_j] = 0;
                }
            } else if (platform[i][j] == 3) { // Kare ise Dik Olmayan Komþularý Denizdir
                int yonler[4][2]={{-1,-1}, {-1,1}, {1,-1}, {1,1}};
                for (k=0; k<4; k++) {
                    int yeni_i = i+yonler[k][0];
                    int yeni_j = j+yonler[k][1];
                    if (yeni_i<0 || yeni_i>=boyut) continue;
                    if (yeni_j<0 || yeni_j>=boyut) continue;
                    depo[yeni_i][yeni_j] = 0;
                }
            } else if (platform[i][j] == 4) { // Sol Yuvarlak ise Saðý Hariç Denizdir
                int yonler[9][2]={{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {-1,2}, {1,2}};
                for (k=0; k<9; k++) {
                    int yeni_i = i+yonler[k][0];
                    int yeni_j = j+yonler[k][1];
                    if (yeni_i<0 || yeni_i>=boyut) continue;
                    if (yeni_j<0 || yeni_j>=boyut) continue;
                    depo[yeni_i][yeni_j] = 0;
                }
                if (j+1>=boyut) {printf("Hatali Girdi!"); return -2;}
                depo[i][j+1] = 1;
            } else if (platform[i][j] == 5) { // Sað Yuvarlak ise Solu Hariç Denizdir
                int yonler[9][2]={{-1,-1}, {-1,0}, {-1,1}, {0,1}, {1,-1}, {1,0}, {1,1}, {-1,-2}, {-1,2}};
                for (k=0; k<9; k++) {
                    int yeni_i = i+yonler[k][0];
                    int yeni_j = j+yonler[k][1];
                    if (yeni_i<0 || yeni_i>=boyut) continue;
                    if (yeni_j<0 || yeni_j>=boyut) continue;
                    depo[yeni_i][yeni_j] = 0;
                }
                if (j-1<0) {printf("Hatali Girdi!"); return -2;}
                depo[i][j-1] = 1;
            } else if (platform[i][j] == 6) { // Üst Yuvarlak ise Altý Hariç Denizdir
                int yonler[9][2]={{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,1}, {2,-1}, {2,1}};
                for (k=0; k<9; k++) {
                    int yeni_i = i+yonler[k][0];
                    int yeni_j = j+yonler[k][1];
                    if (yeni_i<0 || yeni_i>=boyut) continue;
                    if (yeni_j<0 || yeni_j>=boyut) continue;
                    depo[yeni_i][yeni_j] = 0;
                }
                if (i+1>=boyut) {printf("Hatali Girdi!"); return -2;}
                depo[i+1][j] = 1;
            } else if (platform[i][j] == 7) { // Alt Yuvarlak ise Üstü Hariç Denizdir
                int yonler[9][2]={{-1,-1}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}, {-2,-1}, {-2, 1}};
                for (k=0; k<9; k++) {
                    int yeni_i = i+yonler[k][0];
                    int yeni_j = j+yonler[k][1];
                    if (yeni_i<0 || yeni_i>=boyut) continue;
                    if (yeni_j<0 || yeni_j>=boyut) continue;
                    depo[yeni_i][yeni_j] = 0;
                }
                if (i-1<0) {printf("Hatali Girdi!"); return -2;}
                depo[i-1][j] = 1;
            }
    
    // Tahtayý Oluþtur
    int tahta[boyut][boyut]; for (i=0; i<boyut; i++) for(j=0; j<boyut; j++) tahta[i][j] = depo[i][j];

    // Bitmemiþ Gemi Uzunluklarýný Bul
    int bitmemisGemiUzunluk[boyut+1];
    int toplamGemiAdedi = 0;
    for (i=0; i<boyut+1; i++) {
        toplamGemiAdedi += i*gemiUzunluk[i];
        bitmemisGemiUzunluk[i] = gemiUzunluk[i];
        for (j=0; j<i; j++) bitmemisGemiUzunluk[j] += gemiUzunluk[i];
    }
    
    i=0; j=0; int yon = 1;
    while (1) {
                
        // j ileriden Limit Dýþýna Çýktýysa
        if (j>=boyut) {
            j=0; i++; 
            // Doðru Tahtalardan Birisi Bulundu
            if (i>=boyut) {
                sonuc++;
                
                // Ekranda Göster
                for (m=0; m<boyut; m++) {
                    for (n=0; n<boyut; n++) {
                        tahtaGit(n+2, m+2);
                        printf("%c ", (tahta[m][n]==1) ? 254: 32);
                    }
                }
                gotoxy(0, (boyut+1)*2+2+8+boyut+2);
                
                if (!tumCozumlerMi) return -1;
                // Diðer Çözümleri Bulmak için
                getch(); 
                i=boyut-1; j=boyut-1;
                yon = -1; continue;
            }
        }
        // j geriden Limit Dýþýna Çýktýysa
        if (j==-1) {
            j=boyut-1; i--;
            // Baþka Tahta Kalmadý
            if (i==-1) {
                gotoxy(0, (boyut+1)*2+2+8+boyut+2);
                if (sonuc == 0) printf("Cozum Bulunamadi!");
                return sonuc;
            }
        }
        
        // O Hücreye Kullanýcý Sayý Girmediyse
        if (depo[i][j] == -1) {
            tahta[i][j]++;
            yon = 1;
        } else {
            j+=yon;
            continue;
        }
        
        // tahta[i][j] Alamayacaðý Bir Deðer Aldýysa
        if (tahta[i][j]>1) {
            tahta[i][j] = -1;
            j--;
            yon = -1;
            continue;
        }
        
        // Þimdilik Doðru Bir Deðer Aldýysa
        bool dogruMu = true;
        
        // Çaprazýnda 1 Olamaz
        if (tahta[i][j] == 1) {
            int yonler[4][2] = {{1,1}, {-1,1}, {1,-1}, {-1,-1}};
            for (k=0; k<4; k++) {
                int yeni_i = i+yonler[k][0];
                int yeni_j = j+yonler[k][1];
                if (yeni_i<0 || yeni_i>=boyut) continue;
                if (yeni_j<0 || yeni_j>=boyut) continue;
                if (tahta[yeni_i][yeni_j] == 1) {
                    dogruMu = false;
                    break;
                }
            }
        }
        if (!dogruMu) continue;
        
        // Komþusu Kare ise 
        int yonler[4][2] = {{1,0}, {-1,0}, {0,-1}, {0,1}};
        for (k=0; k<4; k++) {
            int yeni_i = i+yonler[k][0];
            int yeni_j = j+yonler[k][1];
            if (yeni_i<0 || yeni_i>=boyut) continue;
            if (yeni_j<0 || yeni_j>=boyut) continue;
            if (platform[yeni_i][yeni_j] != 3) continue;
            
            // Dikeyde 0 Var Mý
            for (m=0; m<2; m++) {
                int komsu_i = yeni_i+yonler[m][0];
                int komsu_j = yeni_j+yonler[m][1];
                if (komsu_i<0 || komsu_i>=boyut) continue;
                if (komsu_j<0 || komsu_j>=boyut) continue;
                if (tahta[komsu_i][komsu_j] == 0) break;    
            }
            if (m<2) {
                // Yatayda 0 Var Mý
                for (m=2; m<4; m++) {
                    int komsu_i = yeni_i+yonler[m][0];
                    int komsu_j = yeni_j+yonler[m][1];
                    if (komsu_i<0 || komsu_i>=boyut) continue;
                    if (komsu_j<0 || komsu_j>=boyut) continue;
                    if (tahta[komsu_i][komsu_j] == 0) break;    
                }
                if (m<4) {
                    dogruMu = false;
                    break;
                }
            }
        }
        if (!dogruMu) continue;
        
        // Satýr Bazlý Kontrol
        for (m=0; m<boyut; m++) {
            int bosluk = 0, bir = 0;
            for (n=0; n<boyut; n++) {
                // Boþluklarý Say
                if (tahta[m][n] == -1) bosluk++;
                if (tahta[m][n] == 1) bir++;
            }
            if (bir>dikey[m]) {dogruMu = false; break;}
            if (bir+bosluk<dikey[m]) {dogruMu = false; break;}
        }
        if (!dogruMu) continue;
        
        // Sütun Bazlý Kontrol
        for (n=0; n<boyut; n++) {
            int bosluk = 0, bir = 0;
            for (m=0; m<boyut; m++) {
                // Boþluklarý Say
                if (tahta[m][n] == -1) bosluk++;
                if (tahta[m][n] == 1) bir++;
            }
            if (bir>yatay[n]) {dogruMu = false; break;}
            if (bir+bosluk<yatay[n]) {dogruMu = false; break;}
        }
        if (!dogruMu) continue;
        
        // Gemi Uzunluk Kontrol Yeterli Mi
        int tBitmisGemiUzunluk[boyut+1]; for (k=0; k<boyut+1; k++) tBitmisGemiUzunluk[k]=0;
        int tBitmemisGemiUzunluk[boyut+1]; for (k=0; k<boyut+1; k++) tBitmemisGemiUzunluk[k]=0;
        
        for (m=0; m<boyut; m++) {
            for (n=0; n<boyut; n++) {
                // Gemi Deðilse
                if (tahta[m][n] != 1) continue;
                
                // Daha Önce Zaten Bakýldýysa
                if (m-1>=0 && tahta[m-1][n] == 1) continue; 
                if (n-1>=0 && tahta[m][n-1] == 1) continue; 
                
                int uzunluk; bool gemiBitmisMi = true;
                // Saðýna Bak, Uzunluk Say
                for (k=n; k<boyut; k++) if (tahta[m][k] != 1) break;
                uzunluk = k-n;
                if (k<boyut && tahta[m][k] == -1) gemiBitmisMi = false;
                
                // Aþaðýsýna Bak, Uzunluk Say
                if (uzunluk == 1) { // Uzunluk 1 den Büyükse Aþaðýsý Zaten Olamaz
                    for (k=m; k<boyut; k++) if (tahta[k][n] != 1) break;
                    uzunluk = k-m;
                    if (k<boyut && tahta[k][n] == -1) gemiBitmisMi = false;
                }
                
                // Gemi Bitmiþ Mi
                if (n-1>=0 && tahta[m][n-1] == -1) gemiBitmisMi = false;
                if (m-1>=0 && tahta[m-1][n] == -1) gemiBitmisMi = false;
                
                tBitmemisGemiUzunluk[uzunluk]++;
                if (tBitmemisGemiUzunluk[uzunluk] > bitmemisGemiUzunluk[uzunluk]) dogruMu = false;
                
                if (gemiBitmisMi) {
                    tBitmisGemiUzunluk[uzunluk]++;
                    if (tBitmisGemiUzunluk[uzunluk] > gemiUzunluk[uzunluk]) dogruMu = false;
                }
                
            }
        }
        if (!dogruMu) continue;
        
        // Fazla Gemi Kalmasýn
        if (i==boyut-1 && j==boyut-1) {
            for (k=0; k<boyut+1; k++) {
                if (tBitmisGemiUzunluk[k] != gemiUzunluk[k]) {
                    dogruMu = false;
                    break;
                }
            }
        }
        if (!dogruMu) continue;
        j++;
    }
}
#endif
