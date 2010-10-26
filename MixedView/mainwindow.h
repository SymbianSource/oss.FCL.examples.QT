#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QAccelerometer>
#include <QLineEdit>
#include <QGraphicsProxyWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaServiceProvider>
#include <QAudioOutput>
#include <QFile>
QTM_USE_NAMESPACE

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsEllipseItem *mPacman, *mPacCollider;
    QTimer *mUpdateTimer;
    int mPacState;
    QAccelerometer *mAccelerometer;
    qreal xAxis, yAxis;
    QPointF mLastPt;
    bool mPause;
    QPushButton *pauseButton;
    QMediaPlayer *mPlayer;
    QMediaPlaylist *mPlayList;
    QGraphicsScene *mScene;
    int mNumHits;
    QAudioOutput* mAudio;
    QFile file;


private slots:
    void updateGraphics();
    void updateReading();
    void pause();
    void statusChanged(QMediaPlayer::MediaStatus);

private:
    void setupBoundries();
    void checkCollisions();

};

#endif // MAINWINDOW_H
