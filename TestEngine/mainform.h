#ifndef MAINFORM_H
#define MAINFORM_H

#include <QCoreApplication>
#include <QWindow>
#include <QOpenGLFunctions>
#include <QOpenGLPaintDevice>
#include <QPainter>

#include "statusgame.h"
#include "Engine/ForDebug/gridcoord.h"
#include "Engine/setting.h"
#include "Engine/fps.h"
#include "Engine/managermouse.h"
#include "Engine/managerkeyboard.h"
#include "Engine/mesh.h"
#include "Engine/managermesh.h"
#include "Engine/shader.h"
#include "Engine/managershader.h"
#include "Engine/texture.h"
#include "Engine/managertexture.h"
#include "Engine/sprite.h"
#include "Engine/managersprite.h"
#include "Engine/gamescene.h"
#include "Engine/managertilemap.h"
#include "testcreatorgameobject.h"
#include "cube.h"

class MainForm : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MainForm(QWindow *parent = 0);
    ~MainForm();

    virtual void render(QPainter *painter);
    virtual void render();
    virtual void initialize();
    void setAnimating(bool animating);

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event);
    void exposeEvent(QExposeEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent* key);
    void keyReleaseEvent(QKeyEvent* key);

    void resizeEvent(QResizeEvent * event);

private:
    bool m_update_pending;
    bool m_animating;

    QOpenGLContext *m_context;
    QOpenGLPaintDevice *m_device;

    /*
     * Для избавления избыточности
     * это будет описываться в GameScene.Load
    */
    ManagerTileMap* map;
    GameScene level;
    Cube cube;

    GridCoord grid;
};

#endif // MAINFORM_H
