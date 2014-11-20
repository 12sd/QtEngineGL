#ifndef TILEMAP_H
#define TILEMAP_H

#include <QHash>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include "managersprite.h"
#include "layer.h"

class TileMap
{
public:
    TileMap();
    ~TileMap();
    void SetMeshKey(int key);
    void SetShaderKey(int key);
    bool Load(QString filename);
    void Destroy();
private:
    int key_mesh;
    int key_shader;
    QHash<QString, Sprite*> hash_sprite;
    QHash<QString, Layer*> hash_layer;
    int count_x, count_y;
    int tile_width, tile_height;
};

#endif // TILEMAP_H
