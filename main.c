#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _5_CHOICE_QUESTION_COUNT 13
#define _3_CHOICE_QUESTION_COUNT 6
#define LONG_QUESTION_COUNT 4

#define FILENAME "res.txt"

int n;

int answers5[_5_CHOICE_QUESTION_COUNT][5];
int answers3[_3_CHOICE_QUESTION_COUNT][3];

char* questions5[_5_CHOICE_QUESTION_COUNT] = {
    "1. Dersin genel degerlendirilmesi",
    "2. Konu hakimiyeti",
    "Ogretme ve iletisim yetenegi",
    "Sorulari cevaplama yetenegi",
    "3. Powerpoint",
    "Flipchart",
    "Whiteboard",
    "Hand-outs",
    "Video/DVD",
    "3. Uygun Havalandirma, Isitma ve Aydinlatma",
    "Dersligin Ses Yalitimi?",
    "Yeterli Sayida Ogrenci Icin Oturma Yeri?",
    "Ogrencilerin Dersi Dinlemesi icin Uygun Sinif Duzeni Saglanmasi?" 
};
char* questions3[_3_CHOICE_QUESTION_COUNT] = {
    "4. Ders",
    "Grup calismasi",
    "Sorular icin zaman",
    "Tum program",
    "5. Konu icerigi",
    "5. Sunum Calisma Alaninizin Belirli Ihtiyaclarini Karsiliyor mu" 
};
char* questions_long[LONG_QUESTION_COUNT] = {
    "En faydali olan malzeme ve konular hangileriydi?",
    "Atlanmis konu veya malzeme var mi?",
    "Ilave hangi bilgilerin sunulmasini isterdiniz, eksik olan birsey var miydi?",
    "Bu dersi gelistimek icin genel yorum ve oneriler:"
};

char* choice5[_5_CHOICE_QUESTION_COUNT] = {
    "1 - kotu, 2 - vasat, 3 - iyi, 4 - cok iyi, 5 - mukemmel",
    "1 - kotu, 2 - vasat, 3 - iyi, 4 - cok iyi, 5 - mukemmel",
    "1 - kotu, 2 - vasat, 3 - iyi, 4 - cok iyi, 5 - mukemmel",
    "1 - kotu, 2 - vasat, 3 - iyi, 4 - cok iyi, 5 - mukemmel",
    "1 - kotu, 2 - vasat, 3 - iyi, 4 - cok iyi, 5 - mukemmel",
    "1 - kotu, 2 - vasat, 3 - iyi, 4 - cok iyi, 5 - mukemmel",
    "1 - kotu, 2 - vasat, 3 - iyi, 4 - cok iyi, 5 - mukemmel",
    "1 - kotu, 2 - vasat, 3 - iyi, 4 - cok iyi, 5 - mukemmel",
    "1 - kotu, 2 - vasat, 3 - iyi, 4 - cok iyi, 5 - mukemmel",
    "1 - kotu, 2 - vasat, 3 - iyi, 4 - cok iyi, 5 - mukemmel",
    "1 - kotu, 2 - vasat, 3 - iyi, 4 - cok iyi, 5 - mukemmel",
    "1 - kotu, 2 - vasat, 3 - iyi, 4 - cok iyi, 5 - mukemmel",
    "1 - kotu, 2 - vasat, 3 - iyi, 4 - cok iyi, 5 - mukemmel"
};
char* choice3[_3_CHOICE_QUESTION_COUNT] = {
    "1 - cok uzun, 2 - yeterli, 3 - cok kisa",
    "1 - cok uzun, 2 - yeterli, 3 - cok kisa",
    "1 - cok uzun, 2 - yeterli, 3 - cok kisa",
    "1 - cok uzun, 2 - yeterli, 3 - cok kisa",
    "1 - cok karisik, 2 - yeterli, 3 - cok kisa",
    "1 - evet, 2 - hayir, 3 - kismen"
};

char** names;
char*** answers_long;

typedef struct {
    char egitmen[255];
    char egitim[255];
    char sirket[255];
    char tarih[255];
    char adres[255];
    char dersyeri[255];
} info_t;

info_t* info;

void print_instructions() {
    printf("5 sikli sorular icin 1 5 arasi sayi gir\n");
    printf("3 sikli sorular icin 1 3 arasi sayi gir\n");
    printf("N/A icin 0 gir\n");
}

void chomp(char* str) {
    int n = strlen(str);
    if(str[n-1]=='\n')
        str[n-1]='\0';
}

