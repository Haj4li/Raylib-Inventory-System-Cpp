#include "Sprite2D.h"
#include <string>
#include <vector>

// Define a struct for representing items in the inventory
struct Item
{
    std::string name;       // Name of the item
    bool usable = false;    // Whether the item is usable
    Vector2 tile_pos = {0,0}; // Position of the item in a grid (tile position)
    Sprite2D* sprite;       // Pointer to the item's sprite

    unsigned short add_health = 0; // Amount of health the item adds (if usable)
    float add_speed = 0;    // Amount of speed the item adds (if usable)
    float duration = 0;     // Duration of the item's effect (if usable)
    bool mouse_hover = false; // Whether the mouse is hovering over the item

    Item(std::string name, bool usable, Sprite2D* sprite, Vector2 tile_pos);
};

// Define a class to represent an inventory
class Inventory
{
private:
    Vector2 position;               // Position of the inventory
    unsigned short inventory_rows = 0; // Number of rows in the inventory grid
    unsigned short inventory_cols = 0; // Number of columns in the inventory grid
    std::vector<Item*> Items;       // Vector to store pointers to items in the inventory
    bool isShowing = false;         // Whether the inventory is currently visible
    Sprite2D* Inventory_BG;         // Pointer to the inventory's background sprite

public:
    Inventory(Vector2 position, unsigned int rows, unsigned int cols); // Constructor
    void Add_Item(Item* item);      // Method to add an item to the inventory
    void Draw();                    // Method to draw the inventory
    void Update();                  // Method to update the inventory
    void ToggleInventory();         // Method to toggle the visibility of the inventory
    std::vector<Item*>* Get_Items(); // Method to get a pointer to the vector of items in the inventory
};
