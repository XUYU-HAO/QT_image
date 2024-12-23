#include "imagetransform.h"
#include <QPixmap>

imagetransform::imagetransform(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);
    leftLayout = new QVBoxLayout(this);
    mirrorGroup = new QGroupBox(QStringLiteral("鏡射"), this);
    groupLayout = new QVBoxLayout(mirrorGroup);

    vCheckBox = new QCheckBox(QStringLiteral("垂直"), mirrorGroup);
    hCheckBox = new QCheckBox(QStringLiteral("水平"), mirrorGroup);
    mirrorButton = new QPushButton(QStringLiteral("執行"), mirrorGroup);
    saveButton = new QPushButton(QStringLiteral("存檔"), mirrorGroup); // 新增存檔按鈕

    hCheckBox->setGeometry(QRect(13, 28, 87, 19));
    vCheckBox->setGeometry(QRect(13, 54, 87, 19));
    mirrorButton->setGeometry(QRect(13, 80, 93, 28));
    saveButton->setGeometry(QRect(13, 115, 93, 28)); // 設定存檔按鈕位置

    groupLayout->addWidget(hCheckBox);
    groupLayout->addWidget(vCheckBox);
    groupLayout->addWidget(mirrorButton);
    groupLayout->addWidget(saveButton); // 加入存檔按鈕到介面
    leftLayout->addWidget(mirrorGroup);

    rotateDial = new QDial(this);
    rotateDial->setNotchesVisible(true);
    vSpacer = new QSpacerItem(20, 58, QSizePolicy::Minimum, QSizePolicy::Expanding);
    leftLayout->addWidget(rotateDial);
    leftLayout->addItem(vSpacer);
    mainLayout->addLayout(leftLayout);

    inWin = new QLabel(this);
    inWin->setScaledContents(true);
    QPixmap *initPixmap = new QPixmap(300, 200);
    initPixmap->fill(QColor(255, 255, 255));
    inWin->setPixmap(*initPixmap);
    inWin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(inWin);

    connect(mirrorButton, SIGNAL(clicked()), this, SLOT(mirroredImage()));
    connect(rotateDial, SIGNAL(valueChanged(int)), this, SLOT(rotatedImage()));
    connect(saveButton, &QPushButton::clicked, this, &imagetransform::saveTransformedImage); // 連接存檔按鈕
}

imagetransform::~imagetransform()
{
}

void imagetransform::mirroredImage()
{
    bool H, V;
    if (srcImg.isNull())
        return;
    H = hCheckBox->isChecked();
    V = vCheckBox->isChecked();
    dstImg = srcImg.mirrored(H, V);
    inWin->setPixmap(QPixmap::fromImage(dstImg));
    srcImg = dstImg;
}

void imagetransform::rotatedImage()
{
    QTransform tran;
    int angle;
    if (srcImg.isNull())
        return;
    angle = rotateDial->value();
    tran.rotate(angle);
    dstImg = srcImg.transformed(tran);
    inWin->setPixmap(QPixmap::fromImage(dstImg));
}

void imagetransform::saveTransformedImage()
{
    if (dstImg.isNull()) {
        QMessageBox::warning(this, QStringLiteral("存檔失敗"), QStringLiteral("沒有可存檔的影像！"));
        return;
    }

    QString saveFileName = QFileDialog::getSaveFileName(
        this,
        QStringLiteral("存檔影像"),
        ".",
        "Images (*.png *.jpg *.bmp);;All Files (*)"
        );

    if (!saveFileName.isEmpty()) {
        if (!dstImg.save(saveFileName)) {
            QMessageBox::warning(this, QStringLiteral("存檔失敗"), QStringLiteral("存檔時發生錯誤！"));
        } else {
            QMessageBox::information(this, QStringLiteral("存檔成功"), QStringLiteral("影像已成功儲存！"));
        }
    }
}
