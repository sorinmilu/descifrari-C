// list_functions.h

#ifndef LIST_FUNCTIONS_H
#define LIST_FUNCTIONS_H

struct Node {
    int data;
    struct Node* next;
};

struct LinkedList {
    struct Node* head;
};

struct Node* createNode(int data);
void addNode(struct LinkedList* list, int data);
void deleteNode(struct LinkedList* list, int data);
struct Node* findNode(struct LinkedList* list, int data);
int countNodes(struct LinkedList* list);
void printList(struct LinkedList* list);
void freeList(struct LinkedList* list);

// New functions
void addNodeAtBeginning(struct LinkedList* list, int data);
void addNodeAfterIndex(struct LinkedList* list, int index, int data);
void addMultipleNodes(struct LinkedList* list, int count, int data);
void deleteNodeByIndex(struct LinkedList* list, int index);
void deleteAllNodesAfterIndex(struct LinkedList* list, int index);

void createNewList(struct LinkedList* list, int numNodes);
void reverseList(struct LinkedList* list);
void printStatistics(struct LinkedList* list);
int isListEmpty(struct LinkedList* list); 
void sortList(struct LinkedList* list);
void removeDuplicates(struct LinkedList* list);

#endif // LIST_FUNCTIONS_H
