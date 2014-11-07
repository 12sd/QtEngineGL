#include "managermesh.h"

ManagerMesh* ManagerMesh::instance = 0;

ManagerMesh::ManagerMesh()
{
}

ManagerMesh::~ManagerMesh()
{
    Clear();
    qDebug()<<"~ManagerMesh";
}

ManagerMesh* ManagerMesh::getInstance()
{
    if (!instance)
        instance = new ManagerMesh();
    return instance;
}

void ManagerMesh::Add(int key, Mesh* value)
{
    hash_tab.insert(key, value);
}

Mesh* ManagerMesh::GetValue(int key)
{
    return hash_tab.value(key);
}

void ManagerMesh::Clear()
{
    QHash<int, Mesh*>::iterator it = hash_tab.begin();
    while (it != hash_tab.end())
    {
        delete it.value();
        it++;
    }
    hash_tab.clear();
}

void ManagerMesh::Destroy()
{
    if (instance)
    {
        delete instance;
    }
}
