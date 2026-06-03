#include "ItemSearch.hpp"

//  ItemNode constructor
ItemNode::ItemNode(const string& id,
                   const string& nm,
                   const string& loc)
    : itemID(id), name(nm), location(loc), left(nullptr), right(nullptr)
{
}


//  ItemBST constructor 
ItemBST::ItemBST() : root(nullptr), count(0) {}

ItemBST::~ItemBST()
{
    destroyTree(root);
}



//  destroyTree-post-order deletion of all nodes
void ItemBST::destroyTree(ItemNode* node)
{
    if (node == nullptr) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}


//  toLower – returns a lowercase copy of a string
string ItemBST::toLower(const string& str) const
{
    string result = str;
    for (int i = 0; i < (int)result.size(); i++)
    {
        
        if (result[i] >= 'A' && result[i] <= 'Z')
            result[i] = result[i] + 32;
    }
    return result;
}


void ItemBST::printBorder() const
{
    cout << "+----------+---------------------------+------------------------------+" << endl;
}



//  insertNode-recursive BST insertion
//  BST property-left child ID < parent ID < right child ID
ItemNode* ItemBST::insertNode(ItemNode* node,
                               const string& id,
                               const string& name,
                               const string& loc)
{
    
    if (node == nullptr)
    {
        count++;
        return new ItemNode(id, name, loc);
    }

    
    if (id < node->itemID)
        node->left = insertNode(node->left, id, name, loc);

    
    else if (id > node->itemID)
        node->right = insertNode(node->right, id, name, loc);

    
    else
        cout << "  [WARNING] Item ID '" << id << "' already exists. Duplicate skipped.\n";

    return node;
}


//  searchByID-recursive search for exact Item ID
ItemNode* ItemBST::searchByID(ItemNode* node, const string& id) const
{
    if (node == nullptr)    return nullptr;  
    if (id == node->itemID) return node;     
    if (id < node->itemID)  return searchByID(node->left,  id);
    return                         searchByID(node->right, id);
}


//  inorderDisplay-prints items in sorted order (by ID)
void ItemBST::inorderDisplay(ItemNode* node) const
{
    if (node == nullptr) return;

    inorderDisplay(node->left);

    string idField   = node->itemID;   idField.resize(8,  ' ');
    string nameField = node->name;     nameField.resize(25, ' ');
    string locField  = node->location; locField.resize(28, ' ');

    cout << "| " << idField << " | " << nameField << " | " << locField << " |\n";

    inorderDisplay(node->right);
}


//  searchByName-full-tree scan for keyword in item name
void ItemBST::searchByName(ItemNode* node, const string& keyword) const
{
    if (node == nullptr) return;

    searchByName(node->left, keyword);

    
    if (toLower(node->name).find(keyword) != string::npos)
    {
        string idField   = node->itemID;   idField.resize(8,  ' ');
        string nameField = node->name;     nameField.resize(25, ' ');
        string locField  = node->location; locField.resize(28, ' ');

        cout << "| " << idField << " | " << nameField << " | " << locField << " |\n";
    }

    searchByName(node->right, keyword);
}


//  findMin-returns leftmost node in a subtree
ItemNode* ItemBST::findMin(ItemNode* node) const
{
    while (node->left != nullptr)
        node = node->left;
    return node;
}


//  deleteNode- recursive BST deletion
//  Case 1: No children-simply delete
//  Case 2: One child-replace with child
//  Case 3: Two children-replace with in-order successor
ItemNode* ItemBST::deleteNode(ItemNode* node,
                               const string& id,
                               bool& deleted)
{
    if (node == nullptr)
    {
        deleted = false;
        return nullptr;
    }

    if (id < node->itemID)
        node->left = deleteNode(node->left, id, deleted);
    else if (id > node->itemID)
        node->right = deleteNode(node->right, id, deleted);
    else
    {
        
        deleted = true;
        count--;

        if (node->left == nullptr)
        {
            ItemNode* temp = node->right;
            delete node;
            return temp;
        }
        if (node->right == nullptr)
        {
            ItemNode* temp = node->left;
            delete node;
            return temp;
        }

        
        ItemNode* successor = findMin(node->right);
        node->itemID   = successor->itemID;
        node->name     = successor->name;
        node->location = successor->location;

        
        count++;
        node->right = deleteNode(node->right, successor->itemID, deleted);
    }

    return node;
}


