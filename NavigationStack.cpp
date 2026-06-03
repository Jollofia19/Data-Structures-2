#include "NavigationStack.hpp"

NavigationStack::NavigationStack() {
    top = nullptr;
    logHead = nullptr;
    logTail = nullptr;

    addLog("Navigation module started.");
}

bool NavigationStack::isEmpty() {
    return top == nullptr;
}

void NavigationStack::addLog(string message) {
    LogNode* newLog = new LogNode;
    newLog->logMessage = message;
    newLog->next = nullptr;

    if (logHead == nullptr) {
        logHead = newLog;
        logTail = newLog;
    }
    else {
        logTail->next = newLog;
        logTail = newLog;
    }
}

void NavigationStack::pushMovement(string movement) {
    MovementNode* newNode = new MovementNode;

    newNode->movement = movement;
    newNode->next = top;
    top = newNode;

    cout << "Movement recorded: " << movement << endl;
    addLog("Movement recorded: " + movement);
}

string NavigationStack::popMovement() {
    if (isEmpty()) {
        return "";
    }

    MovementNode* temp = top;
    string movement = temp->movement;

    top = top->next;
    delete temp;

    return movement;
}

void NavigationStack::recordMovement() {
    string movement;

    cout << "\nEnter movement direction" << endl;
    cout << "Options: Forward, Backward, Left, Right" << endl;
    cout << "Movement: ";
    cin >> movement;

    if (movement == "Forward" || movement == "Backward" ||
        movement == "Left" || movement == "Right") {
        pushMovement(movement);
    }
    else {
        cout << "Invalid movement. Please enter Forward, Backward, Left, or Right." << endl;
        addLog("Invalid movement entered: " + movement);
    }
}

// Recursive function to display path from oldest movement to newest movement.
// This shows the actual forward path in the correct order.
void NavigationStack::displayForwardRecursive(MovementNode* current) {
    if (current == nullptr) {
        return;
    }

    displayForwardRecursive(current->next);

    cout << current->movement;

    if (current != top) {
        cout << " -> ";
    }
}

void NavigationStack::displayForwardPath() {
    if (isEmpty()) {
        cout << "\nNo movement path recorded yet." << endl;
        addLog("Forward path display requested, but path was empty.");
        return;
    }

    cout << "\nForward Movement Path:" << endl;
    displayForwardRecursive(top);
    cout << endl;

    addLog("Forward movement path displayed.");
}

string NavigationStack::getReverseMovement(string movement) {
    if (movement == "Forward") {
        return "Backward";
    }
    else if (movement == "Backward") {
        return "Forward";
    }
    else if (movement == "Left") {
        return "Right";
    }
    else if (movement == "Right") {
        return "Left";
    }
    else {
        return "Unknown";
    }
}

void NavigationStack::returnToStart() {
    if (isEmpty()) {
        cout << "\nNo path available. Robot cannot return." << endl;
        addLog("Return requested, but no path was available.");
        return;
    }

    cout << "\nRobot has completed the task." << endl;
    cout << "Returning to starting point using reverse path..." << endl;
    cout << "\nReverse Path for Returning:" << endl;

    addLog("Robot completed task and started return journey.");

    while (!isEmpty()) {
        string lastMovement = popMovement();
        string reverseMovement = getReverseMovement(lastMovement);

        cout << reverseMovement;

        addLog("Returned by reversing " + lastMovement + " into " + reverseMovement);

        if (!isEmpty()) {
            cout << " -> ";
        }
    }

    cout << "\n\nRobot returned safely to the starting point." << endl;
    addLog("Robot returned safely to the starting point.");
}

void NavigationStack::handleObstacle() {
    if (isEmpty()) {
        cout << "\nNo movement to remove. Path is empty." << endl;
        addLog("Obstacle handling requested, but no movement existed.");
        return;
    }

    string wrongMove = popMovement();

    cout << "\nObstacle detected!" << endl;
    cout << "Last movement removed from path: " << wrongMove << endl;
    cout << "Robot backtracked and can choose another route." << endl;

    addLog("Obstacle detected. Removed wrong movement: " + wrongMove);
}

void NavigationStack::displayNavigationLog() {
    if (logHead == nullptr) {
        cout << "\nNo navigation log available." << endl;
        return;
    }

    cout << "\nComplete Navigation Log:" << endl;
    cout << "------------------------" << endl;

    LogNode* current = logHead;
    int count = 1;

    while (current != nullptr) {
        cout << count << ". " << current->logMessage << endl;
        current = current->next;
        count++;
    }
}

void NavigationStack::clearPath() {
    while (!isEmpty()) {
        popMovement();
    }

    cout << "\nNavigation path cleared." << endl;
    addLog("Navigation path cleared.");
}

NavigationStack::~NavigationStack() {
    while (!isEmpty()) {
        popMovement();
    }

    while (logHead != nullptr) {
        LogNode* temp = logHead;
        logHead = logHead->next;
        delete temp;
    }
}