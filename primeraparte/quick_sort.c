#include "JonSnow.h"

// Estructura de un grafo
struct WinterSt {
    u32 total_vertices;
    u32 total_edges;
    u32 coloreo;
    vert *vertices;
    u32 total_vert_cargados;
    u32 *orden;
    u32 ult_cargado;
};

// Estructura de un vértice
struct VertexSt {
    u32 id_node;
    node neighbours;
    u32 grado;
    u32 color;
    cols colisiones;
    u32 total_cols;
};

//ordena un array de menor a mayor
void qs_normal(u32 lista[],u32 limite_izq,u32 limite_der)
{
    u32 izq,der,pivote;

    izq = limite_izq;
    der = limite_der;
    pivote = lista[(izq+der)/2];

    do{
        while(lista[izq]<pivote && izq<limite_der)
            izq++;

        while(pivote<lista[der] && der > limite_izq)
        {
            if(der > 0)
                der--;
        }

        if(izq <=der)
        {
            swap(lista,izq,der);
            izq++;
            if(der > 0)
                der--;
        }

    }while(izq<=der);

    if(limite_izq<der)
        qs_normal(lista,limite_izq,der);

    if(limite_der>izq)
        qs_normal(lista,izq,limite_der);
}

void quicksort_normal(u32 lista[],u32 n)
{
    qs_normal(lista,0,n-1);
}
//-----------------------------------------------//

//ordena un array de mayor a menor
void qs_normal_backward(u32 lista[],u32 limite_izq,u32 limite_der)
{
    u32 izq,der,pivote;

    izq = limite_izq;
    der = limite_der;
    pivote = lista[(izq+der)/2];

    do{
        while(lista[izq]>pivote && izq<limite_der)
            izq++;

        while(pivote>lista[der] && der > limite_izq)
         {
            if(der > 0)
                der--;
         }

        if(izq <=der)
        {
            swap(lista,izq,der);
            izq++;
            if(der > 0)
                der--;
        }

    }while(izq<=der);

    if(limite_izq<der)
        qs_normal_backward(lista,limite_izq,der);

    if(limite_der>izq)
        qs_normal_backward(lista,izq,limite_der);
}

void quicksort_normal_backward(u32 lista[],u32 n)
{
    qs_normal_backward(lista,0,n-1);
}
//-----------------------------------------------//



//ordena el array W->orden basado en los colores de W->vertices de menor a mayor
void qs_mio(WinterIsHere W,u32 limite_izq,u32 limite_der)
{
    u32 izq,der,pivote;

    izq = limite_izq;
    der = limite_der;
    pivote = W->vertices[search_vertex(W,W->orden[(izq+der)/2])]->color;

    do{
        while(W->vertices[search_vertex(W,W->orden[izq])]->color<pivote && izq<limite_der)
            izq++;

        while(pivote<W->vertices[search_vertex(W,W->orden[der])]->color && der > limite_izq)
        {
            if(der > 0)
                der--;
        }

        if(izq <=der)
        {
            swap(W->orden,izq,der);
            izq++;
            if(der > 0)
                der--;
        }

    }while(izq<=der);

    if(limite_izq<der)
        qs_mio(W,limite_izq,der);

    if(limite_der>izq)
        qs_mio(W,izq,limite_der);
}

void quicksort_mio(WinterIsHere W,u32 n)
{
    qs_mio(W,0,n-1);
}
//-----------------------------------------------//



