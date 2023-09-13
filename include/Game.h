#include "Sprite2D.h"
#include <string>
#include <vector>
#include <map>



struct Item
{
    std::string name;
    bool usable = false;
    Vector2 tile_pos = {0,0};
    Sprite2D* sprite;

    unsigned short add_health = 0;
    unsigned short add_speed = 0;
    unsigned short duration = 0;
    bool mouse_hover = false;

    Item(std::string name,bool usable, Sprite2D* sprite,Vector2 tile_pos);
};

class Inventory
{
    private:
        Vector2 position;
        unsigned short inventory_rows = 0;
        unsigned short inventory_cols = 0;
        std::vector<Item*> Items;
        bool isShowing = false;

    public:
        Inventory(Vector2 position,unsigned int rows,unsigned int cols);
        void Add_Item(Item* item);
        void Draw();
        void Update();
        void ToggleInventory();


};

class Player
{
    private:
        Sprite2D* sprite;
        Inventory* inventory;
        unsigned int health = 20;
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


};

class Game
{
    private:
        Player* player;
        Sprite2D* player_sprite;
        Sprite2D* tile_sheet;
        std::vector<Item> items;
        std::map<Item*,Vector2> items_in_map;


    public:
        void Start();
        void Update();
        void Draw();
        ~Game()
        {
            delete player;
            delete tile_sheet;
            delete player_sprite;
        }
};

