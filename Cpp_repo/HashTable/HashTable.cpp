#include <iostream>
#include <string>

using namespace std;

class HashTable{
    private:
        string* t;
        int capacity;
        int size;
    public:
        HashTable(int c);                //konstruktor tworz¹cy pust¹ tablicê o pojemnoœci c
        bool empty();
        bool full();
        int hashFunction(string s);        //funkcja haszuj¹ca dla klucza s
        int insert(string s);            //wstawienie klucza s (zwraca liczbê prób przy wyst¹pieniu kolizji - 0 jeœli kolizja nie wyst¹pi³a)
        void del(string s);                //usuwa element z kluczem s
        string search(string s);        //wyszukuje i zwraca element z s
        int search1(string s);            //wyszukuje s i zwraca liczbê prób przy wyst¹pieniu kolizji - 0 jeœli kolizja nie wyst¹pi³a
        friend ostream& operator<<(ostream& out, HashTable& ht){
            for(int i = 0; i < ht.capacity; i++){
                out << ht.t[i] << " ";
            }
        }; //wypisuje tablicê (z numerami pól), pozostawia puste dla wolnych pól
};

HashTable::HashTable(int c){
    this->capacity = c;
    t = new string[c];
    size = 0;
    for(int i = 0; i < c; i++){
        t[i]= "NULL";
    }
};
bool HashTable::empty(){
    if(size == 0){
        return true;
    }else return false;
};
bool HashTable::full(){
    if(size == capacity){
        return true;
    }else return false;
};
int HashTable::hashFunction(string s){
    int suma = 0;
    for(int i = 0; i < s.length(); i++){
        char znak = s[i];
        int value = (int) znak;
        suma += value;
    }
    return (suma%capacity);
};
int HashTable::insert(string s){
    if(!full()){
        int i = 0; //numer próby
        for(int a=hashFunction(s); a<capacity; a++){
            if(t[a]=="NULL" || t[a]=="FREE"){
                t[a] = s;
                size++;
                return i;
            }
            i++;
        }
        for(int a=0; a<hashFunction(s); a++){
            if(t[a]=="NULL" || t[a]=="FREE"){
                t[a] = s;
                size++;
                return i;
            }
            i++;
        }
        return -1;
    }
};
void HashTable::del(string s){
        for(int a=hashFunction(s); a<capacity; a++){
            if(t[a]==s){
                t[a] = "FREE";
                size--;
                return;
            }
        }
        for(int a=0; a<hashFunction(s); a++){
            if(t[a]==s){
                t[a] = "FREE";
                size--;
                return;
            }
        }
};
string HashTable::search(string s){
    for(int a = hashFunction(s); a<capacity; a++){
        if(t[a]=="NULL"){
            return "Nie ma";
        }
        if(t[a]==s){
            return t[a];
        }
    }
    for(int a = 0; a<hashFunction(s); a++){
        if(t[a]=="NULL"){
            return "Nie ma";
        }
        if(t[a]==s){
            return t[a];
        }
    }
    return "Nie ma";
}
int HashTable::search1(string s){
    int i = 1; //iloœæ prób
    for(int a = hashFunction(s); a<capacity; a++){
        if(t[a]=="NULL"){
            return i;
        }
        if(t[a]==s){
            return i;
        }
        i++;
    }
    for(int a = 0; a<hashFunction(s); a++){
        if(t[a]=="NULL"){
            return i;
        }
        if(t[a]==s){
            return i;
        }
        i++;
    }
    return i;
}
int main(){

}
