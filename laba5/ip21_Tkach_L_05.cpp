#include <iostream>
#include <cstring>
#include <cstdio>
#include <fstream>

using namespace std;
// функція для отримання індекса лівого нащадка вершини піраміди
int Left(int i) {
    return 2 * i + 1;
}

// функція для отримання індекса правого нащадка вершини піраміди
int Right(int i) {
    return 2 * i + 2;
}

// функція, яка зміщує локально мінімальний елемент у поточну вершину, і далі підтримує властивість піраміди, так щоб найбільні елемнти опинились внизу піраміди
void MinHeapify(int data[], int i, int heap_size) {
    // отримуємо індекси лівого та правого нащадків
    int p = Left(i);
    int q = Right(i);
    // знаходимо найменший елемент серед елемента вершини та нащадків
    int smallest;
    if (p < heap_size && data[p] < data[i]) {
        smallest = p;
    } else {
        smallest = i;
    }

    if (q < heap_size && data[q] < data[smallest]) {
        smallest = q;
    }
    // якщо найменший елемент - це не елемент вершини, міняємо елемент вершини та найменший місцями та викликаємо функцію MinHeapify для найменшого
    if (smallest != i) {
        swap(data[i], data[smallest]);
        MinHeapify(data, smallest, heap_size);
    }
}

// функція побудови неспадаючої піраміди
void BuildMinHeap(int data[], int heap_size) {
    for (int i = heap_size / 2 - 1; i > -1; i--) {
        MinHeapify(data, i, heap_size);
    }
}

// функція, яка зміщує локально максимальний елемент у поточну вершину, і далі підтримує властивість піраміди, так щоб найменші елемнти опинились внизу піраміди
void MaxHeapify(int data[], int i, int heap_size) {
    // отримуємо індекси лівого та правого нащадків
    int p = Left(i);
    int q = Right(i);
    // знаходимо найбільший елемент серед елемента вершини та нащадків
    int largest;
    if (p < heap_size && data[p] > data[i]) {
        largest = p;
    } else {
        largest = i;
    }

    if (q < heap_size && data[q] > data[largest]) {
        largest = q;
    }

    // якщо найбільший елемент - це не елемент вершини, міняємо елемент вершини та найбільший місцями та викликаємо функцію MaxHeapify для найбільшого
    if (largest != i) {
        swap(data[i], data[largest]);
        MaxHeapify(data, largest, heap_size);
    }
}

// функція побудови незростаючої піраміди
void BuildMaxHeap(int data[], int heap_size) {
    for (int i = heap_size / 2 - 1; i > -1; i--) {
        MaxHeapify(data, i, heap_size);
    }
}

// функція, яка виймає максимальнтй елемент з черги
int HeapExtractMax(int data[], int heap_size) {
    if (heap_size < 1) {
        cout << "Heap is empty" << endl;
    }
    int max_val = data[0];
    data[0] = data[heap_size - 1];
    heap_size--;
    MaxHeapify(data, 0, heap_size - 1);
    return max_val;
}

// функція, яка виймає мінімальний елемент з черги
int HeapExtractMin(int data[], int heap_size) {
    if (heap_size < 1) {
        cout << "Heap is empty" << endl;
    }
    int min_val = data[0];
    data[0] = data[heap_size - 1];
    heap_size--;
    MinHeapify(data, 0, heap_size - 1);
    return min_val;
}

// функція для отримання найбільшого, чи найменшого елемента піраміди
int Max_Min(int data[]){
    return data[0];
}

// записую медіанні елементи у новий файл
void WriteMediansToFile(pair<int, int> Medians[], int len, string filename) {
    ofstream file(filename);
    for (int i = 0; i < len; i++) {
        if (Medians[i].first == Medians[i].second) {
            file << Medians[i].first << endl;
        }
        else {
            file << Medians[i].first << " " << Medians[i].second << endl;
        }
    }
    file.close();
}

// оброблюю файл, вказаний при старті програми
void FileProcessing(const string& filename) {

    // зчитую кількість елементів та самі елементи з файлу
    ifstream file(filename);
    int len;
    file >> len;
    int data[len];
    for (int i = 0; i < len; ++i) {
        file >> data[i];
    }
    file.close();

    int H_low[len/2+1];
    int H_high[len/2+1];
    int low_size = 0;
    int high_size = 0;
    pair<int, int> Medians[len];
    int cur_len = len;

    // Обробка першого елементу з data
    int x_i = data[0];
    H_low[0] = x_i;
    low_size+=1;
    Medians[0] = make_pair(x_i, x_i);

    for (int i = 0; i < len- 1; i++) {
        data[i] = data[i+1];
    }
    cur_len-=1;
    
   
    // Обробка усіх інших елементів з data
    for (int i = 0; i < len-1; i++) {
        x_i = data[0];
        for (int l = 0; l < cur_len- 1; l++) {
            data[l] = data[l+1];
        }
        cur_len-=1;

        if (x_i < Max_Min(H_low)) {
            H_low[low_size] = x_i;
            low_size++;
        } else {
            H_high[high_size] = x_i;
            high_size++;
        }

        BuildMaxHeap(H_low, low_size);
        BuildMinHeap(H_high, high_size);

        if (low_size > high_size + 1) {
            int max_elem = HeapExtractMax(H_low, low_size);
            low_size--;
            H_high[high_size] = max_elem;
            high_size++;
        } else if (high_size > low_size + 1) {
            int min_elem = HeapExtractMin(H_high, high_size);
            high_size--;
            H_low[low_size] = min_elem;
            low_size++;
        }

        BuildMaxHeap(H_low, low_size);
        BuildMinHeap(H_high, high_size);

        if (low_size > high_size) {
            int Med = Max_Min(H_low);
            Medians[i + 1] = make_pair(Med, Med);
        }
        else if (high_size > low_size) {
            int Med = Max_Min(H_high);
            Medians[i + 1] = make_pair(Med, Med);
        }
        else {
            int Med1 = Max_Min(H_low);
            int Med2 = Max_Min(H_high);
            Medians[i + 1] = make_pair(Med1, Med2);
        }
    }
    
    //записую медіанні елементи у новий файл 
    string name="ip21_Tkach_L_05_output.txt";
    WriteMediansToFile(Medians, len, name);
        
}

int main(int argc, char* argv[]){
    FileProcessing(argv[1]);
    return 0;
}