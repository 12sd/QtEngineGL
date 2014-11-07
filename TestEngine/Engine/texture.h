#ifndef TEXTURE_H
#define TEXTURE_H

#include <QString>
#include <QImage>
#include <QOpenGLFunctions>
#include <QDebug>

class Texture
{
public:
    Texture();
    Texture(QString filename);
    ~Texture();
    bool Load(QString filename);
    void Create();
    void Bind();
    void UnBind();
    unsigned int GetId();
    int GetWidth();
    int GetHeight();

private:
    QImage img;
    unsigned int id;
};

#endif // TEXTURE_H
