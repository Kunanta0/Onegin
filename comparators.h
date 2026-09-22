#ifndef COMPARATORS_H_INCLUDED
#define COMPARATORS_H_INCLUDED

int CompareUp(const void*, const void*);
int CompareDown(const void*, const void*);
int CompareStrsStart(const void*, const void*);
int CompareStrsEnd(const void*, const void*);

int CompareUp(const void* value_a, const void* value_b)
{
    const int a = *(const int*) value_a;
    const int b = *(const int*) value_b;

    return (a - b);
}

int CompareDown(const void* value_a, const void* value_b)
{
    const int a = *(const int*) value_a;
    const int b = *(const int*) value_b;

    return (b - a);
}

int CompareStrsEnd(const void* a, const void* b)
{
    const char* s1 = *(const char**) a;
    const char* s2 = *(const char**) b;

    size_t i1 = strlen(s1) - 1;
    size_t i2 = strlen(s2) - 1;

    s1 += i1;
    s2 += i2;

    while (i1 * i1 + i2 * i2)
    {
        while((i1) && !isalpha((unsigned char)*s1))
        {
            --i1;
            --s1;
        }
        while((i2) && !isalpha((unsigned char)*s2))
        {
            --i2;
            --s2;
        }

        if(i1 + i2 < 2) break;

        int c1 = tolower((unsigned char)*s1);
        int c2 = tolower((unsigned char)*s2);

        if (c1 != c2) return c1 - c2;

        --s1;
        --i1;

        --s2;
        --i2;
    }

    while((i1) && !isalpha((unsigned char)*s1))
    {
        --s1;
        --i1;
    }
    while((i2) && !isalpha((unsigned char)*s2))
    {
        --s2;
        --i2;
    }

    return (unsigned char)* s1 - (unsigned char)* s2;
}

int CompareStrsStart(const void* a, const void* b)
{
    const char* s1 = *(const char**) a;
    const char* s2 = *(const char**) b;

    while (*s1 && *s2)
    {
        while(*s1 && !isalpha((unsigned char)*s1)) s1++;
        while(*s2 && !isalpha((unsigned char)*s2)) s2++;

        if(!*s1 || !*s2) break;

        int c1 = tolower((unsigned char)*s1);
        int c2 = tolower((unsigned char)*s2);

        if (c1 != c2) return c1 - c2;

        s1++;
        s2++;
    }

    while(*s1 && !isalpha((unsigned char)*s1)) s1++;
    while(*s2 && !isalpha((unsigned char)*s2)) s2++;

    return (unsigned char)* s1 - (unsigned char)* s2;
}

#endif // COMPARATORS_H_INCLUDED
