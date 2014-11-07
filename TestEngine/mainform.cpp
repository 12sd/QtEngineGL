#include "mainform.h"

MainForm::MainForm(QWindow *parent) :
    QWindow(parent),
    m_update_pending(false),
    m_animating(false),
    m_context(0),
    m_device(0)
{
    setSurfaceType(QWindow::OpenGLSurface);
}

MainForm::~MainForm()
{
    delete m_device;
}

void MainForm::render(QPainter *painter)
{
    Q_UNUSED(painter);
    //setTitle("FPS = "+QString::number(Fps::getInstance()->GetFps()));
}

void MainForm::initialize()
{
    Mesh* m = new Mesh();
    m->Create();
    ManagerMesh::getInstance()->Add(0, m);

    ManagerShader::getInstance()->Add(0, new Shader());

    Texture* t = new Texture("://Resources/backgroundmenu.png");
    t->Create();
    ManagerTexture::getInstance()->Add(0, t);
    t = new Texture("://Resources/buttonstartmenu.png");
    t->Create();
    ManagerTexture::getInstance()->Add(1, t);
    t = new Texture("://Resources/Original/tmp_sprite.png");
    t->Create();
    ManagerTexture::getInstance()->Add(2, t);

    Sprite* s = new Sprite();
    s->SetMeshKey(0);
    s->SetShaderKey(0);
    s->SetTextureKey(0);
    s->Create();
    ManagerSprite::getInstance()->Add(0, s);
    i = 0;
    j = 0;

    glViewport(0, 0, 800, 600);
}

void MainForm::render()
{
    if (!m_device)
        m_device = new QOpenGLPaintDevice();

    //glViewport(0,0,width(),height());
    //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    //glEnable(GL_DEPTH_TEST);

    ///*Альфа смешивание
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //qDebug()<<"CurrentStatusGame="<<CurrentStatusGame;
    switch (CurrentStatusGame)
    {
    case MainMenu:
    {
        Sprite* s = ManagerSprite::getInstance()->GetValue(0);
        s->SetTextureKey(0);
        s->Bind();
        QMatrix4x4 mat;
        mat.setToIdentity();
        mat.ortho(-1, 1, -1, 1, -1, 1);
        s->GetShader()->setUniformValue(s->GetShader()->GetNameMatrixPos().toStdString().c_str(), mat);
        glDrawArrays(GL_TRIANGLES, 0, s->GetMesh()->GetCountVertex());

        s->SetTextureKey(1);
        s->Bind();
        QMatrix4x4 mv;
        mat.setToIdentity();
        mat.ortho(-1, 19, -1, 19, -1, 1);
        mv.setToIdentity();
        mv.translate(10, 10, 0);
        s->GetShader()->setUniformValue(s->GetShader()->GetNameMatrixPos().toStdString().c_str(), mat * mv);
        glDrawArrays(GL_TRIANGLES, 0, s->GetMesh()->GetCountVertex());

        s->SetTextureKey(2);
        s->Bind(48, 65, i, j);
        mat.setToIdentity();
        mat.ortho(0, 800, 0, 600, -1, 1);
        //mat.ortho(-1, 19, -1, 19, -1, 1);
        mv.setToIdentity();
        //mv.scale(48, 65);
        mv.scale(48.0/2, 65.0/2);
        mv.translate(1, 1, 0);
        s->GetShader()->setUniformValue(s->GetShader()->GetNameMatrixPos().toStdString().c_str(), mat * mv);
        glDrawArrays(GL_TRIANGLES, 0, s->GetMesh()->GetCountVertex());

        s->UnBind();

        grid.SetColor(0, 1, 0);
        //grid.Draw(0, 800, 0, 600);
        //grid.Draw(0, 800, 0, 600);
        break;
    }
    case DragPlayer1:
        break;
    }

    m_device->setSize(size());

    QPainter painter(m_device);
    render(&painter);
}

void MainForm::renderLater()
{
    if (!m_update_pending)
    {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

bool MainForm::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::UpdateRequest:
        m_update_pending = false;
        renderNow();
        return true;
    case QEvent::Close:
        ManagerMouse::getInstance()->Destroy();
        ManagerMesh::getInstance()->Destroy();
        ManagerShader::getInstance()->Destroy();
        ManagerTexture::getInstance()->Destroy();
        ManagerSprite::getInstance()->Destroy();
        return QWindow::event(event);
    default:
        return QWindow::event(event);
    }
}

void MainForm::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}

void MainForm::renderNow()
{
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if (!m_context)
    {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();
        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if (needsInitialize)
    {      
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    m_context->swapBuffers(this);

    if (m_animating)
        renderLater();
}

void MainForm::setAnimating(bool animating)
{
    m_animating = animating;

    if (animating)
        renderLater();
}

void MainForm::mouseMoveEvent(QMouseEvent *event)
{
    ManagerMouse::getInstance()->Update(event);
    i++;
    if (i == 4)
        i = 0;
    //qDebug()<<"Event: X="<<event->x()<<" Y="<<event->y();
}

void MainForm::mousePressEvent(QMouseEvent *event)
{
    ManagerMouse::getInstance()->Update(event);
    j++;
    if (j == 4)
        j = 0;
}

void MainForm::mouseReleaseEvent(QMouseEvent *event)
{
    ManagerMouse::getInstance()->Update(event);
}
