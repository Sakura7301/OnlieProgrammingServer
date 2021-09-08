#ifndef EDIT_H
#define EDIT_H

#include <QMainWindow>
#include <QDialog>
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>

#define IP "8.140.14.233"
#define PORT 8888
#define BUFFSIZE 4096
#define HEAD "Onlie*"			//固定包头
#define HEAD_LEN 6				//包头长度
#define USER_ID_LEN 8			//ID长度
#define USER_LANGUAGE_LEN 8		//编程语言字节长度

//语言分类
#define C		"c*******"
#define CPP		"cpp*****"
#define PYTHON	"python**"


QT_BEGIN_NAMESPACE
namespace Ui { class Edit; }
QT_END_NAMESPACE

class Edit : public QMainWindow
{
    Q_OBJECT

public:
    Edit(QWidget *parent = nullptr);

    int getComboBox();
    ~Edit();

private slots:
    //点击运行的槽函数
    void on_pushButton_run_clicked();

    //和服务器断开连接时执行的槽函数
    void onDisconnected();

    //接受服务器所转发的聊天消息的槽函数
    void onReadyRead();



private:
    Ui::Edit *ui;
    QTcpSocket tcpsocket;//和服务器通信的套接字

    QHostAddress serverIp;//服务器地址

    quint16 serverPort;//服务器端口号

    int language;//语言选择

    QString userid;

    QString type;


};
#endif // EDIT_H
