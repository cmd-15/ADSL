#include<iostream>
using namespace std;

#define MAX 10

class Node{
    public:
    int data;
    Node *next;
};

class queue{
    int Q[MAX];
    int front, rear;

    public:
    queue(){
        front = rear = -1;
    }

    bool IsEmpty(){
        return (front == -1);
    }

    bool IsFull(){
        return (rear == MAX - 1);
    }

    void enqueue(int val){
        if(!IsFull()){
            if(rear==-1){
                front = rear = 0;
                Q[rear] = val;
            }
            else{
            Q[++rear] = val;
            }
        }
        else{
            cout << "Queue is full\n";
            return;
        }
    }

    int dequeue(){
        int val;
        if(!IsEmpty()){
            if(front==rear){
                val = Q[front];
                front = rear = -1;
                return val;
            }
            else{
                return Q[front++];
            }
        }
        else{
            cout << "Queue Empty\n";
            return -1;
        }
    }
};

   class graph{
       int adjmat[MAX][MAX];
       Node *adjlist[MAX];
       int visited[MAX];
       int n;
       string Landmark[MAX] = {"Admin","canteen","Ground","workshop","library"};

   public:
       graph(){
           n = 0;
           for (int i = 0; i < MAX; i++){
               visited[i] = 0;
               adjlist[i] = NULL;

               for (int j = 0; j < MAX;j++){
                   adjmat[i][j] = 0;
               }
            }
       }



       void creategraph(){
           int edges, s, d;

           for (int i = 0; i < MAX; i++){
               visited[i] = 0;
               adjlist[i] = NULL;

               for (int j = 0; j < MAX; j++){
                   adjmat[i][j] = 0;
               }
           }

           cout << "Enter the Number of vertices: ";
           cin >> n;

           if(n>5 || n<0){
               cout << "Error: You enter the wrong number of vertices!!!";
               n = 0;
               return;
           }

           cout << "Enter the number of Edges: ";
           cin >> edges;

           for (int i = 0; i < edges; i++){

               cout << "Enter the Source Vertex: ";
               cin >> s;

               cout << "Enter the Destination vertex: ";
               cin >> d;
           
           if (s<1 || s>n || d<1 || d>n){
               cout << "Invalid vertices\n";
               i--;
               continue;
           }

           adjmat[s][d] = 1;
           adjmat[d][s] = 1;

           Node *newNode = new Node;
           newNode->data = d;
           newNode->next = adjlist[s];
           adjlist[s] = newNode;

           Node *newNode2 = new Node;
           newNode2->data = s;
           newNode2->next = adjlist[d];
           adjlist[d] = newNode2;
       }
    }

    void resetVisited(){
        for (int i = 0; i < MAX; i++){
            visited[i] = 0;
        }
    }

    void Dadjmat(){
        cout << "\nAdjancency Matrix:\n";
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                cout << adjmat[i][j] << " ";
            }
            cout << endl;
        }
    }

    void Dadjlist(){
        cout << "\nAdjacency List\n";
        for (int i = 1; i <= n; i++){
            cout << Landmark[i - 1] << " -> ";

            Node *temp = adjlist[i];
            while(temp!=NULL){
            cout << Landmark[temp->data-1]<<" -> ";
            temp = temp->next;
            }
            cout << "NULL" << endl;
        }
    }

    void DFS(int v){
        if (v < 1 || v > n)
        {
            cout << "Invalid vertex";
            return;
        }
        visited[v] = 1;
        cout << Landmark[v - 1] << " -> ";

        for (int i = 1; i <= n; i++){
            if(adjmat[v][i]==1 && visited[i]==0){
                DFS(i);
            }
        }
    }

    void BFS(int v){
        if (v < 1 || v > n)
        {
            cout << "Invalid vertex";
            return;
        }
        queue Q;
        Q.enqueue(v);
        visited[v] = 1;

        while(!Q.IsEmpty()){
            int current = Q.dequeue();
            cout << Landmark[current - 1] << " -> ";

            Node *temp = adjlist[current];
            while(temp!=NULL){
                if(visited[temp->data]==0 ){
                    Q.enqueue(temp->data);
                    visited[temp->data] = 1;
                }
                temp = temp->next;
            }
        }
        cout << "NULL" << endl;
    }
};

int main(){
    int choice,start;
    graph G;

    do{
        cout << "\nWelcome to menu\n";
        cout << "1. Create Graph\n";
        cout << "2. Adjacency Matrix\n";
        cout << "3. Adjacency List\n";
        cout << "4. Print DFS Traversal\n";
        cout << "5. Print BFS Traversal\n";
        cout << "6. Exit\n";

        cout << "Enter the choice: ";
        cin >> choice;

        switch(choice){

            case 1:
                G.creategraph();
                break;

            case 2:
                G.Dadjmat();
                break;

            case 3:
                G.Dadjlist();
                break;

            case 4:
                cout << "Enter the starting Vertex: ";
                cin >> start;
                G.resetVisited();
                G.DFS(start);
                cout << "NULL" << endl;
                break;
            
            case 5:
                cout << "Enter the starting Vertex: ";
                cin >> start;
                G.resetVisited();
                G.BFS(start);
                break;

            case 6:
                cout << "Exiting....." << "Thank You!!";
                break;

            default:
                cout << "Entered The Invalid Choice";
        }
    } while (choice != 6);
    return 0;
}
