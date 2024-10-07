#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For sleep function

/*
UserId=Moinul
Password=Moinul909
*/

// Define login credentials
#define USER_ID "Moinul"
#define PASSWORD "Moinul909"

// Node structure for the queue
typedef struct Node {
    int carId;
    struct Node* next;
} Node;

// Queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to initialize the queue
void initQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Function to enqueue a car (add to the queue)
void enqueue(Queue* queue, int carId) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->carId = carId;
    newNode->next = NULL;

    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to dequeue a car (remove from the queue)
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        return -1;  // Queue is empty
    }
    Node* temp = queue->front;
    int carId = temp->carId;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;  // Queue is now empty
    }

    free(temp);
    return carId;
}

// Function to display the queue
void displayQueue(Queue* queue) {
    Node* current = queue->front;
    printf("Cars in queue: ");
    while (current != NULL) {
        printf("%d ", current->carId);
        current = current->next;
    }
    printf("\n");
}

// Function to verify login credentials
int login() {
    char inputUserId[50];
    char inputPassword[50];

    printf("Enter User ID: ");
    scanf("%s", inputUserId);

    printf("Enter Password: ");
    scanf("%s", inputPassword);

    // Check if the entered credentials match the predefined credentials
    if (strcmp(inputUserId, USER_ID) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        printf("Login successful!\n\n");
        return 1;  // Return 1 for successful login
    } else {
        printf("Invalid User ID or Password.\n");
        return 0;  // Return 0 for failed login
    }
}

// Function to simulate traffic control
void simulateTrafficControl(Queue* queue) {
    int signalDuration = 5;  // Duration of green light in seconds
    int carsProcessed = 0;

    while (!isEmpty(queue)) {
        printf("Green light! Car %d is passing...\n", dequeue(queue));
        carsProcessed++;
        displayQueue(queue);
        sleep(signalDuration);  // Simulate time taken for a car to pass
    }

    printf("All cars have passed. %d cars processed.\n", carsProcessed);
}

// Main function to demonstrate the traffic simulation
int main() {
    // Login mechanism
    if (login()) {
        Queue queue;
        initQueue(&queue);

        int choice, carId;

        while (1) {
            printf("1. Add car to queue\n");
            printf("2. Simulate traffic control\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter car ID to add to queue: ");
                    scanf("%d", &carId);
                    enqueue(&queue, carId);
                    displayQueue(&queue);
                    break;
                case 2:
                    if (isEmpty(&queue)) {
                        printf("No cars in queue to process.\n");
                    } else {
                        simulateTrafficControl(&queue);
                    }
                    break;
                case 3:
                    printf("Exiting program.\n");
                    return 0;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    } else {
        printf("Access denied. Exiting program.\n");
    }

    return 0;
}

