// ============================================================
// Task 4: Item Search and Management Module
// Data Structure: Binary Search Tree (BST)
// ============================================================

#ifndef ITEMSEARCH_HPP
#define ITEMSEARCH_HPP

#include <iostream>
#include <string>
using namespace std;

// ============================================================
// NODE STRUCTURE
// ============================================================
struct ItemNode {
    int itemID;
    string itemName;
    string itemLocation;
    ItemNode* left;
    ItemNode* right;

    ItemNode(int id, string name, string location) {
        itemID = id;
        itemName = name;
        itemLocation = location;
        left = nullptr;
        right = nullptr;
    }
};

// ============================================================
// BINARY SEARCH TREE CLASS
// ============================================================
class ItemBST {
private:
    ItemNode* root;

    ItemNode* insertHelper(ItemNode* node, int id, string name, string location) {
        if (node == nullptr) {
            return new ItemNode(id, name, location);
        }
        if (id < node->itemID) {
            node->left = insertHelper(node->left, id, name, location);
        } else if (id > node->itemID) {
            node->right = insertHelper(node->right, id, name, location);
        } else {
            cout << "[!] Item with ID " << id << " already exists.\n";
        }
        return node;
    }

    ItemNode* searchByIDHelper(ItemNode* node, int id) {
        if (node == nullptr || node->itemID == id) {
            return node;
        }
        if (id < node->itemID) {
            return searchByIDHelper(node->left, id);
        } else {
            return searchByIDHelper(node->right, id);
        }
    }

    void searchByNameHelper(ItemNode* node, string name) {
        if (node == nullptr) return;
        searchByNameHelper(node->left, name);
        if (node->itemName == name) {
            cout << "  Found -> ID: " << node->itemID
                 << " | Name: " << node->itemName
                 << " | Location: " << node->itemLocation << "\n";
        }
        searchByNameHelper(node->right, name);
    }

    void inOrderHelper(ItemNode* node) {
        if (node == nullptr) return;
        inOrderHelper(node->left);
        cout << "  ID: " << node->itemID
             << " | Name: " << node->itemName
             << " | Location: " << node->itemLocation << "\n";
        inOrderHelper(node->right);
    }

    ItemNode* findMin(ItemNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    ItemNode* deleteHelper(ItemNode* node, int id) {
        if (node == nullptr) {
            cout << "[!] Item ID " << id << " not found.\n";
            return nullptr;
        }
        if (id < node->itemID) {
            node->left = deleteHelper(node->left, id);
        } else if (id > node->itemID) {
            node->right = deleteHelper(node->right, id);
        } else {
            if (node->left == nullptr) {
                ItemNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                ItemNode* temp = node->left;
                delete node;
                return temp;
            } else {
                ItemNode* successor = findMin(node->right);
                node->itemID = successor->itemID;
                node->itemName = successor->itemName;
                node->itemLocation = successor->itemLocation;
                node->right = deleteHelper(node->right, successor->itemID);
            }
        }
        return node;
    }

public:
    ItemBST() {
        root = nullptr;
    }

    void insertItem(int id, string name, string location) {
        root = insertHelper(root, id, name, location);
        cout << "[+] Item inserted: ID=" << id
             << ", Name=" << name
             << ", Location=" << location << "\n";
    }

    void searchByID(int id) {
        ItemNode* result = searchByIDHelper(root, id);
        if (result != nullptr) {
            cout << "[Search Result]\n";
            cout << "  ID: " << result->itemID
                 << " | Name: " << result->itemName
                 << " | Location: " << result->itemLocation << "\n";
        } else {
            cout << "[!] Item with ID " << id << " not found.\n";
        }
    }

    void searchByName(string name) {
        cout << "[Search by Name: " << name << "]\n";
        searchByNameHelper(root, name);
    }

    void updateItem(int id, string newLocation) {
        ItemNode* result = searchByIDHelper(root, id);
        if (result != nullptr) {
            result->itemLocation = newLocation;
            cout << "[~] Item ID " << id
                 << " location updated to: " << newLocation << "\n";
        } else {
            cout << "[!] Item with ID " << id << " not found.\n";
        }
    }

    void deleteItem(int id) {
        root = deleteHelper(root, id);
        cout << "[-] Item ID " << id << " deleted.\n";
    }

    void displayAll() {
        if (root == nullptr) {
            cout << "[!] No items in the system.\n";
            return;
        }
        cout << "\n===== All Items (Sorted by ID) =====\n";
        inOrderHelper(root);
        cout << "=====================================\n";
    }
};

#endif