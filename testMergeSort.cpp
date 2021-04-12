#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <fstream>

// Scala dwie części tablicy w jedną posortowaną
void merge(int arr[], int left, int middle, int right)
{
    // ilość elementów w obu fragmenta
    int sizeL = middle - left + 1;
    int sizeR = right - middle;

    // tablice pomocnicze
    int tempL[sizeL], tempR[sizeR];

    // kopiowanie wartości do tablic pomocniczych
    for (int i = 0; i < sizeL; i++)
    {
        tempL[i] = arr[left + i];
    }
    for (int j = 0; j < sizeR; j++)
    {
        tempR[j] = arr[middle + 1 + j];
    }

    int i = 0;    // początek pierwszej tablicy pomocniczcej
    int j = 0;    // początek drugiej tablicy pomocniczcej
    int k = left; // początek scalania głównej tablicy

    // Scalanie pomocniczych tablic w odpowiedniej kolejności w głównej tablicy
    while (i < sizeL && j < sizeR)
    {
        if (tempL[i] <= tempR[j])
        {
            arr[k] = tempL[i];
            i++;
        }
        else
        {
            arr[k] = tempR[j];
            j++;
        }
        k++;
    }

    // scal(?) pozostałości lewej tablicy pomocniczej, o ile jakieś zostały
    while (i < sizeL)
    {
        arr[k] = tempL[i];
        i++;
        k++;
    }

    // zescal(?) pozostałości prawej tablicy pomocniczej, o ile jakieś zostały
    while (j < sizeR)
    {
        arr[k] = tempR[j];
        j++;
        k++;
    }
}

// Główna funkcja sortująca
void mergeSort(int *arr, int left, int right)
{
    if (left >= right) // kiedy fragment ma tylko jeden element
    {                  // zacznij zwracać
        return;
    }

    int middle = left + (right - left) / 2; // ustal środek

    mergeSort(arr, left, middle);      // sortuj lewą połowę
    mergeSort(arr, middle + 1, right); // sortuj prawą połowę
    merge(arr, left, middle, right);   // scal(?) obie połowy
}

int main()
{
    int loops = 0;
    std::ofstream data("mergeSortData.txt");

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

        mergeSort(arr, 0, n - 1);

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