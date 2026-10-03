/**
*\file
*\brief Header with comparators
*all functions here accepts two parameters which we need to compare
*/

#ifndef COMPARATORS_H_INCLUDED
#define COMPARATORS_H_INCLUDED

///function compares integer numbers in ascending order
int CompareUp(const void*, const void*);

///function compares integer numbers in descending order
int CompareDown(const void*, const void*);

///function compares strings by alphabet skipping non-alpha symbols
int CompareStrsStart(const void*, const void*);

///function compares strings by alphabet from the end skipping non-alpha symbols
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
    Line s1 = *(Line*) a;
    Line s2 = *(Line*) b;

    size_t i1 = s1.length;
    size_t i2 = s2.length;

    s1.line += i1;
    s2.line += i2;

    while (i1 * i1 + i2 * i2)
    {
        while((i1) && !isalpha((unsigned char)*(s1.line)))
        {
            --i1;
            --(s1.line);
        }
        while((i2) && !isalpha((unsigned char)*(s2.line)))
        {
            --i2;
            --(s2.line);
        }

        if(i1 + i2 < 2) break;

        int c1 = tolower((unsigned char)*(s1.line));
        int c2 = tolower((unsigned char)*(s2.line));

        if (c1 != c2) return c1 - c2;

        --(s1.line);
        --i1;

        --(s2.line);
        --i2;
    }

    while((i1) && !isalpha((unsigned char)*(s1.line)))
    {
        --(s1.line);
        --i1;
    }
    while((i2) && !isalpha((unsigned char)*(s2.line)))
    {
        --(s2.line);
        --i2;
    }

    return (unsigned char)*(s1.line) - (unsigned char)*(s2.line);
}

int CompareStrsStart(const void* a, const void* b)
{
    Line s1 = *(Line*) a;
    Line s2 = *(Line*) b;

    while (*(s1.line) && *(s2.line))
    {
        while(*(s1.line) && !isalpha((unsigned char)*(s1.line))) (s1.line)++;
        while(*(s2.line) && !isalpha((unsigned char)*(s2.line))) (s2.line)++;

        if(!*(s1.line) || !*(s2.line)) break;

        int c1 = tolower((unsigned char)*(s1.line));
        int c2 = tolower((unsigned char)*(s2.line));

        if (c1 != c2) return c1 - c2;

        (s1.line)++;
        (s2.line)++;
    }

    while(*(s1.line) && !isalpha((unsigned char)*(s1.line))) (s1.line)++;
    while(*(s2.line) && !isalpha((unsigned char)*(s2.line))) (s2.line)++;

    return (unsigned char)* (s1.line) - (unsigned char)* (s2.line);
}

#endif // COMPARATORS_H_INCLUDED

//function
//struct
