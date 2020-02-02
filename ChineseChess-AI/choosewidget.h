#ifndef CHOOSEWIDGET_H
#define CHOOSEWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include "define.h"
#include "gamewidget.h"
class ChooseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChooseWidget(QWidget *parent = nullptr);
    ~ChooseWidget();
    void paintEvent(QPaintEvent *);

    GameWidget * gameWidget;
signals:

public slots:
};

#endif // CHOOSEWIDGET_H