//ordena el array W->orden basado en los colores de W->vertices de mayor a menor
void qs_mio_backward(WinterIsHere W,u32 limite_izq,u32 limite_der)
{
    u32 izq,der,pivote;

    izq = limite_izq;
    der = limite_der;
    pivote =  W->vertices[search_vertex(W,W->orden[(izq+der)/2])]->color;

    do{
        while( W->vertices[search_vertex(W,W->orden[izq])]->color > pivote && izq < limite_der)
            izq++;

        while(pivote> W->vertices[search_vertex(W,W->orden[der])]->color && der > limite_izq)
        {
            if(der > 0)
                der--;
        }

        if(izq <= der)
        {
            swap(W->orden,izq,der);
            izq++;
            if(der > 0)
                der--;
        }

    }while(izq<=der);

    if(limite_izq<der)
        qs_mio_backward(W,limite_izq,der);

    if(limite_der>izq)
        qs_mio_backward(W,izq,limite_der);
}

void quicksort_mio_backward(WinterIsHere W, u32 n)
{
    qs_mio_backward(W,0,n-1);
}
//-----------------------------------------------//



//ordena los colores usados basado en sus cardinales de menor a mayor
void qs_bloque(u32 *colores, u32 *colores_cardinal,u32 limite_izq,u32 limite_der)
{
    u32 izq,der,pivote;

    izq = limite_izq;
    der = limite_der;
    pivote = colores_cardinal[(izq+der)/2];

    do{
        while(colores_cardinal[izq]<pivote && izq<limite_der)
            izq++;

        while(pivote<colores_cardinal[der] && der > limite_izq)
        {
            if(der > 0)
                der--;
        }

        if(izq <=der)
        {
            swap(colores,izq,der);
            swap(colores_cardinal,izq,der);
            izq++;
            if(der > 0)
                der--;
        }

    }while(izq<=der);

    if(limite_izq<der)
        qs_bloque(colores,colores_cardinal,limite_izq,der);

    if(limite_der>izq)
        qs_bloque(colores,colores_cardinal,izq,limite_der);
}

void quicksort_bloque(u32 colores[], u32 colores_cardinal[],u32 n)
{
    qs_bloque(colores,colores_cardinal,0,n-1);
}
//-----------------------------------------------//



// ordena los colores usados basado en sus cardinales de mayor a menor
void qs_bloque_backward(u32 *colores, u32 *colores_cardinal,u32 limite_izq,u32 limite_der)
{
    u32 izq,der,pivote;

    izq = limite_izq;
    der = limite_der;
    pivote = colores_cardinal[(izq+der)/2];

    do{
        while(colores_cardinal[izq]>pivote && izq<limite_der)
            izq++;

        while(pivote>colores_cardinal[der] && der > limite_izq)
        {
            if(der > 0)
                der--;
        }

        if(izq <= der)
        {
            swap(colores,izq,der);
            swap(colores_cardinal,izq,der);
            izq++;
            if(der > 0)
                der--;
        }

    }while(izq<=der);

    if(limite_izq<der)
        qs_bloque_backward(colores,colores_cardinal,limite_izq,der);

    if(limite_der>izq)
        qs_bloque_backward(colores,colores_cardinal,izq,limite_der);
}

void quicksort_bloque_backward(u32 colores[], u32 colores_cardinal[],u32 n)
{
    qs_bloque_backward(colores,colores_cardinal,0,n-1);
}
//-----------------------------------------------//

/* Ordena un grafo por grado de colores (Para Welsh Powell)*/
void quicksort_w(u32 *A, u32 len, WinterIsHere W)
{
  if (len < 2) return;

  u32 pivot = W->vertices[search_vertex(W,A[len / 2])]->grado;

  int i, j;
  for (i = 0, j = len - 1; ; i++, j--)
  {
    while (W->vertices[search_vertex(W,A[i])]->grado > pivot) i++;
    while (W->vertices[search_vertex(W,A[j])]->grado < pivot) j--;

    if (i >= j) break;

    int temp = W->vertices[search_vertex(W,A[i])]->grado;
    W->vertices[search_vertex(W,A[i])]->grado = W->vertices[search_vertex(W,A[j])]->grado;
    W->vertices[search_vertex(W,A[j])]->grado = temp;
  }

  quicksort_w(A, i, W);
  quicksort_w(A + i, len - i, W);
}