//  saveToFile-in-order write to open CSV file stream
void ItemBST::saveToFile(ItemNode* node, ofstream& outFile) const
{
    if (node == nullptr) return;
    saveToFile(node->left, outFile);
    outFile << node->itemID << ","
            << node->name   << ","
            << node->location << "\n";
    saveToFile(node->right, outFile);
}



//  Public Interface
void ItemBST::insertItem(const string& id,
                          const string& name,
                          const string& loc)
{
    root = insertNode(root, id, name, loc);
}

void ItemBST::searchItemByID(const string& id) const
{
    ItemNode* result = searchByID(root, id);

    if (result == nullptr)
    {
        cout << "\n  [NOT FOUND] No item with ID '" << id << "' exists.\n";
        return;
    }

    cout << "\n  Search Result:\n";
    printBorder();
    cout << "| Item ID  | Name                      | Location                     |\n";
    printBorder();

    string idField   = result->itemID;   idField.resize(8,  ' ');
    string nameField = result->name;     nameField.resize(25, ' ');
    string locField  = result->location; locField.resize(28, ' ');

    cout << "| " << idField << " | " << nameField << " | " << locField << " |\n";
    printBorder();
}

void ItemBST::searchItemByName(const string& keyword) const
{
    cout << "\n  Search Results for name keyword: \"" << keyword << "\"\n";
    printBorder();
    cout << "| Item ID  | Name                      | Location                     |\n";
    printBorder();
    searchByName(root, toLower(keyword));
    printBorder();
}

void ItemBST::updateItem(const string& id,
                          const string& newName,
                          const string& newLoc)
{
    ItemNode* target = searchByID(root, id);

    if (target == nullptr)
    {
        cout << "\n  [ERROR] Item ID '" << id << "' not found. Update aborted.\n";
        return;
    }

    if (!newName.empty()) target->name     = newName;
    if (!newLoc.empty())  target->location = newLoc;

    cout << "\n  [SUCCESS] Item '" << id << "' has been updated.\n";
    searchItemByID(id);
}

void ItemBST::deleteItem(const string& id)
{
    bool deleted = false;
    root = deleteNode(root, id, deleted);

    if (deleted)
        cout << "\n  [SUCCESS] Item '" << id << "' has been deleted.\n";
    else
        cout << "\n  [ERROR] Item ID '" << id << "' not found. Nothing deleted.\n";
}

void ItemBST::displayAllItems() const
{
    if (root == nullptr)
    {
        cout << "\n  [INFO] The item catalogue is currently empty.\n";
        return;
    }

    cout << "\n  ===== Warehouse Item Catalogue (" << count << " items) =====\n";
    printBorder();
    cout << "| Item ID  | Name                      | Location                     |\n";
    printBorder();
    inorderDisplay(root);
    printBorder();
    cout << "  Total items: " << count << "\n";
}

string ItemBST::getItemLocation(const string& id) const
{
    ItemNode* node = searchByID(root, id);
    if (node == nullptr) return "";
    return node->location;
}

string ItemBST::getItemName(const string& id) const
{
    ItemNode* node = searchByID(root, id);
    if (node == nullptr) return "";
    return node->name;
}

bool ItemBST::itemExists(const string& id) const
{
    return searchByID(root, id) != nullptr;
}

int ItemBST::getCount() const
{
    return count;
}



