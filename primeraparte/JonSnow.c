#include "JonSnow.h"

/*
    Definición de estructuras de datos
*/

// Estructura de un vértice
struct VertexSt {
    u32 id_node;
    node neighbours;
    u32 grado;
    u32 color;
    cols colisiones;
    u32 total_cols;
};

// Estructura de vecinos
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

// Estructura para manejar las colisiones
struct Collisions{
    struct Collisions *next;
    u32 indice;
    u32 id_node;
};

// Estructura para pasar los datos del input
struct Data{
    u32 u;
    u32 v;
    u32 total_edges;
    u32 total_vertices;
    u32 caso;
};

// Funciones para creación y destrucción de grafos

/*
    Aloca memoria, carga el grafo, lo colorea
    y devuelve un puntero al grafo g, en caso de
    error devuelve NULL
*/
WinterIsHere WinterIsComing(){
    int scan = 0;
    FILE *fp;
    char fname[255]; // Longitud máxima por defecto para nombre de archivos
    printf("Ingrese el nombre del archivo a leer:\n");
    scan = scanf("%s",fname);
    scan = scan - scan;
    fp = fopen(fname,"r");
    if (fp != NULL)
    {
        WinterIsHere g = new_graph();
        clock_t begin = clock();
        printf("Cronómetro empezado\n");
        printf("Cargando grafo...\n");
        g = load_graph(g,fp);
        fclose(fp);
        printf("Grafo cargado correctamente.\n");
        clock_t end = clock();
        printf("\n\n\tTiempo en cargar Grafo: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
        printf("Coloreando con Greedy...\n");
        begin = clock();
        u32 greedy = Greedy(g);
        end = clock();
        printf("Grafo coloreado en %f segundos con %d colores\n", (double)(end - begin) / CLOCKS_PER_SEC,greedy);
		return g;
    }else{
        printf("Archivo inexistente.\n");
        return NULL;
    }
}

/*
    Función que crea un nuevo grafo g y devuelve
    un puntero a g vacío
*/
WinterIsHere new_graph() {
    WinterIsHere g;
    g = (WinterIsHere)malloc(sizeof(struct WinterSt));
    g->coloreado = false;
    return g;
}

/*
    Destruye el grafo
*/
WinterIsHere Primavera(WinterIsHere g) {
    for (u32 i = 0; i < g->total_vertices; ++i)
    {
        g->vertices[i]->neighbours = destroy_list(g->vertices[i]->neighbours);
        free(g->vertices[i]);
        g->vertices[i] = NULL;
    }
    free(g);
    g = NULL;
    return g;
}

/*
    Función que carga los datos en el grafo y devuelve un
    puntero al grafo cargado
*/
WinterIsHere load_graph(WinterIsHere g, FILE *fp) {
    char *c = NULL;
    char linea[80];
    line data = (line)malloc(sizeof(struct Data));
    // Lee una línea mientras el archivo no llegue al final

    c = fgets(linea, 80, fp);
    data = split_input(linea);
    if (data->caso != 2)
    {
        while(data->caso != 2){
            c = fgets(linea, 80, fp);
            data = split_input(linea);
        }
    }

    g->total_vertices = data->total_vertices;
    g->total_edges = data->total_edges;
    g->vertices = (vert*)calloc(g->total_vertices,sizeof(vert));
    g->orden = (u32*)calloc(g->total_vertices,sizeof(u32));
    g->total_vert_cargados = 0;
    g->ult_cargado = 0;
    while (!feof(fp)) {
        c = fgets(linea, 80, fp);
        //avanzar a siguiente linea archivo
        data = split_input(linea);
        if (data->caso == 1)
        {
            // Se asume que los pares de vertices no se repiten
            add_edge(g, data->u, data->v);
            add_edge(g, data->v, data->u);
        }
    }
    c = c;
    return g;
}


/*
    Agrega una arista a un vértice en el grafo g
    y devuelve un puntero a g
*/
WinterIsHere add_edge(WinterIsHere g, u32 v1, u32 v2) {
    int pos = search_vertex(g, v1);

    // Si no se ha encontrado, se debe intentar agregar
    if(pos == -1){
        pos = add_vertex(g,v1);
    }

    g->vertices[pos]->neighbours = insert(g->vertices[pos]->neighbours,v2);
    g->vertices[search_vertex(g, v1)]->grado++;

    return g;
}
/*
    Agrega un nuevo vértice al arreglo del grafo g
*/
u32 add_vertex(WinterIsHere g, u32 v) {
    u32 pos = power_hash(g,v);

    if (g->vertices[pos] != 0){
        // Si no está libre, entonces lo agrega como una colisión
        pos = new_collision(g,pos,v);
    }
    g->vertices[pos] = (vert) malloc(sizeof(struct VertexSt));
    g->vertices[pos]->id_node = v;
    g->vertices[pos]->neighbours = NULL;
    g->vertices[pos]->color = 0;
    g->vertices[pos]->grado = 0;
    g->vertices[pos]->colisiones = NULL;
    g->vertices[pos]->total_cols = 0;
    g->total_vert_cargados = g->total_vert_cargados+1;
    g->orden[g->total_vert_cargados-1] = v;
    return pos;
}

/*
    Función que devuelve una posición válida para
    almacenar un vértice en el arreglo de g, en caso
    de que se produzca una colisión en la función de hash
*/
u32 new_collision(WinterIsHere g, u32 pos, u32 v) {
    /*
        Si no ha sido agregado, entonces recorremos el arreglo
        linealmente en busca de una posición libre y la guardamos
        en la tabla colisiones de la celda pos. De esta forma, acceder
        va a ser de O(1+|tabla_colisiones(pos)|)
    */
    u32 i = g->ult_cargado;
    while(g->vertices[i] != 0){
        i++;
        if (i > g->total_vertices)
        {
            abort();
        }
    }
    g->ult_cargado = i;
    // Si no se produjeron colisiones antes, aloca una nueva tabla de colisiones
    // apuntando a null como next
    cols nueva = (cols)malloc(sizeof(struct Collisions));
    if(g->vertices[pos]->total_cols == 0){
        nueva->next = NULL;
        nueva->indice = i;
        nueva->id_node = v;
    }else{
        // Si ya habían colisiones, apunta la nueva colisión al principio de la
        // tabla
        nueva->next = g->vertices[pos]->colisiones;
        nueva->indice = i;
        nueva->id_node = v;
    }
    g->vertices[pos]->colisiones = nueva;
    g->vertices[pos]->total_cols+=1;
    return i;
}

int collision_lookup(WinterIsHere g, u32 pos, u32 v){
    /*
        Verificamos la tabla de colisiones de la posición
        para ver si ya hemos agregado el vértice antes
     */
    int index_found = -1;
    if (g->vertices[pos]->total_cols > 0)
    {
        cols colissions = g->vertices[pos]->colisiones;
        while(colissions != NULL && index_found == -1){
            if (colissions->id_node == v)
            {
                index_found = (int)colissions->indice;
            }else{
                colissions = colissions->next;
            }
        }
    }
    return index_found;
}


// Devuelve la posición en la tabla de un vértice
int search_vertex(WinterIsHere g, u32 v){
    u32 pos = power_hash(g,v);
    if (g->vertices[pos] == 0)
    {
        // Vértice no encontrado (celda vacía)
        return -1;
    }

    if(g->vertices[pos] != 0 && g->vertices[pos]->id_node != v){
        // Ya hay un vértice agregado en la posición pos, se busca en la tabla
        // de colisiones para ver si está agregado el vértice v1
        pos = collision_lookup(g,pos,v);
    }

    return pos;
}


/*
    Función que 'tokeniza' una línea cadena de caracteres de
    acuerdo a el formato DIMACS y devuelve una tupla con
    los datos obtenidos
*/
line split_input(const char *string) {
    line data = (line)malloc(sizeof(struct Data));
    char *token1;
    char *s = " ";
    char buff[80];
    strcpy (buff, string);

    /* Primer token */
    token1 = strtok(buff, s);
    if (strcmp(token1, "e") == 0) {
        data->caso = 1;
        // Caso 1: Guardo vertices en tupla
        data->u = (u32) atoi(strtok(NULL, s));
        data->v = (u32) atoi(strtok(NULL, s));
    } else if (strcmp(token1, "p") == 0) {
        // Caso 2: Guardo información del grafo
        data->caso = 2;

        strtok(NULL, s);// Ignoro el token 'edge'

        data->total_vertices = (u32) atoi(strtok(NULL, s));
        data->total_edges = (u32) atoi(strtok(NULL, s));
    } else {
        // Caso 3, input es un comentario y no hago nada
        data->caso = 3;
    }

    return data;
}


u32 power_hash(WinterIsHere g, u32 v){
    u32 pos = v*265443 % g->total_vertices;
    return pos;
}

void read_graph(WinterIsHere g){
    for (u32 i = 0; i < g->total_vertices; ++i)
    {
        printf("Vertice:%u, Colisiones:%d \n",g->vertices[i]->id_node,g->vertices[i]->total_cols);
    }
}

// Funciones de Coloreo
u32 Greedy(WinterIsHere W){
    // Decolorea el grafo en caso de ya haber sido coloreado
    if (W->coloreado == true)
    {
        decolorear_grafo(W);
    }
    /*Variables que guardan el coloreo hasta el momento, color usado para colorear
    el ultimo color que se usó, y una estructura colores_vec, que es un array donde se
    provee una biyección entre un color (índice) y el vecino de un vértice que usa ese
    color.
    */
    u32 coloreo = 0;
    u32 color = 0;
    u32 ult_color = color;
    u32 j;
    u32 total_vertices = W->total_vertices;
    u32 *colores_vec = (u32*)calloc(total_vertices+1, sizeof(u32));
    for (u32 i = 0; i < total_vertices; ++i)
    {
        u32 vertice = W->orden[i];
        int pos = search_vertex(W, vertice);
        /* Función que registra los colores que utilizan los vecinos de
        un vértice en la tabla colores_vec */
        color_distinto_vecinos(W, vertice, pos, colores_vec);
        /* Empieza por el color más bajo (j=1), y se va fijando en la tabla
        el menor color disponible, cuando lo encuentra lo asigna a color */
        j = 1;
        color = 0;
        while (color == 0 && j <= total_vertices)
        {
            /* Si el colores_vec[j] está en 0 (color no usado por ningun vecino), o es distinto de v
            (usado por un vértice anterior no vecino a v) entonces el color j está disponible
            para usarse y se asigna a `color` lo que provoca salir del loop. */
            if (colores_vec[j] == 0 || colores_vec[j] != vertice)
            {
                color = j;
            }
            // avanza al siguiente color
            j++;

        }
        // Asigna al vértice el menor color encontrado
        W->vertices[pos]->color = color;

        //Si el color asignado es > que el último color usado, entonces el coloreo aumenta
        if (!(color <= ult_color))
        {
            ult_color = color;;
            coloreo++;
        }
    }
    free(colores_vec);
    colores_vec = NULL;
    W->coloreo = coloreo;
    W->coloreado = true;
    return coloreo;
}

void color_distinto_vecinos(WinterIsHere W, u32 v, u32 pos, u32* colores_vec) {
    // Guarda la lista de vecinos en neighbours
    node neighbours = W->vertices[pos]->neighbours;
    // Si no tiene vecinos sale
    if (neighbours == NULL)
    {
        return;
    }else{
        // Recorre la lista registrando los colores que usan los vecinos en la tabla
        while(neighbours != NULL){
            u32 neig_pos = search_vertex(W,node_value(neighbours));
            u32 color_vert = W->vertices[neig_pos]->color;
            /* Si tiene un color asignado, se registra el color
             como índice y se asigna el vértice v (el vértice del cual se buscan los colores vecinos),
             de esta forma al usarse colores de 0 a n, luego será lineal en el peor caso
             buscar el menor color disponible para v. */
            if (color_vert != 0)
            {
                colores_vec[color_vert] = v;
            }
            // Avanza al siguiente vecino
            neighbours = node_next(neighbours);
        }
    }
}

WinterIsHere decolorear_grafo(WinterIsHere g){
    for (u32 i = 0; i < g->total_vertices; ++i)
    {
        g->vertices[i]->color = 0;
    }
    g->coloreado = false;
    return g;
}

//verifica si el vertice cuya etiqueta es i pertenece al array vertices_AB
bool pertenece(int vertices_AB[], int i)
{
    if(vertices_AB[i] != 0)
        return true;

    return false;
}

int Bipartito(WinterIsHere W)
{
    int i = 0;
    int a = 0;
    int b = 0;
    int b2 = 0;
    int a2 = 1;
    int vertice_a;
    int vertice_a2;
    int vertice_b;
    int vertice_b2;
    bool encontrado = false;
    node next_ver;

    //array vertices_A que guarda los vertices (asumiendo que el grafo es BP) de color 1
    int *vertices_A = malloc(W->total_vertices*sizeof(int));
    /*vertices_A2 guarda el valor de verdad de si un vertice esta o no en vertices_A
    (p.e el vertice v1 tiene etiqueta i con 0 <= i <= n-1, si v1 esta en vertices_A en la
    posicion i en vertices_A2 tendremos un 1 de lo contrario un 0), esto es para verificar
    con orden O(1) si un vertice pertenece al conjunto A o B*/
    int *vertices_A2 = malloc(W->total_vertices*sizeof(int));

    //array vertices_B que guarda los vertices (asumiendo que el grafo es BP) de color 2
    int *vertices_B = malloc(W->total_vertices*sizeof(int));
    //igual a vertices_A2 para el conjunto vertices_B
    int *vertices_B2 = malloc(W->total_vertices*sizeof(int));

    // inicialización de los arrays
    for(i = 0; i < (int)W->total_vertices; i++)
    {
        vertices_A[i] = -1;
        vertices_B[i] = -1;
        vertices_A2[i] = 0;
        vertices_B2[i] = 0;
    }
    // empezamos tomando el primer vertice (podría ser cualquiera)
    // y lo agregamos a ambos conjuntos
    vertices_A[a] = (int)W->vertices[search_vertex(W,W->orden[0])]->id_node;
    vertices_A2[search_vertex(W,W->orden[0])] = 1;
    encontrado = true;
    i= 1;

    while(vertices_B[b] != -1 || vertices_A[a] != -1)
    {
        vertice_a = 0;
        vertice_b = 0;
        encontrado = false;

        while(vertices_A[a] != -1 && a < (int)W->total_vertices)
        {
            // vertice_a es igual al vertice en la posicion a de vertices_A
            vertice_a = (int)vertices_A[a];
            // nodo a los vecinos de vertice_a
            next_ver = W->vertices[search_vertex(W,vertice_a)]->neighbours;

            // mientras tenga vecinos
            while(next_ver != NULL)
            {
                //vertice_b es igual a un vecino de vertice_a
                vertice_b = (int)next_ver->data;
                //vertice_b2 es igual a la etiqueta de vertice_b
                vertice_b2 = (int)search_vertex(W,vertice_b);
                /* si el vertice_b (vecino de vertice_a) pertenece
                al conjunto de vertices_A (o sea al conjunto de vertice_a)
                el grafo no es bipartito, si no pertenece lo agrego al conjunto 
                vertices_B (en caso de que no pertenezca)*/
                if(pertenece(vertices_A2,vertice_b2))
                    return 0;
                else if(!pertenece(vertices_B2,vertice_b2))
                {
                    vertices_B[b2] = vertice_b;
                    vertices_B2[vertice_b2] = 1;
                    b2++;
                }
                //puntero al siguiente vecino
                next_ver = next_ver->next;
            }
            /*variable que indica a vertice cuyos vecinos debo
            agregar al otro conjunto (conjunto B en este caso)*/
            a++;
        }

        // igual al while anterior (agrega los vecinos del conjunto B al conjunto A) 
        while(vertices_B[b] != -1 && b < (int)W->total_vertices)
        {
            vertice_b = (int)vertices_B[b];
            next_ver = W->vertices[search_vertex(W,vertice_b)]->neighbours;

            while(next_ver != NULL)
            {
                vertice_a = next_ver->data;
                vertice_a2 = (int)search_vertex(W,vertice_a);

                if(pertenece(vertices_B2,vertice_a2))
                    return 0;
                else if(!pertenece(vertices_A2,vertice_a2))
                {
                    vertices_A[a2] = vertice_a;
                    vertices_A2[vertice_a2] = 1;
                    a2++;
                }
                next_ver = next_ver->next;
            }
            b++;
        }
        /*como asumimos que el grafo es no conexo, debemos buscar algun vertice
        que no este en ninguno de los des conjuntos (A y B) y agregarlo a 
        cualquiera, A en este caso*/
        while(i<(int)W->total_vertices && !encontrado)
        {
            if(!pertenece(vertices_A2,search_vertex(W,W->orden[i])) && 
               !pertenece(vertices_B2,search_vertex(W,W->orden[i]))  )
            {
                vertices_A[a] = (int)W->vertices[search_vertex(W,W->orden[i])]->id_node;
                vertices_A2[search_vertex(W,W->orden[i])] = 1;
                encontrado = 1;
            }
            i++;
        }
    }
    /* si la variable b y a estan ambas en una posicion en la que hay un -1
    quiere decir que no hay mas vecinos para agregar a ninguno de los conjuntos,
    como separo exitosamente los vertices de un grafo en dos conjuntos, entonces
    es bipartito y procede a colorear el grafo*/
    if(vertices_B[b] == -1 && vertices_A[a] == -1){
        for (u32 i = 0; i < W->total_vertices; ++i)
        {
            if (vertices_B[i] == -1)
            {
                break;
            }else{
                W->vertices[search_vertex(W,vertices_B[i])]->color = 1;
            }
        }
        for (u32 i = 0; i < W->total_vertices; ++i)
        {
            if (vertices_A[i] == -1)
            {
                break;
            }else{
                W->vertices[search_vertex(W,vertices_A[i])]->color = 2;
            }
        }
        return 1;
    }

    return 0;
}


//mapea la posicon i a la posicion esa(que puede salir del rango)
u32 map(u32 i, u32 x)
{
    return (i*x + x*x + i*i);
}

void swap(u32 array[], u32 i, u32 j)
{
    u32 tmp = array[i];
    array[i] =  array[j];
    array[j] = tmp;
}

void randomize(u32 array[], u32 length, u32 x)
{
    u32 i = 0;
    // mapea la posicion i a la posicion map(i,x) con el modulo
    // para mantener el rango 0..n-1 y swapea i con su mapeo
    for(i = 0; i < length; i++)
        swap(array,i,map(i,x)%length);
}

void AleatorizarVertices(WinterIsHere W, u32 x)
{
    randomize(W->orden,W->total_vertices,x);
}

// Funciones para extraer información del grafo

u32 NumeroDeVertices(WinterIsHere W){
    u32 total_vertices = W->total_vertices;
    return total_vertices;
}

u32 NumeroDeLados(WinterIsHere W){
    return W->total_edges;
}

u32 NumeroVerticesDeColor(WinterIsHere W, u32 i){
    u32 total_i_colors = 0;
    for (u32 j = 0; j < W->total_vertices; ++j)
    {
        if (W->vertices[j]->color == i)
        {
            total_i_colors++;
        }
    }
    return total_i_colors;
}

u32 NumeroDeColores(WinterIsHere W){
    return W->coloreo;
}

u32 IesimoVerticeEnElOrden(WinterIsHere W, u32 i){
    u32 vertice = search_vertex(W,W->orden[i]);
    return vertice;
}


//Funciones de Ordenación de grafos

void Print_Ordered_Graph(WinterIsHere W){
    u32 vertice;
    for (u32 i = 0; i < W->total_vertices; ++i)
    {
        vertice = IesimoVerticeEnElOrden(W,i);
        printf("Vertice %u está en orden %d y tiene grado %u\n",vertice, i, W->vertices[search_vertex(W,vertice)]->grado);
    }
}

void OrdenNatural(WinterIsHere W){
    quicksort_normal(W->orden,W->total_vertices);
}

void OrdenWelshPowell(WinterIsHere W){
    quicksort_w(W->orden,W->total_vertices,W);
}

void ReordenManteniendoBloqueColores(WinterIsHere W,u32 x)
{
    // dependiendo del parametro ejecuta la funcion correspondiente
    if(W->coloreo > 0)
    {
        if(x == 0)
            ReordenManteniendoBloqueColores_0(W);
        else if(x == 1)
            ReordenManteniendoBloqueColores_1(W);
        else if(x == 2)
            ReordenManteniendoBloqueColores_2(W);
        else if(x == 3)
            ReordenManteniendoBloqueColores_3(W);
        else if(x > 3)
            ReordenManteniendoBloqueColores_x(W,x);
    }
}

void ReordenManteniendoBloqueColores_0(WinterIsHere W)
{
    /* ordena los verties dependiendo de su color, en orden
    no decreciente (de menor a mayor se suele decir)*/
    quicksort_mio(W,W->total_vertices);

    int i = 0;
    int j = 0;

    // busca cuantos vertices hay con color r (X(G), el coloreo)
    for(i = W->total_vertices-1; i != -1; --i)
    {
        if(W->vertices[search_vertex(W,W->orden[i])]->color != W->coloreo)
        {
            j = i+1;
            break;
        }
    }

    // los de color r los pone primeros
    for(i = j; i < (int)W->total_vertices; i++)
        swap(W->orden,i-j,i);

    qs_mio(W,W->total_vertices-j,W->total_vertices-1);
}

void ReordenManteniendoBloqueColores_1(WinterIsHere W)
{
    quicksort_mio_backward(W,W->total_vertices);
}

void ReordenManteniendoBloqueColores_2(WinterIsHere W)
{
    u32 i = 0, j = 0, k = 0, c = 0;
    u32 *colores = malloc(W->coloreo*sizeof(u32));
    u32 *colores_cardinal = malloc(W->coloreo*sizeof(u32));
    /* tenemos dos arreglos, uno guarda simplemente los colores usados (colores)
    y el otro su cardinalidad (colores_cardinal), es decir cuantos vertices hay 
    con ese color*/
    for(i = 0; i < W->coloreo; i++){
        colores[i] = i+1;
        colores_cardinal[i] = 0;
    }
    // calculamos la cardinalidad de cada color
    for(i = 0; i < W->total_vertices; i++)
        colores_cardinal[W->vertices[i]->color-1]++;
    //ordenamos el array de colores basado en sus cardinalidades
    quicksort_bloque(colores,colores_cardinal,W->coloreo);

    i = 0;
    // procedemos a reordenar los vertices basados en sus colores, 
    //tomando en cuenta sus cardinalidades(de los colores)
    while(i < W->coloreo)
    {
        for(j = k; j<W->total_vertices && c != colores_cardinal[i]; j++)
        {
            if(W->vertices[search_vertex(W,W->orden[j])]->color == colores[i])
            {
                swap(W->orden,j,k);
                k++;
                c++;
            }
        }
        i++;
        c = 0;
    }
}
// muy parecido al anterior (casi lo mismo) solo que en orden inverso al anterior
void ReordenManteniendoBloqueColores_3(WinterIsHere W)
{
    u32 i = 0, j = 0, k = 0, c = 0;
    u32 *colores = malloc(W->coloreo*sizeof(u32));
    u32 *colores_cardinal = malloc(W->coloreo*sizeof(u32));

    for(i = 0; i<W->coloreo; i++){
        colores[i] = i+1;
        colores_cardinal[i] = 0;
    }

    for(i = 0; i<W->total_vertices; i++)
        colores_cardinal[W->vertices[i]->color-1]++;

    quicksort_bloque_backward(colores,colores_cardinal,W->coloreo);

    i = 0;
    while(i<W->coloreo)
    {
        for(j = k; j<W->total_vertices && c != colores_cardinal[i]; j++)
        {
            if(W->vertices[search_vertex(W,W->orden[j])]->color == colores[i])
            {
                swap(W->orden,j,k);
                k++;
                c++;
            }
        }
        i++;
        c = 0;
    }
}

// usando la misma idea de los dos anteriores, aleatorizamos los colores
// los reordenamos basados en sus colores
void ReordenManteniendoBloqueColores_x(WinterIsHere W,u32 x)
{
    u32 i = 0, j = 0, k = 0, c = 0;
    u32 *colores = malloc(W->coloreo*sizeof(u32));
    u32 *colores_cardinal = malloc(W->coloreo*sizeof(u32));

    for(i = 0; i<W->coloreo; i++)
    {
        colores[i] = i+1;
        colores_cardinal[i] = 0;
    }

    for(i = 0; i<W->total_vertices; i++)
        colores_cardinal[W->vertices[i]->color-1]++;

    randomize(colores,W->coloreo,x);
    randomize(colores_cardinal,W->coloreo,x);

    i = 0;
    while(i<W->coloreo)
    {
        for(j = k; j<W->total_vertices && c != colores_cardinal[i]; j++)
        {
            if(W->vertices[search_vertex(W,W->orden[j])]->color == colores[i])
            {
                swap(W->orden,j,k);
                k++;
                c++;
            }
        }
        i++;
        c = 0;
    }
}

// Funciones de los vértices
u32 ColorDelVertice(WinterIsHere W, u32 x){
    return W->vertices[x]->color;
}

u32 NombreDelvertice(WinterIsHere W, u32 x){
	return W->vertices[x]->id_node;
}

u32 GradoDelVertice(WinterIsHere W, u32 x){
	return W->vertices[x]->grado;
}

u32 IesimoVecino(WinterIsHere W, u32 x, u32 i){
	u32 vertice = W->orden[x];
	u32 pos = search_vertex(W, vertice);
	return search_vertex(W, find_ith_node(W->vertices[pos]->neighbours, i));
}
