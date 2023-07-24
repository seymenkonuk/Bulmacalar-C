/*
N*M'lik Bir Platformdaki At Problemini Çözer
*/
#ifndef ATPROBLEMI_H
#define ATPROBLEMI_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

int atProblemiCoz(int genislik, int yukseklik, int x, int y, bool tumCozumlerMi); // N*M'lik Bir Platformdaki At Problemini Çözer

int atProblemiCoz(int genislik, int yukseklik, int x, int y, bool tumCozumlerMi) {
    int atHareketleri[8][2] = {{-2,-1}, {-1,-2}, {1,-2}, {2,-1}, {2,1}, {1,2}, {-1,2}, {-2,1}};
    int deger = 0;
    void atKostur(int adim, int x, int y, int tahta[yukseklik][genislik]) {
        int i, j; tahta[y][x] = adim;
        if (adim == yukseklik*genislik) {
            deger++;
            system("cls");
            for (i=0; i<yukseklik; i++) {
                for (j=0; j<genislik; j++) printf("%3d ", tahta[i][j]);
                printf("\n");
            }
            if (tumCozumlerMi) getch();
            else return;
        } else {
            for (i=0; i<8; i++) {
                int yeni_x = x+atHareketleri[i][0];
                int yeni_y = y+atHareketleri[i][1];
                if (yeni_x >= 0 && yeni_x < genislik)
                    if (yeni_y >= 0 && yeni_y < yukseklik)
                        if (tahta[yeni_y][yeni_x] == 0)
                            atKostur(adim+1, yeni_x, yeni_y, tahta);
            }
        }
        tahta[y][x] = 0;
    }
    
    int tahta[yukseklik][genislik], i, j;
    for (i=0; i<yukseklik; i++) for (j=0; j<genislik; j++) tahta[i][j] = 0;
    atKostur(1, x-1, y-1, tahta);
    if (deger == 0) {system("cls"); printf("COZUM BULUNAMADI!"); return 0;};
    if (!tumCozumlerMi) return -1;
    return deger;
}
#endif
