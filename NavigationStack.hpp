#ifndef NAVIGATION_STACK_HPP
#define NAVIGATION_STACK_HPP

#include <iostream>
#include <string>
using namespace std;

// Node used for the stack.
// Each node stores one movement step taken by the robot.
struct MovementNode {
    string movement;
    MovementNode* next;
};

// Node used for the navigation log.
// This keeps a full history of actions performed by the robot.
struct LogNode {
    string logMessage;
    LogNode* next;
};

class NavigationStack {
private:
    MovementNode* top;
    LogNode* logHead;
    LogNode* logTail;

    void displayForwardRecursive(MovementNode* current, bool& firstPrinted);
    void addLog(string message);
    string getReverseMovement(string movement);

public:
    NavigationStack();

    bool isEmpty();

    void pushMovement(string movement);
    string popMovement();

    void recordMovement();
    void displayForwardPath();
    void returnToStart();
    void handleObstacle();
    void displayNavigationLog();
    void clearPath();

    ~NavigationStack();
};

#endif