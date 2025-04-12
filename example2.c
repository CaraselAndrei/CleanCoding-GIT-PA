#include <stdio.h>
#include <stdlib.h>

// Structura nod
typedef struct node {
    int data;
    struct node *next;
} NODE;

// Structura graf
typedef struct graph {
    int vertices;
    NODE **adjacency_lists;
    int *visited;
} GPH;

// Creează un nod nou
NODE *create_node(int data) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Creează un graf nou
GPH *create_graph(int vertices) {
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Adaugă o muchie
void add_edge(GPH *graph, int src, int dest) {
    NODE *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

// DFS
void DFS(GPH *graph, int vertex) {
    NODE *adj_list = graph->adjacency_lists[vertex];
    NODE *temp = adj_list;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

// Coada pentru BFS
void enqueue(NODE **queue, int data) {
    NODE *new_node = create_node(data);
    if (*queue == NULL) {
        *queue = new_node;
    } else {
        NODE *temp = *queue;
        while (temp->next) temp = temp->next;
        temp->next = new_node;
    }
}

int dequeue(NODE **queue) {
    if (*queue == NULL) return -1;
    NODE *temp = *queue;
    int val = temp->data;
    *queue = (*queue)->next;
    free(temp);
    return val;
}

// BFS
void BFS(GPH *graph, int start_vertex) {
    NODE *queue = NULL;
    graph->visited[start_vertex] = 1;
    enqueue(&queue, start_vertex);

    while (queue != NULL) {
        int current_vertex = dequeue(&queue);
        printf("%d ", current_vertex);

        NODE *temp = graph->adjacency_lists[current_vertex];

        while (temp) {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

// Reset vizitat
void reset_visited(GPH *graph) {
    for (int i = 0; i < graph->vertices; i++)
        graph->visited[i] = 0;
}

// Afișare graf
void print_graph(GPH *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        NODE *temp = graph->adjacency_lists[i];
        printf("%d: ", i);
        while (temp) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int nr_noduri, nr_drumuri;
    printf("Introduceti nr de muchii:\n");
    scanf("%d", &nr_noduri);
    GPH *graph = create_graph(nr_noduri);
    printf("Introduceti nr de muchii:\n");
    scanf("%d", &nr_drumuri);
    printf("\n");
    for (int i = 0; i < nr_drumuri; i++) {
        int x,y;
        printf("Introduceti o muchie:");
        scanf("%d %d", &x, &y);
        add_edge(graph, x, y);
    }

   // printf("Lista de adiacenta:\n");
   // print_graph(graph);

    printf("\nDFS: ");
    DFS(graph, 0);

    reset_visited(graph);

    printf("\nBFS: ");
    BFS(graph, 0);

    return 0;
}
