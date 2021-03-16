#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "string.h"
#include <ctype.h>

#define N 10
#define hane 30
int kayitli_mi(long int);
int dosya_sorgulama(void);
int numerik_mi(long int );
char cinsiyet_sorgu(char );

int b=0;
int i=1;
int a=1;
int secim=0;
long int aranacakNo;
float max_ort;
char cikis;
long int ogr_nosu;

typedef struct {
   long no;
   char ad[15];
   char bolum[15];
   int notu;
} ogrenci;// yap� tan�mlamay� b�yle yaparsan, program� yazarken kolayl�k sa�lar sana struct falan yazmana kalmaz tan�mlarken
 
 
 typedef struct {
long int ogrNo;
	char ad[30];
	char soyad[30];
	char cinsiyet;		// E: Erkek, K:Kiz
	//char *bolum;
	char bolum[20];
	float ortalama;
} Ogrenci;


Ogrenci ogr_f;//dosyadan okunacak ��renci bilgileri i�in bir de�i�ken olu�turuluyor


// bu da numune

FILE *dosya;
FILE *dosya2;

main()
{
   
  
  while(a)
  {
   
   printf("Ogrenci Ekle 		-> 1	\nOgrenci Sil 		-> 2  \nOgrenci Guncelle	-> 3  \nFakulte Birincisi	-> 4\nCikis			-> 5  \n");
   scanf("%d", &secim);
   switch(secim)
   {
   	case 1: //��renci Ekle
   	Ogrenci ogr;
   	
   	printf("Ogrencinin");
	printf("\n   Numarasi  : "); scanf("%ld", &ogr.ogrNo);
	if(b==1)
	{
	while(kayitli_mi(ogr.ogrNo))
   	{
   		printf("Ogrenci kayitli\n");
   		scanf("%ld", &ogr.ogrNo);
   	}
	   b=1;	
	}

	
	printf("   Adi       : "); scanf("%s", ogr.ad);
	printf("   Soyadi    : "); scanf("%s", ogr.soyad);
	
	i=1;
	printf("   Cinsiyeti : "); 
	while(i)
	{
	scanf("%s", &ogr.cinsiyet);	
	ogr.cinsiyet = cinsiyet_sorgu(ogr.cinsiyet);
	if(ogr.cinsiyet=='E'||ogr.cinsiyet=='K')
	{
		i=0;
	}
	}
	
	
	//printf("   Bolumu    : "); scanf("%s", &ogr.bolum);//*bolum olmas� laz�m bu nas�l olacak??? %c olmas� gerekebilir mi ogr.*bolum yaz�lamaz onun yerine &ogr.bolum yaz�l�r
	printf("   Bolumu    : "); scanf("%s", ogr.bolum);
	printf("   Ortalamasi: "); scanf("%f", &ogr.ortalama);
	
	dosya=fopen("ogrenciler.txt","a");
	fprintf(dosya, "%ld\t%s\t%s\t%c\t%s\t%.2f\n", ogr.ogrNo, ogr.ad, ogr.soyad, ogr.cinsiyet, ogr.bolum, ogr.ortalama);
   	//fprintf(dosya,"%d\t%s\t%s\t%c\t%s\t%.2f\n", ogr.ogrNo,ogr.ad, ogr.soyad, ogr.cinsiyet, &ogr.bolum, ogr.ortalama );//D�KKAT ogr.bolum deki veriye ula�mak i�in ba��na adres operat�r� koyulur ��nk� ogr.*bolum diye �a��ram�yoruz burda
   	
   	fclose(dosya);
   	printf("%s isimli ogrencinin kaydi yapilmistir.",ogr.ad);
   	getch();
   	system("CLS");//konsol ekran� temizleme
   		
   	break;
   	
   	
   	case 2:	//��renci Sil
   	if(dosya_sorgulama())
   	{
	
   	printf("Kaydini silmek istediginiz ogrencinin numarasini giriniz\n");
   	scanf("%ld",&aranacakNo);
   	
   	
  	while(!kayitli_mi(aranacakNo))
   	{
   		printf("Ogrenci kayitli degil\n");
   		scanf("%ld",&aranacakNo);
   	}
	dosya=fopen("ogrenciler.txt","r");
	dosya2=fopen("ogrenciler2.txt","w");
	
	   	while(!feof(dosya))
   	{
   		fscanf(dosya,"%ld%s%s%s%s%f", &ogr_f.ogrNo, ogr_f.ad, ogr_f.soyad, &ogr_f.cinsiyet, ogr_f.bolum, &ogr_f.ortalama);
   		if(ogr_f.ogrNo==aranacakNo)
   		{	
			printf("%s isimli ogrencinin kaydi silinmistir.\n", ogr_f.ad);
		}
		else
		{
			fprintf(dosya2,"%ld\t%s\t%s\t%c\t%s\t%.2f\n", ogr_f.ogrNo, ogr_f.ad, ogr_f.soyad, ogr_f.cinsiyet, ogr_f.bolum, ogr_f.ortalama);	
		}
    }
	fclose(dosya);
	fclose(dosya2);
	
	remove("ogrenciler.txt");	
	rename("ogrenciler2.txt", "ogrenciler.txt");
	}
	getch();
   	system("CLS");//konsol ekran� temizleme

   	break;
   	
   	
   	
   	case 3:	//��renci G�ncelle
   	
	if(dosya_sorgulama())
	{
	
	
   	printf("Kaydini guncellemek istediginiz ogrencinin numarasini giriniz\n");
   	scanf("%ld",&aranacakNo);
   	
  	while(!kayitli_mi(aranacakNo))
   	{
   		printf("Ogrenci kayitli degil\n");
   		scanf("%ld",&aranacakNo);
   	}
   	
	dosya=fopen("ogrenciler.txt","r");
	dosya2=fopen("ogrenciler2.txt","w");
	
	   	while(!feof(dosya))
   	{
   		fscanf(dosya,"%ld%s%s%s%s%f", &ogr_f.ogrNo, ogr_f.ad, ogr_f.soyad, &ogr_f.cinsiyet, ogr_f.bolum, &ogr_f.ortalama);
   		if(ogr_f.ogrNo==aranacakNo)
   		{	
			printf("%ld\t%s\t%s\t%c\t%s\t%.2f\n", ogr_f.ogrNo, ogr_f.ad, ogr_f.soyad, ogr_f.cinsiyet, ogr_f.bolum, ogr_f.ortalama);
			
			printf("Ogrencinin Yeni Bilgileri");
			printf("\n   Numarasi  : "); scanf("%ld", &ogr_f.ogrNo);
			printf("   Adi       : "); scanf("%s", ogr_f.ad);
			printf("   Soyadi    : "); scanf("%s", ogr_f.soyad);
			printf("   Cinsiyeti : "); scanf("%s", &ogr_f.cinsiyet);
			
	
			printf("   Ortalamasi: "); scanf("%f", &ogr_f.ortalama);
	
			fprintf(dosya2, "%ld\t%s\t%s\t%c\t%s\t%.2f\n", ogr_f.ogrNo, ogr_f.ad, ogr_f.soyad, ogr_f.cinsiyet, ogr_f.bolum, ogr_f.ortalama);	
			}  
		else
		{
		fprintf(dosya2,"%ld\t%s\t%s\t%c\t%s\t%.2f\n", ogr_f.ogrNo, ogr_f.ad, ogr_f.soyad, ogr_f.cinsiyet, ogr_f.bolum, ogr_f.ortalama);		
		}
    }
	
	fclose(dosya);
		
	fclose(dosya2);
	
	remove("ogrenciler.txt");
	
	rename("ogrenciler2.txt", "ogrenciler.txt");
    }
	getch();
   	system("CLS");//konsol ekran� temizleme
   	
   	break;
   	
   	
   	case 4:	//Fak�lte Birincisi
	
	max_ort = -1;
	dosya=fopen("ogrenciler.txt","r");
	if(dosya_sorgulama())
	{
	
   	while(!feof(dosya))
	{
		fscanf(dosya,"%ld%s%s%s%s%f", &ogr_f.ogrNo, ogr_f.ad, ogr_f.soyad, &ogr_f.cinsiyet, ogr_f.bolum, &ogr_f.ortalama);
		if(ogr_f.ortalama>max_ort)
		max_ort=ogr_f.ortalama;
	}
	fclose(dosya);
	
	dosya=fopen("ogrenciler.txt","r");
	while(!feof(dosya))
	{
		fscanf(dosya,"%ld%s%s%s%s%f", &ogr_f.ogrNo, ogr_f.ad, ogr_f.soyad, &ogr_f.cinsiyet, ogr_f.bolum, &ogr_f.ortalama);
		if(ogr_f.ortalama==max_ort)
		printf("%s isimli ogrenci fakulte birincisi olmustur.\n", ogr_f.ad );
	}

   		
   	fclose(dosya);	
   	
   }
   getch();
   system("CLS");//konsol ekran� temizleme
   break;
   	
   	case 5:	//��k��
   	printf("E(evet) ye basarsaniz program kapanacak\n");
   	
   	scanf("%s",&cikis);			//			SOR BURADA NEDEN GETCHAR KULLANDI�IMIZDA BEKLEM�YOR PROGRAM???
	if((cikis=='E') || (cikis=='e')) return 0;

   }
   

}	
 	return 0;
}

   
   int kayitli_mi(long int aranacak)
   {
   	dosya=fopen("ogrenciler.txt","r");
   	while(!feof(dosya))
   	{
   		fscanf(dosya,"%ld%s%s%s%s%f", &ogr_f.ogrNo, ogr_f.ad, ogr_f.soyad, &ogr_f.cinsiyet, ogr_f.bolum, &ogr_f.ortalama);
   		if(ogr_f.ogrNo==aranacak)
   		{
			fclose(dosya);
			return 1;
		}
    }
    fclose(dosya);
    return 0;
   }
   
   int numerik_mi(long int taranacak)
   {
   	if((taranacak>=1000000) && (taranacak<=9999999)) 
   	{
   	  return 0;
    }
   	else
	{
   	   return 1;
	}	
   }
   
   
   int dosya_sorgulama(void)
   {
   	dosya=fopen("ogrenciler.txt","r");
   	if(dosya==NULL)
	   {
	   	printf("Dosya acilamadi.\n");
	   	fclose(dosya);
		return 0;
		} 
	else
	{
	fclose(dosya);
	return 1;	
	} 
   }
   
   char cinsiyet_sorgu(char cins )
   {
   	if(cins=='E'|| cins=='e') 
   	{
   		return 'E';
	}
	
	else if(cins=='K'||cins=='k')
	{
		return 'K';
	}
	else
	{
		printf("Yalnizca E(e) veya K(k) yaziniz.");
		return '\0';
	}
	
   }
   
   
