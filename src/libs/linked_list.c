#include "linked_list.h"

LinkedList* list_creater(){
    LinkedList *list =malloc(sizeof(LinkedList));
    if(list==NULL) return NULL;
    list->head=NULL;
    return list;
}

void list_insert_end(LinkedList *list,void *data){
    if(list == NULL) return;
    
    Node *new=malloc(sizeof(Node));
    if (new == NULL) return;
    new->data=data;
    new->next=NULL;

    if(list->head==NULL) list->head=new;
    else{
        Node *aux=list->head;
        while(aux->next!=NULL) aux=aux->next;
        aux->next=new;
    }
}

int list_lenght(LinkedList *list){
    if(list==NULL || list->head==NULL) return 0;
    else{
        int cont=0;
        Node *aux=list->head;
        while(aux!=NULL){
            aux=aux->next;
            cont++;
        }
        return cont;
    }
}