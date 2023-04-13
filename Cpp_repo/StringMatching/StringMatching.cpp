#include <iostream>
#include <string>
#include <cmath>

using namespace std;

void naiveStringMatching(string T, string p){
    int i;
    for(int s=0; s<=T.length()-p.length(); s++){
        i=0;
        while(i<p.length() && p[i]==T[s+i]){
            i++;
        }
        if(i==p.length()){
            cout << "Wzorzec wystapil z przesunieciem " << s << endl;
        }
    }
}
bool compare(string p, int m, string T, int s){
    int i=0;
    while(i<m && p[i]==T[s+i]){
        i++;
    }
    if(i==p.length()){
        return true;
    }
    return false;
}
int hashFunction(string p, int m){
    int h=0;
    for(int i=0; i<m; i++){
        h+=pow(2,m-i-1)*p[i];
    }
    return h;
}
void RabinKarp(string T, string p){
    int hp = hashFunction(p, p.length());
    int hs = hashFunction(T, p.length());
    bool match;
    for(int s=0; s<=T.length()-p.length(); s++){
        if(hs == hp){
            match = compare(p, p.length(),T,s);
            if(match==true){
                cout << "Wzorzec wystapil z przesunieciem " << s << endl;;
            }
        }
        if(s<T.length()-p.length()){
            hs = (hs - pow(2,p.length()-1)*T[s])*2+pow(2,0)*T[s+p.length()];
        }
    }
}
void BoyerMoore(string T, string p){
    int bc[256];
    for(int i=0; i<256; i++){
        bc[i]=-1;
    }
    for(int i=0; i<p.length();i++){
        bc[p[i]]=i;
    }
    int s=0;
    int i;
    while(s<=T.length()-p.length()){
        i=p.length()-1;
        while(i>=0 && p[i]==T[s+i]){
            i--;
        }
        if(i==-1){
            cout << "Wzorzec wystapil z przesunieciem " << s << endl;
            s++;
        }
        else{
            if(bc[T[s+i]]==-1){
                s=s+i+1;
            }
            else if(bc[T[s+i]]<i){
                s=s+i-bc[T[s+i]];
            }
            else{
                s++;
            }
        }
    }
}
int main(){

    string text="siala baba mak nie wiedziala jak mak";
    string pattern="mak";
    cout << "naiwny" << endl;
    naiveStringMatching(text, pattern);
    cout << "Rabin Karp"<<endl;
    RabinKarp(text, pattern);
    cout << "Boyer Moor"<<endl;
    BoyerMoore(text, pattern);

}
