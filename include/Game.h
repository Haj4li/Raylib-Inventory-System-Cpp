#include "Player.h"
#include <random>

// Define window dimensions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class Game
{
private:
    Player* player;           // Pointer to the game's player
    Sprite2D* player_sprite;  // Pointer to the player's sprite
    Sprite2D* tile_sheet;     // Pointer to the tile sheet (assuming it's used for something)
    std::vector<Item> items;  // Vector to store items
    std::map<Item*, Vector2> items_in_map; // Map to store items associated with positions

public:
    // Method to call the game object's start function
    void Start();

    // Method to update the game obejcts
    void Update();

    // Method to draw the game screen
    void Draw();

    // Destructor to clean up memory when the game is destroyed
    ~Game()
    {
        delete player;
        delete tile_sheet;
        delete player_sprite;

        // Iterate through the items in the map and delete them
        for (auto it = items_in_map.begin(); it != items_in_map.end(); ++it)
        {
            delete it->first;
        }
        items_in_map.clear(); // Clear the map after deleting items
    }
};
