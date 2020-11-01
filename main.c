#include "JonSnow.h"

// Estructura de un vértice
struct VertexSt {
    u32 id_node;
    node neighbours;
    u32 grado;
    u32 color;
    cols colisiones;
    u32 total_cols;
};

struct neig_list{
    u32 data;
    u32 order;
    struct neig_list *next;
};


// Estructura de un grafo
struct WinterSt {
    u32 total_vertices;
    u32 total_edges;
    u32 coloreo;
    vert *vertices;
    u32 total_vert_cargados;
    u32 *orden;
    u32 ult_cargado;
    bool coloreado;
};

int main()
{
    WinterIsHere G;
    G = WinterIsComing();
    clock_t begin = clock();
    u32 bip = Bipartito(G);
    clock_t end = clock();
    printf("Bipartito: %d\n", bip);
    printf("\n\tTiempo en Bipartitos: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
    /*
    printf("Corriendo greedy 1000 veces\n");
    clock_t begin = clock();
    for (int i = 0; i < 1001; ++i)
    {
        Greedy(G);
        printf("Corrido %d veces\n", i);
    }
    clock_t end = clock();
    printf("\n\tTiempo en colorear 1000 veces: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
    */
    /*
    for (u32 i = 0; i < G->total_vertices; ++i)
    {
        printf("Color del vertice %d es %d\n",G->vertices[i]->id_node,G->vertices[i]->color );
    }
    u32 vertice = G->vertices[3]->id_node;
    node aux = G->vertices[3]->neighbours;
    while(aux != NULL){
        printf("Vecino de %d: %d\n",vertice,aux->data);
        aux = aux->next;
    }
    */

    return 0;
}