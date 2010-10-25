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
* Declaration of the MyWebWidget class.
*/

#ifndef MYWEBWIDGET_H
#define MYWEBWIDGET_H

#include <QtGui/QWidget>

class QWebView;
class QLineEdit;
class QVBoxLayout;
class QLabel;
class QAction;
class QWebHistory;
class QGeoPositionInfoSource;
class MyToolBar; //added

class MyWebWidget : public QWidget
{
    Q_OBJECT

public:
    MyWebWidget(QWidget *parent = 0);
    ~MyWebWidget();

private slots:
    void openUrl();
    void onLoadFinished(bool finished);
    void loadPreviousPage();

private:
    QAction* m_softkeyAction;
    QWebView* m_view;
    QLineEdit* m_lineEdit;
    QLabel* m_label;
    QVBoxLayout* m_layout;
    MyToolBar* m_toolbar;
    QWebHistory* m_history;
};

#endif // MYWEBWIDGET_H
