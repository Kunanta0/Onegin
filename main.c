/**
*\file
*\brief file with main function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

///this structure contains array of strings (pointers to them) and theirs length
typedef struct
{
    char* line;
    size_t length;
} Line;

#include "MyString.h"
#include "Sorters.h"
#include "comparators.h"

/**
*this function reads file with name "name" to buffer "buffer"
*\param[in] name name of file
*\param[in] SIZE buffer's size
*\param[out] buffer buffer with text from file
*/
size_t ReadFile(const char* name, size_t SIZE, char* buffer);

/**
*this function reads number of not empty lines in "buffer" with size "length"
*\param[in,out] buffer buffer with text from file
*\param[in,out] length size of file
*/
size_t GetLines(char* buffer, size_t length);

/**
*this function reads file with name "name" to buffer "buffer"
*\param[out] data structure with info
*\param[out] message helpful message to print to file
*/
void PrintFile(Line* text, size_t nlines, const char* message);

/**
*this function fills array of structure with lines
*\param[in,out] buffer buffer with text from file
*\param[out] length size of file
*\param[out] nlines number of non-empty lines
*/
Line* FillIndex(char* buffer, size_t length, size_t* nlines);

/**
*this function uses stat to know file's size without opening
*\param[out] name name of file
*/
size_t GetSize(const char* name);

int main(void)
{
    size_t SIZE = GetSize("Eugene_Onegin.txt");
    size_t nlines = 0;
    char* buffer = (char*)calloc(SIZE, sizeof(char));

    size_t length = ReadFile("Eugene_Onegin.txt", SIZE, buffer);
    buffer[length] = '\0';
    printf("%s", buffer);

    Line* text = FillIndex(buffer, length, &nlines);
    //printf("%d", nlines);

    qsort(text, nlines, sizeof(Line), CompareStrsStart);
    PrintFile(text, nlines, "qsort() CompareStrsStart");

    QSort(text, nlines, sizeof(Line), CompareStrsEnd);
    PrintFile(text, nlines, "QSort() CompareStrsEnd");

    qsort(text, nlines, sizeof(Line), CompareUp);

    PrintFile(text, nlines, "Original Onegin");

    free(text);
    free(buffer);

    return 0;
}
size_t GetSize(const char* filename)
{
    struct stat file_info;
    stat(filename, &file_info);
    size_t SIZE = file_info.st_size;
    return SIZE;
}

size_t GetLines(char* buffer, size_t length)
{
    size_t nlines = 0;
    for (size_t i = 0; i < length; ++i)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            if (buffer[i + 1] == '\n') --nlines;
            ++nlines;
        }
    }
    ++nlines;

    return nlines;
}

size_t ReadFile(const char* name, size_t SIZE, char* buffer)
{
    FILE* input_file = fopen(name, "r");
    size_t length = fread(buffer, sizeof(char), SIZE, input_file);
    fclose(input_file);
    return length;
}

Line* FillIndex(char* buffer, size_t length, size_t* nlines)
{
    *nlines = GetLines(buffer, length);

    Line* lines = calloc((*nlines) + 1, sizeof(Line));

    int current_line = 0;
    lines[0].line = buffer;
    size_t previous_length = 0;

    for (size_t i = 0; i < length; ++i)
    {
        if (buffer[i] == '\0')
        {
            lines[current_line].length = i - previous_length;
            if (buffer[i + 1] == '\0') ++i;
            lines[++current_line].line = buffer + i + 1;
            if (i == length) lines[current_line].length = length - previous_length;
            previous_length = i;
        }
    }

    return lines;
}

void PrintFile(Line* text, size_t nlines, const char* message)
{
    FILE* fo = fopen("output.txt", "a");
    fprintf(fo, "%s\n\n", message);
    for (size_t i = 0; i < nlines; ++i) fprintf(fo, "%s\n", text[i].line);

    fprintf(fo, "\n************************************************************************************************\n\n");

    fclose(fo);
}
