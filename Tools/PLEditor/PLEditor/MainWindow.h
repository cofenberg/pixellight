#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void on_actionAbout_PL_Editor_triggered();

	void on_actionAbout_Plugins_triggered();

	void on_actionOptions_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
