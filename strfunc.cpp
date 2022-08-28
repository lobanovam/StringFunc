#include <stdio.h>
#include <stdlib.h>

int puts(const char *s);
char *strchr(const char *s, int ch); //const????
int strlen(const char *s);
char *strcpy(char *s1, const char *s2);
char *strncpy(char *dest, const char *source, size_t num);
char *strcat(char *s1, const char *s2);
char *strncat (char *s1, const char *s2, size_t n);
char *fgets(char *s, int num, FILE *fp);
char *strdup(char *str);
size_t getline (char **s, size_t *n, FILE *stream);
int strcmp (const char *str1, const char *str2);

int main() {
    char word[] =  "1111111111"; //10
    char word1[] =  "22222";//5

    /**testing puts()*/
    printf("word is ");
    puts(word);

    printf("word1 is ");
    puts(word1);

    /**testing strlen()*/
    printf("word len is %lu\n", strlen(word));
    printf("word1 len is %lu\n", strlen(word1));

    /**testing strcpy()*/
    char shit1[] = "shit";
    char shit2[] = "even shittier";
    printf("strcpy is %s\n", strcpy(shit2, shit1));


    /**testing strncpy()*/
    int cnt = 7;
    printf("strncpy parametr is %d\n", cnt);
    printf("word after strncpy is %s\n", strncpy(word, word1, cnt));

    /**testing strchr()*/
    char str[] = "12456789";
    char ch = '3';
    char *pt;
    pt = strchr(str, ch);
    printf("String after %c is %s\n", ch, pt);

    /**testing strcat()*/
    char s1[15] = "shot ";
    char s2[15] = "shit";
    printf("s1 after strcat is %s\n", strcat(s1, s2));

    /**testing strncat()*/
    char ss1[15] = "shot ";
    char ss2[15] = "shit";
    printf("ss1 after strncat is %s\n", strncat(ss1, ss2, 3));

    /**testing fgets()*/
    FILE *fp = NULL;
    char read[20];
    if ((fp = fopen("tests.txt", "r")) == NULL) {
        printf("can't open file");
        return 0;
    }
    printf("%s\n", fgets(read, 5, fp));
    fclose(fp);

    /**testing strdup()*/
    char word2[] = "disaster";
    char* word3 = NULL;;
    word3 = strdup(word2);
    printf("%s\n", word3);
    free(word3);

    /**testing getline()*/
    FILE *fp1 = NULL;
    if ((fp1 = fopen("tests.txt", "r")) == NULL) {
        printf("can't open file");
        return 0;
    }

    size_t buffSize = 10;
    char *word6 = (char*)calloc(buffSize, sizeof(char));

    printf("%d symbols were read\n", getline(&word6, &buffSize, fp1));
    printf("result is %s\n", word6);
    free(word6);

     /**testing strcmp()*/
     char word4[] = "abc";
     char word5[] = "abc";
     printf("strcmp res is %d\n", strcmp(word4, word5));

    return 0;
}


int puts (const char *s) {
    if (*s == EOF)
        return EOF;
    while (*s != '\0' && putchar(*s) != EOF ) {
        s++;
    }
    putchar('\n');
    return(0);
}


char *strchr(const char *s, int ch) {
    size_t i = 0;
    size_t len = strlen(s);
    while (*s != ch) {
        s++;
        i++;
    }
    if (i == len) {
        return NULL;
    }

    return (char*)s+1;

}


int strlen(const char *s) {
    size_t i = 0;
    while (*s++ != 0) {
        i++;
    }

    return i;
}


char *strcpy(char *s1, const char*s2) {
    char *v1 = s1;
    while ((*v1++ = *s2++) != '\0') {}
    return(s1);
}


char *strncpy(char *s1, const char *s2, size_t num) {
    size_t i = 0;
    char *v1 = s1;
    while ((s2 != '\0') && (i++ < num)) {
        *v1 = *s2;
        v1++;
        s2++;
    }
    while(i < num && i < strlen(s1)) {
        *v1 = '\0';
        i++;
        v1++;
    }

    return(s1);
}


char *strcat(char *s1, const char *s2) {
    char *v1 = s1;
    while (*v1 != '\0') {
        v1++;
    }
    while (*s2 != '\0') {
        *v1 = *s2;
        s2++;
        v1++;
    }

    return s1;
}


char *strncat(char *s1, const char *s2, size_t n) {
    char *v1 = s1;
    size_t i = 0;
    while (*v1 != '\0') {
        v1++;
    }
    while (*s2 != '\0' && i < n ) {
        *v1 = *s2;
        s2++;
        v1++;
        i++;
    }

    return s1;
}


char *fgets(char *s, int num, FILE *fp) {
    int ch;
    char *v = s;
    size_t i = 0;
    while ((ch = fgetc(fp)) != '\n' && ch != EOF && i < num-1) {
        *v = ch;
        v++;
        i++;
    }
    *v = '\0';

    return s;
}


char *strdup(char *str) {
    char *ptd;
    ptd = (char*)(calloc(strlen(str), sizeof(char)));
    strcpy(ptd, str);
    printf("strlen ptd is %d\n", strlen(ptd));

    return ptd;
}


size_t getline (char **s, size_t *n, FILE *fp) {
    if (*s == NULL) {
        *s = (char*)(calloc(*n, sizeof(char)));
    }
    int ch;
    printf("\n\ngetline is working\n");
    size_t i = 0;
    while ((ch = fgetc(fp))!= '\n' && ch != EOF) {
        (*s)[i] = ch;
        printf("(*s)[%d] is %c\n",i, (*s)[i]);
        i++;
        printf("i is %d and n is %d\n", i, *n);
        if (i == *n) {

            printf("i exceeding n, time to realloc\n");
            *n *= 2;
            //size_t len = strlen(*s);
            printf("Trying Realloc for size %d with ptr = %p\n", *n, *s);
            *s = (char*)(realloc(*s, *n * sizeof(char)));
            printf("Realloc finished for size %d with ptr = %p\n", *n, *s);

            printf("strlen finished\n");

            (*s)[i] = '\0';
            printf("adding 0 finished\n");

        }
    }
    (*s)[i] = '\0';
    //*s = (char*)(realloc(*s, strlen(*s)));
    //printf("final len is %d\n", strlen(*s));
    //printf("final version is %s\n", *s);
    *n = i;
    return *n;
}


int strcmp(const char *s1, const char *s2) {
    while (*s1 == *s2 && *s1 != '\0' ) {
            s1++;
            s2++;
        }

        return (*s1 - *s2);
}


















