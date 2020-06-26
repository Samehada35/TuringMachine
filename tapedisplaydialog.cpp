#include "tapedisplaydialog.h"
#include "ui_tapedisplaydialog.h"


TapeDisplayDialog::TapeDisplayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TapeDisplayDialog)
{
    ui->setupUi(this);
    this->move(650,30);
    this->setStyleSheet("background-color:##d9e7ff");
    this->setModal(false);
    this->resize(650,1000);


}

TapeDisplayDialog::~TapeDisplayDialog()
{
    delete ui;
}

void TapeDisplayDialog::setTapeHistory(vector<string> tapeHistory){
    this->tapeHistory = tapeHistory;
}
void TapeDisplayDialog::setIndexHistory(vector<int> indexHistory){
    this->indexHistory = indexHistory;
}
void TapeDisplayDialog::setTransitionHistory(vector<Transition> transitionHistory){
    this->transitionHistory = transitionHistory;
}

void TapeDisplayDialog::paintEvent(QPaintEvent* e){
    QPainter painter(this);
    QFont font1 = painter.font();
    QFont font2 = painter.font();
    int x = 150;
    int y = -50;


    font1.setPointSize(font1.pointSize()*2.5);
    font1.setFamily(QString("Lucida Sans"));

    font2.setPointSize(font2.pointSize()*1.75);
    font2.setFamily(QString("Lucida Sans"));

    int rectHeight = 40;
    int rectWidth = 400;

    for(unsigned int i=0;i<tapeHistory.size()-1;i++){
        if(i!=0&&i%12==0){
            y=-50;
            x+=600;
        }

        painter.setFont(font1);

        QRect rect(x,y+=70,rectWidth,rectHeight);
        painter.drawText(rect,Qt::AlignCenter,QString::fromStdString(tapeHistory[i]));
        painter.drawRect(rect);

        painter.setFont(font2);

        painter.drawText(x-145,y+15,QString::fromStdString("State :"+transitionHistory[i].getCurrentState()));
        painter.drawText(x-145,y+45,QString::fromStdString("Symbol :"+string(1,transitionHistory[i].getCurrentSymbol())));
        painter.drawText(x+indexHistory[i]*20+rectWidth/2-double(tapeHistory[i].size())*7.8,y-5,QString::fromStdString("↓"));

    }

    painter.setFont(font1);

    QRect rect(x,y+=60,400,40);
    painter.drawText(rect,Qt::AlignCenter,QString::fromStdString(tapeHistory[tapeHistory.size()-1]));
    painter.drawRect(rect);

    painter.setFont(font2);
    painter.drawText(x-145,y+15,QString::fromStdString("State :"+transitionHistory[transitionHistory.size()-1].getCurrentState()));
    painter.drawText(x-145,y+45,QString::fromStdString("Symbol :"+string(1,transitionHistory[transitionHistory.size()-1].getCurrentSymbol())));
}
