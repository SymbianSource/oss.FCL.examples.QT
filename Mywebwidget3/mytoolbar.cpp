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
* Implementation of the MyToolBar class.
*/

#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QHBoxLayout>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>

#include "mytoolbar.h"

const QString locString("My Location: ");

MyToolBar::MyToolBar(QWidget* parent)
    :QWidget(parent)
{
    m_backButton = new QPushButton("Back",this);
    m_locationLabel = new QLabel(this);

    m_location = QGeoPositionInfoSource::createDefaultSource(this);
    m_location->setUpdateInterval(10000);
    m_location->startUpdates();

    m_layout = new QHBoxLayout;
    m_layout->addWidget(m_backButton);
    m_layout->addWidget(m_locationLabel);
    m_layout->insertSpacing(1,10);
    setLayout(m_layout);
    m_layout->addStretch();

    connect(m_backButton,SIGNAL(clicked()),SLOT(onBackPressed()));
    connect(m_location,SIGNAL(positionUpdated(QGeoPositionInfo)),SLOT(onPositionUpdated(QGeoPositionInfo)));
}

MyToolBar::~MyToolBar()
{

}

void MyToolBar::onPositionUpdated(const QGeoPositionInfo& posInfo)
{
    QGeoCoordinate coordinate = posInfo.coordinate();
    QString label_coordinate = coordinate.toString();
    m_locationLabel->setText(locString+" "+label_coordinate);
}

void MyToolBar::onBackPressed()
{
    emit goBack();
}