void alloc_strings() {
    names = malloc(n*sizeof(char*));
    answers_long = malloc(n*sizeof(char**));

    int i, j;
    for(i=0;i<n;i++) {
        names[i] = malloc(255*sizeof(char));
        answers_long[i] = malloc(LONG_QUESTION_COUNT*sizeof(char*));

        for(j=0;j<LONG_QUESTION_COUNT; j++) {
            answers_long[i][j] = malloc(511*sizeof(char));
        }
    }
}

void print_questions() {
    printf("Kac kisi?\n");
    scanf("%d", &n);

    alloc_strings();

    int i, j;
    for(i=0;i<n;i++) {
        printf("kisi %d\n", i+1);

        for(j=0;j<_5_CHOICE_QUESTION_COUNT;j++) {
            int x;

            printf("%s?\n", questions5[j]);
            printf("%s\n", choice5[j]);
            scanf("%d", &x);

            if(x!=0) {
                answers5[j][x-1]++;
            }
        }

        for(j=0;j<_3_CHOICE_QUESTION_COUNT;j++) {
            int x;

            printf("%s?\n", questions3[j]);
            printf("%s\n", choice3[j]);
            scanf("%d", &x);

            if(x!=0) {
                answers3[j][x-1]++;
            }
        }

        for(j=0; j<LONG_QUESTION_COUNT; j++) {
            printf("%s\n", questions_long[j]);
            scanf("%s", answers_long[i][j]);
        }

        printf("isim? ");
        scanf("%s", names[i]);
        chomp(names[i]);
    }
}

void print_answers() {
    int i,j;

    FILE* fp = fopen(FILENAME, "w");

    if(!fp) {
        fprintf(stderr, "file handling error!\n");
    }

    fprintf(fp, "Egitmen adi\n");
    fprintf(fp, "%s\n", info->egitmen);

    fprintf(fp, "Egitimin adi\n");
    fprintf(fp, "%s\n", info->egitim);

    fprintf(fp, "Sirket adi\n");
    fprintf(fp, "%s\n", info->sirket);

    fprintf(fp, "Kursun Baslama ve Bitis Tarihi\n");
    fprintf(fp, "%s\n", info->tarih);

    fprintf(fp, "Sirket adresi\n");
    fprintf(fp, "%s\n", info->adres);

    fprintf(fp, "Ders alinan yer\n");
    fprintf(fp, "%s\n", info->dersyeri);

    fprintf(fp, "\n=======================================\n\n");

    for(i=0;i<_5_CHOICE_QUESTION_COUNT;i++) {
        int x;

        fprintf(fp, "%s\n", questions5[i]);
        for(j=0; j<5; j++) {
            fprintf(fp, "%%%.2f ", (100.0 * (double)answers5[i][j])/((double)n));
        }

        fprintf(fp, "\n");
    }

    for(i=0;i<_3_CHOICE_QUESTION_COUNT;i++) {
        int x;

        fprintf(fp, "%s\n", questions3[i]);
        for(j=0; j<5; j++) {
            fprintf(fp, "%%%.2f ", (100.0 * (double)answers3[i][j])/((double)n));
        }

        fprintf(fp, "\n");
    }

    fprintf(fp, "\n\n individual responses\n=======================\n\n");

    for(i=0; i<n; i++) {
        fprintf(fp, "kullanici %d (%s)\n", i+1, names[i]);
        for(j=0;j<LONG_QUESTION_COUNT;j++) {
            fprintf(fp, "%s\n%s\n", questions_long[j], answers_long[i][j]);
        }
        fprintf(fp, "\n\n");
    }

    fclose(fp);
}

void general_questions() {
    info = malloc(sizeof(info_t));

    printf("Egitmen adi?\n");
    fgets(info->egitmen, 255, stdin);

    printf("Egitimin adi?\n");
    fgets(info->egitim, 255, stdin);

    printf("Sirket adi?\n");
    fgets(info->sirket, 255, stdin);

    printf("Kursun Baslama ve Bitis Tarihi?\n");
    fgets(info->tarih, 255, stdin);

    printf("Sirket adresi?\n");
    fgets(info->adres, 255, stdin);

    printf("Ders alinan yer?\n");
    fgets(info->dersyeri, 255, stdin);
}

int main() {
    print_instructions();
    general_questions();
    print_questions();
    print_answers();

    #ifdef _WIN32
    getch();
    #endif

    return 0;
}
