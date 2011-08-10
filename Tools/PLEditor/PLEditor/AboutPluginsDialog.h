#ifndef ABOUTPLUGINSDIALOG_H
#define ABOUTPLUGINSDIALOG_H

#include <QDialog>

namespace Ui {
    class AboutPluginsDialog;
}

class AboutPluginsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutPluginsDialog(QWidget *parent = 0);
    ~AboutPluginsDialog();

private:
    Ui::AboutPluginsDialog *ui;
};

#endif // ABOUTPLUGINSDIALOG_H
