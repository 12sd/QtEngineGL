#ifndef MANAGERTILEMAP_H
#define MANAGERTILEMAP_H

#include <QHash>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QtMath>
#include "setting.h"
#include "managersprite.h"
#include "layer.h"
#include "transformer.h"
#include "camera.h"

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
    void Draw(QRectF rect);
    QVector2D GetTileIJ(QVector3D pos);
    QRectF GetTilePos(QVector2D ij);
    bool CollisionX(QString layer_name, QVector3D& pos, QRectF bound, QVector2D dir);
    bool CollisionY(QString layer_name, QVector3D& pos, QRectF bound, QVector2D dir, float& gravity, bool& ground);
    QVector<Tile> GetTiles(QString layer_name, QRectF bound);
private:
    static ManagerTileMap* instance;
    int key_mesh;
    int key_shader;
    QList<Sprite*> list_sprite;
    QList<DataLayer> list_layer;
    int count_x, count_y;
    int tile_width, tile_height;
};

#endif // TILEMAP_H
