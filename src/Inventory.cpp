#include "Inventory.h"

// Constructor for the Item class
Item::Item(std::string name, bool usable, Sprite2D* sprite, Vector2 tile_pos)
{
    this->name = name;
    this->sprite = sprite;
    this->tile_pos = tile_pos;
    this->usable = usable;
}

// Constructor for the Inventory class
Inventory::Inventory(Vector2 position, unsigned int rows, unsigned int cols)
{
    Inventory_BG = new Sprite2D("Assets/inventory.png");
    Inventory_BG->position.x = position.x - 3;
    Inventory_BG->position.y = position.y - 3;
    this->position = position;
    this->inventory_rows = rows;
    this->inventory_cols = cols;
}

// Method to add an item to the inventory
void Inventory::Add_Item(Item* item)
{
    Items.push_back(item);
}

// Method to draw the inventory
void Inventory::Draw()
{
    if (!isShowing)
    {
        return; // If the inventory is not shown, return without drawing
    }

    unsigned int ccol = 0, crow = 0; // Initialize column and row counters
    Inventory_BG->Draw(); // Draw the inventory background

    // Loop through the items in the inventory
    for (auto& item : Items)
    {
        if (ccol >= inventory_cols) // Check if the column count exceeds the number of columns
        {
            crow++; // Move to the next row
            ccol = 0; // Reset the column count
        }

        // Calculate the position to draw the item's sprite
        Vector2 draw_pos = Vector2{ item->sprite->GetRect().width * (ccol) + position.x, item->sprite->GetRect().height * (crow) + position.y };

        item->sprite->DrawRectAt(item->tile_pos.x, item->tile_pos.y, draw_pos); // Draw the item's sprite

        // Check if the mouse is hovering over the item
        Rectangle mouse_rect = Rectangle{ (float)GetMouseX(), (float)GetMouseY(), 2, 2 };
        Rectangle item_rect = Rectangle{ draw_pos.x, draw_pos.y, item->sprite->GetRect().width, item->sprite->GetRect().height };
        if (CheckCollisionRecs(item_rect, mouse_rect))
        {
            item->mouse_hover = true;
            item->sprite->DrawOutline(RED); // Draw a red outline if the mouse is hovering over the item
        }
        else
        {
            item->mouse_hover = false;
        }

        ccol++; // Increment the column count
    }
}

// Method to update the inventory
void Inventory::Update()
{
    if (IsKeyPressed(KEY_I)) // Check if the 'I' key is pressed to toggle the inventory
    {
        ToggleInventory(); // Toggle the visibility of the inventory
    }
}

// Method to toggle the visibility of the inventory
void Inventory::ToggleInventory()
{
    isShowing = !isShowing; // Toggle the value of isShowing
}

// Method to get a pointer to the vector of items in the inventory
std::vector<Item*>* Inventory::Get_Items()
{
    return &Items;
}
