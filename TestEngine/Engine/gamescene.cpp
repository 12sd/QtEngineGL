#include "gamescene.h"

GameScene::GameScene()
{
}

bool GameScene::Load(QString filename)
{
    QFile f(filename);
    if (!f.open(QIODevice::ReadOnly))
        return false;

    QXmlStreamReader reader(&f);

    while(!reader.atEnd() && !reader.hasError())
    {
        reader.readNext();
        if (reader.isStartElement())
        {
            //Считка массива вершин
            if (reader.name()=="Mesh")
            {
                if (reader.attributes().hasAttribute("id"))
                {
                    qDebug()<<"Tag:"<<reader.name()<<"Id:"<<reader.attributes().value("id").toString();
                    Mesh* mesh = new Mesh();
                    mesh->Create();
                    ManagerMesh::getInstance()->Add(reader.attributes().value("id").toInt(),mesh);
                }
            }
            //Считка шейдера
            if (reader.name()=="Shader")
            {
                if (reader.attributes().hasAttribute("id"))
                {
                    qDebug()<<"Tag:"<<reader.name()<<"Id:"<<reader.attributes().value("id").toString();
                    ManagerShader::getInstance()->Add(reader.attributes().value("id").toInt(),new Shader());
                }
            }
            //Считка текстуры
            if (reader.name()=="Texture")
            {
                if (reader.attributes().hasAttribute("id"))
                {
                    int id = reader.attributes().value("id").toInt();
                    qDebug()<<"Tag:"<<reader.name()<<"Id:"<<id;
                    reader.readNext();
                    QString filename = reader.text().toString();
                    qDebug()<<"Path:"<<filename;
                    Texture* texture = new Texture(filename);
                    texture->Create();
                    ManagerTexture::getInstance()->Add(id, texture);
                }
            }
            //Считка спрайта
            if (reader.name()=="Sprite")
            {
                if (reader.attributes().hasAttribute("id"))
                {
                    int id = reader.attributes().value("id").toInt();
                    qDebug()<<"Tag:"<<reader.name()<<"Id:"<<id;
                    Sprite* sprite = new Sprite();
                    if (reader.attributes().hasAttribute("mid"))
                    {
                        sprite->SetMeshKey(reader.attributes().value("mid").toInt());
                    }
                    if (reader.attributes().hasAttribute("tid"))
                    {
                        sprite->SetTextureKey(reader.attributes().value("tid").toInt());
                    }
                    if (reader.attributes().hasAttribute("sid"))
                    {
                        sprite->SetShaderKey(reader.attributes().value("sid").toInt());
                    }
                    sprite->Create();
                    ManagerSprite::getInstance()->Add(id, sprite);
                }
            }
        }

    }
    f.close();

    if (reader.hasError())
        return false;

    return true;
}
