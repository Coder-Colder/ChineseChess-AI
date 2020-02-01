#include "choosewidget.h"

ChooseWidget::ChooseWidget(QWidget *parent) : QWidget(parent)
{
    //初始化窗口信息
    setWindowIcon(QIcon("://res/B_BISHOP1.png"));
    setWindowTitle("中国象棋");
    setFixedSize(650,720);

    //创建难度按钮
    QPushButton  * easyButton = new QPushButton(this);
    easyButton->setText("简单难度");
    easyButton->move(this->width() * 0.5 - easyButton->width() *0.5, this->height() * 0.5);
    easyButton->resize(100,75);

    QPushButton  * midButton = new QPushButton(this);
    midButton->setText("中等难度");
    midButton->move(this->width() * 0.5 - midButton->width() *0.5, this->height() * 0.65);
    midButton->resize(100,75);

    QPushButton  * crazyButton = new QPushButton(this);
    crazyButton->setText("令人发狂");
    crazyButton->move(this->width() * 0.5 - crazyButton->width() *0.5, this->height() * 0.8);
    crazyButton->resize(100,75);

    gameWidget = new GameWidget;
    connect(easyButton,&QPushButton::clicked,[=](){
        this->hide();
        gameWidget->show();
    });

    connect(midButton,&QPushButton::clicked,[=](){
        this->hide();
        gameWidget->show();
    });

    connect(easyButton,&QPushButton::clicked,[=](){
        this->hide();
        gameWidget->show();
    });

}

ChooseWidget::~ChooseWidget()
{
    delete gameWidget;
}

void ChooseWidget::paintEvent(QPaintEvent *)
{
    //绘制设置背景图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/ChooseSence.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
