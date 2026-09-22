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

const int INDEX_SIZE = 10000;

struct Text
{
    const char** index;
    size_t nlines;
};

size_t ReadFile(const char* name, char* buffer, size_t SIZE, size_t* length);
void PrintFile(struct Text data, const char* message);
void FillIndex(char* buffer, const char* index[], size_t length);

int main(void)
{
    struct stat file_info;
    const char* filename = "Eugene_Onegin.txt";
    stat(filename, &file_info);
    size_t SIZE = file_info.st_size;

    char buffer[SIZE + 1] = {};
    size_t length = 0;
    size_t nlines = ReadFile(filename, buffer, SIZE, &length);

    /*const char** index = (const char**)calloc(nlines, sizeof(char*));
    const char** copy_index = (const char**)calloc(nlines, sizeof(char*));*/

    const char* index[INDEX_SIZE] = {};
    const char* copy_index[INDEX_SIZE] = {};

    FillIndex(buffer, index, length);

    memcpy(copy_index, index, nlines * sizeof(char*));

    struct Text data = {index, nlines};
    struct Text copy_data = {copy_index, nlines};

    qsort(data.index, data.nlines, sizeof(char*), CompareStrsStart);
    PrintFile(data, "qsort() CompareStrsStart");

    BubbleSort(data.index, data.nlines, sizeof(char*), CompareStrsEnd);
    PrintFile(data, "BubbleSort() CompareStrsEnd");

    PrintFile(copy_data, "Original Onegin");

    //free(index);
    //free(copy_index);

    return 0;
}

size_t ReadFile(const char* name, char* buffer, size_t SIZE, size_t* length)
{
    FILE* input_file = fopen(name, "r");
    *length = fread(buffer, sizeof(char), SIZE, input_file);
    fclose(input_file);

    size_t current_line = 0;

    for (size_t i = 0; i < *length; ++i)
    {
        if (*(buffer + i) == '\n')
        {
            *(buffer + i) = '\0';
            if (i + 1 < *length)
            {
                if (*(buffer + i + 1) == '\n') ++i;
                ++current_line;
            }
        }
    }

    return current_line;
}

void FillIndex(char* buffer, const char* index[], size_t length)
{
    size_t current_line = 0;
    index[0] = buffer;

    for (size_t i = 0; i < length; ++i)
    {
        if ((*(buffer + i) == '\0') && (i + 1 < length))
        {
            if (*(buffer + i + 1) == '\n') ++i;
            index[++current_line] = buffer + i + 1;
        }
    }
}

void PrintFile(struct Text data, const char* message)
{
    FILE* fo = fopen("output.txt", "a");
    fprintf(fo, "%s\n\n", message);
    for (size_t i = 0;i < data.nlines;++i) fprintf(fo, "%s\n", data.index[i]);

    fprintf(fo, "\n************************************************************************************************\n\n");

    fclose(fo);
}
