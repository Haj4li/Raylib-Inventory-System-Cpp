#include "Player.h"

// Method to handle player movement
void Player::Movement()
{
    if (IsKeyDown(KEY_A))
    {
        sprite->SetAnimation(animations["player_walk_l"], 15);
        sprite->AnimationPlay(true);
        sprite->position.x -= speed;
    }
    else if (IsKeyDown(KEY_D))
    {
        sprite->SetAnimation(animations["player_walk_r"], 15);
        sprite->AnimationPlay(true);
        sprite->position.x += speed;
    }
    else if (IsKeyDown(KEY_W))
    {
        sprite->SetAnimation(animations["player_walk_t"], 15);
        sprite->AnimationPlay(true);
        sprite->position.y -= speed;
    }
    else if (IsKeyDown(KEY_S))
    {
        sprite->SetAnimation(animations["player_walk_d"], 15);
        sprite->AnimationPlay(true);
        sprite->position.y += speed;
    }
    else
    {
        sprite->AnimationPlay(false);
    }
}

// Constructor for the Player class
Player::Player(Sprite2D* sprite)
{
    this->sprite = sprite;
}

// Method to initialize the player
void Player::Start()
{
    can_move = true;
    inventory = new Inventory(Vector2{ 50, 400 }, 5, 4);
    speed = 3.5;

    // Player settings
    sprite->position.x = 400;
    sprite->position.y = 300;

    // Define player animations
    animations["player_walk_l"] = Animation(9, 1, 10);
    animations["player_walk_t"] = Animation(9, 1, 9);
    animations["player_walk_d"] = Animation(9, 1, 11);
    animations["player_walk_r"] = Animation(9, 1, 12);
}

// Method to update the player's state
void Player::Update()
{
    if (IsKeyPressed(KEY_SPACE))
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

    // Iterate through items in the inventory
    for (auto it = Items->begin(); it != Items->end();)
    {
        if ((*it)->mouse_hover && IsMouseButtonPressed(0) && (*it)->usable) // Use items
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

// Method to draw the player and related information
void Player::Draw()
{
    sprite->Draw();
    inventory->Draw();

    // Draw Health
    std::string _health = "Health: " + std::to_string(health);
    DrawText(_health.c_str(), 20, 50, 20, BLACK);

    // Draw Coins
    std::string _coins = "Coins: " + std::to_string(coins);
    DrawText(_coins.c_str(), 20, 75, 20, BLACK);
}

// Method to pick up an item
void Player::Pickup(Item* item)
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

// Method to check collision with a given rectangle
bool Player::Collision(Rectangle rect)
{
    if (CheckCollisionRecs(sprite->GetRect(), rect))
    {
        return true;
    }
    return false;
}
