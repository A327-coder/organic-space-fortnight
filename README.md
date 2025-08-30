#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct node {
    int data;
    struct node* next;
} node, * linklist;

void init(linklist& l) {
    l = (node*)malloc(sizeof(node));
    l->data = -1; 
    l->next = NULL;
}

void tail_insert(linklist& l, int data) {
    node* p = (node*)malloc(sizeof(node));
    p->data = data;
    p->next = NULL;

    node* tail = l;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    tail->next = p;  
}

void print_list(linklist& l) {
    node* p = l->next;
    cout << "链表内容: ";
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

void destroy(linklist& l) {
    node* p;
    while (l != NULL) {
        p = l;
        l = l->next;
        free(p);
    }
}

int main() {
    linklist list;
    init(list);

    for (int i = 1; i <= 5; i++) {
        tail_insert(list, i);
    }

    print_list(list);  

    tail_insert(list, 10);
    tail_insert(list, 20);
    print_list(list); 

    destroy(list);
    return 0;
}
