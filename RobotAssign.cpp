#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Robot
{
private:
    int robotID;
    string status; // Available, Busy, Maintenance
    int taskCount;
    string currentTask;

public:
    // constructors
    Robot (){ //initializes all robot values to default
        robotID = 0;
        status = "Available";
        taskCount = 0;
        currentTask = "None";
    }

    Robot(int id){ //same but with user input for robotID
        robotID = id;
        status = "Available";
        taskCount = 0;
        currentTask = "None";
    }

    // getters
    int getRobotID(){
        return robotID;
    }
    string getStatus(){
        return status;
    }

    int getTaskCount() const{
        return taskCount;
    }

    string getCurrentTask(){
        return currentTask;
    }

    // setters
    void setStatus(string newStatus)
    {
        status = newStatus;
    }

    void incrementTaskCount()
    {
        taskCount++;
    }

    void setCurrentTask(string task){
        currentTask = task;
    }

    void display()
    {
        cout << "Robot ID: " << robotID
             << " | Status: " << status
             << " | Current Task: " << currentTask
             << " | Tasks: " << taskCount << endl;
    }
};

class CircularQueue
{
private:
    static const int MAX = 20; //max num of robots
    Robot robots[MAX]; //array for robots
    int front; //first
    int rear; //last
    int count;

public:

    CircularQueue()
    {   //initializes the queue to be empty
        front = 0; 
        rear = -1;
        count = 0;
    }

    bool isEmpty(){
        return count ==0;
    }
    bool isFull(){
        return count == MAX;
    }

    void enqueue(Robot r){
        if (isFull()) {
            cout << "Queue is full. Cannot add robot." << endl;
            return;
        }
        rear = (rear + 1) % MAX; //move rear forward (index of new rear = (current rear + 1) mod max size)
        robots[rear] = r; //add robot to new rear index
        count++;
    }
    Robot dequeue(){
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue robot." << endl;
            return Robot(); // Return a default robot
        }
        Robot temp = robots[front]; // Store the robot to return
        front = (front + 1) % MAX; //move front forward
        count--; //decrease count
        return temp;
    }

    void display(){
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Robots in Queue: " << endl;
        for (int i = 0; i < count; i++) {
            int index = (front + i) % MAX; // Calculate the actual index in the circular queue
            robots[index].display(); //call rebot display function
        }
    }

    void assignTask(string orderID)
{
    if (isEmpty())
    {
        cout << "No robots available." << endl;
        return;
    }

    int n = count;   // FIX: freeze size
    bool assigned = false;

    while (n--) // Loops through the queue as many times as there are robots
    {
        Robot current = dequeue(); //temporarily remove the front robot to check its status

        if (current.getStatus() == "Available")
        {
            current.setStatus("Busy");
            current.incrementTaskCount();
            current.setCurrentTask(orderID);

            cout << "Order " << orderID
                 << " assigned to Robot "
                 << current.getRobotID() << endl;

            enqueue(current);
            assigned = true;
            break;
        }
        else
        {
            enqueue(current); //put the robot back at the rear of the queue if it's not available
        }
    }

    if (!assigned) // If we went through all robots and didn't find an available one
    {
        cout << "No available robots for " << orderID << endl;
    }
}
    
    void updateStatus(int robotID, string newStatus){
        for (int i = 0; i < count; i++) {
            int index = (front + i) % MAX;
            if (robots[index].getRobotID() == robotID) { // Found the robot
                robots[index].setStatus(newStatus); // Update the status
                break;
            }
        }
    }

    void completeTask(int robotID)
{
    bool found = false; 

    for (int i = 0; i < count; i++)
    {
        int index = (front + i) % MAX;

        if (robots[index].getRobotID() == robotID)
        {
            robots[index].setStatus("Available");
            robots[index].setCurrentTask("None");

            cout << "Robot " << robotID
                 << " has completed its task and is now Available." << endl;

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Robot not found." << endl;
    }
}

void loadRobotsFromCSV(string robots)
{
    ifstream file(robots);

    if (!file)
    {
        cout << "Cannot open robot file.\n";
        return;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line))
    {
        int comma = line.find(',');

        int id = stoi(line.substr(0, comma));
        string status = line.substr(comma + 1);

        Robot r(id);
        r.setStatus(status);

        enqueue(r);
    }

    file.close();

    cout << "Robots loaded successfully.\n";
}


};






int main()
{
    CircularQueue q;

    // Initial robots
    q.loadRobotsFromCSV("robots.csv");
    

    int choice;
    string orderID;
    int robotID;
    string status;

    do
    {
        cout << "\n===== ROBOT SYSTEM MENU =====\n";
        cout << "1. Display Robots\n";
        cout << "2. Assign Task\n";
        cout << "3. Complete Task\n";
        cout << "4. Update Robot Status\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            q.display();
            break;

        case 2:
            cout << "Enter Order ID to assign: ";
            cin >> orderID;
            q.assignTask(orderID);
            break;

        case 3:
            cout << "Enter Robot ID to complete task: ";
            cin >> robotID;
            q.completeTask(robotID);
            break;

        case 4:
            cout << "Enter Robot ID: ";
            cin >> robotID;
            cout << "Enter Status (Available/Busy/Maintenance): ";
            cin >> status;
            q.updateStatus(robotID, status);
            break;

        case 5:
            cout << "Exiting system...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}