#ifndef IMAGE_H
#define IMAGE_H

#include <QMainWindow>
#include <QLabel>
#include <QImage>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include "imagetransform.h"
#include "mouseevent.h"

class image : public QMainWindow
{
    Q_OBJECT

public:
    explicit image(QWidget *parent = nullptr);
    ~image();

private slots:
    void showOpenFile();
    void showGeometryTransform();
    void showMouseEvent();
    void zoomIn();
    void zoomOut();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile(QString filename);

    // 界面元件
    QWidget *central;
    QLabel *imgWin;
    QImage img;
    QString filename;

    // 幾何轉換視窗和滑鼠事件視窗
    imagetransform *gWin;
    MouseEvent *mouseWin;

    // 動作
    QAction *openFileAction;
    QAction *exitAction;
    QAction *geometryAction;
    QAction *mouseEventAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;

    // 菜單和工具列
    QMenu *fileMenu;
    QToolBar *fileTool;
};

#endif // IMAGE_H
