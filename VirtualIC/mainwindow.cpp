#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);

    timerOne = new QTimer();
    connect(timerOne, SIGNAL(timeout()), this, SLOT(AnimateDataOne()));
    timerOne->start(1200);

    timerTwo = new QTimer();
    connect(timerTwo, SIGNAL(timeout()), this, SLOT(AnimateDataTwo()));
    timerTwo->start(1000);

    timerThree = new QTimer();
    connect(timerThree, SIGNAL(timeout()), this, SLOT(AnimateDataThree()));

    instrumentClusterScene = new QGraphicsScene();
    instrumentClusterScene->setSceneRect(0,0,1200,700);
    ui->graphicsView->setScene(instrumentClusterScene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    lTurn = new BackgroundItem(QPixmap(":images_root/turn_left.png"));
    lTurn->setPos(585, 130);
    instrumentClusterScene->addItem(lTurn);

    rTurn = new BackgroundItem(QPixmap(":images_root/turn_right.png"));
    rTurn->setPos(735, 130);
    instrumentClusterScene->addItem(rTurn);

    engine = new BackgroundItem(QPixmap(":images_root/engine.png"));
    engine->setPos(870, 135);
    instrumentClusterScene->addItem(engine);

    speed = new BackgroundItem(QPixmap(":images_root/speed.png"));
    speed->setPos(1022,140);
    instrumentClusterScene->addItem(speed);

    hBeam = new BackgroundItem(QPixmap(":images_root/high_beam.png"));
    hBeam->setPos(595, 340);
    instrumentClusterScene->addItem(hBeam);

    abs = new BackgroundItem(QPixmap(":images_root/abs.png"));
    abs->setPos(725, 346);
    instrumentClusterScene->addItem(abs);

    tpms = new BackgroundItem(QPixmap(":images_root/tpms.png"));
    tpms->setPos(877, 345);
    instrumentClusterScene->addItem(tpms);

    tcontrol = new BackgroundItem(QPixmap(":images_root/t_control.png"));
    tcontrol->setPos(1012, 346);
    instrumentClusterScene->addItem(tcontrol);

    infoText = new InfoText();
    infoText->setPos(43,145);
    instrumentClusterScene->addItem(infoText);

    dataTextOne = new DataTextOne();
    dataTextOne->setPos(45,170);
    instrumentClusterScene->addItem(dataTextOne);

    dataTextOneC = new DataTextOneC();
    dataTextOneC->setPos(45,170);

    dataTextOneWhite = new DataTextOneWhite();
    dataTextOneWhite->setPos(385,170);
    instrumentClusterScene->addItem(dataTextOneWhite);

    dataTextOneRed = new DataTextOneRed();
    dataTextOneRed->setPos(385,170);

    endRedOne = new EndRedOne();
    endRedOne->setPos(463,170);

    dataTextTwo = new DataTextTwo();
    dataTextTwo->setPos(45,200);
    instrumentClusterScene->addItem(dataTextTwo);

    dataTextTwoC = new DataTextTwoC();
    dataTextTwoC->setPos(45,200);

    dataTextTwoWhite = new DataTextTwoWhite();
    dataTextTwoWhite->setPos(325,200);
    instrumentClusterScene->addItem(dataTextTwoWhite);

    dataTextTwoRed = new DataTextTwoRed();
    dataTextTwoRed->setPos(325,200);

    endRedTwo = new EndRedTwo();
    endRedTwo->setPos(495,200);

    dataTextThree = new DataTextThree();
    dataTextThree->setPos(45,230);

    dataTextThreeC = new DataTextThreeC();
    dataTextThreeC->setPos(45,230);

    dataTextThreeWhite = new DataTextThreeWhite();
    dataTextThreeWhite->setPos(384,230);

    dataTextThreeRed = new DataTextThreeRed();
    dataTextThreeRed->setPos(384,230);

    endRedThree = new EndRedThree();
    endRedThree->setPos(463,230);

    //Left Turn signal animation
    leftBlinkerAnimation = new LeftBlinkerAnimation();
    leftBlinkerAnimation->setPos(597,145);

    //Left Turn signal animation
    rightBlinkerAnimation = new RightBlinkerAnimation();
    rightBlinkerAnimation->setPos(746,145);

    speedAnimation = new SpeedAnimation();
    speedAnimation->setPos(1022,140);

    toggleOn = false;
    toggleOnTwo = false;
    toggleOnThree = false;

    isWhite = true;
    isRed = false;

    isWhiteTwo = true;
    isRedTwo = false;

    dataThreeActive = false;
    isWhiteThree = false;
    isRedThree = false;

    itemCount = nullptr;
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::AnimateDataOne(){

    if(isWhite){
        instrumentClusterScene->removeItem(dataTextOne);
        instrumentClusterScene->removeItem(dataTextOneWhite);
        instrumentClusterScene->addItem(dataTextOneC);
        instrumentClusterScene->addItem(dataTextOneRed);
        instrumentClusterScene->addItem(endRedOne);
        isWhite = false;
        isRed = true;
    }
    else if(isRed){
        instrumentClusterScene->removeItem(dataTextOneC);
        instrumentClusterScene->removeItem(dataTextOneRed);
        instrumentClusterScene->removeItem(endRedOne);
        instrumentClusterScene->addItem(dataTextOne);
        instrumentClusterScene->addItem(dataTextOneWhite);
        isWhite = true;
        isRed = false;
    }else{
        return;
    }
}

void MainWindow::AnimateDataTwo(){

    if(isWhiteTwo){
        instrumentClusterScene->removeItem(dataTextTwo);
        instrumentClusterScene->removeItem(dataTextTwoWhite);
        instrumentClusterScene->addItem(dataTextTwoC);
        instrumentClusterScene->addItem(dataTextTwoRed);
        instrumentClusterScene->addItem(endRedTwo);
        isWhiteTwo = false;
        isRedTwo = true;
    }
    else if(isRedTwo){
        instrumentClusterScene->removeItem(dataTextTwoC);
        instrumentClusterScene->removeItem(dataTextTwoRed);
        instrumentClusterScene->removeItem(endRedTwo);
        instrumentClusterScene->addItem(dataTextTwo);
        instrumentClusterScene->addItem(dataTextTwoWhite);
        isWhiteTwo = true;
        isRedTwo = false;
    }else{
        return;
    }
}

void MainWindow::AnimateDataThree(){

    if(!dataThreeActive){
        instrumentClusterScene->addItem(dataTextThree);
        instrumentClusterScene->addItem(dataTextThreeWhite);
        dataThreeActive = true;
        isWhiteThree = true;
    }
    else if(isWhiteThree){
        instrumentClusterScene->removeItem(dataTextThree);
        instrumentClusterScene->removeItem(dataTextThreeWhite);
        instrumentClusterScene->addItem(dataTextThreeC);
        instrumentClusterScene->addItem(dataTextThreeRed);
        instrumentClusterScene->addItem(endRedThree);
        isWhiteThree = false;
        isRedThree = true;
    }
    else if(isRedThree){
        instrumentClusterScene->removeItem(dataTextThreeC);
        instrumentClusterScene->removeItem(dataTextThreeRed);
        instrumentClusterScene->removeItem(endRedThree);
        instrumentClusterScene->addItem(dataTextThree);
        instrumentClusterScene->addItem(dataTextThreeWhite);
        isWhiteThree = true;
        isRedThree = false;
    }else{
        return;
    }
}

void MainWindow::on_On_Off_One_clicked(){

    toggleOn = !toggleOn;

    if (toggleOn){
        timerThree->start(500);
        instrumentClusterScene->removeItem(lTurn);
        instrumentClusterScene->addItem(leftBlinkerAnimation);
    }
    else if(!toggleOn){
        timerThree->stop();
        instrumentClusterScene->removeItem(leftBlinkerAnimation);
        instrumentClusterScene->addItem(lTurn);
        if(isWhiteThree){
            instrumentClusterScene->removeItem(dataTextThree);
            instrumentClusterScene->removeItem(dataTextThreeWhite);
            dataThreeActive = false;
            isRedThree = false;
            isWhiteThree =false;
        }
        else if(isRedThree){
            instrumentClusterScene->removeItem(dataTextThreeC);
            instrumentClusterScene->removeItem(dataTextThreeRed);
            instrumentClusterScene->removeItem(endRedThree);
            dataThreeActive = false;
            isRedThree = false;
            isWhiteThree =false;
        }
    }
}

void MainWindow::on_On_Off_Two_clicked(){
    toggleOnTwo = !toggleOnTwo;

    if (toggleOnTwo){
    instrumentClusterScene->removeItem(rTurn);
    instrumentClusterScene->addItem(rightBlinkerAnimation);
    }
    else if (!toggleOnTwo) {
        instrumentClusterScene->removeItem(rightBlinkerAnimation);
        instrumentClusterScene->addItem(rTurn);
    }
}

void MainWindow::on_On_Off_Three_clicked(){

}

void MainWindow::on_On_Off_Four_clicked(){
    toggleOnThree = !toggleOnThree;

    if (toggleOnThree){
    instrumentClusterScene->removeItem(speed);
    instrumentClusterScene->addItem(speedAnimation);
    }
    else if (!toggleOnThree) {
        instrumentClusterScene->removeItem(speedAnimation);
        instrumentClusterScene->addItem(speed);
    }
}
