#include <stdio.h>
#include <stdlib.h>
                               //200202046             200202012
struct ogrenci
{
    int ogrNo;
    int dersKodu;
    int puan;

    struct ogrenci *next;
};

typedef struct ogrenci node;

void menu()
{
    printf("\n-----------Menu-----------\n");
    printf("1-)Index dosyasini olustur.\n");
    printf("2-)Kayit ekle.\n");
    printf("3-)Kayit bul.\n");
    printf("4-)Kayit sil.\n");
    printf("5-)Kayit guncelle.\n");
    printf("6-)Veri dosyasini goster.\n");
    printf("7-)Index dosyasini goster.\n");
    printf("8-)Index dosyasini sil.\n");
    printf("0-)Cikis.\n");
}

void kayitEkle(int numara,int derskodu,int puan)
{
    node *temp=(node *)malloc(sizeof(node));
    FILE *dosyaptr = fopen("veri.bin","ab");

    if(dosyaptr==NULL)
    {
        printf("Dosya acilamadi");
        exit(1);
    }

     temp->ogrNo=numara;
     temp->dersKodu=derskodu;
     temp->puan=puan;
     temp->next=NULL;

     fwrite(temp,sizeof(node),1,dosyaptr);
     fclose(dosyaptr);

}

void veriDosyasiniGoster()
{
    node *iter=(node *)malloc(sizeof(node));
     FILE *dosyaptr = fopen("veri.bin","rb");
      if(dosyaptr==NULL)
      {
          printf("Dosya acilamadi.");
         exit(1);
      }

      fread(iter,sizeof(node),1,dosyaptr);

      while(!feof(dosyaptr))
      {
          printf("%d    %d     %d\n",iter->ogrNo,iter->dersKodu,iter->puan);
          fread(iter,sizeof(node),1,dosyaptr);
      }
      fclose(dosyaptr);

}

node * sirayaDiz(node *r)
{
   node *root=NULL;

      while(r!=NULL)
      {
          if(root==NULL)
          {
              root=(node *)malloc(sizeof(node));
              root->next=NULL;
              root->ogrNo=r->ogrNo;
              root->dersKodu=r->dersKodu;
              root->puan=r->puan;

              r=r->next;
               continue;
          }
          if(root->ogrNo >= r->ogrNo)
          {
              node *temp=(node *)malloc(sizeof(node));
               temp->ogrNo=r->ogrNo;
               temp->dersKodu=r->dersKodu;
               temp->puan=r->puan;

               temp->next=root;
               root=temp;
               r=r->next;
               continue;

          }

          node *iter=root;
        while(iter->next!=NULL && iter->next->ogrNo <= r->ogrNo)
        {
              iter=iter->next;
        }
         node * temp =(node *)malloc(sizeof(node));
         temp->ogrNo=r->ogrNo;
         temp->dersKodu=r->dersKodu;
         temp->puan=r->puan;

         temp->next=iter->next;
         iter->next=temp;

         r=r->next;

      }

      return root;

}

void indexDosyasiOlustur()
{
    node *r=(node *)malloc(sizeof(node));
    node *iter=(node *)malloc(sizeof(node));

      FILE *dosyaptr = fopen("veri.bin","rb");
      if(dosyaptr==NULL)
      {
          printf("Dosya acilamadi.");
          exit(1);
      }
        fread(r,sizeof(node),1,dosyaptr);
        iter=r;

        while(!feof(dosyaptr))
        {
            iter->next=(node *)malloc(sizeof(node));
            iter=iter->next;
            fread(iter,sizeof(node),1,dosyaptr);
            iter->next=NULL;

        }
            fclose(dosyaptr);
        iter=r;

        while(iter->next->next->next!=NULL)
        {
            iter=iter->next;
        }

        node *sil;
         sil=iter->next->next;
           iter->next->next=NULL;
             free(sil);

        r=sirayaDiz(r);

        iter=r;

        dosyaptr=fopen("indeks.txt","w");

        if(dosyaptr==NULL)
        {
            printf("Dosya acilamadi.");
            exit(2);
        }

        while(iter!=NULL)
        {
            fprintf(dosyaptr,"%d      %d     %d     %d\n",&(iter->ogrNo),iter->ogrNo,iter->dersKodu,iter->puan);
             iter=iter->next;
        }
           fclose(dosyaptr);
}

