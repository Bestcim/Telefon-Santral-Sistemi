#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


struct aboneler
{
  long long int tel_nosu;
  char adi[10];
  char soyadi[12];
  char adresi[25];
  char abone_tipi;
  struct aboneler *tel_nosuna_gore_sonraki;
  struct aboneler *soyada_gore_sonraki;
  struct gorusmeler *gorusmeleri;
};
struct gorusmeler
{
    char aranan_no[11];
    char tarih[9];
    char baslangic_zamani[5];
    int dakika;
    struct gorusmeler *onceki,*sonraki;
};
void Bir_abone_ekleme(struct aboneler tel_noya_gore_hash_tablosu_[],struct aboneler *soyada_gore_hash_tablosu[]);//*bir abonenin eklenmesi fonksiyonu
void Bir_abonenin_nakil_yapilmasi(struct aboneler tel_noya_gore_hash_tablosu_[]); //*bir abonenin nakil yapýlmasý
void Yapilan_gorusmelere_iliskin_bilgilerin_eklenmesi(struct aboneler tel_noya_gore_hash_tablosu_[]); //*gorusme eklenmesi fonksiyonu
void Bir_abonenin_silinmesi(struct aboneler tel_noya_gore_hash_tablosu_[],struct aboneler *soyada_gore_hash_tablosu[]);//*bir abonenin silinmesi
void Bir_abonenin_bilgilerinin_ve_yapmis_oldugu_tum_gorusmelerin_listelenmesi(struct aboneler tel_noya_gore_hash_tablosu_[]);//*tum gorusmelerin listelenmesi
void Bir_abonenin_bilgilerinin_ve_yapmis_oldugu_son_3_gorusmenin_listelenmesi(struct aboneler tel_noya_gore_hash_tablosu_[]);//*son 3 gorusmenin listelenmesi
void Telefon_numarasi_belirli_bir_3_basamakli_sayi_ile_baslayan_abonelerin_bilgilerinin_listelenmesi(struct aboneler tel_noya_gore_hash_tablosu_[]);//*ilk 3 basamagi ayni olan gorusmelerin listelenmesi
void Soyadi_belirli_bir_harf_ile_baslayan_abonelerin_bilgilerinin_listelenmesi(struct aboneler *soyada_gore_hash_tablosu[]);//*Soyadinin bas harfi ayný olan abonelerin listelenmesi
void Soyadi_belirli_bir_metin_parcasi_ile_baslayan_abonelerin_bilgilerinin_listelenmesi(struct aboneler *soyada_gore_hash_tablosu[]);//*soyadi belirli bir metin parcasi ile baslayan abonelerin listelenmesi
void Tum_abonelerin_bilgilerinin_listelenmesi(struct aboneler tel_noya_gore_hash_tablosu_[]);//*tum abonelerinin listelenmesi
void Belirli_bir_tarihten_beridir_hic_gorusme_yapmamis_abonelerin_bulunmasi(struct aboneler tel_noya_gore_hash_tablosu_[]);//*uzun süredir gorusme yapmamis abonelerin bulunmasi
void Belirli_bir_numarayi_arayan_abonelerin_bulunmasi(struct aboneler *soyada_gore_hash_tablosu[]);//*ayný numarayi arayan abonelerin listelenmesi
void Belirli_bir_tarihte_yapilan_tum_gorusmelerin_listelenmesi(struct aboneler tel_noya_gore_hash_tablosu_[]);//*belli bir tarihteki tum gorusmelerin listelenmesi
struct aboneler *tel_noya_gore_ara(struct aboneler *liste_basi_ptr,long long int aranan_tel_no);//*girilen numarayi baska kullanan varmý diye kontrol eder
void tel_noya_gore_sirali_ekle(struct aboneler *liste_basi_ptr, struct aboneler *yeni);//*telefon numarasina gore hash tablosuna sýralý ekler.
void soyadin_ilk_harfine_gore_basa_ekle(struct aboneler **ilk_ptr, struct aboneler *yeni);//*soyadýna gore hash tablosuna alfabetik olarak sýralý ekler.
struct aboneler *tel_no_listesinden_cikar(struct aboneler *liste_basi_ptr,long long int cikarilacak_tel_no);//*hash tablosundan abone cýkarýlýyor ve hash tablosu birbirine baglanýyor.
void gorusmeler_sirali_ekle(struct gorusmeler *liste_basi_ptr, struct gorusmeler *yeni);//*gorusmeleri sýralý ekler.
void eskiden_yeniye_gorusme_listele(struct gorusmeler *liste_basi_ptr);//*eskiden yeni gorusmeleri listeler.
void yeniyeden_eskiye_son_3_gorusme_listele(struct gorusmeler *liste_basi_ptr);//*eskiden yeniye son 3 gorusmeyi listeler.
void ilk_3_basamagi_ayni_olan_aboneleri_kucukten_buyuge_listele(struct aboneler *liste_basi_ptr);//*telefon numarasinin ilk 3 basamagý ayný olanlarý kucukten buyuge listeler.
void ada_gore_listele(struct aboneler *liste_basi_ptr);//*soyada gore hash tablosunu listeler.
void metin_parcasinina_gore_listelemne(struct aboneler *liste_basi_ptr,char aranan[]);//*belli bir metin parcasina gore arar ve listeler.
void tum_aboneleri_listeleme(struct aboneler *liste_basi_ptr,int i);//*tum aboneleri listeler.
void soyad_listesinden_cikar(struct aboneler **ilk_ptr, struct aboneler *cikarilacak_ptr);//*aboneleri soyada gore hash tablosundan cýkartýr.
void belirli_tarihten_sonra_konusmayanlar(struct aboneler *liste_basi_ptr,long long int tarih);////*belli bir tarihten beridir gorusmeyenleri listeler.
void bir_numarayi_arayanlar(struct aboneler *liste_basi_ptr,long long int aranan_no);//*kullanýcadan alýnan numarayi arayanlarý gosterir.
void ayni_tarihte_konusanlar(struct aboneler *liste_basi_ptr,long long int tarih);//ayný tarihte konusan aboneleri listeler.
void gorusmeleri_Silme(struct gorusmeler *liste_basi_ptr);//*gorusmeleri siler.
char *tipe_gore_adi(char);//*kullanýcýdan alýnan karakteri tipe cevirir.
int hash_orani(long long tel_no);//*10000'e boler.
int Secim_menusu();
int main()
{
    struct aboneler tel_noya_gore_hash_tablosu_[1000];
    struct aboneler *soyada_gore_hash_tablosu[26];
    int i,secim;
    char devam;
    for(i=0;i<1000;i++)//*tel no gore hash tablosu ilkleniyor.
    tel_noya_gore_hash_tablosu_[i].tel_nosuna_gore_sonraki=&tel_noya_gore_hash_tablosu_[i];
    for(i=0;i<26;i++)
    soyada_gore_hash_tablosu[i]=NULL;//*soyada gore hash tablosu ilkleniyor.
    while(devam=='e'&&devam=='E'||devam!='H'&&devam!='h')
    {
     if(devam=='e'||devam=='E')
      system("cls");
     secim=Secim_menusu();
      switch(secim)
       {
        case 1:
             Bir_abone_ekleme(tel_noya_gore_hash_tablosu_,soyada_gore_hash_tablosu);
             break;
        case 2:
             Bir_abonenin_nakil_yapilmasi(tel_noya_gore_hash_tablosu_);
             break;
        case 3:
             Yapilan_gorusmelere_iliskin_bilgilerin_eklenmesi(tel_noya_gore_hash_tablosu_);
             break;
        case 4:
            Bir_abonenin_silinmesi(tel_noya_gore_hash_tablosu_,soyada_gore_hash_tablosu);
             break;
        case 5:
            Bir_abonenin_bilgilerinin_ve_yapmis_oldugu_tum_gorusmelerin_listelenmesi(tel_noya_gore_hash_tablosu_);
             break;
        case 6:
           Bir_abonenin_bilgilerinin_ve_yapmis_oldugu_son_3_gorusmenin_listelenmesi(tel_noya_gore_hash_tablosu_);
             break;
        case 7:
            Telefon_numarasi_belirli_bir_3_basamakli_sayi_ile_baslayan_abonelerin_bilgilerinin_listelenmesi(tel_noya_gore_hash_tablosu_);
             break;
        case 8:
            Soyadi_belirli_bir_harf_ile_baslayan_abonelerin_bilgilerinin_listelenmesi(soyada_gore_hash_tablosu);
            break;
        case 9:
            Soyadi_belirli_bir_metin_parcasi_ile_baslayan_abonelerin_bilgilerinin_listelenmesi(soyada_gore_hash_tablosu);
            break;
        case 10:
            Tum_abonelerin_bilgilerinin_listelenmesi(tel_noya_gore_hash_tablosu_);
            break;
        case 11:
            Belirli_bir_tarihten_beridir_hic_gorusme_yapmamis_abonelerin_bulunmasi(tel_noya_gore_hash_tablosu_);
            break;
        case 12:
            Belirli_bir_numarayi_arayan_abonelerin_bulunmasi(soyada_gore_hash_tablosu);
            break;
        case 13:
            Belirli_bir_tarihte_yapilan_tum_gorusmelerin_listelenmesi(tel_noya_gore_hash_tablosu_);
            break;
       }



        printf("\n\n\n\n\tAna Menuye Donmek Ister Misiniz? ==>(E/e/H/h):");
        fflush(stdin);
        devam=getchar();
    }




    return 0;
}
int Secim_menusu()
{
    int sec;
    printf("\n\n");
    printf("\t  --------------->\n\t  | SECIM MENUSU |\n\t  <---------------");
    printf("\n\n");
    printf("\n\t1.Yeni Bir Abonenin Eklenmesi....");
    printf("\n\t2.Bir Abonenin Nakil Yapilmasi....");
    printf("\n\t3.Yapilan Gorusmelere Iliskin Bilgilerin Eklenmesi....");
    printf("\n\t4.Bir Abonenin Silinmesi....");
    printf("\n\t5.Bir Abonenin Bilgilerinin ve Yapmis Oldugu Tum Gorusmelerin Listelenmesi....");
    printf("\n\t6.Bir Abonenin Bilgilerinin ve Yapmis Oldugu Son 3 Gorusmenin Listelenmesi....");
    printf("\n\t7.Telefon Numarasi Belirli Bir 3 Basamakli Sayi Ile Baslayan Abonelerin Bilgilerinin Listelenmesi....");
    printf("\n\t8.Soyadi Belirli Bir Harf Ile Baslayan Abonelerin Bilgilerinin Listelenmesi....");
    printf("\n\t9.Soyadi Belirli Bir Metin Parcasi Ile Baslayan Abonelerin Bilgilerinin Listelenmesi....");
    printf("\n\t10.Tum Abonelerin Bilgilerinin Listelenmesi....");
    printf("\n\t11.Belirli Bir Tarihten Beridir Hic Gorusme Yapmamis Abonelerin Bulunmasi....");
    printf("\n\t12.Belirli Bir Numarayi Arayan Abonelerin Bulunmasi....");
    printf("\n\t13.Belirli Bir Tarihte Yapilan Tum Gorusmelerin Listelenmesi....");
    printf("\n\n\n\t Yapmak Istediginiz Islemi Seciniz:");
    scanf("%i",&sec);
    return sec;
}
void Bir_abone_ekleme(struct aboneler tel_noya_gore_hash_tablosu_[],struct aboneler *soyada_gore_hash_tablosu[])
{
     struct aboneler *bir_abone;
     struct gorusmeler *baslangici;
     int ilk_kayit_yeri,soyada_gore_yeri,secim;
     long long int tel_no;
     char devam;
      printf("\n\n\n\t....Yeni Bir Abonenin Eklenmesi.....\n\n\n\n");
             printf("\n\tTelefon Numarasini Giriniz:");//*kullanýcýdan telefon numarasi alýnýr.
             scanf("%lli",&tel_no);
             ilk_kayit_yeri=hash_orani(tel_no);//*hashleniyor ve telnoya gore hash tablosunda yeri bulunuyor.
             if(tel_noya_gore_ara(&tel_noya_gore_hash_tablosu_[ilk_kayit_yeri],tel_no)==NULL)//*kayit yeri bos olup olmadýgý kontrol ediliyor.
               {
                 bir_abone=malloc(sizeof(struct aboneler));//*bir abone icin yer aciliyor.
                 baslangici=malloc(sizeof(struct gorusmeler));//*bir gorusme icin yer aciliyor.
                 baslangici->sonraki=baslangici;//*gorusmeler ilkleniyor.
                 baslangici->onceki=baslangici;
                 printf("\n\tAdi:");
                 fflush(stdin);
                 gets(bir_abone->adi);
                 printf("\n\tSoyadi:");
                 fflush(stdin);                                 //*bilgiler alýnýyor.
                 gets(bir_abone->soyadi);
                 printf("\n\tAdresi:");
                 fflush(stdin);
                 gets(bir_abone->adresi);
                 printf("\n\tAbone Tipi (S:Sahis, I:Isyeri, K:Kamu, G:Guvenlik) :");
                 scanf("%c",&bir_abone->abone_tipi);
                 bir_abone->tel_nosu=tel_no;
                 bir_abone->gorusmeleri=baslangici; //*bir abonenin gorusmeleri baglaniyor.
                 tel_noya_gore_sirali_ekle(&tel_noya_gore_hash_tablosu_[ilk_kayit_yeri],bir_abone);//*telnoya gore sýralý ekleniyor.
                 soyada_gore_yeri=toupper(bir_abone->soyadi[0])-'A';    //*soyada gore hash tablosundaki yeri bulunuyor.
                 soyadin_ilk_harfine_gore_basa_ekle(&soyada_gore_hash_tablosu[soyada_gore_yeri],bir_abone);     //*soyadin ilk harfine gore alfabetik olarak ekleniyor.
                 printf("\n\n\t...Abone Eklendi...\n");
               }
               else
               printf("\n\n\tNUMARA BASKASI TARAFINDAN KULLANILIYOR!..");

        printf("\n\n\n\n\n\tIslemi Tekrarlamak Ister Misiniz?[e/E/h/H]:");
        fflush(stdin);
        devam=getchar();
        if(devam=='e'||devam=='E')
        {
            system("cls");
            Bir_abone_ekleme(tel_noya_gore_hash_tablosu_,soyada_gore_hash_tablosu);
        }







}
void Bir_abonenin_nakil_yapilmasi(struct aboneler tel_noya_gore_hash_tablosu_[])
{
   long long int tel_no,tel_no1;
    int tel_yeri,tel_yeri1;
    char devam;
    struct aboneler *kontrol;
    struct aboneler *bir_abone;
     printf("\n\n\n\t....Bir Abonenin Nakil Yapilmasi.....\n\n\n\n");
    printf("\n\tTelefon Numarasini Giriniz:");
    scanf("%lli",&tel_no);
    tel_yeri=hash_orani(tel_no);

    bir_abone=tel_noya_gore_ara(&tel_noya_gore_hash_tablosu_[tel_yeri],tel_no);
    if(bir_abone==NULL)                     //*hata kontrolü.
        printf("\n\t ISTEDIGINIZ KISI BULUNAMADI!..");
    else
    {
         printf("\n\tAdresi:");         //*bilgiler alýnýyor.
         fflush(stdin);
         gets(bir_abone->adresi);
         printf("\n\n\tTel nosunu degisicek mi seciniz[e/E/h/H]:");
         fflush(stdin);
         devam=getchar();
        if(devam=='e'||devam=='E')
         {
            printf("\n\n\tYeni tel nosunu giriniz:");
            scanf("%lli",&tel_no1);
            tel_yeri1=hash_orani(tel_no1);              //*yeni tel no alýnýyor.Hashleniyor.
            kontrol=tel_noya_gore_ara(&tel_noya_gore_hash_tablosu_[tel_yeri1],tel_no1);
            if(kontrol==NULL)               //*tel noya gore aranýyor bos mu dolu mu diye kontrol ediliyor.
            {
             bir_abone=tel_no_listesinden_cikar(&tel_noya_gore_hash_tablosu_[tel_yeri],tel_no);
             bir_abone->tel_nosu=tel_no1;
             tel_noya_gore_sirali_ekle(&tel_noya_gore_hash_tablosu_[tel_yeri1],bir_abone);

            }
            else
            printf("\n\n\tNUMARA BASKASI TARAFINDAN KULLANILIYOR!..");

         }
    }
}
void Yapilan_gorusmelere_iliskin_bilgilerin_eklenmesi(struct aboneler tel_noya_gore_hash_tablosu_[])
{
    long long int tel_no;
    int tel_yeri;
    struct aboneler *bir_abone;
    struct gorusmeler *bir_gorusme;
    char devam;
    printf("\n\n\n\t.....Yapilan Gorusmelere Iliskin Bilgilerin Eklenmesi.....\n\n\n");
    printf("\n\tTelefon Numarasini Giriniz:");
    scanf("%lli",&tel_no);
    tel_yeri=hash_orani(tel_no);
    bir_abone=tel_noya_gore_ara(&tel_noya_gore_hash_tablosu_[tel_yeri],tel_no);
    if(bir_abone==NULL)
        printf("\n\n\tISTEDIGINIZ KISI BULUNAMADI!..");             //*hata kontrolü
    else
    {
     bir_gorusme=malloc(sizeof(struct gorusmeler));     //*yer aciliyor ve ilkleniyor.
     bir_gorusme->onceki=bir_gorusme;
     bir_gorusme->sonraki=bir_gorusme;
     printf("\n\tAranan No:");
     fflush(stdin);
     scanf("%s",bir_gorusme->aranan_no);
     printf("\n\tTarih:");
     fflush(stdin);
     scanf("%s",bir_gorusme->tarih);                        //*bilgiler alýnýyor.
     printf("\n\tBaslangic Zamani:");
     fflush(stdin);
     scanf("%s",bir_gorusme->baslangic_zamani);
     printf("\n\tDakika:");
     scanf("%i",&bir_gorusme->dakika);
     gorusmeler_sirali_ekle(bir_abone->gorusmeleri,bir_gorusme);            //*gorusmeler sýralý ekleniyor
     printf("\n\n\n\n\n\tIslemi Tekrarlamak Ister Misiniz?[e/E/h/H]:");
        fflush(stdin);
        devam=getchar();
        if(devam=='e'||devam=='E')
        {
            system("cls");
            Yapilan_gorusmelere_iliskin_bilgilerin_eklenmesi(tel_noya_gore_hash_tablosu_);
        }


}
}
void Bir_abonenin_silinmesi(struct aboneler tel_noya_gore_hash_tablosu_[],struct aboneler *soyada_gore_hash_tablosu[])
{
    long long int tel_no;
    int tel_yeri;
    int yeri;
    struct aboneler *bir_abone;
    printf("\n\n\n\t.....Bir Abonenin Silinmesi.....\n\n\n");
    printf("\n\n\tTelefon Numarasini Giriniz:");                    //*silinmek istenen abonenin numarasi alýnýyor.
    scanf("%lli",&tel_no);
    tel_yeri=hash_orani(tel_no);
    bir_abone=tel_no_listesinden_cikar(&tel_noya_gore_hash_tablosu_[tel_yeri],tel_no);


    if(bir_abone==NULL)
        printf("\n\n\n\n\tBU TELEFON NUMARASINA SAHIP BIR ABONE YOK!..\n");     //*hata kontrolü.
    else
    {
        yeri=toupper(bir_abone->soyadi[0])-'A'; //*bu fonksiyonda soyada gore hash tablosunda yeri bulunuyor.
        soyad_listesinden_cikar(&soyada_gore_hash_tablosu[yeri],bir_abone); //*soyada gore hash tablosundan cikartiliyor.
        gorusmeleri_Silme(bir_abone->gorusmeleri);
        free(bir_abone);
        printf("\n\t======>> SILME BASARILI <<======\n");
    }
}
void Bir_abonenin_bilgilerinin_ve_yapmis_oldugu_tum_gorusmelerin_listelenmesi(struct aboneler tel_noya_gore_hash_tablosu_[])
{
    long long int tel_no;
    int tel_yeri;
    struct aboneler *bir_abone;
    char *tip_adi;
    printf("\n\n\n\t.....Bir Abonenin Bilgilerinin ve Yapmis Oldugu Tum Gorusmelerin Listelenmesi.....\n\n\n");
    printf("\n\tTelefon Numarasini Giriniz:");
    scanf("%lli",&tel_no);
    tel_yeri=hash_orani(tel_no);
    bir_abone=tel_noya_gore_ara(&tel_noya_gore_hash_tablosu_[tel_yeri],tel_no);
    if(bir_abone==NULL)
        printf("\n\n\n\tISTEDIGINIZ KISI BULUNAMADI!..");            //*hata kontrolü.
    else
    {   tip_adi=tipe_gore_adi(bir_abone->abone_tipi);
        printf("\n\n\tTel Numarasi     Adi       Soyadi       Adres        Abone Tipi ");   //*tabloda gosteriliyor.
        printf("\n\t-------------    ---       ------       ------       -----------\n");
        printf("\t%-16lli %-9s %-12s %-14s %-16s",bir_abone->tel_nosu,bir_abone->adi,bir_abone->soyadi,bir_abone->adresi,tip_adi);
        eskiden_yeniye_gorusme_listele(bir_abone->gorusmeleri);
    }

}
void Bir_abonenin_bilgilerinin_ve_yapmis_oldugu_son_3_gorusmenin_listelenmesi(struct aboneler tel_noya_gore_hash_tablosu_[])
{
    long long int tel_no;
    int tel_yeri;
    struct aboneler *bir_abone;
    char *tip_adi;
    printf("\n\n\n\t.....Bir Abonenin Bilgilerinin ve Yapmis Oldugu Son 3 Gorusmenin Listelenmesi.....\n\n\n");
    printf("\n\n\tTelefon Numarasini Giriniz:");
    scanf("%lli",&tel_no);
    tel_yeri=hash_orani(tel_no);
    bir_abone=tel_noya_gore_ara(&tel_noya_gore_hash_tablosu_[tel_yeri],tel_no);
    if(bir_abone==NULL)
        printf("\n\n\n\tISTEDIGINIZ KISI BULUNAMADI!..");        //*hata kontrolü.
    else
    {
        tip_adi=tipe_gore_adi(bir_abone->abone_tipi);
        printf("\n\n\tTel Numarasi     Adi       Soyadi       Adres        Abone Tipi ");        //*tabloda gosteriliyor.
        printf("\n\t-------------    ---       ------       -----        ----------\n");
        printf("\t%-16lli %-9s %-12s %-14s %-16s",bir_abone->tel_nosu,bir_abone->adi,bir_abone->soyadi,bir_abone->adresi,tip_adi);
        yeniyeden_eskiye_son_3_gorusme_listele(bir_abone->gorusmeleri);
    }

}
void Telefon_numarasi_belirli_bir_3_basamakli_sayi_ile_baslayan_abonelerin_bilgilerinin_listelenmesi(struct aboneler tel_noya_gore_hash_tablosu_[])
{
     int tel_no;
     printf("\n\n\n\t....Telefon Numarasi Belirli Bir 3 Basamakli Sayi Ile Baslayan Abonelerin Bilgilerinin Listelenmesi....\n\n");
     printf("\n\n\n\tTelofon Numarasinin Ilk 3 Hanesini Giriniz:");
     scanf("%i",&tel_no);
     ilk_3_basamagi_ayni_olan_aboneleri_kucukten_buyuge_listele(&tel_noya_gore_hash_tablosu_[tel_no]);
}
void Soyadi_belirli_bir_harf_ile_baslayan_abonelerin_bilgilerinin_listelenmesi(struct aboneler *soyada_gore_hash_tablosu[])
{
      char aranan;
      int yeri;
      printf("\n\n\n\t....Soyadi Belirli Bir Harf Ile Baslayan Abonelerin Bilgilerinin Listelenmesi....\n\n");
      printf("\n\n\tBilgilerini Gormek Istediginiz Abonelerin Soyadinin Ilk Harfini Giriniz: ");
      fflush(stdin);
      scanf("%c",&aranan);
      yeri=toupper(aranan)-'A';
      ada_gore_listele(soyada_gore_hash_tablosu[yeri]);

}
void Soyadi_belirli_bir_metin_parcasi_ile_baslayan_abonelerin_bilgilerinin_listelenmesi(struct aboneler *soyada_gore_hash_tablosu[])
{
   char aranan[12];
   int yeri;
   printf("\n\n\n\t....Soyadi Belirli Bir Metin Parcasi Ile Baslayan Abonelerin Bilgilerinin Listelenmesi....\n\n");
         printf("\n\n\tMetin Parcasini Giriniz: ");
         scanf("%s",&aranan);
         yeri=toupper(aranan[0])-'A';
         metin_parcasinina_gore_listelemne(soyada_gore_hash_tablosu[yeri],aranan);

}
void Tum_abonelerin_bilgilerinin_listelenmesi(struct aboneler tel_noya_gore_hash_tablosu_[])
{
    int i;
    printf("\n\n\n\t....Tum Abonelerin Bilgilerinin Listelenmesi....\n\n");
    printf("\n\n\tTel Numarasi     Adi       Soyadi       Adres        Abone Tipi ");
    printf("\n\t-------------    ---       ------       ------       -----------\n");
    for(i=0;i<1000;i++)
    tum_aboneleri_listeleme(&tel_noya_gore_hash_tablosu_[i],i);   //*tel no'ya gore hash tablosunun icinde geziliyor.

}
void Belirli_bir_tarihten_beridir_hic_gorusme_yapmamis_abonelerin_bulunmasi(struct aboneler tel_noya_gore_hash_tablosu_[])
{
   long long int tarih;
   int i;
   printf("\n\n\n\t....Belirli Bir Tarihten Beridir Hic Gorusme Yapmamis Abonelerin Bulunmasi....\n\n");
   printf("\n\n\n\tHangi Tarihten Beri Gorusme Yapmamis Aboneleri Gormek Istersiniz?:");
   scanf("%lli",&tarih);
   printf("\n\n\n\tTel Numarasi     Adi       Soyadi       Adres        Abone Tipi ");
   printf("\n\t-------------    ---       ------       ------       -----------\n");
   for(i=0;i<1000;i++)
   belirli_tarihten_sonra_konusmayanlar(&tel_noya_gore_hash_tablosu_[i],tarih); //*tel no'ya gore hash tablosunun icinde geziliyor.

}
void Belirli_bir_numarayi_arayan_abonelerin_bulunmasi(struct aboneler *soyada_gore_hash_tablosu[])
{
    long long int aranan_no;
    int i;
    printf("\n\n\n\t....Belirli Bir Numarayi Arayan Abonelerin Bulunmasi....\n\n");
    printf("\n\n\tAyni Numarayi Arayan Aboneleri Gormek Icin Numarayi Giriniz:");
    scanf("%lli",&aranan_no);
    printf("\n\n\n\tTel Numarasi     Adi       Soyadi       Adres        Abone Tipi ");
    printf("\n\t-------------    ---       ------       ------       -----------\n");
    for(i=0;i<26;i++)
    bir_numarayi_arayanlar(soyada_gore_hash_tablosu[i],aranan_no); //*soyada gore hash tablosunun icinde geziliyor.

}
void Belirli_bir_tarihte_yapilan_tum_gorusmelerin_listelenmesi(struct aboneler tel_noya_gore_hash_tablosu_[])
{
   long long int tarih;
   int i;
   printf("\n\n\n\t....Belirli Bir Tarihte Yapilan Tum Gorusmelerin Listelenmesi....\n\n");
   printf("\n\n\tHangi Tarihteki Gorusmeleri Gormek Istersiniz?:");
   scanf("%lli",&tarih);
   printf("\n\n\n\n\tAranan Numara    Tarih       Baslangic Zamani       Dakika ");
    printf("\n\t-------------    -----       ----------------       ------\n");
   for(i=0;i<1000;i++)
   ayni_tarihte_konusanlar(&tel_noya_gore_hash_tablosu_[i],tarih); //*tel no'ya gore hash tablosunun icinde geziliyor.




}
struct aboneler *tel_noya_gore_ara(struct aboneler *liste_basi_ptr,long long int aranan_tel_no)
{
    struct aboneler *gecici; //*istenilen tel numarasi bulunup geriye adresi donduruluyor.
    gecici=liste_basi_ptr;
    gecici=gecici->tel_nosuna_gore_sonraki;
    while (gecici!=liste_basi_ptr && gecici->tel_nosu<=aranan_tel_no)
    {
        if (gecici->tel_nosu==aranan_tel_no) return gecici;
        gecici=gecici->tel_nosuna_gore_sonraki;
    }
    return NULL;
}
void tel_noya_gore_sirali_ekle(struct aboneler *liste_basi_ptr, struct aboneler *yeni)
{
    struct aboneler *onceki, *gecici;       //*tel numarasina gore sýralý ekleniyor.
    onceki=liste_basi_ptr;
    gecici=liste_basi_ptr->tel_nosuna_gore_sonraki;
    while(gecici!=liste_basi_ptr && gecici->tel_nosu<yeni->tel_nosu)
    {
        onceki=gecici;
        gecici=gecici->tel_nosuna_gore_sonraki;
    }
    yeni->tel_nosuna_gore_sonraki=gecici;
    onceki->tel_nosuna_gore_sonraki=yeni;
}
void gorusmeler_sirali_ekle(struct gorusmeler *liste_basi_ptr, struct gorusmeler *yeni)
{
    struct gorusmeler *geciciler; //*gorusmeler hem tarih hem de saate bakýlarak ekleniyor.
    geciciler=liste_basi_ptr->sonraki;
    while (geciciler!=liste_basi_ptr &&atoll(geciciler->tarih)>atoll(yeni->tarih))
    geciciler=geciciler->sonraki;
    if(atoll(geciciler->tarih)==atoll(yeni->tarih)&&atol(geciciler->baslangic_zamani)>atol(yeni->baslangic_zamani))
    geciciler=geciciler->sonraki;
    yeni->sonraki=geciciler;
    yeni->onceki=geciciler->onceki;
    geciciler->onceki->sonraki=yeni;
    geciciler->onceki=yeni;
}
void soyadin_ilk_harfine_gore_basa_ekle(struct aboneler **bas, struct aboneler *yeni)
{
     struct aboneler *gecici, *onceki; //* soyada gore hash tablosuna alfabetik sýrayla ekliyor.

    if (*bas==NULL) {
        yeni->soyada_gore_sonraki=NULL;
        *bas=yeni;
    } else
        if (strcmp(yeni->soyadi,(*bas)->soyadi)<0) {
            yeni->soyada_gore_sonraki=*bas;
            *bas=yeni;
        } else {
            onceki=*bas;
            gecici=(*bas)->soyada_gore_sonraki;
            while ((gecici!=NULL) && strcmp(yeni->soyadi,(*bas)->soyadi)<0 ) {
                onceki=gecici;
                gecici=gecici->soyada_gore_sonraki;
            }
            yeni->soyada_gore_sonraki=gecici;
            onceki->soyada_gore_sonraki=yeni;
        }

}
struct aboneler *tel_no_listesinden_cikar(struct aboneler *liste_basi_ptr,long long int cikarilacak_tel_no)
{
    struct aboneler *onceki, *gecici; //*tel numarasi listesinden abone cikartiliyor ve onceki sonrakine baglanýyor.
    onceki=liste_basi_ptr;
    gecici=liste_basi_ptr->tel_nosuna_gore_sonraki;
    while(gecici!=liste_basi_ptr && gecici->tel_nosu<cikarilacak_tel_no)
    {
        onceki=gecici;
        gecici=gecici->tel_nosuna_gore_sonraki;
    }
    if(gecici==liste_basi_ptr || gecici->tel_nosu>cikarilacak_tel_no)
        return NULL;
    else
    {
        onceki->tel_nosuna_gore_sonraki=gecici->tel_nosuna_gore_sonraki;
        return gecici;
    }
}
void soyad_listesinden_cikar(struct aboneler **ilk_ptr, struct aboneler *cikarilacak_ptr)
{
   struct aboneler *onceki, *gecici; //*soyad listesinden cikartiliyor ve onceki sonrakine baglanýyor.

    if(*ilk_ptr==cikarilacak_ptr)
        *ilk_ptr=(*ilk_ptr)->soyada_gore_sonraki;
    else {
        onceki=*ilk_ptr;
        gecici=(*ilk_ptr)->soyada_gore_sonraki;
        while(gecici!=cikarilacak_ptr)
        {
            onceki=gecici;
            gecici=gecici->soyada_gore_sonraki;
        }

        onceki->soyada_gore_sonraki=gecici->soyada_gore_sonraki;
    }


}
void eskiden_yeniye_gorusme_listele(struct gorusmeler *liste_basi_ptr)
{
    struct gorusmeler *gecici;  //*bir abonenin gorusmeleri eskiden yeniye listeleniyor.
    int arama_Sayisi=0;
    long int gorusme_Suresi=0;
    gecici=liste_basi_ptr->onceki;
    if(gecici==liste_basi_ptr)
    printf("\n\n\n\n\n\t---> ABONE HIC GORUSME YAPMAMISTIR <---\n\n\n");
    else
    {
       printf("\n\n\n\n\tAranan Numara    Tarih       Baslangic Zamani       Dakika ");
        printf("\n\t-------------    -----       ----------------       ------\n");
        while (gecici!=liste_basi_ptr)
        {

        printf("\t%c%c%c%c%c%c%c%c%c%c%c ",gecici->aranan_no[0],gecici->aranan_no[1],gecici->aranan_no[2],'-',gecici->aranan_no[3],gecici->aranan_no[4],gecici->aranan_no[5],gecici->aranan_no[6],gecici->aranan_no[7],gecici->aranan_no[8],gecici->aranan_no[9]);
        printf("\t%c%c%c%c%c%c%c%c%c%c     ",gecici->tarih[6],gecici->tarih[7],'.',gecici->tarih[4],gecici->tarih[5],'.',gecici->tarih[0],gecici->tarih[1],gecici->tarih[2],gecici->tarih[3]);
        printf("\t%c%c%c%c%c     ",gecici->baslangic_zamani[0],gecici->baslangic_zamani[1],':',gecici->baslangic_zamani[2],gecici->baslangic_zamani[3]);
        printf("\t      %i\n",gecici->dakika);
        ++arama_Sayisi;
        gorusme_Suresi+=gecici->dakika;
        gecici=gecici->onceki;
       }
        printf("\n\n\n\t------------------------------------\n");
        printf("\n\tToplam Gorusme Sayisi= %i",arama_Sayisi);
        printf("\n\tToplam Gorusme Suresi= %i dk",gorusme_Suresi);
        printf("\n\tToplam Gorusme Ortalamasi= %.2f dk",(float)gorusme_Suresi/arama_Sayisi);
        printf("\n\n\t------------------------------------\n");
    }

}
char *tipe_gore_adi(char deger)
{
        if(deger=='s'||deger=='S')          //*karaktere gore tip adi dondürülüyor.
        return "Sahis";
        if(deger=='i'||deger=='I')
        return "Isyeri";
        else if(deger=='k'||deger=='K')
        return "Kamu";
        else if(deger=='g'||deger=='G')
        return "Guvenlik";

}
void yeniyeden_eskiye_son_3_gorusme_listele(struct gorusmeler *liste_basi_ptr)
{
    struct gorusmeler *gecici;
    int arama_Sayisi=0;                         //*gorusmeler yeniden eskiye gore eklendigi icin son 3 gorusme ilk basta bulunuyor.Bu yüzden ilk 3'ü son gorusmeler oluyor.
    gecici=liste_basi_ptr->sonraki;
    if(gecici==liste_basi_ptr)
    printf("\n\n\n\n\n\t---> ABONE HIC GORUSME YAPMAMISTIR <---\n\n\n");
    else
    {
        printf("\n\n\n\n\tAranan Numara    Tarih       Baslangic Zamani       Dakika ");
        printf("\n\t-------------    -----       ----------------       ------\n");
       while (gecici!=liste_basi_ptr)
        {
        printf("\t%c%c%c%c%c%c%c%c%c%c%c ",gecici->aranan_no[0],gecici->aranan_no[1],gecici->aranan_no[2],'-',gecici->aranan_no[3],gecici->aranan_no[4],gecici->aranan_no[5],gecici->aranan_no[6],gecici->aranan_no[7],gecici->aranan_no[8],gecici->aranan_no[9]);
        printf("\t%c%c%c%c%c%c%c%c%c%c   ",gecici->tarih[6],gecici->tarih[7],'.',gecici->tarih[4],gecici->tarih[5],'.',gecici->tarih[0],gecici->tarih[1],gecici->tarih[2],gecici->tarih[3]);
        printf("\t%c%c%c%c%c     ",gecici->baslangic_zamani[0],gecici->baslangic_zamani[1],':',gecici->baslangic_zamani[2],gecici->baslangic_zamani[3]);
        printf("\t      %i\n",gecici->dakika);
        ++arama_Sayisi;
        if(arama_Sayisi==3)
        break;
        gecici=gecici->sonraki;
        }
    }

}
void ilk_3_basamagi_ayni_olan_aboneleri_kucukten_buyuge_listele(struct aboneler *liste_basi_ptr)
{
    struct aboneler *gecici;        //*ilk 3 basamagi ayni olan aboneler hash tablosunda bulunup listeleniyor.
    gecici=liste_basi_ptr;
    gecici=gecici->tel_nosuna_gore_sonraki;
    char *tip_adi;
    printf("\n\n\n\tTel Numarasi     Adi       Soyadi       Adres        Abone Tipi ");
    printf("\n\t-------------    ---       ------       ------       -----------\n");
    while (gecici!=liste_basi_ptr)
    {
        tip_adi=tipe_gore_adi(gecici->abone_tipi);
        printf("\t%-16lli %-9s %-12s %-14s %-16s\n",gecici->tel_nosu,gecici->adi,gecici->soyadi,gecici->adresi,tip_adi);
        gecici=gecici->tel_nosuna_gore_sonraki;
    }
}
void ada_gore_listele(struct aboneler *liste_basi_ptr)
{
    struct aboneler *gecici;   //*soyada gore yeri liste basi ptryi veriyor ve icinde geziliyor.
    char *tip_adi;
    gecici=liste_basi_ptr;
    printf("\n\n\n\n\tTel Numarasi     Adi       Soyadi       Adres        Abone Tipi ");
    printf("\n\t-------------    ---       ------       ------       -----------\n");
    while (gecici)
    {
       tip_adi=tipe_gore_adi(gecici->abone_tipi);
       printf("\t%-16lli %-9s %-12s %-14s %-16s\n",gecici->tel_nosu,gecici->adi,gecici->soyadi,gecici->adresi,tip_adi);
       gecici=gecici->soyada_gore_sonraki;
    }

}
void metin_parcasinina_gore_listelemne(struct aboneler *liste_basi_ptr,char aranan[])
{
    struct aboneler *gecici;
    char *tip_adi;
    int uzunluk_aranan,uzunluk_Ad,i,eslesme_Sayaci=0;
    uzunluk_aranan=strlen(aranan);      //*kullanicidan alinan metin uzunlugu hesaplaniyor.
    gecici=liste_basi_ptr;
    printf("\n\n\n\n\tTel Numarasi     Adi       Soyadi       Adres        Abone Tipi ");
    printf("\n\t-------------    ---       ------       ------       -----------\n");
    while (gecici)
    {
       uzunluk_Ad=strlen(gecici->soyadi); //*kullanýcýnýn soyadinin uzunlugu hesaplaniyor
       if(uzunluk_aranan<=uzunluk_Ad)          //*eger aranan uzunluk soyadan kucuk esit ise eslesme fonksiyonuna gidiyor.
       {
          for(i=0;i<uzunluk_aranan;i++)
           {
             if(toupper(gecici->soyadi[i])==toupper(aranan[i])) //*aranan metinin her harfi büyütülüyor. Soyadinin da ilk harfi büyütülüyor. Eslesme sayaci arttýrýlýyor .
                ++eslesme_Sayaci;
           }
       }

          if(eslesme_Sayaci==uzunluk_aranan)   //*eslesme sayaci metin parcasinin uzunluguna esit ise yazdiriliyor.
           {
           tip_adi=tipe_gore_adi(gecici->abone_tipi);
           printf("\t%-16lli %-9s %-12s %-14s %-16s\n",gecici->tel_nosu,gecici->adi,gecici->soyadi,gecici->adresi,tip_adi);
           }
          gecici=gecici->soyada_gore_sonraki;
          eslesme_Sayaci=0;
    }
}
void tum_aboneleri_listeleme(struct aboneler *liste_basi_ptr,int i)
{
    struct aboneler *gecici;
    struct gorusmeler *gezici,*ilk_ptr;
    char *tip_adi;
   static long long int sahis_sayaci=0,isyeri_sayaci=0,kamu_sayaci=0,guvenlik_sayaci=0,s_toplam_sure=0,i_toplam_sure=0,k_toplam_sure=0,g_toplam_sure=0,s_gorusme_sayisi=0,i_gorusme_sayisi=0,k_gorusme_sayisi=0,g_gorusme_sayisi=0;
    gecici=liste_basi_ptr;
    gecici=gecici->tel_nosuna_gore_sonraki;
     while (gecici!=liste_basi_ptr)
    {
        tip_adi=tipe_gore_adi(gecici->abone_tipi);
        printf("\t%-16lli %-9s %-12s %-14s %-16s\n",gecici->tel_nosu,gecici->adi,gecici->soyadi,gecici->adresi,tip_adi);
        ilk_ptr=gecici->gorusmeleri;
        gezici=ilk_ptr->sonraki;
        if(gecici->abone_tipi=='s'||gecici->abone_tipi=='S')
        ++sahis_sayaci;
        if(gecici->abone_tipi=='i'||gecici->abone_tipi=='I')    //*Tiplere gore abone sayisi arttiliyor.Asagida gorusmelere gorede konusma bilgileri sayaclara ekleniyor.
        ++isyeri_sayaci;
        if(gecici->abone_tipi=='k'||gecici->abone_tipi=='K')
        ++kamu_sayaci;
        if(gecici->abone_tipi=='g'||gecici->abone_tipi=='G')
        ++guvenlik_sayaci;
         while (gezici!=ilk_ptr)
         {
            if(gecici->abone_tipi=='s'||gecici->abone_tipi=='S')
            {
                ++s_gorusme_sayisi;
                s_toplam_sure+=gezici->dakika;
            }
            if(gecici->abone_tipi=='i'||gecici->abone_tipi=='I')
            {

                ++i_gorusme_sayisi;
                i_toplam_sure+=gezici->dakika;
            }
            if(gecici->abone_tipi=='k'||gecici->abone_tipi=='K')
            {

                ++k_gorusme_sayisi;
                k_toplam_sure+=gezici->dakika;
            }
            if(gecici->abone_tipi=='g'||gecici->abone_tipi=='G')
            {

                ++g_gorusme_sayisi;
                g_toplam_sure+=gezici->dakika;
            }

            gezici=gezici->sonraki;
          }
        gecici=gecici->tel_nosuna_gore_sonraki;
    }

    if(i==999)          //*Tel noya gore son aboneleri listeledigimiz icin sonunda yazdiriliyor.
    {
        printf("\n\n\n\n\tAbone Tipi   Abone Sayisi  Gorusme Sayisi  Toplam Sure  Ortalama Sure\n");
        printf("\t----------   ------------  --------------  -----------  -------------");
        printf("\n\t  %-13s   %-13lli  %-13lli  %-8lli %.2lf","Sahis",sahis_sayaci,s_gorusme_sayisi,s_toplam_sure,(double)s_toplam_sure/s_gorusme_sayisi);
        printf("\n\t  %-13s   %-13lli  %-13lli  %-8lli %.2lf","Isyeri",isyeri_sayaci,i_gorusme_sayisi,i_toplam_sure,(double)i_toplam_sure/i_gorusme_sayisi);
        printf("\n\t  %-13s   %-13lli  %-13lli  %-8lli %.2lf","Kamu",kamu_sayaci,k_gorusme_sayisi,k_toplam_sure,(double)k_toplam_sure/k_gorusme_sayisi);
        printf("\n\t  %-13s   %-13lli  %-13lli  %-8lli %.2lf","Guvenlik",guvenlik_sayaci,g_gorusme_sayisi,g_toplam_sure,(double)g_toplam_sure/g_gorusme_sayisi);
        printf("\n\t---------------------------------------------------------------------");
        printf("\n\t  %-13s   %-13lli  %-13lli  %-8lli %.2lf","Toplam",sahis_sayaci+isyeri_sayaci+kamu_sayaci+guvenlik_sayaci,s_gorusme_sayisi+i_gorusme_sayisi+k_gorusme_sayisi+g_gorusme_sayisi,s_toplam_sure+i_toplam_sure+k_toplam_sure+g_toplam_sure,(double)(s_toplam_sure+i_toplam_sure+k_toplam_sure+g_toplam_sure)/(s_gorusme_sayisi+i_gorusme_sayisi+k_gorusme_sayisi+g_gorusme_sayisi));
        sahis_sayaci=0;
        isyeri_sayaci=0;
        kamu_sayaci=0;
        guvenlik_sayaci=0;
        s_toplam_sure=0;
        i_toplam_sure=0;
        k_toplam_sure=0;
        g_toplam_sure=0;
        s_gorusme_sayisi=0;
        i_gorusme_sayisi=0;
        k_gorusme_sayisi=0;
        g_gorusme_sayisi=0;
    }


}
void belirli_tarihten_sonra_konusmayanlar(struct aboneler *liste_basi_ptr,long long int tarih)
{
    struct aboneler *gecici;
    struct gorusmeler *gezici,*ilk_ptr;
    char *tip_adi;
    int gorusme_Sayaci=0;                       //*tel noya gore hash tablosundan aboneler bulunuyor , abonelerin gorusmelerine giriliyor.
    gecici=liste_basi_ptr;
    gecici=gecici->tel_nosuna_gore_sonraki;
     while (gecici!=liste_basi_ptr)
      {
        ilk_ptr=gecici->gorusmeleri;
        gezici=ilk_ptr->onceki;
          while (gezici!=ilk_ptr)
          {
            if(atoll(gezici->tarih)>tarih)
            ++gorusme_Sayaci;
            if(gorusme_Sayaci!=0)               //*gorusme tarihinden sonra bir gorusme yapýlýrsa sayac artýyor.
            break;
            gezici=gezici->onceki;
          }
             if(gorusme_Sayaci==0)
              {
             tip_adi=tipe_gore_adi(gecici->abone_tipi);
             printf("\t%-16lli %-9s %-12s %-14s %-16s\n",gecici->tel_nosu,gecici->adi,gecici->soyadi,gecici->adresi,tip_adi);
              }
              gorusme_Sayaci=0;
             gecici=gecici->tel_nosuna_gore_sonraki;

      }
}
void bir_numarayi_arayanlar(struct aboneler *liste_basi_ptr,long long int aranan_no)
{
    struct aboneler *gecici;
    struct gorusmeler *gezici,*ilk_ptr;
    char *tip_adi;
    int arama_sayaci=0;                 //*tel noya gore aboneler bulunuyor, abonelerin gorusmeleri icinde geziliyor ve ayný numarayi arayanlar goruntuleniyor.
    gecici=liste_basi_ptr;
     while (gecici)
     {
        ilk_ptr=gecici->gorusmeleri;
        gezici=ilk_ptr->onceki;
        while (gezici!=ilk_ptr)
        {
            if(atoll(gezici->aranan_no)==aranan_no)
             ++arama_sayaci;
            if(arama_sayaci==1)
            {
             tip_adi=tipe_gore_adi(gecici->abone_tipi);
             printf("\t%-16lli %-9s %-12s %-14s %-16s\n",gecici->tel_nosu,gecici->adi,gecici->soyadi,gecici->adresi,tip_adi);
            }
            gezici=gezici->onceki;
        }
        arama_sayaci=0;
        gecici=gecici->soyada_gore_sonraki;
     }

}
void ayni_tarihte_konusanlar(struct aboneler *liste_basi_ptr,long long int tarih)
{
    struct aboneler *gezici;
    struct gorusmeler *gecici,*ilk_ptr;             //*icinde tarihler eslestigi zaman listeleniyor.
    gezici=liste_basi_ptr;
    gezici=gezici->tel_nosuna_gore_sonraki;
    while (gezici!=liste_basi_ptr)
    {
        ilk_ptr=gezici->gorusmeleri;
        gecici=ilk_ptr->onceki;
        while (gecici!=ilk_ptr)
        {
          if(atoll(gecici->tarih)==tarih)
          {
            printf("\t%c%c%c%c%c%c%c%c%c%c%c ",gecici->aranan_no[0],gecici->aranan_no[1],gecici->aranan_no[2],'-',gecici->aranan_no[3],gecici->aranan_no[4],gecici->aranan_no[5],gecici->aranan_no[6],gecici->aranan_no[7],gecici->aranan_no[8],gecici->aranan_no[9]);
            printf("\t%c%c%c%c%c%c%c%c%c%c   ",gecici->tarih[6],gecici->tarih[7],'.',gecici->tarih[4],gecici->tarih[5],'.',gecici->tarih[0],gecici->tarih[1],gecici->tarih[2],gecici->tarih[3]);
            printf("\t%c%c%c%c%c     ",gecici->baslangic_zamani[0],gecici->baslangic_zamani[1],':',gecici->baslangic_zamani[2],gecici->baslangic_zamani[3]);
            printf("\t      %i\n",gecici->dakika);
          }
          gecici=gecici->onceki;
        }
      gezici=gezici->tel_nosuna_gore_sonraki;
    }

}
void gorusmeleri_Silme(struct gorusmeler *liste_basi_ptr)
{
    struct gorusmeler *gecici,*silici;
    gecici=liste_basi_ptr->onceki;          //*gorusmelerde eskiden yeniye dogru yani sondan basa dogru geziliyor
    while (gecici!=liste_basi_ptr)
    {
        silici=gecici;
        gecici=gecici->onceki;
        free(silici);
        if(gecici==liste_basi_ptr)              //*gecici bir önde gidip , silici arkadakini siliyor.
        free(gecici);
    }
}
int hash_orani(long long tel_no)
{
    return tel_no/10000;
}
