#include "image.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>
#include "imagetransform.h"
#include "mouseevent.h"

image::image(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("Image Processing"));
    central = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    imgWin = new QLabel();
    QPixmap *initPixmap = new QPixmap(300, 200);
    gWin = new imagetransform();
    mouseWin = new MouseEvent(); // 初始化 MouseEvent 視窗
    initPixmap->fill(QColor(255, 255, 255));
    imgWin->resize(300, 200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(*initPixmap);
    mainLayout->addWidget(imgWin);
    setCentralWidget(central);

    createActions();
    createMenus();
    createToolBars();
}

image::~image()
{
    delete gWin;
    delete mouseWin;
}

void image::createActions()
{
    // 開啟檔案動作
    openFileAction = new QAction(QStringLiteral("開啟檔案&O"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(QStringLiteral("開啟影像檔案"));
    connect(openFileAction, &QAction::triggered, this, &image::showOpenFile);

    // 結束程式動作
    exitAction = new QAction(QStringLiteral("結束&Q"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("退出程式"));
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);

    // 幾何轉換動作
    geometryAction = new QAction(QStringLiteral("幾何轉換"), this);
    geometryAction->setShortcut(tr("Ctrl+G"));
    geometryAction->setStatusTip(QStringLiteral("影像幾何轉換"));
    connect(geometryAction, &QAction::triggered, this, &image::showGeometryTransform);

    // 新增 MouseEvent 的動作
    mouseEventAction = new QAction(QStringLiteral("滑鼠事件視窗"), this);
    mouseEventAction->setShortcut(tr("Ctrl+M"));
    mouseEventAction->setStatusTip(QStringLiteral("顯示滑鼠事件視窗"));
    connect(mouseEventAction, &QAction::triggered, this, &image::showMouseEvent);

    // 放大動作
    zoomInAction = new QAction(QStringLiteral("放大&Z"), this);
    zoomInAction->setShortcut(tr("Ctrl+Z"));
    zoomInAction->setStatusTip(QStringLiteral("放大影像"));
    connect(zoomInAction, &QAction::triggered, this, &image::zoomIn);

    // 縮小動作
    zoomOutAction = new QAction(QStringLiteral("縮小&X"), this);
    zoomOutAction->setShortcut(tr("Ctrl+X"));
    zoomOutAction->setStatusTip(QStringLiteral("縮小影像"));
    connect(zoomOutAction, &QAction::triggered, this, &image::zoomOut);
}

void image::createMenus()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("檔案&F"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(geometryAction);
    fileMenu->addAction(mouseEventAction); // 加入滑鼠事件動作
    fileMenu->addAction(exitAction);
    fileMenu->addAction(zoomInAction);
    fileMenu->addAction(zoomOutAction);
}

void image::createToolBars()
{
    fileTool = addToolBar("file");
    fileTool->addAction(openFileAction);
    fileTool->addAction(geometryAction);
    fileTool->addAction(mouseEventAction); // 加入滑鼠事件功能
    fileTool->addAction(zoomInAction);
    fileTool->addAction(zoomOutAction);
}

void image::loadFile(QString filename)
{
    qDebug() << QString("file name: %1").arg(filename);
    QByteArray ba = filename.toLatin1();
    printf("FN:%s\n", (char *)ba.data());
    img.load(filename);
    imgWin->setPixmap(QPixmap::fromImage(img));
}

void image::showOpenFile()
{
    filename = QFileDialog::getOpenFileName(this,
                                            QStringLiteral("Open image"),
                                            tr("."),
                                            "bmp(*.bmp);;png(*.png);;Jpeg(*.jpg)");
    if (!filename.isEmpty())
    {
        if (img.isNull())
        {
            loadFile(filename);
        }
        else
        {
            image *newIPWin = new image();
            newIPWin->show();
            newIPWin->loadFile(filename);
        }
    }
}

void image::showGeometryTransform()
{
    if (!img.isNull())
    {
        gWin->srcImg = img;
        gWin->inWin->setPixmap(QPixmap::fromImage(gWin->srcImg));
        gWin->show();
    }
}

void image::zoomIn()
{
    if (!img.isNull())
    {
        QImage scaledImage = img.scaled(img.size() * 1.5, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        image *newWindow = new image();
        newWindow->show();
        newWindow->img = scaledImage;
        newWindow->imgWin->setPixmap(QPixmap::fromImage(scaledImage));
    }
}

void image::zoomOut()
{
    if (!img.isNull())
    {
        QImage scaledImage = img.scaled(img.size() * 0.75, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        image *newWindow = new image();
        newWindow->show();
        newWindow->img = scaledImage;
        newWindow->imgWin->setPixmap(QPixmap::fromImage(scaledImage));
    }
}

void image::showMouseEvent()
{
    mouseWin->show(); // 顯示 MouseEvent 視窗
}
