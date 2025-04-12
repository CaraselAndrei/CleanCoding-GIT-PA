#include <stdio.h>
#include <stdlib.h>

///STRUCTURI

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int v;           // număr de noduri (restaurante)
    int *vis;        // vector de vizitare
    NODE **alst;     // listă de adiacență
} GPH;

typedef struct Stack {
    int top;
    int scap;
    int *arr;
} STK;


///FUNCȚII GRAF

NODE *create_node(int val) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = val;
    nn->next = NULL;
    return nn;
}

GPH *create_g(int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(sizeof(NODE *) * v);  // vector de pointeri la liste
    g->vis = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }

    return g;
}

void add_edge(GPH *g, int src, int dest) {
    // adăugăm muchie neorientată: src <-> dest
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

void insert_edges(GPH *g, int edg_nr) {
    int src, dest;
    printf("Adauga %d drumuri (index de la 0 la %d):\n", edg_nr, g->v - 1);
    for (int i = 0; i < edg_nr; i++) {
        printf("Drumul %d (src dest): ", i + 1);
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g) {
    for (int i = 0; i < g->v; i++) {
        g->vis[i] = 0;
    }
}


/// FUNCȚII STIVĂ 

STK *create_s(int scap) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(sizeof(int) * scap);
    s->top = -1;
    s->scap = scap;
    return s;
}

void push(int val, STK *s) {
    if (s->top < s->scap - 1) {
        s->arr[++s->top] = val;
    }
}

int pop(STK *s) {
    if (s->top >= 0) {
        return s->arr[s->top--];
    }
    return -1;
}


/// FUNCȚIA DE VERIFICARE DRUM 

int path_exists(GPH *g, int src, int dest) {
    if (src == dest) return 1; // același restaurant

    wipe(g); // resetăm vectorul de vizite

    STK *s = create_s(g->v);
    push(src, s);
    g->vis[src] = 1;

    while (s->top >= 0) {
        int current = pop(s);

        NODE *adj = g->alst[current];
        while (adj != NULL) {
            if (adj->data == dest) {
                free(s->arr); free(s);
                return 1; // drum găsit
            }
            if (!g->vis[adj->data]) {
                g->vis[adj->data] = 1;
                push(adj->data, s);
            }
            adj = adj->next;
        }
    }

    free(s->arr); free(s);
    return 0; // drum inexistent
}


int main() {
    int nr_restaurante, nr_drumuri;
    printf("Cate restaurante sunt? ");
    scanf("%d", &nr_restaurante);

    printf("Cate drumuri sunt intre restaurante? ");
    scanf("%d", &nr_drumuri);

    GPH *g = create_g(nr_restaurante);

    insert_edges(g, nr_drumuri);

    int r1, r2;
    printf("\nVerificam daca exista drum intre doua restaurante.\n");
    printf("Restaurantul sursa: ");
    scanf("%d", &r1);
    printf("Restaurantul destinatie: ");
    scanf("%d", &r2);

    if (path_exists(g, r1, r2)) {
        printf(" Exista drum intre restaurantele %d si %d.\n", r1, r2);
    } else {
        printf("Nu exista drum intre restaurantele %d si %d.\n", r1, r2);
    }

    return 0;
}
