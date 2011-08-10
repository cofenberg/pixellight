#include <QPluginLoader>
#include "AboutDialog.h"
#include "AboutPluginsDialog.h"
#include "OptionsDialog.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	QPluginLoader loader("PLEditorPluginBase.dll");
	QObject *pQObject = loader.instance();
	if (pQObject)
		pQObject = pQObject;
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionAbout_PL_Editor_triggered()
{
	AboutDialog(this).exec();
}

void MainWindow::on_actionAbout_Plugins_triggered()
{
	AboutPluginsDialog(this).exec();
}

void MainWindow::on_actionOptions_triggered()
{
	OptionsDialog(this).exec();
}
