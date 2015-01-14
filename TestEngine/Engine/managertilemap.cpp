#include "managertilemap.h"

ManagerTileMap* ManagerTileMap::instance=0;

ManagerTileMap::ManagerTileMap()
{
    key_mesh = 0;
    key_shader = 0;
    count_x = count_y = 0;
    tile_width = tile_height = 0;
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
                            list_sprite.append(sprite);
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
                        DataLayer data;
                        data.layer_name = name;
                        data.layer = layer;
                        list_layer.append(data);
                        qDebug()<<"Layer:"<<name;
                        for (int i=0;i<count_y;i++)
                        {
                            for (int j=0;j<count_x;j++)
                            {
                                //qDebug()<<layer->GetValue(i, j);
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
    for (int i=0; i<list_layer.size(); i++)
    {
        delete list_layer.value(i).layer;
    }
    list_layer.clear();

    for (int i=0; i<list_sprite.size(); i++)
    {
        delete list_sprite.value(i);
    }
    list_sprite.clear();

}

void ManagerTileMap::Draw()
{
    Transformer tr;
    tr.SetScalX(tile_width);
    tr.SetScalY(tile_height);

    for (int i=0; i<list_layer.size(); i++)
    {
        //Layer* layer = it_l.value();
        Layer* layer = list_layer.value(i).layer;
        for (int i=count_y-1; i>=0; i--)
        {
            for (int j=0; j<count_x; j++)
            {
                Sprite* sprite = 0;
                int id = layer->GetValue(i, j);
                int tmp_summa = 0;
                for (int i=0; i<list_sprite.size(); i++)
                {
                    sprite = list_sprite.value(i);
                    int tmp = sprite->GetTexture()->GetWidth()/tile_width*sprite->GetTexture()->GetHeight()/tile_height;
                    if ((tmp_summa+tmp)>=id)
                        break;
                    else
                        tmp_summa+=tmp;
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
                    sprite->GetShader()->setUniformValue(sprite->GetShader()->GetNameMatrixPos().toStdString().c_str(), Setting::GetProjection()*tr.GetMatrix());
                    glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh()->GetCountVertex());
                }
                tr.MoveX(tile_width);
            }
            tr.SetPosX(0);
            tr.SetPosY((count_y-i)*tile_height);
        }
        tr.SetPosX(0);
        tr.SetPosY(0);
    }
}

QVector2D ManagerTileMap::GetTileIJ(QVector3D pos)
{
    QVector2D res;
    res.setX((int)pos.x()/tile_width);

    float all_height = count_y*tile_height;
    res.setY((int)(all_height-pos.y())/tile_height);
    return res;
}

QRectF ManagerTileMap::GetTilePos(QVector2D ij)
{
    float all_height = count_y*tile_height;
    QRectF res(ij.x()*tile_width, all_height-(ij.y()+1)*tile_height, tile_width, tile_height);
    return res;
}

QVector<Tile> ManagerTileMap::GetTiles(QString layer_name, QRectF bound)
{
    QVector<Tile> tiles;
    Layer* layer = 0;
    for (int i=0; i<list_layer.size(); i++)
    {
        if (list_layer.value(i).layer_name==layer_name)
            layer = list_layer.value(i).layer;
    }
    if (layer==0)
        return tiles;

    QVector2D s = this->GetTileIJ(QVector3D(bound.left(), bound.top(), 0.0f));
    QVector2D f = this->GetTileIJ(QVector3D(bound.left()+bound.width(), bound.top()+bound.height(), 0.0f));

    for (int i=f.y(); i<=s.y(); i++)
    {
        for (int j=s.x(); j<=f.x(); j++)
        {
            Tile tmp;
            tmp.id = layer->GetValue(i, j);
            tmp.ij.setX(j);
            tmp.ij.setY(i);
            tmp.pos = this->GetTilePos(tmp.ij);
            tiles.append(tmp);
        }
    }

//    qDebug()<<"Log tiles size:"<<tiles.size()<<" Pos:"<<bound;
//    for (int i=0; i<tiles.size(); i++)
//    {
//        qDebug()<<tiles.value(i).id<<tiles.value(i).ij<<tiles.value(i).pos;
//    }

    return tiles;
}

bool ManagerTileMap::CollisionX(QString layer_name, QVector3D& pos, QRectF bound, QVector2D dir)
{
    bool flag = false;
    Layer* layer = 0;
    for (int i=0; i<list_layer.size(); i++)
    {
        if (list_layer.value(i).layer_name==layer_name)
            layer = list_layer.value(i).layer;
    }
    if (layer==0)
        return false;

    QVector<Tile> tiles = this->GetTiles(layer_name, bound);
    for (int i=0; i<tiles.size(); i++)
    {
        if (tiles.value(i).id!=0)
        {
            if (bound.intersects(tiles.value(i).pos))
            {
                flag = true;
                QRectF rect = bound.intersected(tiles.value(i).pos);
                if (dir.x()==1)
                {                    
                    pos.setX(pos.x()-rect.width());
                }
                if (dir.x()==-1)
                {                    
                    pos.setX(pos.x()+rect.width());
                }
                return flag;
            }
        }
    }

    return flag;
}

bool ManagerTileMap::CollisionY(QString layer_name, QVector3D& pos, QRectF bound, QVector2D dir, float& gravity, bool& ground)
{
    ground = false;
    bool flag = false;
    Layer* layer = 0;
    for (int i=0; i<list_layer.size(); i++)
    {
        if (list_layer.value(i).layer_name==layer_name)
            layer = list_layer.value(i).layer;
    }
    if (layer==0)
        return false;

    QVector<Tile> tiles = this->GetTiles(layer_name, bound);
    for (int i=0; i<tiles.size(); i++)
    {
        if (tiles.value(i).id!=0)
        {
            if (bound.intersects(tiles.value(i).pos))
            {
                flag = true;
                QRectF rect = bound.intersected(tiles.value(i).pos);
                if (dir.y()==1)
                {                   
                    pos.setY(pos.y()-rect.height());
                }
                if (dir.y()==-1)
                {                    
                    pos.setY(pos.y()+rect.height());
                    gravity = 0;
                    ground = true;
                }
                return flag;
            }
        }
    }

    return flag;
}