void indeksDosyasiniGoster()
{
    FILE *dosyaptr = fopen("indeks.txt","r");

    if(dosyaptr==NULL)
    {
        printf("Dosya acilamadi\n");
        exit(1);
    }
    int adres=0;
      node *temp=(node *)malloc(sizeof(node));
            temp->next=NULL;

         fscanf(dosyaptr,"%d %d %d %d",&adres,&temp->ogrNo,&temp->dersKodu,&temp->puan);

      while(!feof(dosyaptr))
      {
          printf("%d     %d    %d     %d\n",adres,temp->ogrNo,temp->dersKodu,temp->puan);
            fscanf(dosyaptr,"%d %d %d %d",&adres,&temp->ogrNo,&temp->dersKodu,&temp->puan);
      }
      fclose(dosyaptr);

}

void indeksDosyasiniSil()
{
    remove("indeks.txt");
    printf("indeks dosyasi silindi.\n");

}

void kayitBul()
{
    FILE *dosyaptr = fopen("indeks.txt","r");
     if(dosyaptr==NULL)
     {
         printf("Dosya acilamadi.\n");
         exit(1);
     }

     int tutucu=0;

     int *buff=(int *)malloc(sizeof(int));
       fscanf(dosyaptr,"%d",&tutucu);
       fscanf(dosyaptr,"%d",buff);
       fscanf(dosyaptr,"%d",&tutucu);
       fscanf(dosyaptr,"%d",&tutucu);


      int i=2;
      int n=1;

       while(!feof(dosyaptr))
       {
           buff=(int *)realloc(buff,i*sizeof(int));
           fscanf(dosyaptr,"%d",&tutucu);
           fscanf(dosyaptr,"%d",(buff+n));
           fscanf(dosyaptr,"%d",&tutucu);
           fscanf(dosyaptr,"%d",&tutucu);
           n++;
           i++;
       }

       i--;
       n--;
       buff=(int*)realloc(buff,i*sizeof(int));
        fclose(dosyaptr);


   printf("Aramak istediginiz ogrencinin numarasini giriniz:");
   int x=0;
   scanf("%d",&x);
   fflush(stdin);
        int ilk_indeks=BinarySearch(buff,n,x,1);
        int son_indeks;
        if(ilk_indeks==-1)
        {
            printf("Aradiginiz ogrenci listede bulunmamaktadir.\n");
            exit(2);
        }
        else
        {
            son_indeks=BinarySearch(buff,n,x,0);
        }

       //   printf("[%d,%d]\n",ilk_indeks,son_indeks);   Binary serach ile bulunan sayilarin indeksleri

        dosyaptr=fopen("indeks.txt","r");
      node *root=(node *)malloc(sizeof(node));
      root->next=NULL;
      node *iter=root;

      int adres=0;

      fscanf(dosyaptr,"%d %d %d %d",&adres,&iter->ogrNo,&iter->dersKodu,&iter->puan);

        while(!feof(dosyaptr))
        {
            iter->next=(node *)malloc(sizeof(node));
            iter=iter->next;
            fscanf(dosyaptr,"%d %d %d %d",&adres,&iter->ogrNo,&iter->dersKodu,&iter->puan);
            iter->next=NULL;

        }

          fclose(dosyaptr);
            iter=root;
       while(iter->next->next->next!=NULL)
        {
           iter=iter->next;
        }

       node *sil;
         sil=iter->next->next;
           iter->next->next=NULL;
             free(sil);

        iter=root;

    for(i=0;i<ilk_indeks;i++)
    {
        iter=iter->next;
    }


    for(i=0; i<=(son_indeks-ilk_indeks);i++)
    {
        printf("%d       %d      %d      %d\n",&(iter->ogrNo),iter->ogrNo,iter->dersKodu,iter->puan);
        iter=iter->next;
    }

}

