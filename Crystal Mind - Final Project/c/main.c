#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct
{
    char nume[10];
    char prenume[10];
    int varsta;
} PERSOANA;

void scrieInFisierText(char numeFisier[], PERSOANA a[],int n)
{
    FILE *fisier;
    int i;

    fisier=fopen(numeFisier,"wt");
    if(fisier==NULL)
    {
        puts("");
        exit(1);
    }

    for(i=0; i<n; i++)
    {
        printf("Inntroduceti datele persoanei  %d: \n", i);
        printf(" nume: ");
        scanf("%s",a[i].nume);
        printf(" prenume: ");
        scanf("%s",a[i].prenume);
        printf(" varsta: ");
        scanf("%d",&a[i].varsta);
        fprintf(fisier, "%s %s %d \n",a[i].nume, a[i].prenume, a[i].varsta);

    }

    fclose(fisier);
}

void afisareContinutFisierText(char numeFisier[], PERSOANA a[], int *n)
{
    FILE *fisier;
    int nr=0;
    char buffer[200];

    fisier=fopen(numeFisier,"rt");
    if(fisier==NULL)
    {
        puts("nu");
        exit(1);
    }

    while (fgets(buffer,200,fisier)!=NULL)
    {
        sscanf (buffer,"%s %s %d",a[nr].nume, a[nr].prenume, &a[nr].varsta);

        printf ("[%d] %s %s %d \n",nr, a[nr].nume, a[nr].prenume, a[nr].varsta);

        nr++;
    }

    *n=nr;
}

void citireContinutFisierText(char numeFisier[], PERSOANA a[], int *n)
{
    FILE *fisier;
    int nr=0;
    char buffer[200];

    fisier=fopen(numeFisier,"rt");
    if(fisier==NULL)
    {
        puts("nu");
        exit(1);
    }

    while (fgets(buffer,200,fisier)!=NULL)
    {
        sscanf (buffer,"%s %s %d",a[nr].nume, a[nr].prenume, &a[nr].varsta);
        nr++;
    }

    *n=nr;
}

void adaugarePersoana(char numeFisier[], PERSOANA a[],int n, PERSOANA cautat)
{
    FILE *fisier;
    int i,exista=0;

    for(i=0; i<n; i++)
    {

        if(strcmp(a[i].nume,cautat.nume)==0 && strcmp(a[i].prenume,cautat.prenume)==0 && (a[i].varsta==cautat.varsta))
            exista=1;
    }



    if(exista==0)
    {
        fisier=fopen(numeFisier,"at");
        if(fisier==NULL)
        {
            puts("nu");
            exit(1);
        }

        fprintf(fisier, "%s %s %d \n",cautat.nume, cautat.prenume, cautat.varsta);

        fclose(fisier);
    }

}

float medieText(char numeFisier[])
{
    FILE *fisier;
    int suma=0, nr=0;;
    float medie;
    char buffer[200];

    PERSOANA a;
    int n;

    fisier=fopen(numeFisier,"rt");
    if(fisier==NULL)
    {
        puts("nu");
        exit(1);
    }


    while (fgets(buffer,200,fisier)!=NULL)
    {
        sscanf (buffer,"%s %s %d",a.nume, a.prenume, &a.varsta);

        suma =  suma + a.varsta;

        nr++;
    }

    fclose (fisier);

    medie = (float)suma/nr;

    return medie;
}

void ordonare(char numeFisier[])
{
    FILE *fisier2;
    PERSOANA aux, a[10];
    int n, i,j;


    citireContinutFisierText(numeFisier, a,&n);
    for(i=0; i<n-1; i++)
        for(j=i+1; j<n; j++)
            if(a[i].varsta>a[j].varsta)
            {
                aux=a[j];
                a[j]=a[i];
                a[i]=aux;
            }

    printf("Componentele ordonate: \n");
    for(i=0; i<n; i++)
    {
        printf(" %s %s %d / ",a[i].nume, a[i].prenume, a[i].varsta);

    }
}

