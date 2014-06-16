#include <QApplication>
#include <QSplashScreen>

#include "Define.h"
#include "DllLoader.h"
#include "GlobalOption.h"
#include "CoreManager.h"

using namespace EffectEditor;

MainWindow* WindowSet::main_win = NULL;
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap(":/images/OgitorLogo.png"));
	splash->show();

	Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
	splash->showMessage(QObject::tr("Setting up the window ..."),
		topRight, Qt::white);

	CoreManager& core = CoreManager::getInstance();

	if (core.initialize())
	{
		delete splash;
		core.run();
	}
	else
		delete splash;

	core.uninitialize();

    //return 0;
}
