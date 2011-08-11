#include <QPluginLoader>
#include <QDockWidget>
#include "Application.h"
#include "PluginManager.h"
#include "AboutDialog.h"
#include "AboutPluginsDialog.h"
#include "OptionsDialog.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Interfaces/IPlugin.h"
#include "Interfaces/IPluginDockWidget.h"

using namespace PLEditor;

template <class T> class VPtr
{
public:
    static T* asPtr(QVariant v)
    {
	return  (T *) v.value<void *>();
    }

    static QVariant asQVariant(T* ptr)
    {
	return qVariantFromValue((void *) ptr);
    }
};


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	
	fillWindowMenu();
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

void MainWindow::onWindowMenuActionTriggerd(QAction* pAction)
{
	
}

void MainWindow::fillWindowMenu()
{
	PluginManager &cManager = qApp->getPluginManager();
	const QList<const IPlugin*> plugins = cManager.getPlugins();
	foreach(const IPlugin* pPlugin, plugins)
	{
		if (pPlugin->getType() != IPlugin::EType::TypeDockWidget)
			continue;
		
		IPlugin *pPl = pPlugin->Clone();
		
		IPluginDockWidget* pDockPlugin = reinterpret_cast<IPluginDockWidget*>(pPl);
		
		QDockWidget *pDockWidget = pDockPlugin->GetWidget();
		
		addDockWidget(pDockPlugin->InitialArea(), pDockWidget);
		pDockWidget->hide();
		
		ui->menuWindpw->addAction(pDockWidget->toggleViewAction());
	}
}
