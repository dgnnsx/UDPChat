#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(int chatNo, int port, QString style, QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);

    this->setWindowTitle("UDP Chat - " + QString::number(chatNo));

    // Checkbox
    ui->checkBox_conectado->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkBox_conectado->setFocusPolicy(Qt::NoFocus);

    // Área de texto
    ui->plainTextEdit->setReadOnly(true);
    ui->plainTextEdit->setStyleSheet(style);

    // UDP
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, port);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));

    // Meu ip
    ui->label_meu_ip->setText(udpSocket->localAddress().toString());
    // Minha porta
    ui->label_minha_porta->setText(QString::number(udpSocket->localPort()));
}

Dialog::~Dialog() {
    delete ui;
    udpSocket->close();
}

void Dialog::on_pushButton_conectar_clicked() {
    this->ip = ui->lineEdit_ip->text();
    this->port = ui->lineEdit_porta->text();
    this->ui->checkBox_conectado->setChecked(true);
}

void Dialog::on_pushButton_enviar_clicked() {
    QString string = ui->lineEdit->text();

    // Verificação para não enviar strings vazias
    if(!string.isEmpty()) {
        ui->plainTextEdit->appendPlainText("Enviado >> " + string);
        udpSocket->writeDatagram(string.toUtf8(), QHostAddress(this->ip), this->port.toInt());
        ui->lineEdit->clear();
    }
}


void Dialog::readPendingDatagrams() {
    while(udpSocket->hasPendingDatagrams()) {
        QByteArray buffer;
        QHostAddress sender;
        quint16 senderPort;

        buffer.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
        QString senderIp = sender.toString().split("ffff:").value(1);
        ui->plainTextEdit->appendPlainText("Recebido << " + QString::fromUtf8(buffer));
    }
}

void Dialog::on_lineEdit_ip_textChanged() {
    this->ui->checkBox_conectado->setChecked(false);
}

void Dialog::on_lineEdit_porta_textChanged() {
    this->ui->checkBox_conectado->setChecked(false);
}
