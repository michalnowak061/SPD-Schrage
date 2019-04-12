#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#define HEAPSIZE 1000

using namespace std;

class Process {
public:
    int r, p, q, number;
    
    void Print() {
        cout << endl << "Numer zadania: " << number << endl <<
        "r: " << r << " p: " << p << " q: " << q << endl;
    }
};

// ------------------------------- Algorytm Schrage -------------------------------------------------------------------------------------------------------------------
/* Dane:
 * N - liczba zadań
 * R[i] - termin dostępności i-tego zadania
 * P[i] - czas wykonania i-tego zadania
 * Q[i] - czas dostarczenia i-tego zadania
 *
 * Szukane:
 * Permutacja wykonania zadań na maszynie, Cmax - maksymalny z terminów dostarczenia zadań
 *
 */
void Schrage(Process *Process_Array, int n);

// ------------------------- Implementacja kopca na tablicy -----------------------------------------------------------------------------------------------------------
/* Źródło: http://mariusz.makuchowski.staff.iiar.pwr.wroc.pl/download/courses/sterowanie.procesami.dyskretnymi/lab.instrukcje/lab04.schrage/heap.demo.v1.5/demoheap.exe
 * Autor: Dr inż. Mariusz Makuchowski
 * Modyfikacje:
 * - stworzenie klasy ProcessPriorityQueue
 * - dodanie metody Print(), isEmpty()
 * - zmiana nazw niektórych zmiennych
 * Autorzy modyfikacji: Michał Nowak i Mariusz Perskawiec
 */

class ProcessPriorityQueue {
    
private:
    
    Process *array;
    int ActualSize;
    int HeapSize;
    bool maxHeap;
    char priority;
    
public:
    
    ProcessPriorityQueue(int _heapSize, char _priority, bool maxheap) {
        ActualSize = 0;
        HeapSize = _heapSize - 1;
        array = new Process[HeapSize];
        maxHeap = maxheap;
        priority = _priority;
    }
    
    void ShiftDownMax(int node);
    void ShiftUpMax(int node);
    void ShiftDownMin(int node);
    void ShiftUpMin(int node);
    void Make();
    void HeapSort();
    
    void Push(Process value);
    void Pop();
    
    bool isEmpty();
    void Print();

};

void ProcessPriorityQueue::ShiftDownMax(int node){
    
    int next = 2 * node;
    
    while (next <= ActualSize) {
        
        if (priority == 'r') {
            
            if ( (next < ActualSize && (array[next].q < array[next+1].q) ) ) {
                next++;
            }
            
            if (array[node].q < array[next].q) {
                swap(array[node], array[next]);
                node = next;
                next *= 2;
            }
            else {
                next = ActualSize + 1;
            }
        }
        else if (priority == 'p') {
            
            if ( (next < ActualSize && (array[next].p < array[next+1].p) ) ) {
                next++;
            }
            
            if (array[node].p < array[next].p) {
                swap(array[node], array[next]);
                node = next;
                next *= 2;
            }
            else {
                next = ActualSize + 1;
            }
        }
        else if (priority == 'q') {
            
            if ( (next < ActualSize && (array[next].q < array[next+1].q) ) ) {
                next++;
            }
            
            if (array[node].q < array[next].q) {
                swap(array[node], array[next]);
                node = next;
                next *= 2;
            }
            else {
                next = ActualSize + 1;
            }
        }
    }
}

void ProcessPriorityQueue::ShiftUpMax(int node){
    
    int next = node / 2;
    
    if (priority == 'r') {
        
        while ( (node > 1) && (array[next].r < array[node].r) ) {
            swap(array[node], array[next]);
            node = next;
            next /= 2;
        }
    }
    else if (priority == 'p') {
        
        while ( (node > 1) && (array[next].p < array[node].p) ) {
            swap(array[node], array[next]);
            node = next;
            next /= 2;
        }
    }
    else if (priority == 'q') {
        
        while ( (node > 1) && (array[next].q < array[node].q) ) {
            swap(array[node], array[next]);
            node = next;
            next /= 2;
        }
    }
}

