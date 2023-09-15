#include "Inventory.h"


Item::Item(std::string name, bool usable, Sprite2D *sprite, Vector2 tile_pos)
{
    this->name = name;
    this->sprite = sprite;
    this->tile_pos = tile_pos;
    this->usable = usable;
}

Inventory::Inventory(Vector2 position, unsigned int rows, unsigned int cols)
{
    Inventory_BG = new Sprite2D("Assets/inventory.png");
    Inventory_BG->position.x = position.x-3;
    Inventory_BG->position.y = position.y -3;
    this->position = position;
    this->inventory_rows = rows;
    this->inventory_cols = cols;
}

void Inventory::Add_Item(Item* item)
{
    Items.push_back(item);
}

void Inventory::Draw()
{
    if (!isShowing)
    {
        return;
    }
    unsigned int ccol = 0,crow = 0;
    Inventory_BG->Draw();

    for (auto& item: Items)
    {
        
        if (ccol >= inventory_cols)
        {
            crow++;
            ccol = 0;
        }
        Vector2 draw_pos = Vector2{item->sprite->GetRect().width*(ccol)+position.x,item->sprite->GetRect().height * (crow)+position.y};
    
        
        item->sprite->DrawRectAt(item->tile_pos.x,item->tile_pos.y,draw_pos);

        Rectangle mouse_rect = Rectangle{(float)GetMouseX(),(float)GetMouseY(),2,2};
        Rectangle item_rect = Rectangle{draw_pos.x,draw_pos.y,item->sprite->GetRect().width,item->sprite->GetRect().height};
        if (CheckCollisionRecs(item_rect,mouse_rect))
        {
            item->mouse_hover = true;
            item->sprite->DrawOutline(RED);
        }
        else
        {
            item->mouse_hover = false;
        }
        
        ccol++;
    }
}

void Inventory::Update()
{
    if (IsKeyPressed(KEY_I))
    {
        ToggleInventory();
    }
    
}

void Inventory::ToggleInventory()
{
    isShowing = !isShowing;
}

std::vector<Item *> *Inventory::Get_Items()
{
    return &Items;
}
