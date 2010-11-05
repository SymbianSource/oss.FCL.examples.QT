#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsProxyWidget>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QResizeEvent>
#include <QFile>
#include <QStringList>
#include <QSound>

// define the borders of the image
#define LEFT_EDGE -103
#define RIGHT_EDGE 180
#define TOP_EDGE -156
#define BOTTOM_EDGE 145
// The number of Hits is always at least 2
// since there is a visible and invisible image
// on top of each other at the same coordinates
#define HITS 2

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->setupUi(this);
    mPacState = 0;
    xAxis = yAxis = 0;
    mLastPt.setX(0);
    mLastPt.setY(0);
    mPause = false;

    // declare the accelerometer
    mAccelerometer = new QAccelerometer(this);
    mAccelerometer->start();

    QSize screenSize = this->size();
    mScene = new QGraphicsScene();

    QRect sceneRect = ui->mainGraphicsView->rect();
    mScene->setSceneRect(sceneRect);
   // scene->setBackgroundBrush (QBrush(Qt::blue));

    // now set up the boundries
    setupBoundries();

    QPixmap mazeImage(":/media/maze.jpg");
    int width = screenSize.width();
    mazeImage = mazeImage.scaledToWidth(width);
    QGraphicsPixmapItem *backGround = mScene->addPixmap(mazeImage);
    backGround->setPos(-140,-200);

    mPacCollider = new QGraphicsEllipseItem(0, 0, 18, 18);
    mPacCollider->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mPacCollider);

    mPacman = new QGraphicsEllipseItem(0, 0, 18, 18);
    mPacman->setBrush(QBrush(Qt::yellow));
    mPacman->setSpanAngle(4500);
    mScene->addItem(mPacman);

    // lets place a pause button in the view
    pauseButton = new QPushButton("Pause");
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
    pauseButton->setMaximumHeight(40);
    QGraphicsProxyWidget *buttonProxy = mScene->addWidget(pauseButton);
    buttonProxy->setPos(0, -220);

    ui->mainGraphicsView->setScene(mScene);
    ui->mainGraphicsView->show();

    mPacman->setPos(20,-8);
    mPacCollider->setPos(20, -8);
    // declare our update timer
    mUpdateTimer = new QTimer(this);
    connect(mUpdateTimer, SIGNAL(timeout()), this, SLOT(updateGraphics()));
    mUpdateTimer->start(250);

    // connect the accelerometer to the readingChanged signal
    connect(mAccelerometer, SIGNAL(readingChanged()), this, SLOT(updateReading()));
    mNumHits = 1;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateGraphics() {
    if (mPause)
        return;
    // update the pacman mouth state
    // will eventually change this to a graphic
    switch (mPacState) {
    case 0:
        mPacman->setSpanAngle(5700);
        break;
    case 1:
        mPacman->setSpanAngle(4500);
        break;
    case 2:
        mPacman->setSpanAngle(4000);
        break;
    default:
        break;
    }

    mPacState += 1;
    if (mPacState == 2)
        mPacState = 0;

}

void MainWindow::updateReading() {
    if (mPause)
        return;

    checkCollisions();
    xAxis = (xAxis + mAccelerometer->reading()->x()) / 2;
    yAxis = (yAxis + mAccelerometer->reading()->y()) / 2;

}


void MainWindow::checkCollisions() {


    mNumHits = mPacCollider->collidingItems().count();
    if (mNumHits == HITS)
        mLastPt = mPacCollider->pos();

    QPointF pt =  mPacCollider->pos();

    pt.setX(pt.x()-xAxis);
    pt.setY(pt.y()+yAxis);

    if (pt.x()< LEFT_EDGE)
        pt.setX(LEFT_EDGE);
    else if (pt.x()>RIGHT_EDGE)
        pt.setX(RIGHT_EDGE);

    if (pt.y()<TOP_EDGE)
        pt.setY(TOP_EDGE);
    else if (pt.y()>BOTTOM_EDGE)
        pt.setY(BOTTOM_EDGE);

    if (mNumHits == HITS) {
        mPacCollider->setPos(pt);
    }
    else {
        mPacCollider->setPos(mLastPt);

    }
     mPacman->setPos(mLastPt);

}

void MainWindow::pause() {
    mPause = !mPause;
    if (mPause)
        pauseButton->setText("Play");
    else
        pauseButton->setText("Pause");
}


void MainWindow::statusChanged(QMediaPlayer::MediaStatus status) {
    switch (status) {
    case QMediaPlayer::LoadedMedia:
        mPlayer->play();
        break;
    default:
        break;
    }
}

void MainWindow::setupBoundries() {
    // borders
    QGraphicsRectItem *mRect1 = new QGraphicsRectItem(0,0,82,11);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(5,14);

    mRect1 = new QGraphicsRectItem(0,0,11,46);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(40,15);

    mRect1 = new QGraphicsRectItem(0,0,82,11);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(5,91);

    mRect1 = new QGraphicsRectItem(0,0,11,46);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(40,92);

    //
    mRect1 = new QGraphicsRectItem(0,0,47,11);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(-47,-136);

    mRect1 = new QGraphicsRectItem(0,0,50,11);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(88,-136);

    // center square
    mRect1 = new QGraphicsRectItem(0,0,57,35);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(17,-46);

    mRect1 = new QGraphicsRectItem(0,0,11,55);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(40,-160);

    mRect1 = new QGraphicsRectItem(0,0,11,46);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(-82,-131);

    mRect1 = new QGraphicsRectItem(0,0,11,46);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(160,-131);

    mRect1 = new QGraphicsRectItem(0,0,11,64);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(-67,-60);

    mRect1 = new QGraphicsRectItem(0,0,11,64);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(153,-60);

    mRect1 = new QGraphicsRectItem(0,0,11,48);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(-22,-85);

    mRect1 = new QGraphicsRectItem(0,0,11,48);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(103,-85);

    mRect1 = new QGraphicsRectItem(0,0,11,48);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(-27,45);

    mRect1 = new QGraphicsRectItem(0,0,11,48);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(108,45);

    mRect1 = new QGraphicsRectItem(0,0,11,48);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(-71,93);

    mRect1 = new QGraphicsRectItem(0,0,11,48);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(158,95);

    mRect1 = new QGraphicsRectItem(0,0,47,11);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(-63,43);

    mRect1 = new QGraphicsRectItem(0,0,47,11);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(108,45);

    mRect1 = new QGraphicsRectItem(0,0,47,12);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(-70,128);

    mRect1 = new QGraphicsRectItem(0,0,47,11);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(122,132);

    mRect1 = new QGraphicsRectItem(0,0,47,12);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(-23,-85);

    mRect1 = new QGraphicsRectItem(0,0,47,12);
    mRect1->setBrush(QBrush(Qt::transparent));
    mScene->addItem(mRect1);
    mRect1->setPos(67,-85);

}
