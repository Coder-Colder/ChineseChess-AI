#include "overwidget.h"
#include "ui_overwidget.h"

OverWidget::OverWidget(int flag,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OverWidget)
{
    ui->setupUi(this);
    this->setFixedSize(640,470);
    if(flag == 1)
    {
        //设置文字
        this->setWindowTitle("你赢了");
        ui->title->setText("恭喜你，你赢了");
        ui->title->setAlignment(Qt::AlignHCenter);  //设置文字居中
        QFont font( "Microsoft YaHei", 18, 75);
        ui->title->setFont(font);

        //设置图片
        QPixmap pix;
        pix.load(":/res/win.png");
        ui->Picture->setPixmap(pix);
    }
    else {
        //设置文字
        this->setWindowTitle("你输了");
        ui->title->setText("太惨了，你输了");
        ui->title->setAlignment(Qt::AlignHCenter);  //设置文字居中
        QFont font( "Microsoft YaHei", 18, 75);
        ui->title->setFont(font);

        //设置图片
        QPixmap pix;
        pix.load(":/res/lose.png");
        ui->Picture->setPixmap(pix);
    }

    connect(ui->again,&QPushButton::clicked,this,[=](){
        this->hide();
        emit again();
    });

    connect(ui->exit,&QPushButton::clicked,this,[=](){
        exit(0);
    });
}

OverWidget::~OverWidget()
{
    delete ui;
}
