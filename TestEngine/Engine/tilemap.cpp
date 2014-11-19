#include "tilemap.h"

TileMap::TileMap()
{
    key_mesh = 0;
    key_shader = 0;
    count_x = count_y = 0;
    tile_width = tile_height = 0;
}

TileMap::~TileMap()
{
}

void TileMap::SetMeshKey(int key)
{
    key_mesh = key;
}

void TileMap::SetShaderKey(int key)
{
    key_shader = key;
}

bool TileMap::Load(QString filename)
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
            //Считка параметров карты
            if (reader.name()=="map")
            {
                if (reader.attributes().hasAttribute("width") && reader.attributes().hasAttribute("height") && reader.attributes().hasAttribute("tilewidth") && reader.attributes().hasAttribute("tileheight"))
                {
                    count_x = reader.attributes().value("width").toInt();
                    count_y = reader.attributes().value("height").toInt();
                    tile_width = reader.attributes().value("tilewidth").toInt();
                    tile_height = reader.attributes().value("tileheight").toInt();
                    qDebug()<<count_x<<count_y<<tile_width<<tile_height;
                }
            }
            //Считка тайлесетов
            if (reader.name()=="tileset")
            {
                if (reader.attributes().hasAttribute("name"))
                {
                    QString name = reader.attributes().value("name").toString();
                    reader.readNext();
                    reader.readNext();
                    if (reader.isStartElement() && reader.name()=="image")
                    {
                        if (reader.attributes().hasAttribute("tid"))
                        {
                            int id = reader.attributes().value("tid").toInt();
                            Sprite* sprite = new Sprite();
                            sprite->SetMeshKey(key_mesh);
                            sprite->SetShaderKey(key_shader);
                            sprite->SetTextureKey(id);
                            sprite->Create();
                            hash_sprite.insert(name,sprite);
                            qDebug()<<"TileSet:"<<name<<"Id:"<<id;
                        }
                    }

                }
            }
            //Считка слоёв
            if (reader.name()=="layer")
            {
                if (reader.attributes().hasAttribute("name"))
                {
                    QString name = reader.attributes().value("name").toString();
                    reader.readNext();
                    reader.readNext();
                    if (reader.isStartElement() && reader.name()=="data")
                    {
                        Layer* layer = new Layer();
                        layer->Create(count_x, count_y); //ERROR
                        for (int i=0; i<count_x; i++)
                        {
                            for (int j=0; j<count_y; j++)
                            {
                                reader.readNext();
                                reader.readNext();
                                if (reader.isStartElement() && reader.name()=="tile")
                                {
                                    if (reader.attributes().hasAttribute("gid"))
                                    {
                                        qDebug()<<name<<"i:"<<i<<"j:"<<j<<reader.attributes().value("gid").toInt();
                                        layer->SetValue(i, j, reader.attributes().value("gid").toInt());
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    f.close();

    if (reader.hasError())
        return false;

    return true;
}
