#include <stdio.h>
#include "amiralBattiBulmacasi.h"

main() {
    getch();
    while (1) {
        int i, j, boyut = 8;
        int gemiUzunluk[boyut+1];
        int yatay[boyut], dikey[boyut];
        int platform[boyut][boyut];
        
        girdiAlAmiralBattiBulmacasi(boyut, yatay, dikey, platform, gemiUzunluk);
        cozAmiralBattiBulmacasi(boyut, yatay, dikey, platform, gemiUzunluk, true);
        while (getch() != '\r');
    }
}