int BinarySearch(int *buff,int n,int x,int searchFirst)
{
    int alcak=0, yuksek=n-1, sonuc=-1;

      while(alcak<=yuksek)
      {
          int orta=(yuksek+alcak)/2;
            if(*(buff+orta)==x)
            {
                sonuc=orta;
                if(searchFirst==1)
                {
                    yuksek=orta-1;

                }
                else if(searchFirst==0)
                {
                    alcak=orta+1;
                }
            }

            else if(x < *(buff+orta))
            {
                yuksek=orta-1;

            }

            else
            {
                alcak=orta+1;

            }
      }

      return sonuc;
}

void kayitSil()
{
    FILE *dosyaptr = fopen("indeks.txt","r");
     if(dosyaptr==NULL)
     {
         printf("Dosya acilamadi.\n");
         exit(1);
     }

     int tutucu=0;

     int *buff=(int *)malloc(sizeof(int));
       fscanf(dosyaptr,"%d",&tutucu);
       fscanf(dosyaptr,"%d",buff);
       fscanf(dosyaptr,"%d",&tutucu);
       fscanf(dosyaptr,"%d",&tutucu);


      int i=2;
      int n=1;

       while(!feof(dosyaptr))
       {
           buff=(int *)realloc(buff,i*sizeof(int));
           fscanf(dosyaptr,"%d",&tutucu);
           fscanf(dosyaptr,"%d",(buff+n));
           fscanf(dosyaptr,"%d",&tutucu);
           fscanf(dosyaptr,"%d",&tutucu);
           n++;
           i++;
       }

       i--;
       n--;
       buff=(int*)realloc(buff,i*sizeof(int));
        fclose(dosyaptr);


   printf("Aramak istediginiz ogrencinin numarasini giriniz:");
   int x=0;
   scanf("%d",&x);
   fflush(stdin);
        int ilk_indeks=BinarySearch(buff,n,x,1);
        int son_indeks;
        if(ilk_indeks==-1)
        {
            printf("Aradiginiz ogrenci listede bulunmamaktadir.\n");
            exit(2);
        }
        else
        {
            son_indeks=BinarySearch(buff,n,x,0);
        }

         // printf("[%d,%d]\n",ilk_indeks,son_indeks);

          int kod=0;

        printf("Ders kodunu giriniz:");
        scanf("%d",&kod);
        fflush(stdin);

    dosyaptr=fopen("indeks.txt","r");
      node *root=(node *)malloc(sizeof(node));
      root->next=NULL;
      node *iter=root;
      int adres=0;


      fscanf(dosyaptr,"%d %d %d %d",&adres,&iter->ogrNo,&iter->dersKodu,&iter->puan);

        while(!feof(dosyaptr))
        {
            iter->next=(node *)malloc(sizeof(node));
            iter=iter->next;
            fscanf(dosyaptr,"%d %d %d %d",&adres,&iter->ogrNo,&iter->dersKodu,&iter->puan);
            iter->next=NULL;

        }

          fclose(dosyaptr);
            iter=root;
       while(iter->next->next->next!=NULL)
        {
           iter=iter->next;
        }

       node *sil;
         sil=iter->next->next;
           iter->next->next=NULL;
             free(sil);

             iter=root;

    for(i=0;i<ilk_indeks;i++)
    {
        iter=iter->next;
    }

   int check=-1;
   int indeks_say=ilk_indeks;

    for(i=0;i<=(son_indeks-ilk_indeks);i++)
    {
        if(iter->dersKodu==kod)
        {
            check=0;
            break;
        }
        else
        {
            iter=iter->next;
            indeks_say++;
        }
    }

    if(check==-1)
    {
        printf("Girdiginiz numara ait ders kodu listede bulunmamaktadir.\n");
        exit(3);
    }

    iter=root;

    node *temp;
    if(indeks_say==0)
    {
        temp=root;
        root=root->next;
        free(temp);

    }


    else
    {
        iter=root;

      for(i=0;i<(indeks_say-1);i++)
      {
        iter=iter->next;

      }

        temp=iter->next;
        iter->next=iter->next->next;
        free(temp);

    }

    iter=root;

    veri_dosyasi_guncelle(root);

}

void veri_dosyasi_guncelle(node *r)
{
    FILE *dosyaptr = fopen("veri.bin","wb");

    if(dosyaptr==NULL)
    {
        printf("Dosya acilamadi.\n");
        exit(1);
    }
    node *iter;
    iter=r;
      while(iter!=NULL)
      {
          fwrite(iter,sizeof(node),1,dosyaptr);
          iter=iter->next;
      }
      fclose(dosyaptr);
}


