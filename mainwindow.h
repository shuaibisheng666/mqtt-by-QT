#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "QMqttClient"
#include "QDebug"
#include "QLabel"
#include "QFile"
#include "QJsonObject"
#include "QJsonDocument"
#include "QJsonArray"
#include "QMessageBox"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMqttClient *client;
    QMqttSubscription *subscription;
    QJsonArray historyJArray;


    void getHisttoryImfors(QString imfors[]);

private slots:
    void on_connect_clicked();

    void on_mqttConnected();

    void on_disconnect_clicked();

    void on_topicSub_clicked();

    void on_topicUnsub_clicked();

    void on_topicPub_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
