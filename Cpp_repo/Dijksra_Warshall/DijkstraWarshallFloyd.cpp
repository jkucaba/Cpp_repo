#include <iostream>

using namespace std;

struct weightedEdge{
    int s;
    int t;
    double w;        //waga krawêdzi
};
class WeightedGraph{
    private:
        double** adjWeightMatrix;
        int n;                //liczba wêz³ów
        bool directed;
    public:
        WeightedGraph(int n, int m, weightedEdge edges[], bool directed);    //tworzy graf w oparciu o pdana liste krawedzi z wagami
        void Dijkstra(int s);
        void WarshallFloyd();
        friend ostream& operator<<(ostream& out, WeightedGraph& g);
        void shortestPath(int s, int t, int* parent);
        ~WeightedGraph(){};
};
WeightedGraph::WeightedGraph(int n, int m, weightedEdge edges[], bool directed){
    this->n=n;
    this->directed=directed;
    adjWeightMatrix = new double *[n];
    for(int i=0; i<n; i++){
        adjWeightMatrix[i] = new double [n];
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==j){
                adjWeightMatrix[i][j]=0;
            }else{
                adjWeightMatrix[i][j]=1234;
            }
        }
    }
    for(int i=0; i<m; i++){
        adjWeightMatrix[edges[i].s][edges[i].t]=edges[i].w;
        if(!directed){
            adjWeightMatrix[edges[i].t][edges[i].s]=edges[i].w;
        }
    }
}
ostream& operator<<(ostream& out, WeightedGraph& g){
    for(int i=0; i<g.n; i++){
        for(int j=0; j<g.n; j++){
            out << g.adjWeightMatrix[i][j] << " ";
        }
        out << endl;
    }
};
int znajdzMin(int* d, int* S, int n){
    int minIndex=0;
    for(int i=0; i<n; i++){
        if(S[i]!=1){
            minIndex=i;
            break;
        }
    }
    for(int i=0; i<n; i++){
        if(S[i]==0&&d[i]<d[minIndex]){
            minIndex=i;
        }
    }
    return minIndex;
}
void WeightedGraph::shortestPath(int s, int t, int* parent){
    int droga[n];
    int size=0;
    droga[size]=t;
    int x=t;
    while(x!=s){
        x=parent[x];
        size++;
        droga[size]=x;
    }
    cout << "Najkrotsza sciezka od " << s << " do " << t <<":";
    for(int i=size; i>=0; i--){
        cout << droga[i]<< " ";
    }
}
void WeightedGraph::Dijkstra(int s){
    int S[n]{};
    int d[n];
    int parent[n];
    for(int i=0; i<n; i++){
        if(i==s){
            d[i]=0;
        }else {
            d[i]=2115;
        }
        parent[i]=-1;
    }
    for(int i=0; i<n; i++){
        int u=znajdzMin(d,S,n);
        S[u]=1;
        for(int i=0; i<n; i++){
            if(adjWeightMatrix[u][i]!=1234 && u!=i){
                if(d[i]>d[u]+adjWeightMatrix[u][i]){
                    d[i]=d[u]+adjWeightMatrix[u][i];
                    parent[i]=u;
                }
            }
        }
    }
    for(int i=0; i<n; i++){
        cout <<"d["<<i<<"]="<< d[i] <<" ";
    }
    cout << endl;
    for(int i=0; i<n; i++){
        cout <<"p["<<i<<"]="<< parent[i] <<" ";
    }
    cout << endl;
    shortestPath(0,1,parent);
}
void WeightedGraph::WarshallFloyd(){
    int d[n][n];//tablica dróg
    int p[n][n];//tablica przodków
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            d[i][j]=adjWeightMatrix[i][j];
            if(adjWeightMatrix[i][j]!=0&&adjWeightMatrix[i][j]!=1234){
                p[i][j]=i;
            }
        }
    }
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(d[i][j]>d[i][k]+d[k][j]){
                    d[i][j]=d[i][k]+d[k][j];
                    p[i][j]=p[k][j];
                }
            }
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout <<"d["<<i <<" "<<j<<"]="<< d[i][j] <<" ";
        }
        cout << endl;
    }
}
int main(){
    int n = 6, m =15;
    weightedEdge directedWeightedGraph[]={{0,4,6}, {0,5,1},{1,0,2}, {1,2,5}, {1,4,1}, {2,1,3}, {2,3,2},
                                        {2,4,1}, {3,2,1}, {3,5,4}, {4,0,6}, {4,1,4}, {4,3,2}, {5,3,1}, {5,4,1}};
    WeightedGraph h(n,m,directedWeightedGraph,true);
    cout << h;
    h.Dijkstra(0);
    cout << endl;
    h.WarshallFloyd();

}