void kayitGuncelle()
{
    FILE *dosyaptr = fopen("indeks.txt","r");
     if(dosyaptr==NULL)
     {
         printf("Dosya acilamadi.\n");
         exit(1);
     }

     int tutucu=0;

     int *buff=(int *)malloc(sizeof(int));
       fscanf(dosyaptr,"%d",&tutucu);
       fscanf(dosyaptr,"%d",buff);
       fscanf(dosyaptr,"%d",&tutucu);
       fscanf(dosyaptr,"%d",&tutucu);


      int i=2;
      int n=1;

       while(!feof(dosyaptr))
       {
           buff=(int *)realloc(buff,i*sizeof(int));
           fscanf(dosyaptr,"%d",&tutucu);
           fscanf(dosyaptr,"%d",(buff+n));
           fscanf(dosyaptr,"%d",&tutucu);
           fscanf(dosyaptr,"%d",&tutucu);
           n++;
           i++;
       }

       i--;
       n--;
       buff=(int*)realloc(buff,i*sizeof(int));
        fclose(dosyaptr);


   printf("Aramak istediginiz ogrencinin numarasini giriniz:");
   int x=0;
   scanf("%d",&x);
   fflush(stdin);
        int ilk_indeks=BinarySearch(buff,n,x,1);
        int son_indeks;
        if(ilk_indeks==-1)
        {
            printf("Aradiginiz ogrenci listede bulunmamaktadir.\n");
            exit(2);
        }
        else
        {
            son_indeks=BinarySearch(buff,n,x,0);
        }

         // printf("[%d,%d]\n",ilk_indeks,son_indeks);Binary search ile bulunan egerlerin indeks araligi

          int kod=0;

        printf("Ders kodunu giriniz:");
        scanf("%d",&kod);
        fflush(stdin);


      dosyaptr=fopen("indeks.txt","r");
      node *root=(node *)malloc(sizeof(node));
      root->next=NULL;
      node *iter=root;
      int adres=0;


      fscanf(dosyaptr,"%d %d %d %d",&adres,&iter->ogrNo,&iter->dersKodu,&iter->puan);

        while(!feof(dosyaptr))
        {
            iter->next=(node *)malloc(sizeof(node));
            iter=iter->next;
            fscanf(dosyaptr,"%d %d %d %d",&adres,&iter->ogrNo,&iter->dersKodu,&iter->puan);
            iter->next=NULL;

        }

          fclose(dosyaptr);

            iter=root;
       while(iter->next->next->next!=NULL)
        {
           iter=iter->next;
        }

       node *sil;
         sil=iter->next->next;
           iter->next->next=NULL;
             free(sil);

            iter=root;

    for(i=0;i<ilk_indeks;i++)
    {
        iter=iter->next;
    }

   int check=-1;
   int indeks_say=ilk_indeks;

    for(i=0;i<=(son_indeks-ilk_indeks);i++)
    {
        if(iter->dersKodu==kod)
        {
            check=0;
            break;
        }
        else
        {
            iter=iter->next;
            indeks_say++;
        }
    }

    if(check==-1)
    {
        printf("Girdiginiz numara ait ders kodu listede bulunmamaktadir.\n");
        exit(3);
    }

    iter=root;

    printf("Guncellemek istediginiz not degerini giriniz:");
    int not=0;
    scanf("%d",&not);
    fflush(stdin);

    if(indeks_say==0)
    {
        root->puan=not;
    }
    else
    {
        iter=root;
        for(int i=0;i<indeks_say;i++)
        {
            iter=iter->next;
        }
        iter->puan=not;
    }

    veri_dosyasi_guncelle(root);

}

