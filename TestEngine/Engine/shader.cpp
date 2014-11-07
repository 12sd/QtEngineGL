#include "shader.h"

Shader::Shader()
{
    attr_ver = "Vertex";
    attr_tex = "Texture";
    unif_mat_pos = "MatrixPos";
    unif_mat_tex = "MatrixTex";
    Load("://Resources/default.vert", "://Resources/default.frag");
}

Shader::Shader(QString vert_file, QString frag_file)
{
    Load(vert_file, frag_file);
}

Shader::~Shader()
{
    this->removeAllShaders();
    qDebug()<<"~Shader";
}

bool Shader::Load(QString vert_file, QString frag_file)
{
    this->create();
    if (!this->addShaderFromSourceFile(QOpenGLShader::Vertex, vert_file))
        return false;
    if (!this->addShaderFromSourceFile(QOpenGLShader::Fragment, frag_file))
        return false;
    if (!this->link())
        return false;
    return true;
}

void Shader::SetNameVertex(QString name)
{
    attr_ver = name;
}

void Shader::SetNameTexture(QString name)
{
    attr_tex = name;
}

void Shader::SetNameMatrixPos(QString name)
{
    unif_mat_pos = name;
}

void Shader::SetNameMatrixTex(QString name)
{
    unif_mat_tex = name;
}

QString Shader::GetNameVertex()
{
    return attr_ver;
}

QString Shader::GetNameTexture()
{
    return attr_tex;
}

QString Shader::GetNameMatrixPos()
{
    return unif_mat_pos;
}

QString Shader::GetNameMatrixTex()
{
    return unif_mat_tex;
}
