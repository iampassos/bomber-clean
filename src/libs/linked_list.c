#include "linked_list.h"

LinkedList* list_creater(){
    LinkedList *list =malloc(sizeof(LinkedList));
    if(list==NULL) return NULL;
    list->head=NULL;
    return list;
}