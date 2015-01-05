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
    QVector2D GetTileIJ(QVector3D pos);
    QRectF GetTilePos(QVector2D ij);
    QVector<Tile> GetTiles(QString layer_name, QVector3D pos);
    bool CheckCollision(QString layer_name, QVector3D pos, QRectF bound, QVector3D& res_pos);
private:
    static ManagerTileMap* instance;
    int key_mesh;
    int key_shader;
    QList<Sprite*> list_sprite;
    QList<DataLayer> list_layer;
    int count_x, count_y;
    int tile_width, tile_height;
    QMatrix4x4 proj;
    QMatrix4x4 model;
    float dx, dy;
};

#endif // TILEMAP_H
