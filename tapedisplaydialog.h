#ifndef TAPEDISPLAYDIALOG_H
#define TAPEDISPLAYDIALOG_H

#include <QDialog>
#include <QPainter>
#include <vector>
#include <iostream>
#include <QFont>
#include <QGridLayout>
#include <QScrollArea>
#include <QLayout>
#include <QWidgetItem>
#include "transition.h"


using std::vector;
using std::string;

namespace Ui {
class TapeDisplayDialog;
}

class TapeDisplayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TapeDisplayDialog(QWidget *parent = nullptr);
    ~TapeDisplayDialog();
    void setTapeHistory(vector<string> tapeHistory);
    void setIndexHistory(vector<int> indexHistory);
    void setTransitionHistory(vector<Transition> transitionHistory);
private:
    Ui::TapeDisplayDialog *ui;
    vector<string> tapeHistory;
    vector<int> indexHistory;
    vector<Transition> transitionHistory;

protected:
    void paintEvent(QPaintEvent* e);

};

#endif // TAPEDISPLAYDIALOG_H
