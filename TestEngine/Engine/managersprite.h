#ifndef MANAGERSPRITE_H
#define MANAGERSPRITE_H

#include "sprite.h"

class ManagerSprite
{
public:
    ManagerSprite();
    ~ManagerSprite();
    static ManagerSprite* getInstance();
    void Add(int key, Sprite* value);
    Sprite* GetValue(int key);
    void Clear();
    void Destroy();

private:
    static ManagerSprite* instance;
    QHash<int, Sprite*> hash_tab;
};

#endif // MANAGERSPRITE_H
