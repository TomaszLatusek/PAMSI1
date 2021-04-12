#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <fstream>

// Funkcja do zamieniania elementów tablicy
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Główna funkcja sortująca
void quickSort(int *arr, int left, int right)
{
    if (right <= left) // jeśli liczniki się minęły
        return;        // to zakończ

    int i = left, j = right,
        pivot = arr[(left + right) / 2]; // punkt odniesienia

    while (1)
    {
        // szuka indeksu elementu większego niż pivot
        while (arr[i] < pivot)
        {
            i++;
        }

        // szuka indeksu elementu mniejszego niż pivot
        while (arr[j] > pivot)
        {
            j--;
        }

        // Dopóki i <= j zamieniaj elementy, tym sposobem będą po właściwej "połowie" tablicy
        if (i <= j)
        {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
        else // w przeciwnym razie wyjdź z pętli
            break;
    }

    // Rekurencyjnie wywołaj sortowanie dla kolejnych fragmentów
    if (j > left) // dla lewej części tablicy
    {
        quickSort(arr, left, j);
    }
    if (i < right) // i dla prawej
    {
        quickSort(arr, i, right);
    }
}

int main()
{
    int loops = 0;
    std::ofstream data("quickSortData.txt");

    int arr[10000];                       //tablica
    int n = sizeof(arr) / sizeof(arr[0]); // rozmiar tablicy

    while (loops < 100)
    {
        for (int i = 0; i < n * 997 / 1000; i++)
        {
            arr[i] = 0;
        }

        // for (int i = n * 997 / 1000; i < n; i++)
        // {
        //     arr[i] = rand() % 1000;
        // }

        // for (int i = 0; i < n; i++)
        // {
        //     arr[i] = rand() % 1000;
        // }

        // int j = n - 1;
        // for (int i = 0; i < n; i++)
        // {
        //     arr[i] = j;
        //     j--;
        // }

        // moment rozpoczęcia sortowania
        auto start = std::chrono::high_resolution_clock::now();

        quickSort(arr, 0, n - 1);

        // moment zakończenia sortowania
        auto stop = std::chrono::high_resolution_clock::now();

        // czas sortowania
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        // wpisz czas sortownia do pliku
        data << duration.count() << std::endl;

        loops++;
    }

    std::cout << "Finished" << std::endl;

    return 0;
}