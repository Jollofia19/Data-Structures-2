#include "WarehouseTree.hpp"

WarehouseTree::WarehouseTree() {
    root = createNode("Warehouse Entrance", "Root");
}

WarehouseNode* WarehouseTree::createNode(string name, string type) {
    WarehouseNode* newNode = new WarehouseNode;

    newNode->name = name;
    newNode->type = type;
    newNode->firstChild = nullptr;
    newNode->nextSibling = nullptr;

    return newNode;
}

WarehouseNode* WarehouseTree::searchNode(WarehouseNode* current, string name) {
    if (current == nullptr) {
        return nullptr;
    }

    if (current->name == name) {
        return current;
    }

    WarehouseNode* foundInChild = searchNode(current->firstChild, name);

    if (foundInChild != nullptr) {
        return foundInChild;
    }

    return searchNode(current->nextSibling, name);
}

void WarehouseTree::addSection(string parentName, string sectionName, string sectionType) {
    WarehouseNode* parent = searchNode(root, parentName);

    if (parent == nullptr) {
        cout << "Parent location not found: " << parentName << endl;
        return;
    }

    WarehouseNode* newSection = createNode(sectionName, sectionType);

    if (parent->firstChild == nullptr) {
        parent->firstChild = newSection;
    }
    else {
        WarehouseNode* current = parent->firstChild;

        while (current->nextSibling != nullptr) {
            current = current->nextSibling;
        }

        current->nextSibling = newSection;
    }

    cout << sectionType << " added: " << sectionName << " under " << parentName << endl;
}

void WarehouseTree::buildDefaultLayout() {
    // Zones
    addSection("Warehouse Entrance", "Zone A", "Zone");
    addSection("Warehouse Entrance", "Zone B", "Zone");
    addSection("Warehouse Entrance", "Zone C", "Zone");

    // Aisles using full format to avoid duplicate names
    addSection("Zone A", "Zone A / Aisle 1", "Aisle");
    addSection("Zone A", "Zone A / Aisle 2", "Aisle");

    addSection("Zone B", "Zone B / Aisle 1", "Aisle");
    addSection("Zone B", "Zone B / Aisle 2", "Aisle");

    addSection("Zone C", "Zone C / Aisle 1", "Aisle");

    // Shelves using agreed group format
    addSection("Zone A / Aisle 1", "Zone A / Aisle 1 / Shelf A1", "Shelf");
    addSection("Zone A / Aisle 1", "Zone A / Aisle 1 / Shelf A2", "Shelf");
    addSection("Zone A / Aisle 2", "Zone A / Aisle 2 / Shelf A3", "Shelf");

    addSection("Zone B / Aisle 1", "Zone B / Aisle 1 / Shelf B1", "Shelf");
    addSection("Zone B / Aisle 2", "Zone B / Aisle 2 / Shelf B2", "Shelf");

    addSection("Zone C / Aisle 1", "Zone C / Aisle 1 / Shelf C1", "Shelf");
}

void WarehouseTree::displayTree(WarehouseNode* current, int level) {
    if (current == nullptr) {
        return;
    }

    for (int i = 0; i < level; i++) {
        cout << "   ";
    }

    cout << "- " << current->name << " (" << current->type << ")" << endl;

    displayTree(current->firstChild, level + 1);
    displayTree(current->nextSibling, level);
}

void WarehouseTree::displayWarehouseLayout() {
    cout << "\nWarehouse Layout:" << endl;
    cout << "-----------------" << endl;

    displayTree(root, 0);
}

void WarehouseTree::searchLocation(string locationName) {
    WarehouseNode* result = searchNode(root, locationName);

    if (result == nullptr) {
        cout << "\nLocation not found: " << locationName << endl;
    }
    else {
        cout << "\nLocation found!" << endl;
        cout << "Name: " << result->name << endl;
        cout << "Type: " << result->type << endl;
    }
}

bool WarehouseTree::printPath(WarehouseNode* current, string targetName) {
    if (current == nullptr) {
        return false;
    }

    if (current->name == targetName) {
        cout << current->name;
        return true;
    }

    if (printPath(current->firstChild, targetName)) {
        cout << " <- " << current->name;
        return true;
    }

    if (printPath(current->nextSibling, targetName)) {
        return true;
    }

    return false;
}

void WarehouseTree::showPathToLocation(string locationName) {
    cout << "\nPath to selected location:" << endl;

    bool found = printPath(root, locationName);

    if (!found) {
        cout << "Location not found.";
    }

    cout << endl;
}

void WarehouseTree::traversePreOrder(WarehouseNode* current) {
    if (current == nullptr) {
        return;
    }

    cout << current->name << " (" << current->type << ")" << endl;

    traversePreOrder(current->firstChild);
    traversePreOrder(current->nextSibling);
}

void WarehouseTree::traverseWarehouse() {
    cout << "\nWarehouse Traversal Result:" << endl;
    cout << "---------------------------" << endl;

    traversePreOrder(root);
}

void WarehouseTree::deleteTree(WarehouseNode* current) {
    if (current == nullptr) {
        return;
    }

    deleteTree(current->firstChild);
    deleteTree(current->nextSibling);

    delete current;
}

WarehouseTree::~WarehouseTree() {
    deleteTree(root);
}