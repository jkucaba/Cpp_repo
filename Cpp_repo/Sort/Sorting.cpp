#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

void print(int* S, int n){               //wyœwietla dane
    for (int i = 0; i < n; i++){
        cout << S[i] << " ";
    }
}
void init(int* S, int n){               //generuje losowe dane
    for(int i = 0; i < n; i++){
        S[i] = rand()%7;
    }
}
void insertionSort(int* S, int n){
    int i, j, aux;
    for(i = 1; i< n; i++){
        aux = S[i];
        for(j = i-1; j>=0; j--){
            if(S[j]>aux){
                S[j+1]=S[j];
            }else {
                break;
            }
        }
        S[j+1] = aux;
    }
}
void selectionSort(int* S, int n){
    int min;
    for (int i=0; i<n-1; i++){
        min = i;
        for(int j=i+1; j<n; j++){
            if(S[j]<S[min]){
                min = j;
            }
        }
        swap(S[i], S[min]);
    }
}
void bubbleSort(int* S, int n){
    for(int i=1; i<n;i++){
        for(int j=n-1; j>=i; j--){
            if(S[j]<S[j-1]){
                swap(S[j], S[j-1]);
            }
        }
    }
}
int split(int* S, int left, int right){
    int pivot = S[left];//ustalamy pivot na ostatni element S
    int count = 0; //pozycja pivota (na jakiej ma siê znaleŸæ)
    for(int i = left+1; i <= right; i++){
        if(S[i] <= pivot){//ustalamy pozycjê pivota
            count++;
        }
    }
    int PivotIndex = left+count;
    swap(S[left], S[PivotIndex]);//S[count] wskazuje gdzie powinien znaleŸæ siê pivot]
    int i = left; int j = right;
    while(i < PivotIndex && j > PivotIndex){
        while(S[i] <= S[PivotIndex]){
            i++;
        }
        while(S[j] > S[PivotIndex]){
            j--;
        }
        if(i < PivotIndex && j > PivotIndex){
            swap(S[i++],S[j--]);
        }

    }
    return PivotIndex;
}
void quickSort(int* S, int left, int right){
    int index;
    if(left < right){
        index = split(S, left, right);
        quickSort(S, left, index-1);
        quickSort(S, index+1, right);
    }
}
void cntSort(int* S, int n){
    int k = 0;//wartoœæ najwiêksza w tablicy
    for(int i=0; i<n; i++){
        if(S[i]>k){
            k = S[i];
        }
    }
    int cnt[k+1]{0};//tablica pomocnicza
    int tab_wyjsc[n];//tabl wyjsciowa, w tym przypadku przepisuje, bo chce zmieniæ orgina³
    for(int i=0; i<n; i++){
        tab_wyjsc[i]=S[i];
    }
    for(int i=0; i<n; i++){//ustalamy ile jest danych wartoœci np(sa 3 czworki)
        cnt[tab_wyjsc[i]]++;
    }
    for(int j=1; j<=k; j++){//pêtla ustala ile elementów jest mniejszych od danego
        cnt[j]=cnt[j]+cnt[j-1];
    }
    for(int i=n-1; i>=0; i--){
        S[cnt[tab_wyjsc[i]]-1] = tab_wyjsc[i];//ustalamy na jakich pozycjach maj¹ byæ jakie liczby
        cnt[tab_wyjsc[i]]--;
    }
}
int main(){
    srand(time(NULL));
    int n = 20;                //przyk³adowy rozmiar
    int *S = new int[n];
    init(S, n);
    print(S,n);
    cntSort(S,n);
    cout << endl; print(S, n);
}
