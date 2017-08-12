#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <cmath>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/Icon/icon.png"));
    connect(this->ui->Exit,SIGNAL(clicked()),this,SLOT(close()));//Exit button
    connect(this->ui->PlusButton,SIGNAL(clicked()),this,SLOT(plus()));
    connect(this->ui->MinusButton,SIGNAL(clicked()),this,SLOT(minus()));
    connect(this->ui->MultiplieButton,SIGNAL(clicked()),this,SLOT(multiplie()));
    connect(this->ui->DivideButton,SIGNAL(clicked()),this,SLOT(divide()));

    this->comPort = new QSerialPort(this);
    connect(this->comPort, SIGNAL(error(QSerialPort::SerialPortError)), this,SLOT(handleError(QSerialPort::SerialPortError)));
    this->setWindowTitle("FPGA Calculator");
    this->writeOnStatusBar("Ready for new Inputs");
    fillBlank();
}

MainWindow::~MainWindow()
{
    delete ui;
    this->comPort->close();
}
QByteArray MainWindow::readFromPort(){
    QByteArray requestData = this->comPort->readAll();
    QByteArray temp;

               while (this->comPort->waitForReadyRead(75)){
                   temp = this->comPort->readAll();
                   requestData+=temp;
               }


    return requestData.mid(0,sizeof(float)+1);
}
void MainWindow::writeToPort(char command){
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream<<convert(this->ui->A->text().toFloat());
    stream<<convert(this->ui->B->text().toFloat());
    data.append(command);
    this->comPort->write(data);
//    qDebug()<<data;
}

void MainWindow::connectToPort(QString portName){
    this->comPort->setPortName(portName);

    QMessageBox messageBox;
    if(this->comPort->open(QIODevice::ReadWrite)){
        if(\
        this->comPort->setBaudRate(QSerialPort::Baud2400) &&\
        this->comPort->setDataBits(QSerialPort::Data8) &&\
        this->comPort->setParity(QSerialPort::NoParity) &&\
        this->comPort->setStopBits(QSerialPort::OneStop)&&\
        this->comPort->setFlowControl(QSerialPort::NoFlowControl))
        {

        }
        else
        {
            messageBox.setText("Com Port Can't be set");
            messageBox.exec();
            exit(0);
        }
    }else
    {
        messageBox.setText("Com Port Can't be Open");
        messageBox.exec();
        exit(0);
    }
}
void MainWindow::disableAll(){
    this->ui->A->setEnabled(false);
    this->ui->B->setEnabled(false);
    this->ui->PlusButton->setEnabled(false);
    this->ui->MinusButton->setEnabled(false);
    this->ui->MultiplieButton->setEnabled(false);
    this->ui->DivideButton->setEnabled(false);
}
void MainWindow::enableAll(){
    this->ui->A->setEnabled(true);
    this->ui->B->setEnabled(true);
    this->ui->PlusButton->setEnabled(true);
    this->ui->MinusButton->setEnabled(true);
    this->ui->MultiplieButton->setEnabled(true);
    this->ui->DivideButton->setEnabled(true);
}
void MainWindow::writeOnStatusBar(QString message){
    this->statusBar()->showMessage(message);
}
void MainWindow::fillBlank(){
    if(this->ui->A->text().trimmed().isEmpty())
    {
        this->ui->A->setText(QString::number(0.00));
    }
    if(this->ui->B->text().trimmed().isEmpty())
    {
        this->ui->B->setText(QString::number(0.00));
    }
}
int MainWindow::convert(float input){
    convertor conv ;
    conv.f=input;
    return conv.i;
}
float MainWindow::convert(int input){
    convertor conv ;
    conv.i=input;
    return conv.f;
}
void MainWindow::plus(){
    operation(1);
}
void MainWindow::minus(){

    float B = this->ui->B->text().toFloat();
    this->ui->B->setText(QString::number(-1*B));
    operation(1);
    this->ui->B->setText(QString::number(B));
}
void MainWindow::multiplie(){
    operation(2);
}
void MainWindow::divide(){
    operation(4);
}
void MainWindow::operation(char command){
    this->writeOnStatusBar("Sending Data to FPGA");
    disableAll();
    writeToPort(command);
    this->writeOnStatusBar("Wait to read Data  from FPGA");
    QByteArray res = this->readFromPort();
    float resFloat=ByteToFloat(res.mid(0,sizeof(float)));
    QByteArray overflow=res.mid(sizeof(float),1);
    qDebug()<<res;
    QByteArray temp=QByteArrayLiteral("\x80");
    this->ui->Result->setText(QString::number(resFloat,'g',10));
    enableAll();
    this->writeOnStatusBar("Result is Ready");
    return;
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        this->writeOnStatusBar("Serial Port Disconnected");
        this->disableAll();
    }
}
float MainWindow:: ByteToFloat(QByteArray array)
{
    convertor conv;
   for(int i=0;i<array.length();i++)
   {
       conv.ba[sizeof(float)-1-i]=array[i];
   }
   return conv.f;
}
