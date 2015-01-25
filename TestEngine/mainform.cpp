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
    int fps = Fps::getInstance()->GetFps();
    int x = ManagerMouse::getInstance()->GetX();
    int y = ManagerMouse::getInstance()->GetY();
    setTitle("FPS = "+QString::number(fps)+" X="+QString::number(x)+" Y="+QString::number(600-y));
}

void MainForm::initialize()
{
    /* Тут будет одна строка
       GameScene.Load(filename);
    */


    TestCreatorGameObject cr;
    level.Load("://Resources/resource.xml", &cr);

    QHash<QString, QString> h;
    cube.Init(h);

    QMatrix4x4 proj;
    proj.setToIdentity();
    //proj.ortho(-10, 10, -10, 10, -1000, 1000);
    proj.ortho(0, 800, 0, 600, -100, 100);
    //proj.perspective(45, 800/600, -100, 100);
    Setting::SetProjection(proj);
    Setting::SetViewPort(QRectF(0, 0, 800, 600));
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
    case Player:
    {
        level.Update();
        level.Draw();

        cube.Update();
        cube.Draw();

        break;
    }
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
        ManagerKeyboard::getInstance()->Destroy();
        ManagerMesh::getInstance()->Destroy();
        ManagerShader::getInstance()->Destroy();
        ManagerTexture::getInstance()->Destroy();
        ManagerSprite::getInstance()->Destroy();
        ManagerTileMap::getInstance()->Destroy();
        ManagerCamera::getInstance()->Destroy();
        ManagerGameObject::getInstance()->Destroy();
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
}

void MainForm::mousePressEvent(QMouseEvent *event)
{
    ManagerMouse::getInstance()->Update(event);
}

void MainForm::mouseReleaseEvent(QMouseEvent *event)
{
    ManagerMouse::getInstance()->Update(event,false);
}

void MainForm::keyPressEvent(QKeyEvent *key)
{
    ManagerKeyboard::getInstance()->Update(key);
}

void MainForm::keyReleaseEvent(QKeyEvent *key)
{
    ManagerKeyboard::getInstance()->Update(key, false);
}

void MainForm::resizeEvent(QResizeEvent * event)
{
    QMatrix4x4 proj;
    proj.setToIdentity();
    proj.ortho(0, event->size().width(), 0, event->size().height(), -1, 1);
    //Setting::SetProjection(proj);
    Setting::SetViewPort(QRectF(0, 0, event->size().width(), event->size().height()));
}
