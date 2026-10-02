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
#include "MyString.h"
#include "Sorters.h"
#include "comparators.h"

///this structure contains array of strings (pointers to them) and its size
struct Text
{
    char** index;
    size_t nlines;
};

/**
*this function reads file with name "name" to buffer "buffer"
*\param[in] name name of file
*\param[in] SIZE buffer's size
*\param[in,out] length real buffer's length (without "\r" in Windows)
*\param[out] buffer buffer with text from file
*/
void ReadFile(const char* name, size_t SIZE, size_t* length, char* buffer);

/**
*this function reads file with name "name" to buffer "buffer"
*\param[out] data structure with info
*\param[out] message helpful message to print to file
*/
void PrintFile(struct Text data, const char* message);

/**
*this function fills array of strings
*\param[in] buffer buffer with text from file
*\param[in,out] length real buffer's length (without "\r" in Windows)
*\param[out] nlines number of no empty lines in file
*/
char** FillIndex(char* buffer, size_t length, size_t* nlines);

/**
*this function uses stat to know file's size without opening
*\param[out] name name of file
*/
size_t GetSize(const char* name);

int main(void)
{
    size_t SIZE = GetSize("Eugene_Onegin.txt");
    size_t length = 0, nlines = 0;
    char* buffer = (char*)calloc(SIZE, sizeof(char));

    ReadFile("Eugene_Onegin.txt", SIZE, &length, buffer);

    char** index = FillIndex(buffer, length, &nlines);

    struct Text data = {index, nlines};

    qsort(data.index, data.nlines, sizeof(char*), CompareStrsStart);
    PrintFile(data, "qsort() CompareStrsStart");

    QSort(data.index, data.nlines, sizeof(char*), CompareStrsEnd);
    PrintFile(data, "QSort() CompareStrsEnd");

    qsort(data.index, data.nlines, sizeof(char*), CompareUp);

    PrintFile(data, "Original Onegin");

    free(index);
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

void ReadFile(const char* name, size_t SIZE, size_t* length, char* buffer)
{
    FILE* input_file = fopen(name, "r");
    *length = fread(buffer, sizeof(char), SIZE, input_file);
    fclose(input_file);
}

char** FillIndex(char* buffer, size_t length, size_t* nlines)
{
    for (size_t i = 0; i < length; ++i)
    {
        if ((*(buffer + i) == '\n') && (i + 1 < length))
        {
            *(buffer + i) = '\0';
            if (buffer[i + 1] == '\n') --(*nlines);
            ++(*nlines);
        }
    }
    ++(*nlines);

    char** index = calloc((*nlines) + 1, sizeof(char*));

    int current_line = 0;
    index[0] = buffer;

    for (size_t i = 0; i < length; ++i)
    {
        if ((*(buffer + i) == '\0') && (i + 1 < length))
        {
            if (*(buffer + i + 1) == '\0') ++i;
            index[++current_line] = buffer + i + 1;
        }
    }

    return index;
}

void PrintFile(struct Text data, const char* message)
{
    FILE* fo = fopen("output.txt", "a");
    fprintf(fo, "%s\n\n", message);
    for (size_t i = 0;i < data.nlines;++i) fprintf(fo, "%s\n", data.index[i]);

    fprintf(fo, "\n************************************************************************************************\n\n");

    fclose(fo);
}
