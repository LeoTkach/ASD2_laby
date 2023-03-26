#include <iostream>
#include <cstring>
#include <cstdio>
#include <fstream>
using namespace std;

//створюю новий двовимірний масив для підрахунку інверсій
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

//процедура злиття та підрахунку розділених інверсій
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

//процедура підрахунку інверсій
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

//сортую масив кількості інверсій і разом із ним аналогічно переставляю елементи в масиві індексів
void SortRowsWithIndex(pair<int *, int> *sorted_rows, int ind[], int n) {
    for (int i = 1; i < n; i++) {
        pair<int *, int> key = sorted_rows[i];
        int key_ind = ind[i];
        int j = i - 1;
        while (j >= 0 && sorted_rows[j].second > key.second) {
            sorted_rows[j + 1] = sorted_rows[j];
            ind[j + 1] = ind[j];
            j--;
        }
        sorted_rows[j + 1] = key;
        ind[j + 1] = key_ind;
    }
}

//записую індекси та кількість інверсій у рядках у новий файл
void WriteDataToFile(pair<int *, int> *sorted_rows, int ind[], int u, string filename) {
    ofstream file(filename);
    file << ind[0] << endl;
    for (int i = 1; i < u; i++) {
        file << ind[i] << " " << sorted_rows[i].second << endl;
    }
    file.close();
}

//обробляю файл, вказаний при старті програми
void FileProcessing(const string& filename, int x) {

    //зчитую всю інфу з файлу: кількість рядків, довжину рядків, індекси, масив рядків
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

    //створюю новий масив рядків для яких треба буде рахувати кількість інверсій
    int **newArr = CreateNewArray(data, data[x - 1], u, m);

    //застосовую функцію SortAndCountInv() до кожної строки масиву newArr і записую в sorted_rows масив відсортованих рядків та масив кількості інверсій
    pair<int *, int> *sorted_rows = new pair<int *, int>[u];
    for (int i = 0; i < u; i++) {
        sorted_rows[i] = SortAndCountInv(newArr[i], m);
    }
    
    //сортую другий елемент створеного масиву, тобто масив кількості інверсій та разом з ним роблю тіж самі перестановки і в масиві індексів
    SortRowsWithIndex(sorted_rows,ind,u);

    //записую масиви індексів та кількості інверсій, відсортовані за інверсіями, у новий файл
    string name="ip21_Tkach_L_02_output.txt";
    WriteDataToFile(sorted_rows, ind, u, name);;
    
    //звільнення пам'яті
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
    int num = stoi(argv[2]);
    FileProcessing(argv[1], num);
    return 0;
}
