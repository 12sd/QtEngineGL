#ifndef MANAGERTEXTURE_H
#define MANAGERTEXTURE_H

#include "texture.h"

class ManagerTexture
{
public:
    ManagerTexture();
    ~ManagerTexture();
    static ManagerTexture* getInstance();
    void Add(int key, Texture* value);
    Texture* GetValue(int key);
    void Clear();
    void Destroy();

private:
    static ManagerTexture* instance;
    QHash<int, Texture*> hash_tab;
};

#endif // MANAGERTEXTURE_H
