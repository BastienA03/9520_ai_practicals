#include <stdio.h> 
#include <stdbool.h> 
 
#define MAX_DEPTH 100 
 
// Struct to represent a state 
typedef struct { 
    int missionaries_left; 
    int cannibals_left; 
    int boat; // 0 for left, 1 for right 
} State; 
 
// Struct for a node in the BFS search tree 
typedef struct { 
    State state; 
    int parent_index; // Index of the parent node in the 
queue 
} Node; 
 
// Queue implementation for BFS 
typedef struct { 
    Node elements[MAX_DEPTH]; 
    int front; 
    int rear; 
} Queue; 
 
// Function to initialize the queue 
void initialize_queue(Queue *queue) { 
    queue->front = -1; 
    queue->rear = -1; 
} 
 
// Function to check if the queue is empty 
bool is_empty(Queue *queue) { 
    return queue->front == -1 && queue->rear == -1; 
} 
 
// Function to enqueue a node into the queue 
void enqueue(Queue *queue, Node node) { 
    if (is_empty(queue)) { 
        queue->front = 0; 
        queue->rear = 0; 
    } else { 
        queue->rear++; 
    } 
    queue->elements[queue->rear] = node; 
} 
 
// Function to dequeue a node from the queue 
Node dequeue(Queue *queue) { 
    Node node = queue->elements[queue->front]; 
    if (queue->front == queue->rear) { 
        queue->front = -1; 
        queue->rear = -1; 
    } else { 
        queue->front++; 
    } 
    return node; 
} 
 
// Function to check if a state is valid 
bool is_valid(State state) { 
    if ((state.missionaries_left >= 0 && state.missionaries_left 
<= 3) && 
        (state.cannibals_left >= 0 && state.cannibals_left <= 3) 
&& 
        ((state.missionaries_left == 0 || state.missionaries_left 
>= state.cannibals_left) || 
         (state.missionaries_left == 3 || (3 - 
state.missionaries_left) >= (3 - state.cannibals_left)))) 
        return true; 
    return false; 
} 
 
// Function to check if the state is the goal state 
bool is_goal(State state) { 
    return (state.missionaries_left == 0 && 
state.cannibals_left == 0 && state.boat == 1); 
} 
 
// Function to print the path 
void print_path(Node *nodes, int index) { 
    if (index == -1) 
        return; 
    print_path(nodes, nodes[index].parent_index); 
    printf("Move: %d missionaries and %d cannibals from the %s side to the %s side.\n", 
           nodes[index].state.missionaries_left, 
           nodes[index].state.cannibals_left, 
           nodes[index].state.boat == 0 ? "left" : "right", 
           nodes[index].state.boat == 0 ? "right" : "left"); 
} 
 
// Function for breadth-first search 
void bfs(State initial_state) { 
    Queue queue; 
    initialize_queue(&queue); 
 
    Node initial_node = {initial_state, -1}; 
    enqueue(&queue, initial_node); 
 
    while (!is_empty(&queue)) { 
        Node current_node = dequeue(&queue); 
        if (is_goal(current_node.state)) { 
            printf("Solution Found:\n"); 
            print_path(&queue.elements[0], queue.rear); 
            return; 
        } 
 
        // Generate child nodes 
        for (int m = 0; m <= 2; ++m) { 
            for (int c = 0; c <= 2; ++c) { 
                if (m + c > 2 || m + c == 0) 
                    continue; 
                if (current_node.state.boat == 0) { 
                    State next_state = 
{current_node.state.missionaries_left - m, 
                                        current_node.state.cannibals_left - c, 
1}; 
                    if (is_valid(next_state)) { 
                        Node next_node = {next_state, queue.rear}; 
                        enqueue(&queue, next_node); 
                    } 
                } else { 
                    State next_state = 
{current_node.state.missionaries_left + m, 
                                        current_node.state.cannibals_left + c, 
0}; 
                    if (is_valid(next_state)) { 
                        Node next_node = {next_state, queue.rear}; 
                        enqueue(&queue, next_node); 
                    } 
                } 
            } 
        } 
    } 
 
    printf("No solution found.\n"); 
} 
 
int main() { 
    State initial_state = {3, 3, 0}; // initial state 
    bfs(initial_state); 
    return 0; 
}
