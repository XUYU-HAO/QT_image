#ifndef IMAGE_H
#define IMAGE_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include "imagetransform.h"

class image : public QMainWindow
{
    Q_OBJECT

public:
    image(QWidget *parent = 0);
    ~image();
    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile(QString filename);

private slots:
    void showOpenFile();
    void zoomIn();  // 放大功能
    void zoomOut();  // 縮小功能
    void showGeometryTransform();

private:
    imagetransform  *gWin;
    QWidget *central;
    QMenu *fileMenu;
    QToolBar *fileTool;
    QImage img;
    QString filename;
    QLabel *imgWin;
    QAction *openFileAction;
    QAction *exitAction;
    QAction *zoomInAction;  // 放大動作
    QAction *zoomOutAction;  // 縮小動作
    QAction *geometryAction;
};

#endif // IMAGE_H
