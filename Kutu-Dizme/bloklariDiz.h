/*
N Adet Farklý Aðýrlýklardaki Eþit Boylu Kare Kutularý
3 Kutu Geniþliðindeki Bir Platformda En Aðýr En Altta
En Hafif En Üstte Olacak Þekilde En Az Adýmda Sýralar
(Her Zaman En Ýyi Çözümü Bulamýyor)
*/
#ifndef BLOKLARIDIZ_H
#define BLOKLARIDIZ_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lib/rastgele.h" // https://github.com/seymenkonuk/Rastgele-C commit 1

int bloklariDiz(int adet, int tahta[adet][3], bool bekle); // "tahta" dizisindeki platformdaki "adet" adet kutuyu üst üste dizer.
void rastgeleBlokOlustur(int adet, int sonuc[adet][3]);    // "adet" adet kutunun olduðunu rastgele bir platform oluþturur.

int bloklariDiz(int adet, int tahta[adet][3], bool bekle) {
    void tahtayiGoster(int alan[adet][3]) {
        int i, j, k, katsayi;
        for (katsayi=1; katsayi<=adet; katsayi*=10); katsayi /= 10;
        for (i=0; i<adet; i++) {
            for (j=0; j<3; j++) {
                int depo = alan[i][j]; if (depo == 0) depo = 1;
                for (k=katsayi; k>depo; k/=10) printf(" ");
                if (alan[i][j] == 0) 
                    printf(". ");
                else 
                    printf("%d ", alan[i][j]);
            }
            printf("\n");
        }
    }
    int adim = 0, enbuyuk, hangisutun, dizilissutun, neredensutun, nereyesutun, kackutu[3];
    //enbuyuk: dogru siralamada dizilmemis en buyuk kutu
    //kackutu[i]: i. sutunda kac kutu var
    //dizilissutun: kutularin dizilecegi sutun
    //hangisutun: dizilissutununa konulacak ilk kutunun oldugu sutun
    //neredensutun: tasinacak sutunun nereden tasinacagi
    //nereyesutun: tasinacak sutunun nereye tasinacagi
    int kontrol, i, j; //
    int alan[adet][3]; // tahtanýn kopyasý
    int konumlar[adet][2]; // konumlar[agirlik-1][0] = i, konumlar[agirlik-1][1] = j
    
    for (i=0; i<adet; i++)
        for (j=0; j<3; j++) {
            alan[i][j] = tahta[i][j];
            if (alan[i][j] != 0) {
                konumlar[alan[i][j]-1][0] = i;
                konumlar[alan[i][j]-1][1] = j;
            }
        }
    
    system("cls");
    printf("%d. Adim:\n",adim);
    tahtayiGoster(alan);
    
    while (1) {
        //Hangi Sutunda Kac Kutu Var
        for (i=0; i<3; i++) {
            for (j=adet-1; j>=0; j--) if (alan[j][i] == 0) break;
            kackutu[i] = adet - j - 1;
        }
        
        //Dizilis Sutunu Buluyoruz
        dizilissutun = -1;
        for (j=0; j<3; j++)
            if (alan[adet-1][j] == adet) {
                dizilissutun = j;
                break;
            }
            
        //Eger Dizilis Sutunu Yoksa En Az Kutu Olan Sutun Dizilis Sutunu Olur
        if (dizilissutun == -1) {
            dizilissutun = 0;
            for (i=1; i<3; i++)
                if (kackutu[dizilissutun] > kackutu[i])
                    dizilissutun = i;
        }
        
        //Dogru Dizilmemis En Buyuk Kutu Hangisi
        enbuyuk = adet;
        for (i=adet-1; i>=0; i--)
            if (alan[i][dizilissutun] == i+1) enbuyuk--;
            else break;
        
        //Dogru Dizildiyse Bitir
        if (enbuyuk == 0) break;
        
        //Dogru Dizilmemis En Buyuk Kutu Hangi Sutunda
        hangisutun = konumlar[enbuyuk-1][1];
        
        //Dizili Sutunda Ustte Dizili Olmayanlari Baska Sutuna Koy
        if (kackutu[dizilissutun] > adet - enbuyuk) {
            neredensutun = dizilissutun;
            nereyesutun = 0;
            for (i=1; i<3; i++)
                if (i != dizilissutun && i != hangisutun)
                    nereyesutun = i;
        } else if (alan[konumlar[enbuyuk-1][0]-1][hangisutun] != 0) { // En büyük kutunun üstü boþ deðilse
            neredensutun = hangisutun;
            nereyesutun = 0;
            for (i=1; i<3; i++)
                if (i != dizilissutun && i != hangisutun)
                    nereyesutun = i;
        } else {
            neredensutun = hangisutun;
            nereyesutun = dizilissutun;
        }
        
        //Sutun Tasima
        i = adet - kackutu[neredensutun];
        konumlar[alan[i][neredensutun]-1][0] = 0;
        konumlar[alan[i][neredensutun]-1][1] = nereyesutun;
        alan[0][nereyesutun] = alan[i][neredensutun];
        alan[i][neredensutun] = 0;
        
        for (j=1; j<adet; j++) //Yer Cekimi
            if (alan[j][nereyesutun] == 0) { //Kutunun alti bossa asagi dussun
                konumlar[alan[j-1][nereyesutun]-1][0]++;
                alan[j][nereyesutun] = alan[j-1][nereyesutun];
                alan[j-1][nereyesutun] = 0;
            } else break;
        
        //Kacinci Adimda Oldugunu Yaziyoruz
        if (bekle) { getch(); system("cls");}
        adim++; printf("%d. Adim:\n",adim);
        tahtayiGoster(alan);
     }
     printf("\n%d Adimda Bitti", adim);
     return adim;
}

void rastgeleBlokOlustur(int adet, int sonuc[adet][3]) {
    int i, j; for (i=0; i<adet; i++) for (j=0; j<3; j++) sonuc[i][j] = 0;
    int agirliklar[adet]; //Rastgele Uretilecek Kutularin Agirliklari
    {
        bool secildiMi[adet]; for (i=0; i<adet; i++) secildiMi[i] = false;
        for (i=0; i<adet; i++) {
            int rastgele;
            do {
                rastgele = rastgeleAralik(1, adet);
            } while (secildiMi[rastgele-1]);
            secildiMi[rastgele-1] = true;
            agirliklar[i] = rastgele;
        }
    }
    for (i=0; i<adet; i++) {
        int rastgele;
        do {
            rastgele = rastgeleAralik(0, 2);
        } while (sonuc[0][rastgele] != 0);
        sonuc[0][rastgele] = agirliklar[i];
        int index = 0; 
        while(1) {
            if (index+1==adet) break;
            if (sonuc[index+1][rastgele] == 0) {
                sonuc[index+1][rastgele] = sonuc[index][rastgele];
                sonuc[index][rastgele] = 0;
                index++;
            } else break;
        }
    }
    
    for (i=0; i<adet; i++) {
        for (j=0; j<3; j++) printf("%d ", sonuc[i][j]);
        printf("\n");
    }
}
#endif
