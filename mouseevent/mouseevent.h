#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <QMainWindow>
#include <QLabel>
#include <QMouseEvent>

class MouseEvent : public QMainWindow
{
    Q_OBJECT

public:
    explicit MouseEvent(QWidget *parent = nullptr);
    ~MouseEvent();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QLabel *statusLabel;
    QLabel *MousePosLabel;
};

#endif // MOUSEEVENT_H
