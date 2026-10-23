#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

void initStack(Stack *s) {
    s->top = NULL;
}

int isEmpty(Stack *s) {
    if (s->top == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void push(Stack *s, char data) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
}

char pop(Stack *s) {
    if (isEmpty(s)) {
        return '\0'; 
    }
    Node *temp = s->top;
    char data = temp->data;
    s->top = s->top->next;
    free(temp);
    return data;
}

char peek(Stack *s) {
    if (isEmpty(s)) {
        return '\0'; 
    }
    return s->top->data;
}

void displayStack(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return;
    }
    Node *current = s->top;
    printf("Stack (Top to Bottom): ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}


int evalexp(char exp[]) {
    Stack s;
    initStack(&s);
    int i;

    for (i = 0; exp[i] != '\0'; i++) {
      
        if (exp[i] == ' ') continue;

        // If it's a digit, push its numeric value
        if (exp[i] >= '0' && exp[i] <= '9') {
            push(&s, exp[i] - '0');
        } 
      
        else {
            int fo = pop(&s); 
            int so = pop(&s); 
            int result = 0;

            switch (exp[i]) {
                case '+':
                    result = so + fo;
                    break;
                case '-':
                    result = so - fo;
                    break;
                case '*':
                    result = so * fo;
                    break;
                case '/':
                    if (fo == 0) {
                        printf("division by zero is not allowed\n");
                        return 0;
                    }
                    result = so / fo;
                    break;
                default:
                    printf("Invalid operator '%c'\n", exp[i]);
                    break;
            }
            push(&s, result);
        }
    }
    return pop(&s);
}


int main() {
    Stack s;
    initStack(&s);
    int choice;
    char val;
    char exp[100];

    do {
        printf("\n============================\n");
        printf("      STACK & POSTFIX       \n");
        printf("============================\n");
        printf("1. Push Element\n");
        printf("2. Pop Element\n");
        printf("3. Display Stack\n");
        printf("4. Evaluate Postfix Expression\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Exit.\n");
            break;
        }

        switch (choice) {
            case 1:
               
                printf("digit to push: ");
                scanf(" %c", &val);
                push(&s, val);
                printf("Pushed successfully\n");
                break;

            case 2:
                if (isEmpty(&s)) {
                    printf("Stack is empty.\n");
                } else {
                    val = pop(&s);
                    printf("Popped element: %d (Char: %c)\n", val, val);
                }
                break;

            case 3:
                displayStack(&s);
                break;

            case 4:
                printf("Enter a postfix expression (23*5+): ");
                scanf("%99s", exp);
                {
                    int res = evalexp(exp);
                    printf("Result of evaluation: %d\n", res);
                }
                break;

            case 5:
                printf("Exit\n");
                break;

            default:
                printf("Please choose between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}
