#include "mouseevent.h"
#include <QStatusBar>

MouseEvent::MouseEvent(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("Test mouse event"));

    // 初始化狀態欄標籤
    statusLabel = new QLabel(this);
    statusLabel->setText(QStringLiteral("Indicator position"));
    statusLabel->setFixedWidth(100);

    MousePosLabel = new QLabel(this);
    MousePosLabel->setText(tr(""));
    MousePosLabel->setFixedWidth(100);

    statusBar()->addPermanentWidget(statusLabel);
    statusBar()->addPermanentWidget(MousePosLabel);

    // 啟用滑鼠追蹤
    setMouseTracking(true);
    resize(400, 300);
}

MouseEvent::~MouseEvent()
{
    // 不需要手動刪除 statusLabel 和 MousePosLabel，Qt 自動管理子物件
}

void MouseEvent::mouseMoveEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number(event->x()) + "," +
                  QString::number(event->y()) + ")";
    MousePosLabel->setText(str);
}

void MouseEvent::mousePressEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number(event->x()) + "," +
                  QString::number(event->y()) + ") ";
    if (event->button() == Qt::LeftButton)
    {
        statusBar()->showMessage(QStringLiteral("左鍵點擊:") + str);
    }
    else if (event->button() == Qt::RightButton)
    {
        statusBar()->showMessage(QStringLiteral("右鍵點擊:") + str);
    }
    else if (event->button() == Qt::MiddleButton)
    {
        statusBar()->showMessage(QStringLiteral("中鍵點擊:") + str);
    }
}

void MouseEvent::mouseReleaseEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number(event->x()) + "," +
                  QString::number(event->y()) + ")";
    statusBar()->showMessage(QStringLiteral("釋放:") + str);
}

void MouseEvent::mouseDoubleClickEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number(event->x()) + "," +
                  QString::number(event->y()) + ")";
    statusBar()->showMessage(QStringLiteral("雙擊:") + str);
}
