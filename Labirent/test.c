#include <stdio.h>
#include "labirent.h"

/*
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 0 0 0 0 0 0 0 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 0 1 1 1 1 0 0 0 0 1 0 0 0 2
1 0 1 0 1 1 1 0 0 0 0 0 1 0 1 1 1 1 0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 1 1 1 1 0 1 1 1 0 1
1 0 1 0 0 0 1 0 1 0 1 1 1 0 1 1 0 1 0 1 0 0 0 0 0 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 1 0 1
1 1 1 1 1 0 1 0 1 0 1 0 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 0 0 0 0 0 0 1 0 1 1 1 0 1 1 0 1 0 1
2 0 0 0 0 0 1 0 1 0 1 0 1 1 0 1 0 1 1 1 0 1 0 1 0 1 0 1 1 1 1 1 0 1 0 1 0 1 1 1 1 1 1 0 1
1 1 0 1 1 0 1 0 1 1 1 0 0 1 0 1 0 0 0 0 0 1 0 1 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 1 0 0 1
1 1 0 1 0 0 0 0 1 0 1 1 0 1 0 1 0 1 0 1 1 1 0 1 0 1 1 1 1 1 1 0 1 1 1 1 0 1 1 1 1 1 1 0 1
1 1 0 1 0 1 1 1 1 0 1 1 0 1 1 1 0 1 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0 0 0 0 0 1 0 1 0 0 1 0 1
1 0 0 1 0 0 0 1 0 0 0 1 0 0 0 0 0 1 0 1 1 1 1 1 1 1 1 1 1 0 1 0 1 1 1 1 1 1 0 1 1 0 1 0 1
1 1 0 1 1 1 0 1 0 1 1 1 0 1 1 1 1 1 1 1 0 0 0 0 0 0 1 0 1 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0 1
1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 0 1 1 0 1 0 1 0 1 1 1 0 1 1 0 1 1 0 1 0 1
1 1 1 1 1 1 1 1 0 1 1 1 1 0 1 1 1 1 1 1 1 1 0 1 1 1 1 0 1 0 1 0 0 0 1 0 0 0 0 0 1 0 1 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 1 0 1 1 0 1 1 0 1 0 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
*/

main() {
    int genislik = 45, yukseklik = 15, i, j;
    int tahta[yukseklik][genislik];
    yolGirdisiAl(genislik, yukseklik, tahta);
    //for (i=0; i<yukseklik; i++) for (j=0; j<genislik; j++) scanf("%d", &tahta[i][j]);
    //labirentCoz(genislik, yukseklik, tahta);
    yolBul(genislik, yukseklik, tahta);
    while (1);
}
