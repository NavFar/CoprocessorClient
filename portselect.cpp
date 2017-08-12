#include "portselect.h"
#include "ui_portselect.h"
#include <QSerialPortInfo>
#include <QDebug>
PortSelect::PortSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PortSelect)
{
    this->selectedPort= QString();
    ui->setupUi(this);
    QSerialPortInfo info;
    QList<QSerialPortInfo> allPorts =info.availablePorts();
    for(int i=0;i<allPorts.length();i++){
        this->ui->comboBox->addItem(allPorts.at(i).portName());
    }
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(saveChoice()));
    this->setWindowTitle("FPGA Calculator Port");
    this->setWindowIcon(QIcon(":/Icon/icon.png"));

}

PortSelect::~PortSelect()
{
    delete ui;
}
void PortSelect:: saveChoice(){
    int index= this->ui->comboBox->currentIndex();
    this->selectedPort=this->ui->comboBox->itemText(index);
}
QString PortSelect:: getSelectedPort(){
    return this->selectedPort;
}

