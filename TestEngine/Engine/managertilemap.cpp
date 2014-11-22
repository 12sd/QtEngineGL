#include "managertilemap.h"

ManagerTileMap* ManagerTileMap::instance=0;

ManagerTileMap::ManagerTileMap()
{
    dx = dy = 0;
    key_mesh = 0;
    key_shader = 0;
    count_x = count_y = 0;
    tile_width = tile_height = 0;
    proj.setToIdentity();
    proj.ortho(0, 800, 0, 600, -1, 1);
    model.setToIdentity();
}

ManagerTileMap::~ManagerTileMap()
{
    Clear();
    qDebug()<<"~TileMap";
}

ManagerTileMap* ManagerTileMap::getInstance()
{
    if (!instance)
        instance = new ManagerTileMap();
    return instance;
}

void ManagerTileMap::Destroy()
{
    if (instance)
    {
        delete instance;
    }
}

void ManagerTileMap::SetMeshKey(int key)
{
    key_mesh = key;
}

void ManagerTileMap::SetShaderKey(int key)
{
    key_shader = key;
}

bool ManagerTileMap::Load(QString filename)
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
                        layer->Create(count_x, count_y);
                        int i = 0;
                        int j1, j2;
                        j1 = j2 = 0;
                        while(i<count_x*count_y)
                        {
                            reader.readNext();
                            //qDebug()<<reader.name()<<reader.text()<<"--";
                            if (reader.isStartElement() && reader.name()=="tile")
                            {
                                if (reader.attributes().hasAttribute("gid"))
                                {
                                    //qDebug()<<"name:"<<name<<"tile:"<<reader.attributes().value("gid").toInt();
                                    layer->SetValue(j1, j2, reader.attributes().value("gid").toInt());
                                    j2++;
                                    if (j2==count_x)
                                    {
                                        j1++;
                                        j2 = 0;
                                    }

                                    i++;
                                }
                            }
                        }
                        hash_layer.insert(name, layer);
                        qDebug()<<"Layer:"<<name;
                        for (int i=0;i<count_y;i++)
                        {
                            for (int j=0;j<count_x;j++)
                            {
                                qDebug()<<layer->GetValue(i, j);
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

void ManagerTileMap::Clear()
{
    QHash<QString, Sprite*>::iterator it_s = hash_sprite.begin();
    while (it_s != hash_sprite.end())
    {
        delete it_s.value();
        it_s++;
    }
    hash_sprite.clear();

    QHash<QString, Layer*>::iterator it_l = hash_layer.begin();
    while (it_l != hash_layer.end())
    {
        delete it_l.value();
        it_l++;
    }
    hash_layer.clear();
}

void ManagerTileMap::Draw()
{
    model.setToIdentity();
    model.scale(tile_width, tile_height, 0.0f);
    model.translate(0.5f+dx, 0.5f+dy, 0.0f);
    QHash<QString, Layer*>::iterator it_l = hash_layer.begin();
    while (it_l != hash_layer.end())
    {
        Layer* layer = it_l.value();
        for (int i=count_y-1; i>=0; i--)
        {
            for (int j=0; j<count_x; j++)
            {
                Sprite* sprite = 0;
                int id = layer->GetValue(i, j);
                int tmp_summa = 0;
                QHash<QString, Sprite*>::iterator it_s = hash_sprite.begin();
                while (it_s!=hash_sprite.end())
                {
                    sprite = it_s.value();
                    int tmp = sprite->GetTexture()->GetWidth()/tile_width*sprite->GetTexture()->GetHeight()/tile_height;
                    if ((tmp_summa+tmp)>=id)
                        break;
                    else
                        tmp_summa+=tmp;
                    it_s++;
                }
                if (sprite!=0 && id!=0)
                {
                    int tmp_x = sprite->GetTexture()->GetWidth()/tile_width;
                    int tmp_y = sprite->GetTexture()->GetHeight()/tile_height;
                    int tmp_id = tmp_x*tmp_y-(id-tmp_summa);
                    id = id-tmp_summa;
                    int frame_y = tmp_id/tmp_x;
                    int frame_x = (tmp_x*tmp_y)-(frame_y*tmp_x)-tmp_id;
                    sprite->Bind(tile_width, tile_height, frame_x-1, frame_y);
                    sprite->GetShader()->setUniformValue(sprite->GetShader()->GetNameMatrixPos().toStdString().c_str(), proj * model);
                    glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh()->GetCountVertex());
                }
                model.translate(1,0,0);
            }
            model.setToIdentity();
            model.scale(tile_width, tile_height, 0);
            model.translate(0.5f+dx, 0.5f+dy, 0.0f);
            model.translate(0.0f, count_y-i, 0.0f);

        }
        model.setToIdentity();
        model.scale(tile_width, tile_height, 0);
        model.translate(0.5f+dx, 0.5f+dy, 0.0f);
        it_l++;
    }
}

void ManagerTileMap::Scroll(float dx, float dy)
{
    this->dx+=dx;
    this->dy+=dy;
}

bool ManagerTileMap::Collision(QString layer_name, float pos_x, float pos_y, int width, int height)
{
    //ERROR
    bool flag = false;
    Layer* layer = 0;
    layer = hash_layer.value(layer_name);
    if (layer==0)
        return false;
    qDebug()<<"Y ot"<<int(pos_y+dy)/tile_height<<"Y po"<<int(pos_y+dy+height)/tile_height;
    qDebug()<<"X ot"<<int(pos_x+dx)/tile_width<<"X po"<<int(pos_x+dx+width)/tile_width;
    for (int i=int(pos_y+dy+height)/tile_height; i>int(pos_y+dy)/tile_height; i--)
    {
        for (int j=int(pos_x+dx)/tile_width; j<(int(pos_x+dx+width)/tile_width); j++)
        {
            int id = layer->GetValue(i-1, j-1);
            qDebug()<<"ID"<<id<<"i"<<i<<"j"<<j;
            if (id!=0)
            {
                flag = true;
                return flag;
            }
        }
    }
    return flag;
}
