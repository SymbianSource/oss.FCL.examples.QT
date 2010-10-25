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
* Declaration of the MyToolBar class.
*/

#ifndef MYTOOLBAR_H
#define MYTOOLBAR_H

#include <qmobilityglobal.h>
#include <QtGui/QWidget>

QTM_BEGIN_NAMESPACE
class QGeoPositionInfo;
class QGeoPositionInfoSource;
QTM_END_NAMESPACE

QTM_USE_NAMESPACE

class QHBoxLayout;
class QPushButton;
class QLabel;

class MyToolBar : public QWidget
{
    Q_OBJECT

public:
    MyToolBar(QWidget *parent = 0);
    ~MyToolBar();

signals:
    void goBack();
    void showLocation();

private slots:
    void onBackPressed();
    void onPositionUpdated(const QGeoPositionInfo& posInfo);

private:
    QPushButton* m_backButton;
    QLabel* m_locationLabel;
    QHBoxLayout* m_layout;
    QGeoPositionInfoSource* m_location;
};

#endif // MYTOOLBAR_H
