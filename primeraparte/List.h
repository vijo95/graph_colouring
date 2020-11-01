typedef struct neig_list *node; //Usado para el AVL de los vecinos

//Funciones para operar sobre listas
node destroy_list(node T);
node insert(node T,u32 x);
u32 node_value(node T);
int find_ith_node(node T, u32 order);
node node_next(node T);
u32 node_order(node T);