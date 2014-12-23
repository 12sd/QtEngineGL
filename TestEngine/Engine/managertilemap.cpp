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

bool ManagerTileMap::CollisionX(QString layer_name, QVector2D pos, int width, int height, bool right, QVector2D* res_pos)
{
    //ERROR
    bool flag = false;
    Layer* layer = 0;
    for (int i=0; i<list_layer.size(); i++)
    {
        if (list_layer.value(i).layer_name==layer_name)
            layer = list_layer.value(i).layer;
    }
    if (layer==0)
        return false;
    int s_x, f_x, s_y, f_y;
    int height_ortho = 2.0/proj.column(1).y();
    qDebug()<<"HEIGHT_ortho="<<height_ortho<<"Y_ortho="<<proj.column(1).y();
    pos.setY(height_ortho-pos.y()+dy*tile_height);
    pos.setX(pos.x()-dx*tile_width);
    if (right)
    {
        s_x = (pos.x()+width/2)/tile_width;
        f_x = ((pos.x()+width/2)+width)/tile_width;
        s_y = (pos.y()-height/2)/tile_height;
        f_y = ((pos.y()-height/2)+height)/tile_height;
    }else
    {
        s_x = (pos.x()-width/2)/tile_width;
        f_x = ((pos.x()-width/2)+width)/tile_width;
        s_y = (pos.y()-height/2)/tile_height;
        f_y = ((pos.y()-height/2)+height)/tile_height;
    }

    qDebug()<<"Y ot"<<s_y<<"Y po"<<f_y;
    qDebug()<<"X ot"<<s_x<<"X po"<<f_x;
    for (int i=s_y; i<f_y; i++)
    {
        for (int j=s_x; j<f_x; j++)
        {
            if (i>=0 && i<count_y && j>=0 && j<count_x)
            {
                int id = layer->GetValue(i, j);
                if (id!=0)
                {
                    qDebug()<<"ID"<<id<<"i"<<i<<"j"<<j;
                    flag = true;
                    if (right)
                        res_pos->setX(j*tile_width-width+width/2+dx*tile_width);
                    else
                        res_pos->setX(j*tile_width+tile_width+width/2+dx*tile_width);
                }
            }
        }
    }
    return flag;
}

bool ManagerTileMap::CollisionY(QString layer_name, QVector2D pos, int width, int height, bool up, QVector2D* res_pos)
{
    //ERROR
    bool flag = false;
    Layer* layer = 0;
    for (int i=0; i<list_layer.size(); i++)
    {
        if (list_layer.value(i).layer_name==layer_name)
            layer = list_layer.value(i).layer;
    }
    if (layer==0)
        return false;
    int s_x, f_x, s_y, f_y;
    int height_ortho = 2.0/proj.column(1).y();
    qDebug()<<"HEIGHT_OTHO="<<height_ortho;
    pos.setY(height_ortho-pos.y()+dy*tile_height);
    pos.setX(pos.x()-dx*tile_width);
    if (up)
    {
        s_x = (pos.x()-width/2)/tile_width;
        f_x = ((pos.x()-width/2)+width)/tile_width;
        s_y = (pos.y()-height/2)/tile_height;
        f_y = ((pos.y()-height/2)+height)/tile_height;
    }else
    {
        s_x = (pos.x()-width/2)/tile_width;
        f_x = ((pos.x()-width/2)+width)/tile_width;
        s_y = (pos.y()+height/2)/tile_height;
        f_y = ((pos.y()+height/2)+height)/tile_height;
    }

    qDebug()<<"Y ot"<<s_y<<"Y po"<<f_y;
    qDebug()<<"X ot"<<s_x<<"X po"<<f_x;
    for (int i=s_y; i<f_y; i++)
    {
        for (int j=s_x; j<f_x; j++)
        {
            if (i>=0 && i<count_y && j>=0 && j<count_x)
            {
                int id = layer->GetValue(i, j);
                if (id!=0)
                {
                    qDebug()<<"ID"<<id<<"i"<<i<<"j"<<j;
                    flag = true;
                    if (up)
                        res_pos->setY(height_ortho-(i*tile_height+tile_height+height/2)+dy*tile_height);
                    else
                        res_pos->setY(height_ortho-(i*tile_height-height+height/2)+dy*tile_height);
                }
            }
        }
    }
    return flag;
}
