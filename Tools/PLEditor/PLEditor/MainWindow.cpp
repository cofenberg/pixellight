#include <QPluginLoader>
#include "MainWindow.h"
#include "ui_mainwindow.h"

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
