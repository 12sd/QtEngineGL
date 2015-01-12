#include "gamescene.h"

GameScene::GameScene()
{
}

bool GameScene::Load(QString filename, CreatorGameObject* creator)
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
                    Mesh* mesh;
                    if (reader.attributes().hasAttribute("type"))
                    {
                        int type_mesh = reader.attributes().value("type").toInt();
                        if (type_mesh==Vertex_Type)
                        {
                            mesh = new Mesh();
                        }
                        if (type_mesh==Vertex_Texture_Type)
                        {
                            mesh = new Mesh(Vertex_Texture_Type);
                        }

                    }else
                        mesh = new Mesh();
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
            //Считка игровых объектов
            if (reader.name()=="GameObject")
            {
                if (reader.attributes().hasAttribute("type"))
                {
                    uint type = reader.attributes().value("type").toUInt();
                    GameObject* obj = 0;
                    if (creator!=0)
                    {
                        obj = creator->CreateGameObject(type);
                    }
                    if (obj!=0)
                    {
                        if (reader.attributes().hasAttribute("name"))
                        {
                            obj->SetName(reader.attributes().value("name").toString());
                        }
                        qDebug()<<"Tag:"<<reader.name()<<"Type:"<<type<<"Name:"<<obj->GetName();
                        ManagerGameObject::getInstance()->Add(obj->GetName(), obj);
                        QHash<QString,QString> property;

                        //Error
                        /*
                        reader.readNext();
                        while (reader.isEndElement()==false && reader.name()=="GameObject")
                        {
                            if (reader.isStartElement())
                            {
                                QString param = reader.name().toString();
                                reader.readNext();
                                QString value = reader.text().toString();
                                qDebug()<<"NameP="<<param<<"ValueP="<<value;
                                property.insert(param, value);
                            }
                            reader.readNext();
                        }
                        */

                        obj->Init(property);
                    }else
                        qDebug()<<"Error Create GameObject";

                }
            }
        }

    }
    f.close();

    if (reader.hasError())
        return false;

    return true;
}