int main()
{

int sayi=-1,numara=0,derskodu=0,puan=0;


/*
kayitEkle(200202001,1,60);
kayitEkle(200202001,2,70);
kayitEkle(200202001,3,75);
kayitEkle(200202001,4,80);
kayitEkle(200202001,5,100);
kayitEkle(200202002,1,40);
kayitEkle(200202002,2,60);
kayitEkle(200202002,3,80);
kayitEkle(200202002,4,90);
kayitEkle(200202002,5,40);
kayitEkle(200202003,1,20);
kayitEkle(200202003,2,70);
kayitEkle(200202003,3,90);
kayitEkle(200202003,4,100);
kayitEkle(200202003,5,100);
kayitEkle(200202004,1,80);
kayitEkle(200202004,2,60);
kayitEkle(200202004,3,75);
kayitEkle(200202004,4,70);
kayitEkle(200202004,5,80);
kayitEkle(200202005,1,30);
kayitEkle(200202005,2,40);
kayitEkle(200202005,3,65);
kayitEkle(200202005,4,70);
kayitEkle(200202005,5,90);
kayitEkle(200202006,1,10);
kayitEkle(200202006,2,20);
kayitEkle(200202006,3,30);
kayitEkle(200202006,4,40);
kayitEkle(200202006,5,50);
kayitEkle(200202007,1,100);
kayitEkle(200202007,2,100);
kayitEkle(200202007,3,100);
kayitEkle(200202007,4,100);
kayitEkle(200202007,5,100);
kayitEkle(200202008,1,65);
kayitEkle(200202008,2,75);
kayitEkle(200202008,3,90);
kayitEkle(200202008,4,80);
kayitEkle(200202008,5,100);
kayitEkle(200202009,1,20);
kayitEkle(200202009,2,80);
kayitEkle(200202009,3,60);
kayitEkle(200202009,4,70);
kayitEkle(200202009,5,80);
kayitEkle(200202010,1,80);
kayitEkle(200202010,2,90);
kayitEkle(200202010,3,90);
kayitEkle(200202010,4,80);
kayitEkle(200202010,5,75);
*/

    while(1)
    {
        system ("CLS");
           menu();
         printf("Lutfen yapmak istediginiz islemi seciniz [0-8]:");
         scanf("%d",&sayi);
         fflush(stdin);
         if(sayi==0)
            break;
        switch(sayi)
        {
        case 1:
            {
                indexDosyasiOlustur();
                printf("index dosyasi olusturulmustur.\n");
                printf("Gecmek icin bir tusa basiniz...\n");
                getch();
                break;
            }
        case 2:
            {
                printf("Ogrenci numarasini giriniz:");
                scanf("%d",&numara);
                fflush(stdin);
                printf("Ders kodunu giriniz:");
                scanf("%d",&derskodu);
                fflush(stdin);
                printf("Puani giriniz:");
                scanf("%d",&puan);
                fflush(stdin);
                kayitEkle(numara,derskodu,puan);
                printf("Kayit eklenmistir.\n");
                indexDosyasiOlustur();
                printf("Gecmek icin bir tusa basiniz...\n");
                getch();
                break;
            }
        case 3:
            {
                kayitBul();
                printf("Anahtara ait kayitlar bulunmustur.\n");
                printf("Gecmek icin bir tusa basiniz...\n");
                getch();
                break;
            }
        case 4:
            {
                kayitSil();
                printf("Kayit silinmistir.\n");
                indexDosyasiOlustur();
                printf("Gecmek icin bir tusa basiniz...\n");
                getch();
                break;
            }
        case 5:
            {
                kayitGuncelle();
                printf("Kayit guncellenmistir.\n");
                indexDosyasiOlustur();
                printf("Gecmek icin bir tusa basiniz...\n");
                getch();
                break;

            }
        case 6:
            {
                veriDosyasiniGoster();
                printf("Veri dosyasi gosterilmistir.\n");
                printf("Gecmek icin bir tusa basiniz...\n");
                getch();
                break;
            }
        case 7:
            {
                indeksDosyasiniGoster();
                printf("Index dosyasi gosterilmistir.\n");
                 printf("Gecmek icin bir tusa basiniz...\n");
                getch();
                break;
            }
        case 8:
            {
                indeksDosyasiniSil();
                printf("Index dosyasi silinmistir.\n");
                 printf("Gecmek icin bir tusa basiniz...\n");
                getch();
                break;
            }
        default:
            {
                printf("Boyle bir islem gecerli degildir.\n");
                printf("Gecmek icin bir tusa basiniz...\n");
                getch();
                break;
            }
        }

    }

  return 0;
}
