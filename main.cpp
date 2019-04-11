#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// --------------------------------------------------------------------------------------------------------------------------------------------------------
/* IMPLEMENTACJA KOPCA NA TABLICY
 * Źródło: http://mariusz.makuchowski.staff.iiar.pwr.wroc.pl/download/courses/sterowanie.procesami.dyskretnymi/lab.instrukcje/lab04.schrage/heap.demo.v1.5/demoheap.exe
 * Autor: Dr inż. Mariusz Makuchowski
 * Modyfikacje:
 * - stworzenie klasy BinaryHeap
 * - dodanie metody Print()
 * - zmiana nazw niektórych zmiennych
 * Autorzy modyfikacji: Michał Nowak i Mariusz Perskawiec
 */

class BinaryHeap {

private:

    int *array;
    int ActualSize;
    int HeapSize;

public:

    BinaryHeap(int _heapSize) {
        ActualSize = 0;
        HeapSize = _heapSize - 1;
        array = new int[HeapSize];
    }

    void ShiftDown(int node);
    void ShiftUp(int node);
    void Make();
    void HeapSort();

    void Push(int value);
    void Pop();

    void Print();
};

void BinaryHeap::ShiftDown(int node){

    int next = 2 * node;

    while (next <= ActualSize) {

        if (next < ActualSize && array[next] < array[next + 1]) {
            next++;
        }

        if (array[node] < array[next]) {
            swap(array[node], array[next]);
            node = next;
            next *= 2;
        }
        else {
            next = ActualSize + 1;
        }
    }
}

void BinaryHeap::ShiftUp(int node){

    int next = node / 2;

    while ( (node > 1) && (array[next] < array[node]) ) {
        swap(array[node], array[next]);
        node = next;
        next /= 2;
    }
}

void BinaryHeap::Make() {

    for (int count = ActualSize / 2; count > 0; count--) {
        ShiftDown(count);
    }
}

void BinaryHeap::Push(int value) {

    array[++ActualSize] = value;
    ShiftUp(ActualSize);
}

void BinaryHeap::Pop() {

    swap(array[1], array[ActualSize--]);
    ShiftDown(1);
}

void BinaryHeap::HeapSort() {
    
    Make();
    
    while ( ActualSize > 0 ) {
        Pop();
    }
}

void BinaryHeap::Print() {

    cout << endl << "Heap elements: " << endl;

    for (int count = 1; count <= ActualSize ; count++) {
        cout << count << ". "<< array[count] << endl;
    }
    
    cout << endl;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------

int main(void) {

    // TEST KOPCA
    int heap_size = 10;

    BinaryHeap heap(heap_size);

    heap.Push(2);
    heap.Push(12);
    heap.Push(9);
    heap.Push(1);
    heap.Push(4);
    heap.Push(7);
    heap.Push(90);
    heap.Push(11);

    heap.Print();
    
    heap.Pop();
    heap.Pop();
    
    heap.Print();

	system("pause");

	return 0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------
