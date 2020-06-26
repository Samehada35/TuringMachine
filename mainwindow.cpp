#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTabBar>
#include <iostream>
#include <fstream>
#include "tapedisplaydialog.h"
#include "ui_tapedisplaydialog.h"

using std::string;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Turing Machine");
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->tabBar()->hide();
    ui->tabWidget_2->tabBar()->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete tm;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox message;
    message.setText("This application was made by Arabi Sami and Arezki Bouzid");
    message.exec();
}

void MainWindow::on_actionNew_Machine_Description_triggered()
{
    ui->tabWidget_2->setCurrentIndex(0);
    ui->plainTextEdit->setPlainText("");

    tm = new TuringMachine();
}


void MainWindow::on_actionImport_Machine_Description_triggered()
{
    ui->tabWidget_2->setCurrentIndex(1);
    string fileName = QFileDialog::getOpenFileName(this).toStdString();
    ifstream in(fileName);
    string content((std::istreambuf_iterator<char>(in) ),(std::istreambuf_iterator<char>()));
    ui->textBrowser_2->setText(QString::fromStdString(content));

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_clicked()
{
    string input = ui->lineEdit_2->text().toStdString();
    bool steps = ui->checkBox->isChecked();
    bool state = ui->checkBox_2->isChecked();
    bool tape = ui->checkBox_3->isChecked();

    if(!steps && !state && !tape){
        QMessageBox message;
        message.critical(0,"Error","You have to choose at least one of the options : steps,state or tape");
    }else if(input.empty()){
        QMessageBox message;
        message.critical(0,"Error","You have to specify an input word");
    }else if(ui->tabWidget_2->currentIndex()==0 && ui->plainTextEdit->toPlainText().toStdString().empty()){
        QMessageBox message;
        message.critical(0,"Error","You have to provide a turing machine description");
    }else if(ui->tabWidget_2->currentIndex()==1 && ui->textBrowser_2->toPlainText().toStdString().empty()){
        QMessageBox message;
        message.critical(0,"Error","You have to provide a turing machine description");
    }else{
        if(ui->tabWidget_2->currentIndex()==0){
            string description = ui->plainTextEdit->toPlainText().toStdString();

            try{
                tm = TuringMachine::parseString(description);

                string desc = tm->describe();
                string result = tm->run(input,steps,state,tape);

                ui->tabWidget->setCurrentIndex(1);
                ui->textBrowser->setText(QString::fromStdString(desc+"\n\n"+result));

                TapeDisplayDialog* d = new TapeDisplayDialog(this);
                d->setTapeHistory(tm->getTapeHistory());
                d->setIndexHistory(tm->getIndexHistory());
                d->setTransitionHistory(tm->getTransitionsHistory());
                Ui_TapeDisplayDialog ui_d;

                ui_d.setupUi(d);

                d->show();
            }catch(string error){
                QMessageBox message;
                message.critical(0,"Parsing Error",QString::fromStdString(error));
            }
        }else{
            string description = ui->textBrowser_2->toPlainText().toStdString();

            try {
                tm = TuringMachine::parseString(description);

                string desc = tm->describe();
                string result = tm->run(input,steps,state,tape);

                ui->tabWidget->setCurrentIndex(1);
                ui->textBrowser->setText(QString::fromStdString(desc+"\n\n"+result));




                TapeDisplayDialog* d = new TapeDisplayDialog(this);
                d->setTapeHistory(tm->getTapeHistory());
                d->setIndexHistory(tm->getIndexHistory());
                d->setTransitionHistory(tm->getTransitionsHistory());
                Ui_TapeDisplayDialog ui_d;

                ui_d.setupUi(d);

                d->show();
            }catch(string error){
                QMessageBox message;
                message.critical(0,"Parsing Error",QString::fromStdString(error));
            }


        }
    }
}