void EliminaElementDinFisierText(char numeFisier[], char numeEliminat[])
{
    FILE *fisier;
    int i,j,n, dimInitiala;
    PERSOANA a[10];

    citireContinutFisierText(numeFisier, a,&n);
    dimInitiala=n;

    for(i=0; i<n; i++)
    {
        while(strcmp(a[i].nume,numeEliminat)==0 && i<n)
        {
            for(j=i; j<n; j++)
            {
                a[j]=a[j+1];
            }
            n--;
        }
    }

    if (dimInitiala==n) printf ("\nNumele nu a fost gasit\n");
    else
    {
        fisier=fopen(numeFisier,"wt");
        if(fisier==NULL)
        {
            puts("nu");
            exit(1);
        }

        for(i=0; i<n; i++)
            fprintf(fisier, "%s %s %d \n",a[i].nume, a[i].prenume, a[i].varsta);

        fclose(fisier);
    }

}

PERSOANA afisareDePePozitia(char numeFisier[], int pozitie)
{
    FILE *fisier;
    int nr=0;
    PERSOANA a;
    char buffer[200];

    fisier=fopen(numeFisier,"rt");
    if(fisier==NULL)
    {
        puts("nu");
        exit(1);
    }

    while (fgets(buffer,200,fisier)!=NULL && nr< pozitie)
    {
        nr++;
    }

    sscanf (buffer,"%s %s %d",a.nume, a.prenume, &a.varsta);


    fclose (fisier);

    return a;
}

void modificaDePePozitia(char numeFisier[], PERSOANA modificat, int pozitie)
{
    FILE *fisier;
    int i, n;
    PERSOANA a[100];

    citireContinutFisierText(numeFisier,a,&n);


    fisier=fopen(numeFisier,"wt");
           if(fisier==NULL)
    {
        puts("nu");
        exit(1);
    }
    a[pozitie] = modificat;

    for(i=0; i<n; i++)
    {
        fprintf(fisier, "%s %s %d \n",a[i].nume, a[i].prenume, a[i].varsta);
    }

    fclose (fisier);
}

int main ()
{
    PERSOANA a[10],aux, cautat, modificat;
    int i,n, poz, ok=0;
    char numeEliminat[10], optiune, numeCorect[10], numeFisier[20];
    float med;

    printf ("Introduceti numele fiserului si extensia dorita (ex. persoane.txt): ");
    scanf ("%s", numeFisier);

    printf("Cate persoane doriti sa introduceti? ");
    scanf("%d",&n);

    printf("\n -------------- Punctul a + b  ---------------\n");

    scrieInFisierText(numeFisier,a,n);
    afisareContinutFisierText(numeFisier,a,&n);


    printf("\n\n -------------- Punctul c  ---------------\n");
    printf("Introduceti datele persoanei cautate: \n");
    printf("nume : ");
    scanf("%s",cautat.nume);
    printf("prenume :");
    scanf("%s",cautat.prenume);
    printf("varsta :" );
    scanf("%d",&cautat.varsta);

    adaugarePersoana(numeFisier,a,n,cautat);
    printf ("Continutul fisierului dupa adaugare: \n");
    afisareContinutFisierText(numeFisier,a,&n);


    printf("\n\n -------------- Punctul d  ---------------\n");
    med=medieText(numeFisier);
    printf("Media de varsta a persoanelor din fisier %.2f",med);


    printf("\n\n -------------- Punctul e  ---------------\n");
    ordonare(numeFisier);


    printf("\n\n -------------- Punctul f  ---------------\n");
    printf("Introduceti numele ce trebuie sters: \n");
    scanf("%s", numeEliminat);
    EliminaElementDinFisierText(numeFisier,numeEliminat);
    printf ("\nContinutul fisierului dupa eliminare: \n");
    afisareContinutFisierText(numeFisier,a,&n);


    printf("\n\n -------------- Punctul g  ---------------\n");
    puts(" \n\nPentru ce pozitie doriti sa vizualizati informatiile");
    scanf("%d",&poz);
    modificat=afisareDePePozitia(numeFisier,poz);
    printf ("\n[%d]: %s %s %d", poz, modificat.nume, modificat.prenume, modificat.varsta);
    puts(" \nDoriti sa modificati numele (D/N?)");
    fflush(stdin);
    scanf ("%c", &optiune);
    if (optiune=='n' || optiune=='N') return 0;
    else if (optiune=='d' || optiune=='D')
    {
        printf("Introduceti numele corect: ");
        scanf ("%s", numeCorect);
        strcpy(modificat.nume,numeCorect);
        modificaDePePozitia(numeFisier, modificat, poz);
    }
    printf ("Continutul fisierului dupa modificarea numelui: \n");
    afisareContinutFisierText(numeFisier,a,&n);


    return 0;
}
