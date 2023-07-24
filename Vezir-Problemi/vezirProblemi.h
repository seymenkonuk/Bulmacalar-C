/*
N Vezirli Bir Vezir Probleminin Çözümünü Gösterir
*/
#ifndef VEZIRPROBLEMI_H
#define VEZIRPROBLEMI_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int vezirProblemiCoz(int boyut, bool tumCozumlerMi); // N Vezirli Bir Vezir Probleminin Çözümünü Gösterir

int vezirProblemiCoz(int boyut, bool tumCozumlerMi) {
    int vezirler[boyut], hangi = 0; int sonuc = 0;
    int i, j; for (i=0; i<boyut; i++) vezirler[i] = 0;
    
    while (1) {
        vezirler[hangi]++;
        // Vezir Limit Dýþýna Çýkarsa
        if (vezirler[hangi] == boyut + 1) {
            vezirler[hangi] = 0;
            hangi--;
            if (hangi == -1) break;
            continue;
        }
        
        int kontrol = 1;
        for (i=0; i<hangi; i++)
            // Yatay/Dikey Kontrol
            if (vezirler[i] == vezirler[hangi]) 
                kontrol = 0;
            // Çapraz Kontrol
            else if (hangi - i == vezirler[i] - vezirler[hangi] || i - hangi == vezirler[i] - vezirler[hangi])
                kontrol = 0;
        
        if (kontrol == 1) {// Yok
            hangi++;
            if (hangi == boyut) { // Doðru Çözümlerden Biri Bulundu
                system("cls");
                for (i=1; i<=boyut; i++) {
                    for (j=0; j<boyut; j++)
                        if (vezirler[j] == i)
                            printf("X ");
                        else
                            printf(". ");
                    printf("\n");
                }
                sonuc++;
                if (tumCozumlerMi) { getch(); hangi--;} else break;
            }
        }
    } 
    printf("Bitti!");
    if (sonuc == 0) return 0;
    if (!tumCozumlerMi) return -1;
    return sonuc;
}
#endif
