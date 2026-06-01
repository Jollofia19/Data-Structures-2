
#ifndef ORDERMANAGEMENT_HPP
#define ORDERMANAGEMENT_HPP
#include <iostream>
#include <string>
using namespace std;
 

//  Represents a single customer order (one node in the queue)
struct Order {
    int    orderID;
    string customerName;
    string itemRequested;
    string status;
    Order* next;
 
    Order(int id, string name, string item);
};
 

//  Self-implemented linked-list queue (FIFO)
class OrderQueue {
private:
    Order* front;        // Points to the first (oldest) order
    Order* rear;         // Points to the last (newest) order
    int    totalEnqueued; // Tracks total orders ever added (used for ID)
    int    currentSize;  // Number of orders currently in the queue
 
public:
    OrderQueue();
    ~OrderQueue();
 
    bool   isEmpty()  const;
    int    size()     const;
    Order* peek()     const;
 
    void   enqueue(string customerName, string item);
    Order* dequeue();
    void   enqueueExisting(Order* order);
    void   processNextOrder(OrderQueue& completedQueue);
 
    void   displayPending()   const;
    void   displayCompleted() const;
};
void runOrderManagement();
#endif