void ProcessPriorityQueue::ShiftDownMin(int node){
    
    int next = 2 * node;
    
    while (next <= ActualSize) {
        
        if (priority == 'r') {
            
            if ( (next < ActualSize && (array[next].q > array[next+1].q) ) ) {
                next++;
            }
            
            if (array[node].q > array[next].q) {
                swap(array[node], array[next]);
                node = next;
                next *= 2;
            }
            else {
                next = ActualSize + 1;
            }
        }
        else if (priority == 'p') {
            
            if ( (next < ActualSize && (array[next].p > array[next+1].p) ) ) {
                next++;
            }
            
            if (array[node].p > array[next].p) {
                swap(array[node], array[next]);
                node = next;
                next *= 2;
            }
            else {
                next = ActualSize + 1;
            }
        }
        else if (priority == 'q') {
            
            if ( (next < ActualSize && (array[next].q > array[next+1].q) ) ) {
                next++;
            }
            
            if (array[node].q > array[next].q) {
                swap(array[node], array[next]);
                node = next;
                next *= 2;
            }
            else {
                next = ActualSize + 1;
            }
        }
    }
}

void ProcessPriorityQueue::ShiftUpMin(int node){
    
    int next = node / 2;
    
    if (priority == 'r') {
        
        while ( (node > 1) && (array[next].r > array[node].r) ) {
            swap(array[node], array[next]);
            node = next;
            next /= 2;
        }
    }
    else if (priority == 'p') {
        
        while ( (node > 1) && (array[next].p > array[node].p) ) {
            swap(array[node], array[next]);
            node = next;
            next /= 2;
        }
    }
    else if (priority == 'q') {
        
        while ( (node > 1) && (array[next].q > array[node].q) ) {
            swap(array[node], array[next]);
            node = next;
            next /= 2;
        }
    }
}

void ProcessPriorityQueue::Make() {
    
    if (maxHeap == true) {
        
        for (int count = ActualSize / 2; count > 0; count--) {
            ShiftDownMax(count);
        }
    }
    else if (maxHeap == false) {
        for (int count = ActualSize / 2; count > 0; count--) {
            ShiftDownMin(count);
        }
    }
}

void ProcessPriorityQueue::Push(Process value) {
    
    array[++ActualSize] = value;
    
    if (maxHeap == true) {
        ShiftUpMax(ActualSize);
    }
    else {
        ShiftUpMin(ActualSize);
    }
}

void ProcessPriorityQueue::Pop() {
    
    swap(array[1], array[ActualSize--]);
    
    if (maxHeap == true) {
        ShiftDownMax(1);
    }
    else {
        ShiftDownMin(1);
    }
}

void ProcessPriorityQueue::HeapSort() {
    
    Make();
    
    while ( ActualSize > 0 ) {
        Pop();
    }
}

void ProcessPriorityQueue::Print() {
    
    cout << endl << "Heap elements: " << endl;
    
    for (int count = 1; count <= ActualSize ; count++) {
        array[count].Print();
    }
    
    cout << endl;
}

// ------------------------- Algorytm Schrage z podziałem -------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------------------------------------------

int main(void) {
    
    int N = 0; // Liczba danych
    string s;
    
    ifstream data("schr.data.txt");
    
    while( s != "data.001:" ) {
        data >> s;
    }
    
    data >> N;
    
    Process *Process_Array = new Process[N];
    
    cout << "Wczytane zadania: " << endl;
    for(int i = 1; i <= N; i++) {
        
        Process temp_process;
        
        temp_process.number = i;
        data >> temp_process.r >> temp_process.p >> temp_process.q;
        
        Process_Array[i] = temp_process;
        Process_Array[i].Print();
    }
    
    Schrage(Process_Array,N);
    
    //system("pause");
    
    return 0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------

void Schrage(Process *Process_Array, int n) {
    
    // krok 1: inicjacja wszystkich zmiennych
    
    int t = 0;           // <- chwila czasowa
    int k = 0;           // <- pozycja w permutacji
    int Cmax = 0;        // <- maksymalny z terminów dostarczenia zadań
    ProcessPriorityQueue N(HEAPSIZE, 'q', true); // <- zbiór zadań nieuszeregowanych
    ProcessPriorityQueue G(HEAPSIZE, 'q', true); // <- zbiór zadań gotowych do realizacji

    N.Push(Process_Array[1]);
    N.Push(Process_Array[2]);
    N.Push(Process_Array[3]);
    N.Push(Process_Array[4]);
    N.Push(Process_Array[5]);
    N.Push(Process_Array[6]);
    N.Push(Process_Array[7]);
    N.Push(Process_Array[8]);
    
    cout << "Kolejka priorytetowa G (priorytet najwieksze q)" << endl;
    N.Print();
    
    N.Pop();
    N.Pop();
    N.Pop();
    N.Pop();
    N.Pop();
    
    cout << "Kolejka priorytetowa G (priorytet najwieksze q)" << endl;
    N.Print();
}
