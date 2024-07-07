#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    client = new QMqttClient;

    //将mqtt的连接状态用一个槽函数处理，显示连接状态
    connect(client,&QMqttClient::connected,this,&MainWindow::on_mqttConnected);
    //将mqtt话题数据用一个槽函数处理，显示话题数据
    // QObject::connect(subscription, &QMqttSubscription::messageReceived, [](const QMqttMessage &msg) {
    //     qDebug() << "Received message from topic" << msg.topic().name() << ":" << msg.payload();
    // });

}

MainWindow::~MainWindow()
{
    delete ui;
}

//mqtt连接
void MainWindow::on_connect_clicked()
{
    //连接前先断开连接
    client->disconnectFromHost();

    //设置域名
    client->setHostname(ui->ip->text());
    //设置端口
    client->setPort(ui->port->text().toInt());
    //设置用户名
    client->setUsername(ui->userName->text());
    //设置密码
    client->setPassword(ui->passWord->text());
    //设置用户Id
    client->setClientId(ui->clientId->text());
    // client->keepAlive();
    //连接
    client->connectToHost();

}

//mqtt断开连接
void MainWindow::on_disconnect_clicked()
{
    client->disconnectFromHost();

    ui->connect_state->setText("未连接");
    ui->connect_state->setStyleSheet("color:red;");
}
//mqtt连接状态显示
void MainWindow::on_mqttConnected()
{
    ui->connect_state->setText("已连接");
    ui->connect_state->setStyleSheet("color:green;");

}
//mqtt话题订阅
void MainWindow::on_topicSub_clicked()
{
    QString topic = ui->topicSubText->text();

    subscription = client->subscribe(QMqttTopicFilter(topic));
    // QObject::connect(subscription, &QMqttSubscription::messageReceived, [](const QMqttMessage &msg) {
    //     qDebug() << "Received message from topic" << msg.topic().name() << ":" << msg.payload();
    // });
    QObject::connect(subscription, &QMqttSubscription::messageReceived, [this](const QMqttMessage &msg) {
        ui->topicSubMegs->append(msg.topic().name()+":");
        ui->topicSubMegs->append(msg.payload());
        ui->topicSubMegs->append("--------------");
    });
}


void MainWindow::on_topicUnsub_clicked()
{
    QString topic = ui->topicSubText->text();

    client->unsubscribe(QMqttTopicFilter(topic));
}

void MainWindow::on_topicPub_clicked()
{

    // 获取 QTextEdit 中的文本内容
    QString topic = ui->topicPubText->text();
    // 发布消息到指定主题
    const QByteArray Mesg = ui->pubMesg->toPlainText().toUtf8();

    // client->publish(QMqttTopicFilter(topic),Mesg);
    client->publish(QMqttTopicName(topic),Mesg);
}


