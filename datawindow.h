#ifndef DATAWINDOW_H
#define DATAWINDOW_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "Parser/parser.h"
#include <string>
#include <QStringList>
#include "Graph/UndirectedGraph.h"
#include "Graph/Algorithms/astar.h"
#include "QMessageBox"

using json = nlohmann::json;

namespace Ui {
class dataWindow;
}

class dataWindow : public QWidget
{
    Q_OBJECT
    QString fileName;
    unordered_map<string,string> airportIds;
    UnDirectedGraph<string, double> graphD;
    json data;
public:
    explicit dataWindow(QWidget *parent = nullptr, QString fileName = "");
    ~dataWindow();

private slots:
    void on_origin_currentTextChanged(const QString &arg1);

    void on_destiny_currentTextChanged(const QString &arg1);

    void on_calculate_clicked();

private:
    Ui::dataWindow *ui;
};

#endif // DATAWINDOW_H
