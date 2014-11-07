#ifndef MANAGERSHADER_H
#define MANAGERSHADER_H

#include "shader.h"

class ManagerShader
{
public:
    ManagerShader();
    ~ManagerShader();
    static ManagerShader* getInstance();
    void Add(int key, Shader* value);
    Shader* GetValue(int key);
    void Clear();
    void Destroy();

private:
    static ManagerShader* instance;
    QHash<int, Shader*> hash_tab;
};

#endif // MANAGERSHADER_H
