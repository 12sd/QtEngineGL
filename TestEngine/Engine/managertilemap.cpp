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
    model.setToIdentity();
    model.scale(tile_width, tile_height, 0.0f);
    model.translate(0.5f+dx, 0.5f+dy, 0.0f);

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
    }
}

void ManagerTileMap::Scroll(float dx, float dy)
{
    this->dx+=dx;
    this->dy+=dy;
    //model.translate(dx, dy);
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

QVector<Tile> ManagerTileMap::GetTiles(QString layer_name, QVector3D pos)
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

    QVector2D tmp_ij = this->GetTileIJ(pos);
    for (int i=0; i<9; i++)
    {
        int tmp_j = i%3;
        int tmp_i = i/3;
        QVector2D ij = QVector2D(tmp_ij.x()+(tmp_j-1), tmp_ij.y()+(tmp_i-1));
        int id = layer->GetValue(ij.x(), ij.y());
        QRectF rect = this->GetTilePos(ij);
        Tile t;
        t.id = id;
        t.ij = ij;
        t.pos = rect;
        tiles.append(t);
    }

//    qDebug()<<"Original tiles size:"<<tiles.size();
//    for (int i=0; i<tiles.size(); i++)
//    {
//        qDebug()<<tiles.value(i).id<<tiles.value(i).ij<<tiles.value(i).pos;
//    }

    tiles.removeAt(4);
    tiles.insert(6, tiles.value(2));
    tiles.removeAt(2);
    Tile tmp_t = tiles.value(4);
    tiles.replace(4, tiles.value(6));
    tiles.replace(6, tmp_t);
    tmp_t = tiles.value(0);
    tiles.replace(0, tiles.value(4));
    tiles.replace(4, tmp_t);

    qDebug()<<"Log tiles size:"<<tiles.size();
    for (int i=0; i<tiles.size(); i++)
    {
        qDebug()<<tiles.value(i).id<<tiles.value(i).ij<<tiles.value(i).pos;
    }

    return tiles;
}

bool ManagerTileMap::CheckCollision(QString layer_name, QVector3D pos, QRectF bound, QVector3D& res_pos)
{
    bool flag = false;
    res_pos = pos;
    QVector<Tile> tiles = this->GetTiles(layer_name, pos);
    for (int i=0; i<tiles.size(); i++)
    {
        int id = tiles.value(i).id;
        if (id!=0)
        {
            QRectF tile_rect(tiles.value(i).ij.x(), tiles.value(i).ij.y(), tile_width, tile_height);
            if (bound.intersects(tile_rect))
            {
                flag = true;
                QRectF intersection = bound.intersected(tile_rect);
                if (i==0) //Down collision
                {
                    res_pos.setX(res_pos.x());
                    res_pos.setY(res_pos.y()+intersection.size().height());
                }else
                if (i==1) //Up collision
                {
                    res_pos.setX(res_pos.x());
                    res_pos.setY(res_pos.y()-intersection.size().height());
                }else
                if (i==2) //Left collision
                {
                    res_pos.setX(res_pos.x()+intersection.size().width());
                    res_pos.setY(res_pos.y());
                }else
                if (i==3) //Right collision
                {
                    res_pos.setX(res_pos.x()-intersection.size().width());
                    res_pos.setY(res_pos.y());
                }else
                if (intersection.size().width()>intersection.size().height()) //Diagonal
                {
                    float intersectionHeight;
                    if (i>5)
                    {
                        intersectionHeight = intersection.size().height();
                    }else
                    {
                        intersectionHeight = -intersection.size().height();
                    }
                    res_pos.setX(res_pos.x());
                    res_pos.setY(res_pos.y()+intersectionHeight);
                }else //Diagonal
                {
                    float intersectionWidth;
                    if (i==6 || i==4)
                    {
                        intersectionWidth = intersection.size().width();
                    }else
                    {
                        intersectionWidth = -intersection.size().width();
                    }
                    res_pos.setX(res_pos.x()+intersectionWidth);
                    res_pos.setY(res_pos.y());
                }
            }
        }
    }

    return flag;
}
