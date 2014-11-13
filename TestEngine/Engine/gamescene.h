#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QString>

class GameScene
{
public:
    GameScene();
    bool Load(QString filename);
    void Update();
    void Draw();
};

#endif // GAMESCENE_H
