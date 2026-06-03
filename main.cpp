#include <iostream>
#include <string>
#include <limits>
using namespace std;

#include "OrderManagement.hpp"
#include "ItemSearch.hpp"
#include "WarehouseTree.hpp"
#include "NavigationStack.hpp"

// RobotAssign.cpp has no header, so declare it here
void runRobotAssignment();

int getMenuChoice() {
    int choice;
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

void runNavigationModule(NavigationStack& robotNavigation) {
    int choice;

    do {
        cout << "\n======================================" << endl;
        cout << " TASK 3: ROBOT NAVIGATION MODULE" << endl;
        cout << " Data Structure: Stack" << endl;
        cout << "======================================" << endl;
        cout << "1. Record robot movement" << endl;
        cout << "2. Display forward movement path" << endl;
        cout << "3. Handle obstacle / wrong path" << endl;
        cout << "4. Return robot to start" << endl;
        cout << "5. Display complete navigation log" << endl;
        cout << "6. Clear path" << endl;
        cout << "7. Back to main menu" << endl;
        cout << "Enter your choice: ";

        choice = getMenuChoice();

        switch (choice) {
        case 1:
            robotNavigation.recordMovement();
            break;
        case 2:
            robotNavigation.displayForwardPath();
            break;
        case 3:
            robotNavigation.handleObstacle();
            break;
        case 4:
            robotNavigation.returnToStart();
            break;
        case 5:
            robotNavigation.displayNavigationLog();
            break;
        case 6:
            robotNavigation.clearPath();
            break;
        case 7:
            cout << "\nReturning to main menu..." << endl;
            break;
        default:
            cout << "\nInvalid choice. Please enter a number from 1 to 7." << endl;
        }

    } while (choice != 7);
}

void runWarehouseLayoutModule(WarehouseTree& warehouse) {
    int choice;
    string parentName;
    string sectionName;
    string sectionType;
    string locationName;
    string startLocation;
    string endLocation;

    do {
        cout << "\n======================================" << endl;
        cout << " TASK 5: WAREHOUSE LAYOUT MODULE" << endl;
        cout << " Data Structure: Tree" << endl;
        cout << "======================================" << endl;
        cout << "1. Display warehouse layout" << endl;
        cout << "2. Add new section" << endl;
        cout << "3. Search location" << endl;
        cout << "4. Show path to one location" << endl;
        cout << "5. Show path between two locations" << endl;
        cout << "6. Traverse warehouse" << endl;
        cout << "7. Back to main menu" << endl;
        cout << "Enter your choice: ";

        choice = getMenuChoice();

        switch (choice) {
        case 1:
            warehouse.displayWarehouseLayout();
            break;

        case 2:
            cout << "\nEnter parent location name: ";
            getline(cin, parentName);

            cout << "Enter new section name: ";
            getline(cin, sectionName);

            cout << "Enter section type (Zone/Aisle/Shelf): ";
            getline(cin, sectionType);

            warehouse.addSection(parentName, sectionName, sectionType);
            break;

        case 3:
            cout << "\nEnter location name to search: ";
            getline(cin, locationName);

            warehouse.searchLocation(locationName);
            break;

        case 4:
            cout << "\nEnter destination location name: ";
            getline(cin, locationName);

            warehouse.showPathToLocation(locationName);
            break;

        case 5:
            cout << "\nEnter start location: ";
            getline(cin, startLocation);

            cout << "Enter end location: ";
            getline(cin, endLocation);

            warehouse.showPathBetweenLocations(startLocation, endLocation);
            break;

        case 6:
            warehouse.traverseWarehouse();
            break;

        case 7:
            cout << "\nReturning to main menu..." << endl;
            break;

        default:
            cout << "\nInvalid choice. Please enter a number from 1 to 7." << endl;
        }

    } while (choice != 7);
}

void runFullSystemDemo(WarehouseTree& warehouse) {
    cout << "\n======================================" << endl;
    cout << " FULL WAREHOUSE ROBOT SYSTEM WORKFLOW" << endl;
    cout << "======================================" << endl;

    cout << "\n1. New order received." << endl;
    cout << "Order ID: O001" << endl;
    cout << "Customer: Ahmed" << endl;
    cout << "Item ID: I001" << endl;
    cout << "Item Name: Laptop" << endl;

    cout << "\n2. Robot assigned to task." << endl;
    cout << "Assigned Robot: R101" << endl;

    cout << "\n3. Item location identified." << endl;
    cout << "Location: Zone A / Aisle 1 / Shelf A1" << endl;

    cout << "\n4. Route generated by warehouse layout module." << endl;
    warehouse.showPathToLocation("Zone A / Aisle 1 / Shelf A1");

    cout << "\n5. Robot movement recorded by navigation module." << endl;

    NavigationStack demoNavigation;
    demoNavigation.pushMovement("Forward");
    demoNavigation.pushMovement("Right");
    demoNavigation.pushMovement("Forward");
    demoNavigation.pushMovement("Left");

    demoNavigation.displayForwardPath();

    cout << "\n6. Robot returns using reverse path." << endl;
    demoNavigation.returnToStart();

    cout << "\n7. Navigation log:" << endl;
    demoNavigation.displayNavigationLog();

    cout << "\nFull workflow completed successfully." << endl;
}

int main() {
    int choice;

    NavigationStack robotNavigation;
    WarehouseTree warehouse;
    ItemBST itemSystem;

    warehouse.buildDefaultLayout();

    do {
        cout << "\n======================================" << endl;
        cout << " WAREHOUSE ROBOT NAVIGATION SYSTEM" << endl;
        cout << "======================================" << endl;
        cout << "1. Order Management Module" << endl;
        cout << "2. Robot Assignment Module" << endl;
        cout << "3. Robot Navigation and Path Tracking Module" << endl;
        cout << "4. Item Search and Management Module" << endl;
        cout << "5. Warehouse Layout and Navigation Module" << endl;
        cout << "6. Run Full System Workflow Demo" << endl;
        cout << "7. Exit System" << endl;
        cout << "Enter your choice: ";

        choice = getMenuChoice();

        switch (choice) {
        case 1:
            runOrderManagement();
            break;

        case 2:
            runRobotAssignment();
            break;

        case 3:
            runNavigationModule(robotNavigation);
            break;

        case 4:
            itemSystem.runMenu();
            break;

        case 5:
            runWarehouseLayoutModule(warehouse);
            break;

        case 6:
            runFullSystemDemo(warehouse);
            break;

        case 7:
            cout << "\nExiting Warehouse Robot Navigation System..." << endl;
            break;

        default:
            cout << "\nInvalid choice. Please enter a number from 1 to 7." << endl;
        }

    } while (choice != 7);

    return 0;
}