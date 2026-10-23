#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int customerNumber;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmpty(Queue q) {
    if (q.front == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void enqueue(Queue* q, int number) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->customerNumber = number;
    newNode->next = NULL;

    if (isEmpty(*q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf("Customer %d arrived and got a token.\n", number);
}

int dequeue(Queue* q) {
    if (isEmpty(*q)) {
        return -1;
    } else {
        Node* temp = q->front;
        int customerNumber = temp->customerNumber;
        q->front = q->front->next;

        if (q->front == NULL) {
            q->rear = NULL;
        }

        free(temp);
        return customerNumber;
    }
}

int peek(Queue q) {
    if (isEmpty(q)) {
        return -1;
    }
    return q.front->customerNumber;
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 101);
    enqueue(&q, 102);

    int served = dequeue(&q);
    if (served != -1) {
        printf("Customer %d is being served.\n", served);
    }

    enqueue(&q, 103);

    served = dequeue(&q);
    if (served != -1) {
        printf("Customer %d is being served.\n", served);
    }

    served = dequeue(&q);
    if (served != -1) {
        printf("Customer %d is being served.\n", served);
    }

    if (isEmpty(q)) {
        printf("The queue is empty.\n");
    }

    return 0;
}
