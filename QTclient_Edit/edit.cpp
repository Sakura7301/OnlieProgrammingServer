#include "edit.h"
#include "ui_edit.h"

Edit::Edit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Edit)
{
    ui->setupUi(this);


    //获取服务器IP
     serverIp.setAddress(IP);

     //获取服务器端口
     serverPort=PORT;

     tcpsocket.connectToHost(serverIp,serverPort);

     userid="12345678";




    //当客户端连接成功，发送信号：connected()
    connect(&tcpsocket,SIGNAL(connected()),this,SLOT(onConnected()));

    //当客户端断开连接，发送信号：disconnected()
    connect(&tcpsocket,SIGNAL(disconnected()),this,SLOT(onDisconnected()));

    //当客户端收到服务器转发的消息时，发送信号：readyRead()
    connect(&tcpsocket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));

    //当网络异常时，发送信号error(QAbstractSocket::SocketError))
    connect(&tcpsocket,SIGNAL(error(QAbstractSocket::SocketError)),SLOT(onError()));
}

int Edit::getComboBox()
{
    type.clear();
    type=ui->comboBox->currentText();
    if(type ==QString::fromLocal8Bit("C"))
    {
        qDebug()<<"是C语言";
        return 1;
    }
    if(type ==QString::fromLocal8Bit("C++"))
    {
        qDebug()<<"是C++";
        return 2;
    }
    if(type ==QString::fromLocal8Bit("Python"))
    {
        qDebug()<<"是Python";
        return 3;
    }
    ui->textEdit->setFont(QFont(tr("Consolas"), 14));
    return 0;
}

Edit::~Edit()
{
    delete ui;
}


void Edit::on_pushButton_run_clicked()
{
    //组装数据包并发送
    QString str;
    str+=HEAD;
    str+=userid;
    language=getComboBox();
    {
        if(language==1)
        {
            str+=C;
        }
        if(language==2)
        {
            str+=CPP;
        }
        if(language==3)
        {
            str+=PYTHON;
        }
    }
    str += ui->textEdit->toPlainText();
    tcpsocket.write(str.toUtf8());
}

void Edit::onDisconnected()
{
    tcpsocket.connectToHost(serverIp,serverPort);
}

void Edit::onReadyRead()
{
    //bytesAvailable():返回当前套接字待读取的字节数，无数据则返回0
    //  0    无消息
    //  >0   有消息
    if(tcpsocket.bytesAvailable())
    {
            QString buf=tcpsocket.readAll();//读取所有数据
            ui->listWidget->addItem(buf);
            ui->listWidget->scrollToBottom();//消息回滚
            ui->textEdit->setFont(QFont(tr("Consolas"), 14));

    }
}

