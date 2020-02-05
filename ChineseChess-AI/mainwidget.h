#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "choosewidget.h"
namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void paintEvent(QPaintEvent *);
    ChooseWidget * chooseWidget;

    //结束窗口
    OverWidget * winWidget;
    OverWidget * loseWidget;
signals:

public slots:
    void overWin();
    void overLose();
    void restart();
private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
