#include "Player.h"

#include <random>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


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
            for (const auto &item : items_in_map)
            {
                items_in_map.erase(item.first);
                delete item.first;
                
            }
        }
};

