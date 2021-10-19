#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_NUM 128

typedef struct _stud{
    char ime[20];
    char prezime[20];
    int bodovi;
}stud;

int ProcitajBrojRedakaIzDatoteke(char imeFajla[]);
stud* AlocirajProstorIProcitajStudente(int br, char imeFajla[]);
int TraziNajveciBrojBodova(stud* sviPodaciStudenata, int brojSt);
float RacunaRelativanBrBodova(int brBodova, int max_br_bodova);

int main(){
    char imeDatoteke[25]={0};
    int brojSt=0, max_br_bodova=0;
    stud* sviPodaciStudenata=NULL;

    printf("Unesite ime datoteke sa podacima studenata:\t");
    scanf("%s", imeDatoteke);

    brojSt = ProcitajBrojRedakaIzDatoteke(imeDatoteke);
    if(brojSt==-1){
        return 0;
    }

    sviPodaciStudenata = AlocirajProstorIProcitajStudente(brojSt, imeDatoteke);
    if(sviPodaciStudenata==NULL){
        return 0;
    }

    puts(" ");

    max_br_bodova=TraziNajveciBrojBodova(sviPodaciStudenata, brojSt);

    for(int i=0; i<brojSt; i++){
        printf("\t%s %s:\t\t %d | %.2f\n", sviPodaciStudenata[i].ime, sviPodaciStudenata[i].prezime, sviPodaciStudenata[i].bodovi, RacunaRelativanBrBodova(sviPodaciStudenata[i].bodovi, max_br_bodova));
    }

}


int ProcitajBrojRedakaIzDatoteke(char imeFajla[]){
    FILE* fp= NULL;
    char ucenici[MAX_NUM][MAX_LINE]={0};
    int brojac=0;

    fp=fopen(imeFajla, "r");

    if(fp==NULL){
        printf("Nije moguce pristupiti file-u.\n");
        return -1;
    }

    while(!feof(fp)){
        fgets(ucenici[brojac], MAX_LINE, fp);
        brojac++;
    }

    //printf("\nIma %d studenta.\n\n", brojac);

    fclose(fp);

    return brojac;
}

stud* AlocirajProstorIProcitajStudente(int br, char imeFajla[])
{
    FILE* fp=NULL;
    stud* studenti=NULL;
    int brojilo=0;

    studenti=(stud*)malloc(br*sizeof(stud));

    fp=fopen(imeFajla, "r");

    if(fp==NULL){
        printf("Nije moguce pristupiti file-u.\n");
        free(studenti);
        return NULL;
    }

     while(!feof(fp)){
        fscanf(fp, " %s %s %d", studenti[brojilo].ime, studenti[brojilo].prezime, &studenti[brojilo].bodovi);
        brojilo++;
    }

    return studenti;

}

int TraziNajveciBrojBodova(stud* sviPodaciStudenata, int brojSt){
    int pomocniNiz[128]={0};
    int max=sviPodaciStudenata[0].bodovi;

    for(int i=1; i<brojSt; i++){
            if(max<sviPodaciStudenata[i].bodovi){
                max=sviPodaciStudenata[i].bodovi;
            }
    }

    return max;
}


float RacunaRelativanBrBodova(int brBodova, int max_br_bodova){

    return((brBodova/(float) max_br_bodova)*100);

}


