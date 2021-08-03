#include "datawindow.h"
#include "ui_datawindow.h"

using json = nlohmann::json;
using namespace std;

dataWindow::dataWindow(QWidget *parent, QString fileName) :
    QWidget(parent),
    ui(new Ui::dataWindow)
{
    QStringList listID;
    this->fileName = fileName;
    this->data = getJsonFromFile(fileName.toStdString());
    this->graphD = getGraph(this->data);

    for (auto &airport: this->data){
    string id = airport["Airport ID"].get<string>();
string name = airport["Name"].get<string>();
listID << QString::fromStdString(id);
this->airportIds[id] = name;
}


    ui->setupUi(this);
    this->ui->origin->addItems(listID);
    this->ui->destiny->addItems(listID);
    qDebug() << this->fileName;
}

dataWindow::~dataWindow()
{
    delete ui;
}

void dataWindow::on_origin_currentTextChanged(const QString &arg1)
{
    this->ui->originLabel->setText(QString::fromStdString(this->airportIds[arg1.toStdString()]));
}


void dataWindow::on_destiny_currentTextChanged(const QString &arg1)
{
    this->ui->destinyLabel->setText(QString::fromStdString(this->airportIds[arg1.toStdString()]));
}

void dataWindow::on_calculate_clicked()
{
    string destiny = this->ui->destiny->currentText().toStdString();
    string origin = this->ui->origin->currentText().toStdString();
    auto heuristic = getHeuristic(destiny,this->data);
    auto astar = AStar(&this->graphD,heuristic);
    vector<string> result = astar.apply(origin,destiny);
    string display = "";
    int index = 1;
    for (auto& element: result){
        auto airport = getairportfromid(element,this->data);
        display = display + to_string(index) + " " + airport.name + "-" + airport.airport_ID + "\n";
        index++;
    }
    QMessageBox displayResult;
    displayResult.setText(QString::fromStdString(display));
    displayResult.exec();
}

