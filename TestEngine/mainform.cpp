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
    setTitle("FPS = "+QString::number(fps)+" X="+QString::number(x)+" Y="+QString::number(y)+"FPS_QT=");
}

void MainForm::initialize()
{
    /* Тут будет одна строка
       GameScene.Load(filename);
    */

    GameScene sc;
    sc.Load("://Resources/test.xml");

    map = ManagerTileMap::getInstance();
    map->Load("://Resources/map.tmx");

    object_sp = TestCreatorGameObject::CreateGameObject(Test);
    object_sp->Init();

    button_exit = TestCreatorGameObject::CreateGameObject(Button_Exit);
    button_exit->Init();

    button_start = TestCreatorGameObject::CreateGameObject(Button_Start);
    button_start->Init();

    backround = TestCreatorGameObject::CreateGameObject(Back_Ground);
    backround->Init();

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
        backround->Update();
        backround->Draw();
        object_sp->Update();
        object_sp->Draw();
        button_exit->Update();
        button_exit->Draw();
        button_start->Update();
        button_start->Draw();

        grid.SetColor(0, 1, 0);
        //grid.Draw(0, 800, 0, 600);
        //grid.Draw(0, 800, 0, 600);
        break;
    }
    case DragPlayer1:
    {
        map->Draw();
        object_sp->Update();
        object_sp->Draw();
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
        ManagerMesh::getInstance()->Destroy();
        ManagerShader::getInstance()->Destroy();
        ManagerTexture::getInstance()->Destroy();
        ManagerSprite::getInstance()->Destroy();
        //delete object_sp;
        //delete button_start;
        //delete button_exit;
        //delete backround;
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
    qDebug()<<"Mouse Press";
}

void MainForm::mouseReleaseEvent(QMouseEvent *event)
{
    ManagerMouse::getInstance()->Update(event,false);
    qDebug()<<"Mouse Release";
}

void MainForm::keyPressEvent(QKeyEvent *key)
{
    ManagerKeyboard::getInstance()->Update(key);
    qDebug()<<"Key Press";
}

void MainForm::keyReleaseEvent(QKeyEvent *key)
{
    ManagerKeyboard::getInstance()->Update(key, false);
    qDebug()<<"Key Release";
}
