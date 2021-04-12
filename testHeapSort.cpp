#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <fstream>

// funkcja do zamieniania elementów tablicy
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Przestawia elementy tablicy tak, by tworzyły kopiec typu max
void buildHeap(int *arr, int heapSize, int nodeIndex)
{
    int parentNode = nodeIndex;              // indeks "rodzica" węzła
    int leftChildIndex = 2 * nodeIndex + 1;  // indeks lewego "dziecka" węzła
    int rightChildIndex = 2 * nodeIndex + 2; // indeks prawego "dziecka" węzła

    // Jeżeli lewe dziecko istnieje i jest większe niż rodzic
    if (leftChildIndex < heapSize && arr[leftChildIndex] > arr[parentNode])
    {
        parentNode = leftChildIndex; // to teraz ono jest rodzicem
    }

    // Jeżeli prawe dziecko istnieje i jest większe niż rodzic
    if (rightChildIndex < heapSize && arr[rightChildIndex] > arr[parentNode])
    {
        parentNode = rightChildIndex; // to teraz ono jest rodzicem
    }

    // Jeżeli indeks rodzica się zmienił
    if (parentNode != nodeIndex)
    {
        swap(&arr[nodeIndex], &arr[parentNode]); // to zamień te wartości miejscami
                                                 // i jeżeli jakoś to dotknęło "następne pokolenia"
        buildHeap(arr, heapSize, parentNode);    // to napraw to
    }
}

// Główna funkcja sortująca
void heapSort(int *arr, int heapSize)
{
    // Zbuduj kopiec max zaczynnając od "najniższych" węzłów ku górze
    for (int i = heapSize / 2 - 1; i >= 0; i--)
    {
        buildHeap(arr, heapSize, i);
    }

    // Wyciągnij największą wartość z "najwyższego" węzła
    for (int i = heapSize - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]); // i ustaw ją na końcu tablicy,
        buildHeap(arr, i, 0);   // napraw okrojony już kopiec
        // i tak w kółko...
    }
}

int main()
{
    int loops = 0;
    std::ofstream data("heapSortData.txt");

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

        heapSort(arr, n);

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