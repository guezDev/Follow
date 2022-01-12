#include <stdlib.h>
#include "list.h"

s_node * list_create(void) {
    return NULL;    
}

void * list_get_data(s_node * node) {
    return node->data;
}

void list_set_data(s_node * node, void * data) {
    if(data==NULL) return;
    node->data=data;
}

s_node * list_insert(s_node * head, void * data) {
    if(data==NULL) return head;
    s_node* p_new_node=(s_node*) malloc(sizeof(s_node));
    p_new_node->data=data;
    p_new_node->next=head;

    return p_new_node;
}

s_node * list_append(s_node * head, void * data) {
    if(data==NULL) return head;
    s_node* ptr=head;
    s_node* _ptr;
    s_node* p_new_node=(s_node*) malloc(sizeof(s_node));
    p_new_node->data=data;
    p_new_node->next=NULL;

    if(ptr==NULL) {
        return p_new_node;
    }

    while(ptr!=NULL) {
        _ptr=ptr;
        ptr=ptr->next;
    }

    _ptr->next=p_new_node;

    return head;
}

s_node * list_orderedAppend(s_node ** head, int (*compare)(s_node *, void *), void *param) {
    if(param==NULL) return *head;

    s_node* p_new_node=(s_node*) malloc(sizeof(s_node));
    p_new_node->data=param;
    p_new_node->next=NULL;

    if(*head==NULL) {
        return p_new_node;
    }

    s_node* _ptr=NULL;

    if(compare(*head, param)>0) {
        p_new_node->next=*head;
        return p_new_node;
    }

    s_node* ptr=*head;

    while(ptr!=NULL && compare(ptr, param)<=0) {
        if(compare(ptr, param)==0) {
            return *head;
        }

        _ptr=ptr;
        ptr=ptr->next;

    }

    _ptr->next=p_new_node;
    p_new_node->next=ptr;

    return *head;
}

s_node * list_remove(s_node * head, void * data) {
    if(data==NULL || head==NULL) return head;

    s_node* _ptr=NULL;
    s_node* ptr=head;

    while(ptr!=NULL && list_get_data(ptr)!=data) {
        _ptr=ptr;
        ptr=ptr->next;
    }

    if(_ptr==NULL) {
        s_node* n_ptr=ptr->next;
        free(ptr);
        return n_ptr;
    }

    if(ptr==NULL) {
        _ptr->next=ptr;
    } else {
        s_node* n_ptr=ptr->next;
        free(ptr);
        _ptr->next=n_ptr;
    }


    return head;
}

s_node * list_headRemove(s_node * head) {
    if(head==NULL) return head;
    s_node* ptr=head;
    head=head->next;
    free(ptr);
    return head;
}

void list_destroy(s_node * head) {
    s_node* ptr_=NULL;
    s_node* ptr=head;

    while(ptr!=NULL) {
        ptr_=ptr->next;
        free(ptr);
        ptr=ptr_;
    }
}