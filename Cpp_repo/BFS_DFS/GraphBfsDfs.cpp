#include <iostream>
#include <queue>

using namespace std;

struct edge{
    int s; //wierzchołek
    int t; //sąsiad
};

class Graph{
    private:
        int** adjMatrix;    //macierz sąsiedstwa
        int n;              //liczba węzłów
        bool directed;      //true - graf skierowany, false - graf nieskierowany
        void dfs(int s, int* visited);    //wykonuje przeszukiwanie i wyświetla węzły w porządku odwiedzenia
    public:
        Graph(int n, int m, edge edges[], bool directed);    //tworzy graf w oparciu o pdaną listę krawędzi
        void bfs(int s);                //wykonuje przeszukiwanie i wyœwietla węzy w porządku odwiedzenia
        void dfs(int s);                //metoda pomocnicza dla dfs - tworzy tabelę visited i wywołuje metodę prywatną dfs
        friend ostream& operator<<(ostream& out, Graph& g);//wyświetla graf
        ~Graph(){};

};
Graph::Graph(int n, int m, edge edges[], bool directed){
    this->directed=directed;
    this->n=n;
    adjMatrix=new int *[n];
    for(int i=0; i<n; i++){
        adjMatrix[i] = new int [n]{};
    }
    for(int i=0; i<m; i++){
        adjMatrix[edges[i].s][edges[i].t]=1;
        if(!directed){
            adjMatrix[edges[i].t][edges[i].s]=1;
        }
    }
}
ostream& operator<<(ostream& out, Graph& g){
    for(int i=0; i<g.n; i++){
        for(int j=0; j<g.n; j++){
            out << g.adjMatrix[i][j] << " ";
        }
        out << endl;
    }
};
void Graph::bfs(int s){
    int visited[n]{};
    int parent[n]{};
    int u;
    queue<int> g;
    visited[s]=1;
    g.push(s);
    while(!g.empty()){
        u = g.front(); g.pop();
        cout << u << " ";
        for(int i=0; i<n; i++){
            if(adjMatrix[u][i]==1){
                if(visited[i]==0){
                    visited[i]=1;
                    parent[i]=u;
                    g.push(i);
                }
            }
        }
    }
}
void Graph::dfs(int s, int* visited){
    visited[s]=1;
    cout<<s<<" ";
    for(int i=0; i<n; i++){
        if(adjMatrix[s][i]==1){
            if(visited[i]==0){
                dfs(i, visited);
            }
        }
    }
}

void Graph::dfs(int s){
    int visited[n]{};
    dfs(s,visited);
};
int main(){
    int n = 6, m =15;
    edge directedGraph[]={{0,4},{0,5},{1,0},{1,2},{1,4},
                        {2,1},{2,3},{2,4},{3,2},{3,5},
                        {4,0},{4,1},{4,3},{5,3},{5,4}};  //przykładowy graf
    Graph g(n,m,directedGraph,true);
    cout<<g;
    cout << endl << "BFS: ";
    g.bfs(0);
    cout << endl << "DFS: ";
    g.dfs(0);
}
