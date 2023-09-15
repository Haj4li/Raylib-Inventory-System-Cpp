#include <map>
#include "Inventory.h"

class Player
{
    private:
        Sprite2D* sprite;
        Inventory* inventory;
        unsigned int health = 20;
        unsigned int coins = 0;
        float speed = 5;
        bool can_move= false;
        void Movement();

        std::map<std::string,Animation> animations;
    public:
        Player(Sprite2D* sprite);
        void Start();
        void Update();
        void Draw();
        void Pickup(Item* item);
        bool Collision(Rectangle rect);


};