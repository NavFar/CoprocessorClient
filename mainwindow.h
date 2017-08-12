#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void connectToPort(QString portName);

private slots:
    void handleError(QSerialPort::SerialPortError error);
    void plus();
    void minus();
    void multiplie();
    void divide();
private:
    Ui::MainWindow *ui;
    QSerialPort *comPort;
    void disableAll();
    void enableAll();
    void writeOnStatusBar(QString message);
    void writeToPort(char command);
    QByteArray readFromPort();
    void fillBlank();
    int convert(float input);
    float convert(int input);
    void operation(char command);
    float ByteToFloat(QByteArray array);

};
union convertor{
    int   i;
    float f;
    char ba[sizeof(float)];
};

#endif // MAINWINDOW_H
