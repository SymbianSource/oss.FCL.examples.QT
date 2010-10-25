/*
* Copyright (c) 2010 Symbian Foundation.
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of the "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Symbian Foundation - Initial contribution
*
* Description:
* Project main function.
*/

#include <QtGui/QApplication>
#include "mywebwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyWebWidget w;

#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif

    return a.exec();
}
