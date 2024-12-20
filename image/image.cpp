#include "image.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>

image::image(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle (QStringLiteral("Image Processing"));
    central = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout (central);
    imgWin = new QLabel();
    QPixmap      *initPixmap = new QPixmap(300,200);
    initPixmap->fill(QColor(255,255,255));
    imgWin->resize (300,200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap (*initPixmap);
    mainLayout->addWidget(imgWin);
    setCentralWidget ( central );
    createActions();
    createMenus();
    createToolBars();
}

image::~image()
{
    // 析構函數的實現
}

void image::createActions()
{
    openFileAction = new QAction (QStringLiteral("開啟檔案&O"),this);
    openFileAction->setShortcut (tr("Ctrl+0"));
    openFileAction->setStatusTip (QStringLiteral("開啟影像檔案"));
    connect (openFileAction, SIGNAL (triggered()),this, SLOT (showOpenFile()));

    exitAction = new QAction (QStringLiteral("結束&Q"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip (QStringLiteral("退出程式"));
    connect (exitAction, SIGNAL (triggered()),this, SLOT (Close()));
}

void image::createMenus()
{
    fileMenu = menuBar ()->addMenu (QStringLiteral("檔案&F"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction (exitAction);
}

void image::createToolBars()
{
    fileTool = addToolBar("file");
    fileTool->addAction(openFileAction);
}

void image::loadFile(QString filename)
{
    qDebug() <<QString("file name: %1").arg(filename);
    QByteArray ba=filename.toLatin1();
    printf("FN:%s\n", (char *) ba.data());
    img.load(filename);
    imgWin->setPixmap (QPixmap:: fromImage(img));
}

void image::showOpenFile()
{
    filename = QFileDialog::getOpenFileName (this,
                                            QStringLiteral("Open image"),
                                            tr("."),
                                            "bmp(*.bmp);;png(*.png)"
                                            ";;Jpeg(*.jpg)");
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
