#include <map>
#include "Inventory.h"

class Player
{
private:
    Sprite2D* sprite;       // Pointer to the player's sprite
    Inventory* inventory;   // Pointer to the player's inventory
    unsigned int health = 20;  // Player's health
    unsigned int coins = 0;    // Player's coins
    float speed = 5;           // Player's speed
    bool can_move = false;     // Flag indicating if the player can move
    void Movement();           // Private method for handling player movement

    std::map<std::string, Animation> animations; // Map to store player animations

public:
    Player(Sprite2D* sprite);  // Constructor
    void Start();              // Method for initializing the player
    void Update();             // Method for updating the player's state
    void Draw();               // Method for drawing the player
    void Pickup(Item* item);   // Method for picking up an item and adding it to the inventory
    bool Collision(Rectangle rect); // Method for checking collision with a given rectangle
};
