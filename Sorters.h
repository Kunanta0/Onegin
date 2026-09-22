#ifndef SORTERS_H_INCLUDED
#define SORTERS_H_INCLUDED

void Swap(void*, void*, size_t);
void BubbleSort(void*, size_t, size_t, int (*CompareFunc) (const void*, const void*));
//void QuickSort(void*, size_t, size_t, int (*CompareFunc) (const void*, const void*), size_t);

void Swap(void* value_1, void* value_2, size_t SIZE)
{
    void* temp = malloc(SIZE);

    memcpy(temp, value_1, SIZE);
    memcpy(value_1, value_2, SIZE);
    memcpy(value_2, temp, SIZE);

    free(temp);
}

/*void QuickSort(void* data, size_t length, size_t SIZE, int (*CompareFunc) (const void* a, const void* b), size_t low_index = 0)
{
    char* arr = (char *) data;
    size_t high_index = length - 1;
    if (low_index >= high_index) return;

    void* pivot = arr + high_index * SIZE;
    size_t i = low_index;
    for (size_t j = low_index; j < high_index; ++j)
    {
        void* arr2 = arr + j * SIZE;

        if (CompareFunc(arr2, pivot) < 0)
        {
            void* arr1 = arr + i * SIZE;
            Swap(arr1, arr2, SIZE);
            ++i;
        }
    }
    Swap(arr + i * SIZE, pivot, SIZE);
    if (i != 0) QuickSort(arr, i, SIZE, CompareFunc, low_index);
    QuickSort(arr, high_index + 1, SIZE, CompareFunc, i + 1);
}*/

void BubbleSort(void* data, size_t nnums, size_t SIZE, int (*CompareFunc) (const void* a, const void* b))
{
    char* arr = (char*) data;
    for (size_t n = nnums - 1; n > 0;--n)
    {
        bool IsChanged = false;
        for (size_t i = 0;i < n;++i)
        {
            void* arr1 = arr + i * SIZE;
            void* arr2 = arr + (i + 1) * SIZE;
            if (CompareFunc(arr1, arr2) > 0)
            {
                Swap(arr1, arr2, SIZE);
                IsChanged = true;
            }
        }
        if (!IsChanged) return;
    }
}

#endif // SORTERS_H_INCLUDED
