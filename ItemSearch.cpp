// ============================================================
// Task 4: Item Search and Management Module
// Data Structure Used: Binary Search Tree (BST)
// Reason: BST allows efficient insertion, search, update,
//         deletion, and sorted display of warehouse items.
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// ============================================================
// NODE STRUCTURE
// Each node stores one item's details
// ============================================================
struct ItemNode {
    int itemID;
    string itemName;
    string itemLocation; // e.g., "Zone A, Aisle 3, Shelf 2"
    ItemNode* left;
    ItemNode* right;

    // Constructor
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

    // --- Helper: Insert ---
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

    // --- Helper: Search by ID ---
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

    // --- Helper: Search by Name (full tree scan) ---
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

    // --- Helper: In-order display (sorted by ID) ---
    void inOrderHelper(ItemNode* node) {
        if (node == nullptr) return;
        inOrderHelper(node->left);
        cout << "  ID: " << node->itemID
             << " | Name: " << node->itemName
             << " | Location: " << node->itemLocation << "\n";
        inOrderHelper(node->right);
    }

    // --- Helper: Find minimum node (used in delete) ---
    ItemNode* findMin(ItemNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // --- Helper: Delete node ---
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
            // Node found — 3 cases
            if (node->left == nullptr) {
                ItemNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                ItemNode* temp = node->left;
                delete node;
                return temp;
            } else {
                // Two children: replace with in-order successor
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
    // Constructor
    ItemBST() {
        root = nullptr;
    }

    // --- Insert new item ---
    void insertItem(int id, string name, string location) {
        root = insertHelper(root, id, name, location);
        cout << "[+] Item inserted: ID=" << id
             << ", Name=" << name
             << ", Location=" << location << "\n";
    }

    // --- Search by ID ---
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

    // --- Search by Name ---
    void searchByName(string name) {
        cout << "[Search by Name: " << name << "]\n";
        searchByNameHelper(root, name);
    }

    // --- Update item location ---
    void updateItem(int id, string newLocation) {
        ItemNode* result = searchByIDHelper(root, id);
        if (result != nullptr) {
            result->itemLocation = newLocation;
            cout << "[~] Item ID " << id
                 << " location updated to: " << newLocation << "\n";
        } else {
            cout << "[!] Item with ID " << id << " not found. Cannot update.\n";
        }
    }

    // --- Delete item ---
    void deleteItem(int id) {
        root = deleteHelper(root, id);
        cout << "[-] Item ID " << id << " deleted (if it existed).\n";
    }

    // --- Display all items sorted by ID ---
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

// ============================================================
// MAIN MENU — Demo of Task 4
// ============================================================
int main() {
    ItemBST warehouse;
    int choice;

    cout << "======================================\n";
    cout << "  Warehouse Item Search & Management  \n";
    cout << "======================================\n";

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Add New Item\n";
        cout << "2. Search Item by ID\n";
        cout << "3. Search Item by Name\n";
        cout << "4. Update Item Location\n";
        cout << "5. Delete Item\n";
        cout << "6. Display All Items\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            int id;
            string name, location;
            cout << "Enter Item ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Item Name: ";
            getline(cin, name);
            cout << "Enter Item Location (e.g., Zone A Aisle 2 Shelf 3): ";
            getline(cin, location);
            warehouse.insertItem(id, name, location);

        } else if (choice == 2) {
            int id;
            cout << "Enter Item ID to search: ";
            cin >> id;
            warehouse.searchByID(id);

        } else if (choice == 3) {
            string name;
            cout << "Enter Item Name to search: ";
            cin.ignore();
            getline(cin, name);
            warehouse.searchByName(name);

        } else if (choice == 4) {
            int id;
            string newLoc;
            cout << "Enter Item ID to update: ";
            cin >> id;
            cin.ignore();
            cout << "Enter New Location: ";
            getline(cin, newLoc);
            warehouse.updateItem(id, newLoc);

        } else if (choice == 5) {
            int id;
            cout << "Enter Item ID to delete: ";
            cin >> id;
            warehouse.deleteItem(id);

        } else if (choice == 6) {
            warehouse.displayAll();

        } else if (choice != 0) {
            cout << "[!] Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    cout << "\nSystem exited. Goodbye!\n";
    return 0;
}