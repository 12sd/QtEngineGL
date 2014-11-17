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

class GameScene
{
public:
    GameScene();
    bool Load(QString filename);
    void Update();
    void Draw();
};

#endif // GAMESCENE_H
