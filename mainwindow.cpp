#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_readFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(NULL,"Open airports json",".","*.json");
    if (fileName == ""){
        QMessageBox errorFile;
        errorFile.setText("Entered file is not valid");
        errorFile.exec();
    }
    else {
        QMessageBox errorFile;
        errorFile.setText("Nice");
        errorFile.exec();
        dataWindow* dataW = new dataWindow(nullptr, fileName);
        dataW->setAttribute(Qt::WA_QuitOnClose,true);
        dataW->show();
    }
}

