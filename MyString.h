#ifndef MYSTRING_H_INCLUDED
#define MYSTRING_H_INCLUDED

///analog of library function "puts"
int Puts(const char*);

///analog of library function "strlen"
size_t Strlen(const char*);

///analog of library function "strcpy"
char* Strcpy(char* , const char* );

///analog of library function "strcat"
char* Strcat(char*, const char*);

///analog of library function "strcmp"
int Strcmp(const char*, const char*);

/**
*this function prints array of integer elements
*\param[in,out] arr array which we need to print
*\param[in] SIZE size of array
*/
void PrintArr(int*, size_t);

void PrintArr(int* arr, size_t SIZE)
{
    for (size_t i = 0;i < SIZE;++i)
    {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}

size_t Strlen(const char* s)
{
    size_t answer = 0;
    while (*s++ != '\0') ++answer;
    return answer;
}

int Puts(const char* s)
{
    while(*s != '\0')
    {
        putchar(*s);
        ++s;
    }

    putchar('\n');
    return 0;
}

char* Strcpy(char* dest, const char* src)
{
    size_t Size = Strlen(src);

    for (size_t i = 0;i < Strlen(src);++i)
    {
        *(dest + i) = src[i];
    }
    *(dest + Size) = 0;

    return dest;
}

char* Strcat(char* dest, const char* src)
{
    size_t SzSrc = Strlen(src);
    size_t SzDest = Strlen(dest);

    size_t i = SzDest;

    for (size_t j = 0;j <= SzSrc;++j)
    {
        *(dest + i) = src[j];
        ++i;
    }

    return dest;
}

int Strcmp(const char* str1, const char* str2)
{
    size_t max_size = (Strlen(str1) > Strlen(str2)) ? Strlen(str1) : Strlen(str2);

    for (size_t i = 0; i < max_size; ++i)
    {
        int s1 = *(str1 + i);
        int s2 = *(str2 + i);

        if (s1 != s2) return s1 - s2;
    }

    return 0;
}

#endif // MYSTRING_H_INCLUDED
