#include "Game.h"

Item::Item(std::string name, bool usable, Sprite2D *sprite, Vector2 tile_pos)
{
    this->name = name;
    this->sprite = sprite;
    this->tile_pos = tile_pos;
    this->usable = usable;
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
        if ((*it)->mouse_hover && IsMouseButtonPressed(0) && (*it)->usable)
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
    player_sprite = new Sprite2D("Assets/Player.png",21,13);
    tile_sheet->Scale(1,1);

    // Add some items to the item list
    items.push_back(Item("1",true,tile_sheet,Vector2{1,0}));
    items.push_back(Item("2",true,tile_sheet,Vector2{1,1}));
    items.push_back(Item("3",true,tile_sheet,Vector2{1,2}));
    items.push_back(Item("4",true,tile_sheet,Vector2{1,3}));
    items.push_back(Item("5",true,tile_sheet,Vector2{1,4}));
    
    player = new Player(player_sprite);
    player->Start();
    
    
}

void Game::Update()
{
    if (IsKeyPressed(KEY_Q))
    {
        player->Pickup(new Item(items[0]));
    }
    player->Update();
}

void Game::Draw()
{
    player->Draw();
}

void Player::Movement()
{
    if (IsKeyDown(KEY_A))
    {
        // You can set the animation speed with SetAnimation function
        sprite->SetAnimation(animations["player_walk_l"],10);
        sprite->AnimationPlay(true);
        sprite->position.x -=speed;
    }
    else if (IsKeyDown(KEY_D))
    {
        sprite->SetAnimation(animations["player_walk_r"],10);
        sprite->AnimationPlay(true);
        sprite->position.x +=speed;
    }
    else if (IsKeyDown(KEY_W))
    {
        sprite->SetAnimation(animations["player_walk_t"],10);
        sprite->AnimationPlay(true);
        sprite->position.y -=speed;
    }
    else if (IsKeyDown(KEY_S))
    {
        sprite->SetAnimation(animations["player_walk_d"],10);
        sprite->AnimationPlay(true);
        sprite->position.y +=speed;
    }
    else
    {
        // Stop animation when player stop moving
        sprite->AnimationPlay(false);
    }
}

Player::Player(Sprite2D *sprite)
{
    this->sprite = sprite;
}

void Player::Start()
{
    can_move = true;
    inventory = new Inventory(Vector2{50,400},5,4);
    // Player settings
    sprite->position.x = 400;
    sprite->position.y = 300;

    animations["player_walk_l"] = Animation(9,1,10);
    animations["player_walk_t"] = Animation(9,1,9);
    animations["player_walk_d"] = Animation(9,1,11);
    animations["player_walk_r"] = Animation(9,1,12);
}

void Player::Update()
{
    if(IsKeyPressed(KEY_SPACE))
    {
        can_move = !can_move;
    }
    // Movement
    if (can_move)
    {
        Movement();
    }
    inventory->Update();
    
}

void Player::Draw()
{
    sprite->Draw();
    inventory->Draw();
}

void Player::Pickup(Item *item)
{
    inventory->Add_Item(item);
}
