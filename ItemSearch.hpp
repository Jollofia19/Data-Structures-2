#ifndef ITEMSEARCH_HPP
#define ITEMSEARCH_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// ============================================================
//  NODE STRUCTURE
//  Each node stores one warehouse item
// ============================================================
struct ItemNode
{
    string itemID;    // Primary key  (e.g. "I001")
    string name;      // Item name    (e.g. "Laptop")
    string location;  // Shelf path   (e.g. "Zone A / Aisle 1 / Shelf A1")

    ItemNode* left;   // Left child  (smaller ID)
    ItemNode* right;  // Right child (larger ID)

    ItemNode(const string& id,
             const string& nm,
             const string& loc);
};


// ============================================================
//  BINARY SEARCH TREE
//  Manages the entire warehouse item catalogue
// ============================================================
class ItemBST
{
private:
    ItemNode* root;
    int       count;

    // Private recursive helpers
    ItemNode* insertNode(ItemNode* node,
                         const string& id,
                         const string& name,
                         const string& loc);

    ItemNode* searchByID(ItemNode* node, const string& id) const;

    void inorderDisplay(ItemNode* node) const;

    void searchByName(ItemNode* node, const string& keyword) const;

    ItemNode* findMin(ItemNode* node) const;

    ItemNode* deleteNode(ItemNode* node,
                         const string& id,
                         bool& deleted);

    void destroyTree(ItemNode* node);

    void saveToFile(ItemNode* node, ofstream& outFile) const;

    void printBorder() const;

    string toLower(const string& str) const;

public:
    ItemBST();
    ~ItemBST();

    // Core BST operations
    void insertItem(const string& id,
                    const string& name,
                    const string& loc);

    void searchItemByID(const string& id) const;

    void searchItemByName(const string& keyword) const;

    void updateItem(const string& id,
                    const string& newName,
                    const string& newLoc);

    void deleteItem(const string& id);

    void displayAllItems() const;

    string getItemLocation(const string& id) const;

    string getItemName(const string& id) const;

    bool itemExists(const string& id) const;

    int getCount() const;

    // CSV file operations
    void loadFromCSV(const string& filename);

    void saveToCSV(const string& filename) const;

    // Interactive menu
    void runMenu();
};

#endif // ITEMSEARCH_HPP