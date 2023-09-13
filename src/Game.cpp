#include "Game.h"

Item::Item(std::string name, bool usable, Sprite2D *sprite, Vector2 tile_pos)
{
    this->name = name;
    this->sprite = sprite;
    this->tile_pos = tile_pos;
}

Inventory::Inventory(Vector2 position, unsigned int rows, unsigned int cols)
{
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
    unsigned int ccol = 0,crow = 1;

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
    for (auto it = Items.begin(); it != Items.end();)
    {
        if ((*it)->mouse_hover && IsMouseButtonPressed(0))
        {
            delete *it;
            Items.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void Inventory::ToggleInventory()
{
    isShowing = !isShowing;
}

void Game::Start()
{
    tile_sheet = new Sprite2D("Assets/items.png",1,5);
    tile_sheet->Scale(1,1);
    inventory = new Inventory(Vector2{50,400},5,4);
    inventory->Add_Item(new Item("4",true,tile_sheet,Vector2{1,0}));
    inventory->Add_Item(new Item("1",true,tile_sheet,Vector2{1,1}));
    inventory->Add_Item(new Item("2",true,tile_sheet,Vector2{1,2}));
    inventory->Add_Item(new Item("3",true,tile_sheet,Vector2{1,3}));
    inventory->Add_Item(new Item("3",true,tile_sheet,Vector2{1,3}));
    inventory->Add_Item(new Item("3",true,tile_sheet,Vector2{1,3}));
    inventory->Add_Item(new Item("3",true,tile_sheet,Vector2{1,3}));
    inventory->Add_Item(new Item("3",true,tile_sheet,Vector2{1,3}));
    inventory->Add_Item(new Item("3",true,tile_sheet,Vector2{1,3}));
    inventory->Add_Item(new Item("3",true,tile_sheet,Vector2{1,3}));
    inventory->Add_Item(new Item("3",true,tile_sheet,Vector2{1,3}));
    inventory->Add_Item(new Item("3",true,tile_sheet,Vector2{1,3}));
    
}

void Game::Update()
{
    inventory->Update();
}

void Game::Draw()
{
    inventory->Draw();
}
