#ifndef WAREHOUSE_TREE_HPP
#define WAREHOUSE_TREE_HPP

#include <iostream>
#include <string>
using namespace std;

// Tree node for warehouse sections such as zones, aisles, and shelves
struct WarehouseNode {
    string name;
    string type;

    WarehouseNode* firstChild;
    WarehouseNode* nextSibling;
};

class WarehouseTree {
private:
    WarehouseNode* root;

    WarehouseNode* createNode(string name, string type);
    WarehouseNode* searchNode(WarehouseNode* current, string name);

    void addDefaultSection(string parentName, string sectionName, string sectionType);

    void displayTree(WarehouseNode* current, int level);
    void traversePreOrder(WarehouseNode* current);
    void deleteTree(WarehouseNode* current);

    bool findPathToNode(WarehouseNode* current, string targetName, string path[], int& pathLength);

public:
    WarehouseTree();

    void buildDefaultLayout();
    void addSection(string parentName, string sectionName, string sectionType);

    void displayWarehouseLayout();
    void searchLocation(string locationName);
    void showPathToLocation(string locationName);
    void showPathBetweenLocations(string startLocation, string endLocation);
    void traverseWarehouse();

    ~WarehouseTree();
};

#endif