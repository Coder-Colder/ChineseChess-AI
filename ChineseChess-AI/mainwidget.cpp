#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    //初始化窗口信息
    setWindowIcon(QIcon("://res/B_BISHOP1.png"));
    setWindowTitle("中国象棋");
    setFixedSize(650,720);

    //创建开始按钮
    QPushButton  * startButton = new QPushButton(this);
    startButton->setText("开始下棋");
    startButton->move(this->width() * 0.5 - startButton->width() *0.5, this->height() * 0.7);
    startButton->resize(100,75);

    //跳入选择场景
    chooseWidget = new ChooseWidget;
    connect(startButton,&QPushButton::clicked,[=](){
        this->hide();
        chooseWidget->show();
    });
}

MainWidget::~MainWidget()
{
    delete ui;
    delete chooseWidget;
}

void MainWidget::paintEvent(QPaintEvent *)
{
    //绘制设置背景图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/MainSence.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
