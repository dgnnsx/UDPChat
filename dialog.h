#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QUdpSocket>

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(int chatNo, int port, QString style, QWidget *parent = 0);
    ~Dialog();

public slots:
    void readPendingDatagrams();

private slots:
    void on_pushButton_conectar_clicked();

    void on_pushButton_enviar_clicked();

    void on_lineEdit_ip_textChanged();

    void on_lineEdit_porta_textChanged();

private:
    Ui::Dialog * ui;
    QUdpSocket * udpSocket;
    QString ip;
    QString port;
};

#endif // DIALOG_H
