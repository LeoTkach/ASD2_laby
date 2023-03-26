#include <iostream>
#include <cstring>
#include <cstdio>
#include <fstream>
using namespace std;

//создаю новый двумерный массив для подсчёта инверсий
int **CreateNewArray(int **arr, int *ind, int u, int m) {
    int **newArr = new int *[u];
    for (int i = 0; i < u; i++) {
        newArr[i] = new int[m];
        for (int j = 0; j < m; j++) {
            newArr[i][ind[j] - 1] = arr[i][j];
        }
    }
    return newArr;
}

//Процедура злиття та підрахунку розділених інверсій
pair<int *, int> MergeAndCountSplitInv(int A[], int L[], int n1, int R[], int n2) {
    int *merged_A = new int[n1 + n2];
    int i = 0;
    int j = 0;
    int inv_count = 0LL;
    for (int k = 0; k < n1 + n2; k++) {
        if (i == n1) {
            merged_A[k] = R[j];
            j++;
        } else if (j == n2) {
            merged_A[k] = L[i];
            i++;
        } else if (L[i] <= R[j]) {
            merged_A[k] = L[i];
            i++;
        } else {
            merged_A[k] = R[j];
            j++;
            inv_count += n1 - i;
        }
    }
    return make_pair(merged_A, inv_count);
}

//Процедура підрахунку інверсій
pair<int *, int> SortAndCountInv(int A[], int n) {
    if (n == 1) {
        int *sorted_A = new int[n];
        sorted_A[0] = A[0];
        return make_pair(sorted_A, 0LL);
    } else {
        int n1 = n / 2;
        int n2 = n - n1;
        int *L = new int[n1];
        for (int i = 0; i < n1; i++) {
            L[i] = A[i];
        }
        int *R = new int[n2];
        for (int i = 0; i < n2; i++) {
            R[i] = A[n1 + i];
        }
        pair<int *, int> left_result = SortAndCountInv(L, n1);
        pair<int *, int> right_result = SortAndCountInv(R, n2);
        pair<int *, int> merge_result = MergeAndCountSplitInv(A, left_result.first, n1, right_result.first, n2);
        delete[] L;
        delete[] R;
        delete[] left_result.first;
        delete[] right_result.first;
        return make_pair(merge_result.first, left_result.second + right_result.second + merge_result.second);
    }
}

//сортирую массив количества инверсий и вместе с ним аналогично переставляю элементы в массиве индексов
void SortRowsWithIndex(pair<int *, int> *sorted_rows, int ind[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sorted_rows[i].second > sorted_rows[j].second) {
                swap(sorted_rows[i], sorted_rows[j]);
                swap(ind[i], ind[j]);
            }
        }
    }
}

//записываю индексы и количество инверcий в строках в новый файл
void WriteDataToFile(pair<int *, int> *sorted_rows, int ind[], int u, string filename) {
    ofstream file(filename);
    for (int i = 0; i < u; i++) {
        file << ind[i] << " " << sorted_rows[i].second << endl;
    }
    file.close();
}

//обрабатываю файл указаный при старте програмы
void FileProcessing(const string& filename, int x) {

    //считываю всю инфу из файла: количество рядков, длину рядков, индексы, массив рядков
    ifstream file(filename);
    int u, m;
    file >> u >> m;
    int **data = new int *[u];
    int ind[u];
    for (int i = 0; i < u; ++i) {
        file >> ind[i];
        data[i] = new int[m];
        for (int j = 0; j < m; ++j) {
            file >> data[i][j];
        }
    }
    file.close();

    //создаю новый массив рядков для которых надо будет считать количество инверсий
    int **newArr = CreateNewArray(data, data[x - 1], u, m);

    //применяем функцию SortAndCountInv() к каждому рядку массива newArr и записываю в sorted_rows масив отсортированых рядков и масив количества инверсий
    pair<int *, int> *sorted_rows = new pair<int *, int>[u];
    for (int i = 0; i < u; i++) {
        sorted_rows[i] = SortAndCountInv(newArr[i], m);
    }
    SortRowsWithIndex(sorted_rows,ind,u);

    //записываю массивы индексов и количества инверсий, отсортированые по инверсиям, в новыый файл
    string name="ip21_Tkach_L_02_output.txt";
    WriteDataToFile(sorted_rows, ind, u, name);;
    
    //освобождение памяти
    delete[] sorted_rows;
    for (int i = 0; i < u; i++) {
        delete[] newArr[i];
    }
    delete[] newArr;
    for (int i = 0; i < u; ++i){
        delete[] data[i];
    }
    delete[] data;
}

int main(int argc, char* argv[]){
    // cout<<argv[1]<<endl;
    int num = stoi(argv[2]);
    // cout<<num+2;
    FileProcessing(argv[1], num);
    return 0;
}
