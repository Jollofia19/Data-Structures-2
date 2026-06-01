// ============================================================
// Task 4: Item Search and Management Module
// Main entry point
// ============================================================

#include "ItemSearch.hpp"

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