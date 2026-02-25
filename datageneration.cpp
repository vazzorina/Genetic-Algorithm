#include "datageneration.h"
#include <QChart>
#include <QXYSeries>
#include <cmath>
#include <random>

DataGenerator::DataGenerator(QObject *parent) : QObject(parent), gen(std::random_device{}()) {

}

DataGenerator::~DataGenerator() {
    delete start_population;
}

double DataGenerator::get_y(double x) {
    return 2 * x - 3.3 * x * cos(9.3 * x) - 2.3 * sin(1.7 * x);
}

double DataGenerator::fitness_function(double x) {
    return 25 - get_y(x);
}

void DataGenerator::target_function(QXYSeries *series) {
    if (!series) return;
    double x = -5, y = 0;
    QList<QPointF> points;
    for (int i = 1; i <= 50; i++) {
        y = get_y(x);
        points.append(QPointF(x, y));
        x += 0.2;
    }

    series->replace(points);
}

void DataGenerator::generate_population(QXYSeries *series) {
    if (!series) return;
    double x = -5, y = 0;
    QList<QPointF> points;
    for (int i = 1; i <= 50; i++) {
        y = fitness_function(x);
        points.append(QPointF(x, y));
        x += 0.2;
    }

    series->replace(points);
    /*
    if (!series) return;

    double min = -5.0;
    double max = 5.0;
    std::uniform_real_distribution<double> dis(min, max);
    double fenotip;


    for(int i = 1; i <= 50; i++) {
        fenotip = dis(gen);
        //прописать расчет хромосом, целевой функции и функции приспособленности
    }
    */
}

// void write_population(QList<Individual> *population) {

// }

