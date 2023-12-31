#include "Game.h"

// Method to initialize the game
void Game::Start()
{
    // Create tile sheet and player sprite
    tile_sheet = new Sprite2D("Assets/items.png", 1, 5);
    player_sprite = new Sprite2D("Assets/Player.png", 21, 13);
    tile_sheet->Scale(1, 1);

    // Add some items to the item list
    items.push_back(Item("Gem", false, tile_sheet, Vector2{ 1, 0 }));
    items.push_back(Item("Coin", false, tile_sheet, Vector2{ 1, 1 }));
    items.push_back(Item("Fish", true, tile_sheet, Vector2{ 1, 2 }));
    items.push_back(Item("Book", false, tile_sheet, Vector2{ 1, 3 }));
    items.push_back(Item("Candy", true, tile_sheet, Vector2{ 1, 4 }));

    items[2].add_health = 10;
    items[4].add_speed = 0.5;

    // Add items to the map item list with random positions
    std::random_device rd;       // Seed generator from hardware or system
    std::mt19937 mt(rd());       // Mersenne Twister engine

    std::uniform_int_distribution<int> rand_item(0, items.size() - 1);
    std::uniform_int_distribution<int> disty(50, WINDOW_HEIGHT - 50);
    std::uniform_int_distribution<int> distx(50, WINDOW_WIDTH - 50);

    for (int i = 0; i < 15; i++)
    {
        items_in_map[new Item(items[rand_item(mt)])] = Vector2{(float)distx(mt), (float)disty(mt)};
    }

    // Create and start the player
    player = new Player(player_sprite);
    player->Start();
}

// Method to update the game state
void Game::Update()
{
    // Check if the 'E' key is pressed to pick up items
    if (IsKeyPressed(KEY_E))
    {
        std::vector<Item*> itemsToRemove;

        // Loop through items in the map
        for (const auto& item : items_in_map)
        {
            Rectangle rect = Rectangle{item.second.x, item.second.y, item.first->sprite->GetRect().width, item.first->sprite->GetRect().height};
            if (player->Collision(rect))
            {
                player->Pickup(item.first);
                itemsToRemove.push_back(item.first);
            }
        }

        // Remove items from the map after the loop
        for (const auto& item : itemsToRemove)
        {
            items_in_map.erase(item);
        }
    }

    // Update the player
    player->Update();
}

// Method to draw the game
void Game::Draw()
{
    // Loop through items in the map and draw them
    for (const auto& item : items_in_map)
    {
        if (items_in_map.find(item.first) == items_in_map.end())
        {
            continue;
        }
        item.first->sprite->DrawRectAt(item.first->tile_pos.x, item.first->tile_pos.y, item.second);
        Rectangle rect = Rectangle{item.second.x, item.second.y, item.first->sprite->GetRect().width, item.first->sprite->GetRect().height};
        if (player->Collision(rect))
        {
            item.first->sprite->DrawOutline(BLACK);
        }
    }

    // Draw the player
    player->Draw();
}
