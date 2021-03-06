#-------------------------------------------------
#
# Project created by QtCreator 2014-08-21T07:57:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BattleShip
TEMPLATE = app


SOURCES += main.cpp \
    mainform.cpp \
    Engine/fps.cpp \
    Engine/gameobject.cpp \
    Engine/texture.cpp \
    Engine/managermouse.cpp \
    statusgame.cpp \
    Engine/mesh.cpp \
    Engine/managermesh.cpp \
    Engine/managertexture.cpp \
    Engine/shader.cpp \
    Engine/managershader.cpp \
    Engine/sprite.cpp \
    Engine/managersprite.cpp \
    testcreatorgameobject.cpp \
    testgameobject.cpp \
    Engine/gamescene.cpp \
    Engine/managerkeyboard.cpp \
    Engine/layer.cpp \
    Engine/managertilemap.cpp \
    Engine/ForDebug/gridcoord.cpp \
    Engine/managergameobject.cpp \
    Engine/creatorgameobject.cpp \
    Engine/transformer.cpp \
    Engine/setting.cpp \
    Engine/camera.cpp \
    Engine/geometry.cpp \
    Engine/object3d.cpp \
    cube.cpp \
    Engine/managercamera.cpp

HEADERS  += mainform.h \
    Engine/fps.h \
    Engine/gameobject.h \
    Engine/texture.h \
    Engine/managermouse.h \
    statusgame.h \
    Engine/mesh.h \
    Engine/managermesh.h \
    Engine/managertexture.h \
    Engine/shader.h \
    Engine/managershader.h \
    Engine/sprite.h \
    Engine/managersprite.h \
    testcreatorgameobject.h \
    testgameobject.h \
    Engine/gamescene.h \
    Engine/managerkeyboard.h \
    Engine/layer.h \
    Engine/managertilemap.h \
    Engine/ForDebug/gridcoord.h \
    Engine/managergameobject.h \
    Engine/creatorgameobject.h \
    Engine/transformer.h \
    Engine/setting.h \
    Engine/camera.h \
    Engine/geometry.h \
    Engine/object3d.h \
    cube.h \
    Engine/managercamera.h

FORMS    +=

RESOURCES += \
    resources.qrc
