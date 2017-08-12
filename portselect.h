#ifndef PORTSELECT_H
#define PORTSELECT_H

#include <QDialog>

namespace Ui {
class PortSelect;
}

class PortSelect : public QDialog
{
    Q_OBJECT

public:
    explicit PortSelect(QWidget *parent = 0);
    ~PortSelect();
    QString getSelectedPort();
private slots:
    void saveChoice();
private:
    QString selectedPort;
    Ui::PortSelect *ui;
};

#endif // PORTSELECT_H
