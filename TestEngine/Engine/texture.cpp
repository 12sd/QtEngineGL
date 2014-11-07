#include "texture.h"

Texture::Texture()
{
    id = 0;
}

Texture::Texture(QString filename)
{
    id = 0;
    Load(filename);
}

Texture::~Texture()
{
    qDebug()<<"~Texture";
}

bool Texture::Load(QString filename)
{
    if (!img.load(filename))
        return false;
    img=img.convertToFormat(QImage::Format_RGBA8888);
    img=img.mirrored();
    return true;
}

unsigned int Texture::GetId()
{
    return id;
}

void Texture::Create()
{
    glGenTextures(1,&id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::UnBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::GetWidth()
{
    img.width();
}

int Texture::GetHeight()
{
    img.height();
}
