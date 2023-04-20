#include <iostream>
#include <cstring>
#include <cstdio>
#include <fstream>
using namespace std;

// Процедура розбиття
int Partition1(int A[], int p, int r) {
  int x = A[r];
  int i = p - 1;
  for (int j = p; j < r; j++) {
    if (A[j] <= x) {
      i++;
      swap(A[i], A[j]);
    }
  }
  swap(A[i + 1], A[r]);
  return i + 1;
}

// Процедура сортування
void QuickSort1(int A[], int p, int r, int& comparisons) {
  if (p < r) {
    int q = Partition1(A, p, r);
    QuickSort1(A, p, q - 1, comparisons);
    QuickSort1(A, q + 1, r, comparisons);
    // додаю кількість порівнянь у функції Partition
    comparisons += (r - p);
  }
}

//записую кількість порівнянь у першому сортуванні та у другому у новий файл
void WriteDataToFile(int comp1, int comp2, string filename) {
    ofstream file(filename);
    file <<comp1 <<" "<<comp2<< endl;
    
    file.close();
}

// знаходжу медіанний елемент та повертаю його індекс
int Median(int A[], int p, int r) {
    int mid = (p + r) / 2;
    int res;
    if ((A[p]>A[mid] && A[mid]>A[r]) || (A[p]<A[mid] && A[mid]<A[r])) {
        res=mid;
    }else if((A[mid]>A[p] && A[p]>A[r]) || (A[mid]<A[p] && A[p]<A[r])){
        res=p;
    }else{
        res=r;
    }
    
    return res;
}

// Процедура розбиття
int Partition2(int A[], int p, int r) {
    int y= Median(A, p, r); 
    // зміщую медіанний елемнт у кінець, далі йде такий же алгоритм, як і в Partition1
    swap(A[y], A[r]);
    
    int x=A[r];
    int i = p - 1;
    for (int j = p; j <= r - 1; j++) {
    if (A[j] <= x) {
        i++;
        swap(A[i], A[j]);
    }
    }
    swap(A[i + 1], A[r]);
    
    return (i + 1);
    
}

// Процедура сортування
void QuickSort2(int A[], int p, int r, int& comparisons) {
    // якщо підмасив менше або дорівнює 3, то сортую його без процедури розбиття, але теж підразовую кількість інверсій
    if (r - p + 1 <= 3) { 
        for (int i = p; i <= r; i++) {
            for (int j = i + 1; j <= r; j++) {
                comparisons++;
                if (A[i] > A[j]) {
                    swap(A[i], A[j]);
                }
            }
        }
    }
    else {
        int q = Partition2(A, p, r);
        QuickSort2(A, p, q - 1, comparisons);
        QuickSort2(A, q + 1, r, comparisons);
        // додаю кількість порівнянь у функції Partition
        comparisons += (r - p); 
    }
}

//оброблюю файл, вказаний при старті програми
void FileProcessing(const string& filename) {

    //зчитую кількість елементів та самі елементи з файлу
    ifstream file(filename);
    int u;
    file >> u;
    int data[u],data1[u];
    for (int i = 0; i < u; ++i) {
        file >> data[i];
        data1[i]=data[i];
    }
    file.close();
    // сортую за першим алгоритмом та підраховую кількість інверсій
    int comp1=0;
    QuickSort1(data, 0, u-1,comp1);
    // сортую за другим алгоритмом та підраховую кількість інверсій
    int comp2=0;
    QuickSort2(data1, 0, u-1,comp2);

    //записую кількість порівнянь у першому сортуванні та у другому у новий файл
    string name="ip21_Tkach_L_02_output.txt";
    WriteDataToFile(comp1, comp2, name);
    
    
}

int main(int argc, char* argv[]){
    FileProcessing(argv[1]);
    return 0;
}
