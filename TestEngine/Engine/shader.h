#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLShaderProgram>

class Shader: public QOpenGLShaderProgram
{
public:
    Shader();
    Shader(QString vert_file, QString frag_file);
    ~Shader();
    bool Load(QString vert_file, QString frag_file);
    void SetNameVertex(QString name);
    void SetNameTexture(QString name);
    void SetNameMatrixPos(QString name);
    void SetNameMatrixTex(QString name);
    QString GetNameVertex();
    QString GetNameTexture();
    QString GetNameMatrixPos();
    QString GetNameMatrixTex();

private:
    QString attr_ver;
    QString attr_tex;
    QString unif_mat_pos;
    QString unif_mat_tex;
};

#endif // SHADER_H
