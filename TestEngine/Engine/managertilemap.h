#ifndef MANAGERTILEMAP_H
#define MANAGERTILEMAP_H

#include <QHash>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include "managersprite.h"
#include "layer.h"

class ManagerTileMap
{
public:
    ManagerTileMap();
    ~ManagerTileMap();
    static ManagerTileMap* getInstance();
    void SetMeshKey(int key);
    void SetShaderKey(int key);
    bool Load(QString filename);
    void Clear();
    void Destroy();
    void Draw();
    void Scroll(float dx = 0, float dy = 0);
private:
    static ManagerTileMap* instance;
    int key_mesh;
    int key_shader;
    QHash<QString, Sprite*> hash_sprite;
    QHash<QString, Layer*> hash_layer;
    int count_x, count_y;
    int tile_width, tile_height;
    QMatrix4x4 proj;
    QMatrix4x4 model;
    float dx, dy;
};

#endif // TILEMAP_H
