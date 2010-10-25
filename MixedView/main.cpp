#include <QtGui/QApplication>
#include "mainwindow.h"

// Needed Symbian specific headers
#ifdef Q_OS_SYMBIAN
#include <eikenv.h>
#include <eikappui.h>
#include <aknenv.h>
#include <aknappui.h>
#include <coeaui.h>
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);




    MainWindow w;
    a.installEventFilter(&w);
    w.setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    // Symbian specific code to keep the screen orientation of the game in Portrait mode.
#ifdef Q_OS_SYMBIAN
    CAknAppUi* appUi = dynamic_cast<CAknAppUi*> (CEikonEnv::Static()->AppUi());
    if(appUi){
      TRAP_IGNORE( appUi->SetOrientationL( CAknAppUi::EAppUiOrientationPortrait ) );
    }
#endif

#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif

    return a.exec();
}
