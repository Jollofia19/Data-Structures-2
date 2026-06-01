#ifndef WAREHOUSE_TREE_HPP
#define WAREHOUSE_TREE_HPP

#include <iostream>
#include <string>
using namespace std;

// Tree node for warehouse sections
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

    void displayTree(WarehouseNode* current, int level);
    bool printPath(WarehouseNode* current, string targetName);
    void traversePreOrder(WarehouseNode* current);
    void deleteTree(WarehouseNode* current);

public:
    WarehouseTree();

    void buildDefaultLayout();
    void addSection(string parentName, string sectionName, string sectionType);

    void displayWarehouseLayout();
    void searchLocation(string locationName);
    void showPathToLocation(string locationName);
    void traverseWarehouse();

    ~WarehouseTree();
};

#endif