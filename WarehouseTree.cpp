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

// Private helper used only for default layout.
// It adds sections silently without printing many messages at program startup.
void WarehouseTree::addDefaultSection(string parentName, string sectionName, string sectionType) {
    WarehouseNode* parent = searchNode(root, parentName);

    if (parent == nullptr) {
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
}

void WarehouseTree::buildDefaultLayout() {
    // Zones
    addDefaultSection("Warehouse Entrance", "Zone A", "Zone");
    addDefaultSection("Warehouse Entrance", "Zone B", "Zone");
    addDefaultSection("Warehouse Entrance", "Zone C", "Zone");

    // Aisles using full format to avoid duplicate names
    addDefaultSection("Zone A", "Zone A / Aisle 1", "Aisle");
    addDefaultSection("Zone A", "Zone A / Aisle 2", "Aisle");

    addDefaultSection("Zone B", "Zone B / Aisle 1", "Aisle");
    addDefaultSection("Zone B", "Zone B / Aisle 2", "Aisle");

    addDefaultSection("Zone C", "Zone C / Aisle 1", "Aisle");

    // Shelves using agreed location format
    addDefaultSection("Zone A / Aisle 1", "Zone A / Aisle 1 / Shelf A1", "Shelf");
    addDefaultSection("Zone A / Aisle 1", "Zone A / Aisle 1 / Shelf A2", "Shelf");
    addDefaultSection("Zone A / Aisle 2", "Zone A / Aisle 2 / Shelf A3", "Shelf");

    addDefaultSection("Zone B / Aisle 1", "Zone B / Aisle 1 / Shelf B1", "Shelf");
    addDefaultSection("Zone B / Aisle 2", "Zone B / Aisle 2 / Shelf B2", "Shelf");

    addDefaultSection("Zone C / Aisle 1", "Zone C / Aisle 1 / Shelf C1", "Shelf");
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

bool WarehouseTree::findPathToNode(WarehouseNode* current, string targetName, string path[], int& pathLength) {
    if (current == nullptr) {
        return false;
    }

    path[pathLength] = current->name;
    pathLength++;

    if (current->name == targetName) {
        return true;
    }

    if (findPathToNode(current->firstChild, targetName, path, pathLength)) {
        return true;
    }

    pathLength--;

    if (findPathToNode(current->nextSibling, targetName, path, pathLength)) {
        return true;
    }

    return false;
}

void WarehouseTree::showPathToLocation(string locationName) {
    string path[100];
    int pathLength = 0;

    bool found = findPathToNode(root, locationName, path, pathLength);

    cout << "\nPath to selected location:" << endl;

    if (!found) {
        cout << "Location not found: " << locationName << endl;
        return;
    }

    for (int i = 0; i < pathLength; i++) {
        cout << path[i];

        if (i < pathLength - 1) {
            cout << " -> ";
        }
    }

    cout << endl;
}

void WarehouseTree::showPathBetweenLocations(string startLocation, string endLocation) {
    string startPath[100];
    string endPath[100];

    int startLength = 0;
    int endLength = 0;

    bool startFound = findPathToNode(root, startLocation, startPath, startLength);
    bool endFound = findPathToNode(root, endLocation, endPath, endLength);

    cout << "\nPath between selected locations:" << endl;

    if (!startFound) {
        cout << "Start location not found: " << startLocation << endl;
        return;
    }

    if (!endFound) {
        cout << "End location not found: " << endLocation << endl;
        return;
    }

    int commonIndex = 0;

    while (commonIndex < startLength &&
           commonIndex < endLength &&
           startPath[commonIndex] == endPath[commonIndex]) {
        commonIndex++;
    }

    int lowestCommonIndex = commonIndex - 1;

    for (int i = startLength - 1; i > lowestCommonIndex; i--) {
        cout << startPath[i] << " -> ";
    }

    cout << startPath[lowestCommonIndex];

    for (int i = lowestCommonIndex + 1; i < endLength; i++) {
        cout << " -> " << endPath[i];
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