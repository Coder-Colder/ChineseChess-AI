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
    startButton->setText("开始游戏");
    startButton->move(this->width() * 0.5 - startButton->width() *0.5, this->height() * 0.7);
    startButton->resize(100,75);

    //跳入选择场景
    chooseWidget = new ChooseWidget;
    connect(startButton,&QPushButton::clicked,[=](){
        this->hide();
        chooseWidget->show();
    });

    //结束场景初始化
    winWidget = new OverWidget(1);
    winWidget->hide();

    loseWidget = new OverWidget(2);
    loseWidget->hide();

    connect(this->chooseWidget->gameWidget,&GameWidget::win,this,&MainWidget::overWin);
    connect(this->chooseWidget->gameWidget,&GameWidget::lose,this,&MainWidget::overLose);
    connect(winWidget,&OverWidget::again,this,&MainWidget::restart);
    connect(loseWidget,&OverWidget::again,this,&MainWidget::restart);
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

void MainWidget::overWin()
{
    winWidget->setWindowModality(Qt::ApplicationModal); //设置窗体模态
    winWidget->show();
}
void MainWidget::overLose()
{
    loseWidget->setWindowModality(Qt::ApplicationModal);
    loseWidget->show();
}

void MainWidget::restart()
{
    /*
    delete chooseWidget;
    chooseWidget = new ChooseWidget();
    chooseWidget->show();
    */
    //TODO:程序会异常退出，原因不明
}
