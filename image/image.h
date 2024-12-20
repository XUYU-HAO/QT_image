#ifndef IMAGE_H
#define IMAGE_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>


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

private:
    QWidget *central;
    QMenu *fileMenu;
    QToolBar *fileTool;
    QImage img;
    QString filename;
    QLabel *imgWin;
    QAction *openFileAction;
    QAction *exitAction;
};
#endif // IMAGE_H
