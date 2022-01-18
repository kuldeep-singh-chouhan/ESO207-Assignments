#include<iostream>
using namespace std;

bool is_bipart = true; // flag to check whether graph is bipartite or not

class Node{    
    public:
        int vertex;
        Node* next;
};

Node* createNode(int x) { // creating a new node
    Node* newNode = new Node();
    newNode -> vertex = x;
    newNode -> next = NULL;
    return newNode;
}

void attach(Node* n, int x) { // add node(with data x adjacent to a vertex n) in front of linked list
    Node* temp = createNode(x);
    temp -> next = n -> next;
    n -> next = temp;
}

void mark(int index, int partition, int set[], Node** graph, int v){ // mark whether vertex belongs to any of the partition or it's not possible
    Node* temp = graph[index] -> next;
    if(set[index]!=0) {  // if vertex is already parted
        if(set[index] != partition){ // if parted in wrong set
            is_bipart = false;
            return;
        }

        return; // if parted in same set
    }

    set[index] = partition; // vertex not visited before

    while(temp != NULL) {
        if(partition == 1) mark(temp->vertex, 2, set, graph, v);                       // parting the adjacent vertices
        else if(partition == 2) mark(temp -> vertex, 1, set, graph, v);                // in other set
        
        temp = temp -> next;
    }
}

void is_bipartite(Node** graph, int v){      
    int set[v] = {0};

    mark(0, 1, set, graph, v); // parting vertices by calling for vertex 0 here and 
                               //other vertices will be called recursively because graph is connected  


    if(is_bipart) {  // if bipartite
        cout << "YES\n";
        for(int i = 0; i < v; i++) {
            printf("%d\n", set[i]);
        }
    }
    else cout << "NO\n"; // if not
}

int main() {
    int v,e;
    scanf("%d %d", &v, &e);

    Node** graph = new Node*[v]; // initializing vertex of graph
    for(int i = 0; i < v; i++) {
        graph[i] = createNode(i); 
    }
    for(int i = 0; i < e; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
       // attaching nodes to adjacency list
        attach(graph[a], b);
        attach(graph[b], a);
    }
    is_bipartite(graph, v);
}