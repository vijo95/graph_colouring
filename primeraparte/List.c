#include "JonSnow.h"

struct neig_list{
    u32 data;
    u32 order;
    node next;
};

node insert(node T,u32 x)
{
    if(T==NULL)
    {
        T = (node)malloc(sizeof(struct neig_list));
        T->data = x;
        T->order = 1;
        T->next = NULL;
    }
    else{
        node aux = (node)malloc(sizeof(struct neig_list));
        aux->data = x;
        aux->next = T;
        aux->order = T->order+1;
        T = aux;
    }
    return(T);
}

node destroy_list(node T){
    node aux;
    while(T != NULL){
        aux = T;
        T = T->next;
        free(aux);
    }
    return T;
}

u32 node_value(node T){
    return T->data;
}

u32 node_order(node T){
    return T->order;
}

node node_next(node T){
    return T->next;
}

int find_ith_node(node T, u32 order){
    node aux = T;
    bool found = false;
    u32 value = -1;
    if (aux->order < order)
    {
        return value;
    }
    while(aux != NULL && found == false){
        if (aux->order == order)
        {
            value = aux->data;
            found = true;
        }else{
            aux = aux->next;
        }
    }
    return value;
}