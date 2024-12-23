#ifndef IMAGETRANSFORM_H
#define IMAGETRANSFORM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QDial>
#include <QLabel>
#include <QSpacerItem>
#include <QImage>
#include <QPixmap>
#include <QTransform>
#include <QMessageBox>
#include <QFileDialog>

class imagetransform : public QWidget
{
    Q_OBJECT

public:
    explicit imagetransform(QWidget *parent = nullptr);
    ~imagetransform();

    QImage srcImg;  // 原始影像
    QImage dstImg;  // 幾何轉換後的影像
    QLabel *inWin;  // 顯示影像的視窗

private slots:
    void mirroredImage();         // 處理鏡射影像的槽函式
    void rotatedImage();          // 處理旋轉影像的槽函式
    void saveTransformedImage();  // 處理存檔影像的槽函式

private:
    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QGroupBox *mirrorGroup;
    QVBoxLayout *groupLayout;
    QCheckBox *vCheckBox;
    QCheckBox *hCheckBox;
    QPushButton *mirrorButton;
    QPushButton *saveButton;      // 新增的存檔按鈕
    QDial *rotateDial;
    QSpacerItem *vSpacer;
};

#endif // IMAGETRANSFORM_H
