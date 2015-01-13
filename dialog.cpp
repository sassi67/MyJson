#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent, QStandardItemModel *model) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_Model(model)
{
    ui->setupUi(this);

    ui->treeView->setModel(m_Model);
}

Dialog::~Dialog()
{
    delete ui;
}
