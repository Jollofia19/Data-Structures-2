#ifndef ITEMSEARCH_HPP
#define ITEMSEARCH_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// ============================================================
//  NODE STRUCTURE
//  Each node stores one warehouse item in the BST
// ============================================================
struct ItemNode
{
    string itemID;    // Primary key  (e.g. "I001")
    string name;      // Item name    (e.g. "Laptop")
    string location;  // Shelf path   (e.g. "Zone A / Aisle 1 / Shelf A1")

    ItemNode* left;   // Pointer to left  child (smaller ID)
    ItemNode* right;  // Pointer to right child (larger  ID)

    // Constructor
    ItemNode(const string& id,
             const string& nm,
             const string& loc);
};


// ============================================================
//  BINARY SEARCH TREE CLASS
//  Manages the entire warehouse item catalogue
// ============================================================
class ItemBST
{
private:
    ItemNode* root;   // Root node of the BST
    int       count;  // Total number of items stored

    // ---- Private recursive helpers ----

    // Insert a new node into the subtree rooted at 'node'
    ItemNode* insertNode(ItemNode* node,
                         const string& id,
                         const string& name,
                         const string& loc);

    // Search for an item by exact Item ID
    ItemNode* searchByID(ItemNode* node, const string& id) const;

    // In-order traversal – prints all items sorted by Item ID
    void inorderDisplay(ItemNode* node) const;

    // Search by name keyword – case-insensitive partial match
    void searchByName(ItemNode* node, const string& keyword) const;

    // Find the in-order successor (smallest node in right subtree)
    ItemNode* findMin(ItemNode* node) const;

    // Delete node matching 'id' from subtree
    ItemNode* deleteNode(ItemNode* node,
                         const string& id,
                         bool& deleted);

    // Destroy all nodes recursively (used in destructor)
    void destroyTree(ItemNode* node);

    // Save all nodes to open file stream in CSV format
    void saveToFile(ItemNode* node, ofstream& outFile) const;

    // Print a formatted table border line
    void printBorder() const;

    // Convert string to lowercase for case-insensitive search
    string toLower(const string& str) const;

public:
    // Constructor / Destructor
    ItemBST();
    ~ItemBST();

    // ---- Core BST operations ----

    // Insert a new item; rejects duplicates
    void insertItem(const string& id,
                    const string& name,
                    const string& loc);

    // Search and print one item by exact Item ID
    void searchItemByID(const string& id) const;

    // Search and print all items whose name contains keyword
    void searchItemByName(const string& keyword) const;

    // Update name and/or location of an existing item
    void updateItem(const string& id,
                    const string& newName,
                    const string& newLoc);

    // Delete an item by Item ID
    void deleteItem(const string& id);

    // Display all items sorted by Item ID
    void displayAllItems() const;

    // Return location string for a given Item ID
    string getItemLocation(const string& id) const;

    // Return name for a given Item ID
    string getItemName(const string& id) const;

    // Check whether item with given ID exists
    bool itemExists(const string& id) const;

    // Return total number of items stored
    int getCount() const;

    // ---- CSV file operations ----

    // Load all items from CSV file into BST
    void loadFromCSV(const string& filename);

    // Save current BST contents to CSV file
    void saveToCSV(const string& filename) const;

    // ---- Interactive menu ----
    void runMenu();
};

#endif // ITEMSEARCH_HPP