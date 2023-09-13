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

void Game::Start()
{
    
    tile_sheet = new Sprite2D("Assets/items.png",1,5);
    player_sprite = new Sprite2D("Assets/Player.png",21,13);
    tile_sheet->Scale(1,1);

    // Add some items to the item list
    items.push_back(Item("Gem",false,tile_sheet,Vector2{1,0}));
    items.push_back(Item("Coin",false,tile_sheet,Vector2{1,1}));
    items.push_back(Item("Fish",true,tile_sheet,Vector2{1,2}));
    items.push_back(Item("Book",false,tile_sheet,Vector2{1,3}));
    items.push_back(Item("Candy",true,tile_sheet,Vector2{1,4}));

    items[2].add_health = 10;
    items[4].add_speed = 0.5;

    // Add items to map item list
    // Random numbers
    std::random_device rd;  // Seed generator from hardware or system
    std::mt19937 mt(rd()); // Mersenne Twister engine

    // We need to make sure that the random position is visible in the screen x  and y
    std::uniform_int_distribution<int> rand_item(0, items.size()-1);
    std::uniform_int_distribution<int> disty(50, WINDOW_HEIGHT-50);
    std::uniform_int_distribution<int> distx(50, WINDOW_WIDTH-50);
    std::cout << "Mapping" << std::endl;
    for (int i = 0; i < 15; i++)
    {
        items_in_map[new Item(items[rand_item(mt)])] = Vector2{(float)distx(mt),(float)disty(mt)};
    }
    

    std::cout << "player" << std::endl;
    player = new Player(player_sprite);
    player->Start();
    
    
}

void Game::Update()
{
    if (IsKeyPressed(KEY_E))
    {
        std::vector<Item*> itemsToRemove;

        for (const auto &item : items_in_map)
        {
            Rectangle rect = Rectangle{ item.second.x, item.second.y, item.first->sprite->GetRect().width, item.first->sprite->GetRect().height };
            if (player->Collision(rect))
            {
                player->Pickup(item.first);
                itemsToRemove.push_back(item.first);
            }
        }

        // Remove items from the map after the loop
        for (const auto &item : itemsToRemove)
        {
            items_in_map.erase(item);
        }
    }

    
    player->Update();
}

void Game::Draw()
{
    for (const auto &item : items_in_map)
    {
        if (items_in_map.find(item.first) == items_in_map.end())
        {
            continue;
        }
        item.first->sprite->DrawRectAt(item.first->tile_pos.x, item.first->tile_pos.y,item.second);
        Rectangle rect = Rectangle{item.second.x,item.second.y,item.first->sprite->GetRect().width,item.first->sprite->GetRect().height};
        if (player->Collision(rect)){
            item.first->sprite->DrawOutline(BLACK);
        }
    }
    player->Draw();
}

void Player::Movement()
{
    if (IsKeyDown(KEY_A))
    {
        sprite->SetAnimation(animations["player_walk_l"],15);
        sprite->AnimationPlay(true);
        sprite->position.x -=speed;
    }
    else if (IsKeyDown(KEY_D))
    {
        sprite->SetAnimation(animations["player_walk_r"],15);
        sprite->AnimationPlay(true);
        sprite->position.x +=speed;
    }
    else if (IsKeyDown(KEY_W))
    {
        sprite->SetAnimation(animations["player_walk_t"],15);
        sprite->AnimationPlay(true);
        sprite->position.y -=speed;
    }
    else if (IsKeyDown(KEY_S))
    {
        sprite->SetAnimation(animations["player_walk_d"],15);
        sprite->AnimationPlay(true);
        sprite->position.y +=speed;
    }
    else
    {
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
    speed = 3.5;
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

    std::vector<Item*>* Items = inventory->Get_Items();

    for (auto it = Items->begin(); it != Items->end();)
    {
        if ((*it)->mouse_hover && IsMouseButtonPressed(0) && (*it)->usable)
        {
            health += (*it)->add_health;
            speed += (*it)->add_speed;
            delete *it;
            Items->erase(it);
        }
        else
        {
            it++;
        }
    }
    
}

void Player::Draw()
{
    sprite->Draw();
    inventory->Draw();
    // Draw Health
    std::string _health = "Health : " + std::to_string(health);
    DrawText(_health.c_str(),20,50,20,BLACK);
    // Draw Coins 
    std::string _coins = "Coins : " + std::to_string(coins);
    DrawText(_coins.c_str(),20,75,20,BLACK);
}

void Player::Pickup(Item *item)
{
    if (item->name == "Coin")
    {
        delete item;
        coins += 10;
    }
    else
    {
        inventory->Add_Item(item);
    }
    
}

bool Player::Collision(Rectangle rect)
{
    if (CheckCollisionRecs(sprite->GetRect(),rect))
    {
        return true;
    }
    return false;
}
