/*
Kullanýcýdan Sudoku Girdisi Alýr ve Çözümünü Gösterir
*/
#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "../lib/metin.h" // https://github.com/seymenkonuk/Metin-C commit 1
#include "../lib/tahta.h"  // https://github.com/seymenkonuk/Tahta-Olusturma-C commit 1

int sudokuCoz(bool tumCozumlerMi); // Kullanýcýdan Sudoku Girdisi Alýr ve Çözümünü Gösterir

int sudokuCoz(bool tumCozumlerMi) {
    bool sudokuKontrol(int konum, const char tahta[82]) {
        int i, j, kontrol[10] = {0};
        // Yatay Kontrol
        for (i=konum - konum%9; i<9 + (konum - konum%9); i++) {
            kontrol[tahta[i]-'0']++;
            if (kontrol[tahta[i]-'0'] > 1 && tahta[i] != '0') return false;
        }
        for (i=0; i<10; i++) kontrol[i] = 0; // kontrolü sýfýrla
        // Dikey Kontrol
        for (i=(konum%9); i<81; i+=9) {
            kontrol[tahta[i]-'0']++;
            if (kontrol[tahta[i]-'0'] > 1 && tahta[i] != '0') return false;
        }
        for (i=0; i<10; i++) kontrol[i] = 0; // kontrolü sýfýrla
        // Bölgesel Kontrol
        konum = (konum/27)*27 + ((konum%9)/3)*3;
        for (i=0; i<3; i++) {
            for (j=0; j<3; j++) {
                kontrol[tahta[i*9+j+konum]-'0']++;
                if (kontrol[tahta[i*9+j+konum]-'0'] > 1 && tahta[i*9+j+konum] != '0') return false;
            }
        }
        return true;
    }
    
    int i, j; char tahta[82]; 
    for (i=0; i<81; i++) tahta[i] = '0'; tahta[81] = '\0';
    tahtaOlustur(9, 9, 2);
    // Girdiyi Al
    while (1) {
        char tus = getch();
        tahtaKontrol(tus, 2);
        if (tus >= '0' && tus <= '9') {
            tahta[(konumx - 1) + (konumy - 1)*9] = tus;
            if (tus != 48)
                printf("%d", tus-48);
            else
                printf(" ");
            tahtaKontrol('d', 2);
        } else if (tus == '\r')
            break;
    }
    // Hile Kontrol
    for (i=0; i<81; i+= 13) 
        if (!sudokuKontrol(i, tahta)) {
            system("cls"); 
            printf("YANLIS GIRDI"); 
            return -2;
        }
    if (!sudokuKontrol(28, tahta)) {
        system("cls"); 
        printf("YANLIS GIRDI"); 
        return -2;
    }
    if (!sudokuKontrol(59, tahta)) {
        system("cls"); 
        printf("YANLIS GIRDI"); 
        return -2;
    }
    // Çöz
    char sonuc[82]; esitle(sonuc, tahta); int index = 0, yon = 1, cozumSayisi = 0;
    while (1) {
        if (index == -1) {
            if (cozumSayisi == 0) {
                system("cls");
                printf("COZUM BULUNAMADI!\n");
            }
            return cozumSayisi;
        }
        if (index == 81) {
            cozumSayisi++;
            for (i=0; i<9; i++) {
                for (j=0; j<9; j++) {
                    tahtaGit(j+1, i+1);
                    printf("%c", sonuc[i*9+j]);
                }
            }
            printf("\n\n");
            if (tumCozumlerMi) {
                getch();
                yon = -1;
                index += yon;
                continue;
            }
            else return -1;
        }
        if (tahta[index] != '0') {
            index += yon;
            continue;
        }
        if (sonuc[index] == '9') {
            sonuc[index] = '0';
            yon = -1;
            index += yon;
        } else {
            yon = 1;
            sonuc[index]++;
            if (sudokuKontrol(index, sonuc)) index += yon;
        }
    }
}
#endif
