#ifndef IMAGETRANSFORM_H
#define IMAGETRANSFORM_H

#include <QWidget>
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QDial>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>

class imagetransform : public QWidget
{
    Q_OBJECT

public:
    imagetransform(QWidget *parent = 0);
    ~imagetransform();
    QLabel      *inWin;
    QGroupBox   *mirrorGroup;
    QCheckBox   *hCheckBox;
    QCheckBox   *vCheckBox;
    QPushButton *mirrorButton;
    QDial       *rotateDial;
    QSpacerItem *vSpacer;
    QHBoxLayout *mainLayout;
    QVBoxLayout *groupLayout;
    QVBoxLayout *leftLayout;
    QImage      srcImg;
    QImage      dstImg;

private slots:
    void mirroredImage();
    void rotatedImage();
};
#endif // IMAGETRANSFORM_H
