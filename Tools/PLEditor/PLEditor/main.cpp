#include "Application.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
	PLEditor::Application a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
