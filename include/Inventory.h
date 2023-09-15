#include "Sprite2D.h"
#include <string>
#include <vector>

struct Item
{
    std::string name;
    bool usable = false;
    Vector2 tile_pos = {0,0};
    Sprite2D* sprite;

    unsigned short add_health = 0;
    float add_speed = 0;
    float duration = 0;
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
        Sprite2D* Inventory_BG;

    public:
        Inventory(Vector2 position,unsigned int rows,unsigned int cols);
        void Add_Item(Item* item);
        void Draw();
        void Update();
        void ToggleInventory();
        std::vector<Item*>* Get_Items();


};