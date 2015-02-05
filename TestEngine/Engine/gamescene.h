#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

#include "managermesh.h"
#include "managershader.h"
#include "managertexture.h"
#include "managersprite.h"
#include "managergameobject.h"
#include "managertilemap.h"
#include "creatorgameobject.h"

class GameScene
{
public:
    GameScene();
    bool Load(QString filename, CreatorGameObject* creator);
    void Update();
    void Draw();
    void Draw(QRectF rect);
};

#endif // GAMESCENE_H
