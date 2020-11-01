#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Alias para estructuras
typedef unsigned int u32;

//Punteros a estructuras
typedef struct VertexSt *vert;
typedef struct WinterSt *WinterIsHere;
typedef struct Collisions *cols;
typedef struct Data *line;

// Librerías propias externas que usan estructuras de JonSnow.h
#include "List.h"
#include "quick_sort.h"

//Funciones para crear, leer y eliminar grafo
WinterIsHere WinterIsComing();
WinterIsHere new_graph();
WinterIsHere Primavera(WinterIsHere g);
WinterIsHere load_graph(WinterIsHere g, FILE *fp);
WinterIsHere add_edge(WinterIsHere g, u32 v1, u32 v2);
u32 add_vertex(WinterIsHere g, u32 v);
u32 new_collision(WinterIsHere g, u32 pos, u32 v);
u32 power_hash(WinterIsHere g, u32 v);
int collision_lookup(WinterIsHere g, u32 pos, u32 v);
int search_vertex(WinterIsHere g, u32 v);
line split_input(const char *string);
void read_graph(WinterIsHere g);
void print_neighbors(WinterIsHere g, u32 v);

// Funciones de coloreo
u32 Greedy(WinterIsHere W);
void color_distinto_vecinos(WinterIsHere W, u32 v, u32 pos, u32* colores);
int Bipartito(WinterIsHere W);
WinterIsHere decolorear_grafo(WinterIsHere g);

// Funciones para extraer información sobre el grafo
u32 IesimoVerticeEnElOrden(WinterIsHere W, u32 i);
u32 NumeroDeColores(WinterIsHere W);
u32 NumeroVerticesDeColor(WinterIsHere W, u32 i);
u32 NumeroDeLados(WinterIsHere W);
u32 NumeroDeVertices(WinterIsHere W);

//Funciones de ordenación de grafos
void OrdenWelshPowell(WinterIsHere W);
void OrdenNatural(WinterIsHere W);
void Print_Ordered_Graph(WinterIsHere W);
void OrdenWelshPowell(WinterIsHere W);
void AleatorizarVertices(WinterIsHere W, u32 x);
void ReordenManteniendoBloqueColores(WinterIsHere W, u32 x);
void ReordenManteniendoBloqueColores_0(WinterIsHere W);
void ReordenManteniendoBloqueColores_1(WinterIsHere W);
void ReordenManteniendoBloqueColores_2(WinterIsHere W);
void ReordenManteniendoBloqueColores_3(WinterIsHere W);
void ReordenManteniendoBloqueColores_x(WinterIsHere W,u32 x);
void swap(u32 array[], u32 i, u32 j);

//Funciones de los vértices
u32 NombreDelVertice(WinterIsHere W, u32 x);
u32 ColorDelVertice(WinterIsHere W, u32 x);
u32 GradoDelVertice(WinterIsHere W, u32 x);
u32 IesimoVecino(WinterIsHere W, u32 x, u32 i);
