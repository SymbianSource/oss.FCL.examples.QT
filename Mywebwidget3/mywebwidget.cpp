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
* Implementation of the MyWebWidget class.
*/

#include <QtGui/QLineEdit>
#include <QtWebKit/QWebView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtCore/QUrl>
#include <QtGui/QAction>
#include <QtWebKit/QWebHistory>

#include "mytoolbar.h" //added
#include "mywebwidget.h"

MyWebWidget::MyWebWidget(QWidget *parent)
    : QWidget(parent)
{
    m_softkeyAction = new QAction( tr("Options"), this );
    m_softkeyAction->setSoftKeyRole(QAction::PositiveSoftKey);
    addAction(m_softkeyAction);

    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setStyleSheet("background-color:white; padding: 6px ; color:blue");
    m_lineEdit->setText("Enter url ...");

    m_view = new QWebView(this);
    m_view->load(QUrl("http://blog.symbian.org"));

    m_layout = new QVBoxLayout();

    m_layout->addWidget(m_lineEdit);
    m_layout->addWidget(m_view);
    m_layout->insertSpacing(1,10);

    //add toolbar
    m_toolbar = new MyToolBar(this);
    m_layout->addWidget(m_toolbar);

    setLayout(m_layout);
    m_layout->addStretch();

    connect(m_lineEdit,SIGNAL(editingFinished()),SLOT(openUrl()));
    connect(m_view,SIGNAL(loadFinished(bool)),SLOT(onLoadFinished(bool)));

    //connect the toolbar as well
    connect(m_toolbar,SIGNAL(goBack()),SLOT(loadPreviousPage()));
}

MyWebWidget::~MyWebWidget()
{

}

//added
void MyWebWidget::loadPreviousPage()
{
    if(m_view->history()->canGoBack())
    {
        m_view->history()->back();
    }
}

void MyWebWidget::openUrl()
{
    QString url(m_lineEdit->text());
    if(!url.contains("http://",Qt::CaseInsensitive))
        url.prepend("http://");
    m_view->load(QUrl(url));

}

void MyWebWidget::onLoadFinished(bool finished)
{
    if(finished){
        m_lineEdit->clear();
        m_lineEdit->setText(tr("Enter url ..."));
    }
}
