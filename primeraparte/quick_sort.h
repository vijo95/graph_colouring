//ordena un array de menor a mayor
void qs_normal(u32 lista[],u32 limite_izq,u32 limite_der);
void quicksort_normal(u32 lista[],u32 n);

//ordena un array de mayor a menor
void qs_normal_backward(u32 lista[],u32 limite_izq,u32 limite_der);
void quicksort_normal_backward(u32 lista[],u32 n);

//ordena el array W->orden basado en los colores de W->vertices de menor a mayor
void qs_mio(WinterIsHere W,u32 limite_izq,u32 limite_der);
void quicksort_mio(WinterIsHere W,u32 n);

// ordena grafo por orden de colores
void quicksort_w(u32 *A, u32 len, WinterIsHere W);

//ordena el array W->orden basado en los colores de W->vertices de mayor a menor
void qs_mio_backward(WinterIsHere W,u32 limite_izq,u32 limite_der);
void quicksort_mio_backward(WinterIsHere W, u32 n);

//ordena los colores usados basado en sus cardinales de menor a mayor
void qs_bloque(u32 colores[], u32 colores_cardinal[],u32 limite_izq,u32 limite_der);
void quicksort_bloque(u32 colores[], u32 colores_cardinal[],u32 n);

// ordena los colores usados basado en sus cardinales de mayor a menor
void qs_bloque_backward(u32 colores[], u32 colores_cardinal[],u32 limite_izq,u32 limite_der);
void quicksort_bloque_backward(u32 colores[], u32 colores_cardinal[],u32 n);

