#include <iostream>

using namespace std;

class MinHeap{
    private:
        int* kopiec;
        int capacity;
        int size;
    public:
        MinHeap(int c);            //tworzy pusty kopiec o pojemnoœci c
        MinHeap();                //konstruktor do testów kopca - nale¿y utworzyæ kopiec z nastêpuj¹c¹ zawartoœci¹: 1, 2, 4, 6, 5, 4, 7, 7, 7, 9, 6
        bool empty();
        bool full();
        int getLeft(int i);                    //zwraca pozycjê lewego syna
        int getRight(int i);                //zwraca pozycjê prawego syna
        int getParent(int i);                //zwraca pozycjê ojca
        int getSize();                        //zwraca rozmiar kopca
        void setSize(int s);                //ustawia rozmiar kopca na s
        int getValue(int i);                //zwraca wartoœæ z pozycji i
        void setValue(int i, int x);        //ustawia wartoœæ x na pozycji i
        void bottomUp(int i);                //przywraca w³asnoœæ kopca metod¹ wynurzania
        void topDown(int i);                //przywraca w³asnoœæ kopca metod¹ zatapiania
        void insert(int x);                    //wstawia element z wartoœci¹ x (tutaj wartoœæ jest jednoczeœnie priorytetem)
        void deleteMin();                     //usuwa element z minimaln¹ wartoœci¹
        int minimum();                        //zwraca minimaln¹ wartoœæ
        void del(int i);                         //usuwa element na pozycji i
        void decreaseKey(int i, int x);        //zmniejsza wartoœæ priotytetu dla danych na pozycji i, ustawia x
        friend std::ostream& operator<<(std::ostream& out, MinHeap& h){
            if(!h.empty()){
                for(int i = 0; i<h.size; i++){
                    out << h.kopiec[i] << " ";
                }
            }
        };
};
MinHeap::MinHeap(int c){
    kopiec = new int [c];
    capacity = c;
    size = 0;
};
MinHeap::MinHeap(){
    kopiec = new int [11]{1, 2, 4, 6, 5, 4, 7, 7, 7, 9, 6};
    size = 11;
    capacity = 11;
};
bool MinHeap::empty(){
    if(size==0){
        return true;
    }
    else return false;
};
bool MinHeap::full(){
    if(size==capacity){
        return true;
    }
    else return false;
};
int MinHeap::getLeft(int i){
    if((2*i+1)<size){
        return (2*i+1);
    }else return -1;
};
int MinHeap::getRight(int i){
    if((2*i+2)<size){
        return (2*i+2);
    }else return -1;
};
int MinHeap::getParent(int i){
    if(i==0){
        return -1;
    }else{
        return (i-1)/2;
    }
};
int MinHeap::getSize(){
    return size;
};
void MinHeap::setSize(int s){
    size = s;
};
int MinHeap::getValue(int i){
    if(i<size){
        return kopiec[i];
    }else return -420;
};
void MinHeap::setValue(int i, int x){
    kopiec[i] = x;
};
void MinHeap::bottomUp(int i){
    if(i>0){
        int p = getParent(i);
        if(kopiec[i]<kopiec[p]){
            swap(kopiec[i],kopiec[p]);
            bottomUp(p);
        }
    }
};
void MinHeap::topDown(int i){
    int l = getLeft(i);
    int r = getRight(i);
    int g = i;
    if(l != -1 && kopiec[l]<kopiec[g]){
        g = l;
    }
    if(r != -1 && kopiec[r]<kopiec[g]){
        g = r;
    }
    if(g != i){
        swap(kopiec[i], kopiec[g]);
        topDown(g);
    }
}
void MinHeap::insert(int x){
    if(!full()){
        kopiec[size] = x;
        bottomUp(size);
        size++;
    }
};
void MinHeap::deleteMin(){
    if(!empty()){
        size--;
        swap(kopiec[0], kopiec[size]);
        topDown(0);
    }
};
int MinHeap::minimum(){
    if(!empty()){
        return kopiec[0];
    }
};
void MinHeap::del(int i){
    if(!empty()){
        size--;
        swap(kopiec[i], kopiec[size]);
        topDown(i);
    }
};
void MinHeap::decreaseKey(int i, int x){
    kopiec[i] = x;
    bottomUp(i);
};
int main(){



}
