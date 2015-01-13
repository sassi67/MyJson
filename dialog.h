#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent, QStandardItemModel *model);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QStandardItemModel *m_Model;

};

#endif // DIALOG_H
