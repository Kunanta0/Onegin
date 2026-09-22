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

size_t ReadFile(const char* name, char* buffer, const char* index[], size_t SIZE);
void PrintFile(const char* index[], size_t nlines, const char* message);

int main(void)
{
    struct stat file_info;
    const char* filename = "Eugene_Onegin.txt";
    stat(filename, &file_info);
    size_t SIZE = file_info.st_size;

    char buffer[SIZE + 1] = {};
    const char* index[INDEX_SIZE] = {};

    size_t nlines = ReadFile(filename, buffer, index, SIZE);
    const char* copy_index[INDEX_SIZE];
    memcpy(copy_index, index, nlines * sizeof(char*));

    //struct Text data = {index, nlines};
    //struct Text copy_data = {copy_index, nlines};

    qsort(index, nlines, sizeof(char*), CompareStrsStart);
    PrintFile(index, nlines, "qsort() CompareStrsStart");

    BubbleSort(index, nlines, sizeof(char*), CompareStrsEnd);
    PrintFile(index, nlines, "BubbleSort() CompareStrsEnd");

    PrintFile(copy_index, nlines, "Original Onegin");

    return 0;
}

size_t ReadFile(const char* name, char* buffer, const char* index[], size_t SIZE)
{
    FILE* input_file = fopen(name, "r");
    size_t length = fread(buffer, sizeof(char), SIZE, input_file);
    fclose(input_file);

    size_t current_line = 0;
    index[0] = buffer;

    for (int i = 0; i < length; ++i)
    {
        if (*(buffer + i) == '\n')
        {
            *(buffer + i) = '\0';
            if (i + 1 < length)
            {
                if (*(buffer + i + 1) == '\n') ++i;
                index[++current_line] = buffer + i + 1;
            }
        }
    }

    return current_line;
}

void PrintFile(const char* index[], size_t nlines, const char* message)
{
    FILE* fo = fopen("output.txt", "a");
    fprintf(fo, "%s\n\n", message);
    for (size_t i = 0;i < nlines;++i) fprintf(fo, "%s\n", index[i]);

    fprintf(fo, "\n************************************************************************************************\n\n");

    fclose(fo);
}
