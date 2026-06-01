#include "OrderManagement.hpp"
 
//  STRUCT Order — Constructor
Order::Order(int id, string name, string item)
    : orderID(id), customerName(name), itemRequested(item),
      status("Pending"), next(nullptr) {}
 
//  CLASS OrderQueue — Constructor & Destructor
// Initialise an empty queue
OrderQueue::OrderQueue()
    : front(nullptr), rear(nullptr),
      totalEnqueued(0), currentSize(0) {}
 
// Free all remaining nodes to prevent memory leaks
OrderQueue::~OrderQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}
 
//  Returns true if there are no orders in the queue
bool OrderQueue::isEmpty() const {
    return front == nullptr;
}
 
//  Returns the number of orders currently in the queue
int OrderQueue::size() const {
    return currentSize;
}
 

//  Returns the front order without removing it
Order* OrderQueue::peek() const {
    if (isEmpty()) {
        cout << "\n  [INFO]  Queue is empty - nothing to peek at.\n";
        return nullptr;
    }
    return front;
}
 
//  Adds a new order to the REAR of the queue
void OrderQueue::enqueue(string customerName, string item) {
    totalEnqueued++;
    Order* newOrder = new Order(totalEnqueued, customerName, item);
 
    if (isEmpty()) {
        front = rear = newOrder;   // First node — both pointers aim here
    } else {
        rear->next = newOrder;     // Link new node to the current tail
        rear       = newOrder;     // Advance rear to the new node
    }
    currentSize++;
 
    cout << "\n  [ORDER RECEIVED]  Order #" << newOrder->orderID
         << " | Customer: " << customerName
         << " | Item: "     << item << "\n";
}
 

//  Removes and returns the FRONT order (oldest)
Order* OrderQueue::dequeue() {
    if (isEmpty()) {
        cout << "\n  [ERROR]  Queue is empty - no orders to process.\n";
        return nullptr;
    }
 
    Order* processed = front;     // Save the front node to return
    front = front->next;          // Advance front to the next node
 
    if (front == nullptr) {
        rear = nullptr;           // Queue is now empty, reset rear too
    }
 
    processed->next = nullptr;    // Detach the node from the queue
    currentSize--;
    return processed;
}
 
//  Adds an already-created Order node into this queue
//  Used to transfer orders to the completed queue
void OrderQueue::enqueueExisting(Order* order) {
    order->next = nullptr;        // Cleanly detach from previous links
    if (isEmpty()) {
        front = rear = order;
    } else {
        rear->next = order;
        rear       = order;
    }
    currentSize++;
}
 
//  Dequeues the front order, marks it completed,
//  and moves it to the completed queue
void OrderQueue::processNextOrder(OrderQueue& completedQueue) {
    if (isEmpty()) {
        cout << "\n  [INFO]  No pending orders to process.\n";
        return;
    }
 
    Order* order  = dequeue();
    order->status = "Completed";
 
    cout << "\n  [PROCESSING]  Order #" << order->orderID
         << " assigned to robot."
         << "\n                Customer : " << order->customerName
         << "\n                Item     : " << order->itemRequested
         << "\n                Status   : " << order->status << "\n";
 
    completedQueue.enqueueExisting(order);
}
 
//  Prints all orders currently waiting in the queue
void OrderQueue::displayPending() const {
    cout << "\n  ***** PENDING ORDERS IN QUEUE *****\n";
 
    if (isEmpty()) {
        cout << "  (No pending orders)\n";
        return;
    }
 
    Order* current  = front;
    int    position = 1;
 
    while (current != nullptr) {
        cout << "  [" << position << "] Order #" << current->orderID
             << "  |  Customer : " << current->customerName
             << "  |  Item : "     << current->itemRequested
             << "  |  Status : "   << current->status << "\n";
        current = current->next;
        position++;
    }
    cout << "  Total pending: " << currentSize << "\n";
}
 
//  Prints all orders that have been processed
void OrderQueue::displayCompleted() const {
    cout << "\n  ***** COMPLETED ORDER HISTORY *****\n";
 
    if (isEmpty()) {
        cout << "  (No completed orders yet)\n";
        return;
    }
 
    Order* current  = front;
    int    position = 1;
 
    while (current != nullptr) {
        cout << "  [" << position << "] Order #" << current->orderID
             << "  |  Customer : " << current->customerName
             << "  |  Item : "     << current->itemRequested
             << "  |  Status : "   << current->status << "\n";
        current = current->next;
        position++;
    }
    cout << "  Total completed: " << currentSize << "\n";
}

void runOrderManagement() {
    OrderQueue pendingQueue;
    OrderQueue completedQueue;
 
    int    choice;
    string customerName, itemName;
 
    cout << "\n  ==========================================\n";
    cout <<   "   Task 1 : Order Management Module\n";
    cout <<   "  ==========================================\n";
 
    do {
        cout << "\n  ********************************************\n";
        cout <<   "  *     WAREHOUSE ORDER MANAGEMENT SYSTEM    *\n";
        cout <<   "  ********************************************\n";
        cout <<   "  *  1. Add New Order                        *\n";
        cout <<   "  *  2. Process Next Order (Assign to Robot) *\n";
        cout <<   "  *  3. View Next Order (Peek)               *\n";
        cout <<   "  *  4. View All Pending Orders              *\n";
        cout <<   "  *  5. View Completed Order History         *\n";
        cout <<   "  *  6. Exit                                 *\n";
        cout <<   "  ********************************************\n";
        cout <<   "  Enter your choice: ";
 
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\n  [ERROR]  Please enter a number between 1-6.\n";
            continue;
        }
        cin.ignore();
 
        switch (choice) {
            case 1:
                cout << "  Enter customer name : ";
                getline(cin, customerName);
                cout << "  Enter item requested: ";
                getline(cin, itemName);
                if (customerName.empty() || itemName.empty()) {
                    cout << "\n  [ERROR]  Name and item cannot be empty.\n";
                } else {
                    pendingQueue.enqueue(customerName, itemName);
                }
                break;
 
            case 2:
                pendingQueue.processNextOrder(completedQueue);
                break;
 
            case 3: {
                Order* nextOrder = pendingQueue.peek();
                if (nextOrder != nullptr) {
                    cout << "\n  [NEXT ORDER]  Order #" << nextOrder->orderID
                         << "  |  Customer : " << nextOrder->customerName
                         << "  |  Item : "     << nextOrder->itemRequested << "\n";
                }
                break;
            }
 
            case 4:
                pendingQueue.displayPending();
                break;
 
            case 5:
                completedQueue.displayCompleted();
                break;
 
            case 6:
                cout << "\n  [SYSTEM]  Order Management Module closed.\n";
                break;
 
            default:
                cout << "\n  [ERROR]  Invalid choice. Please enter 1-6.\n";
                break;
        }
 
    } while (choice != 6);
}
 
int main () {
    runOrderManagement();
}