//  CSV File Operations
void ItemBST::loadFromCSV(const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "\n  [ERROR] Cannot open file: " << filename << "\n";
        return;
    }

    string line;
    int  loaded    = 0;
    bool firstLine = true;

    while (getline(file, line))
    {
        
        if (firstLine) { firstLine = false; continue; }
        if (line.empty()) continue;

        stringstream ss(line);
        string id, name, loc;

        getline(ss, id,   ',');
        getline(ss, name, ',');
        getline(ss, loc,  ',');

        if (id.empty() || name.empty() || loc.empty()) continue;

        root = insertNode(root, id, name, loc);
        loaded++;
    }

    file.close();
    cout << "\n  [INFO] Loaded " << loaded << " items from '" << filename << "'.\n";
}

void ItemBST::saveToCSV(const string& filename) const
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "\n  [ERROR] Cannot write to file: " << filename << "\n";
        return;
    }

    
    file << "Item ID,Name,Location\n";

    
    saveToFile(root, file);
    file.close();

    cout << "\n  [INFO] " << count << " items saved to '" << filename << "'.\n";
}



//  Interactive Menu
void ItemBST::runMenu()
{
    
    loadFromCSV("Items.csv");

    int choice = 0;

    do
    {
        cout << "\n";
        cout << "  ==========================================\n";
        cout << "   ITEM SEARCH AND MANAGEMENT MODULE\n";
        cout << "   Data Structure: Binary Search Tree\n";
        cout << "  ==========================================\n";
        cout << "   1. Display All Items\n";
        cout << "   2. Search Item by ID\n";
        cout << "   3. Search Item by Name\n";
        cout << "   4. Insert New Item\n";
        cout << "   5. Update Item\n";
        cout << "   6. Delete Item\n";
        cout << "   7. Save to CSV\n";
        cout << "   8. Show Total Item Count\n";
        cout << "   0. Exit Module\n";
        cout << "  ==========================================\n";
        cout << "  Enter your choice: ";
        cin >> choice;
        cin.ignore();

        string id, name, loc, keyword;

        switch (choice)
        {
        case 1:
            displayAllItems();
            break;

        case 2:
            cout << "  Enter Item ID to search: ";
            getline(cin, id);
            searchItemByID(id);
            break;

        case 3:
            cout << "  Enter name keyword to search: ";
            getline(cin, keyword);
            searchItemByName(keyword);
            break;

        case 4:
            cout << "  Enter new Item ID   : ";
            getline(cin, id);
            cout << "  Enter Item Name     : ";
            getline(cin, name);
            cout << "  Enter Item Location\n";
            cout << "  (Format: Zone A / Aisle 1 / Shelf A1)\n";
            cout << "  > ";
            getline(cin, loc);

            if (id.empty() || name.empty() || loc.empty())
                cout << "\n  [ERROR] All fields are required. Insert cancelled.\n";
            else
            {
                insertItem(id, name, loc);
                cout << "\n  [SUCCESS] Item '" << id << "' inserted.\n";
            }
            break;

        case 5:
            cout << "  Enter Item ID to update: ";
            getline(cin, id);

            if (!itemExists(id))
            {
                cout << "\n  [ERROR] Item ID '" << id << "' not found.\n";
                break;
            }

            cout << "  Enter new Name     (press Enter to keep current): ";
            getline(cin, name);
            cout << "  Enter new Location (press Enter to keep current)\n";
            cout << "  (Format: Zone A / Aisle 1 / Shelf A1)\n";
            cout << "  > ";
            getline(cin, loc);

            updateItem(id, name, loc);
            break;

        case 6:
            cout << "  Enter Item ID to delete: ";
            getline(cin, id);
            deleteItem(id);
            break;

        case 7:
            saveToCSV("Items.csv");
            break;

        case 8:
            cout << "\n  Total items in BST: " << getCount() << "\n";
            break;

        case 0:
            cout << "\n  Exiting Item Management Module...\n";
            break;

        default:
            cout << "\n  [ERROR] Invalid choice. Please enter 0-8.\n";
            break;
        }

    } while (choice != 0);
}


