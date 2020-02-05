#ifndef OVERWIDGET_H
#define OVERWIDGET_H

#include <QWidget>

namespace Ui {
class OverWidget;
}

class OverWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OverWidget(int flag, QWidget *parent = nullptr);
    ~OverWidget();
signals:
    void again();
public slots:

private:
    Ui::OverWidget *ui;
};

#endif // OVERWIDGET_H
