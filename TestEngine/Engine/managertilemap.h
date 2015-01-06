#ifndef MANAGERTILEMAP_H
#define MANAGERTILEMAP_H

#include <QHash>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QtMath>
#include "managersprite.h"
#include "layer.h"
#include "transformer.h"

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
    bool CheckCollision(QString layer_name, QVector3D pos, QVector3D future_pos, QRectF bound, QVector3D& res_pos, bool& ground, float& gravity);
    bool IntersectsRect(QRectF rect1, QRectF rect2);
    QRectF IntersectedRect(QRectF rect1, QRectF rect2);
private:
    static ManagerTileMap* instance;
    int key_mesh;
    int key_shader;
    QList<Sprite*> list_sprite;
    QList<DataLayer> list_layer;
    int count_x, count_y;
    int tile_width, tile_height;
    QMatrix4x4 proj;
};

#endif // TILEMAP_H
