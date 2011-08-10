#include "AboutPluginsDialog.h"
#include "ui_AboutPluginsDialog.h"

AboutPluginsDialog::AboutPluginsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutPluginsDialog)
{
    ui->setupUi(this);
}

AboutPluginsDialog::~AboutPluginsDialog()
{
    delete ui;
}
