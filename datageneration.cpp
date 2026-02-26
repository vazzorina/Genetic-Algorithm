#include "datageneration.h"
#include <QChart>
#include <QXYSeries>
#include <cmath>
#include <random>
#include <iostream>

DataGenerator::DataGenerator(QObject *parent) : QObject(parent) {

}

DataGenerator::~DataGenerator() {
    delete prev_population;
    delete population;
    delete parents;
    delete children;
}

double DataGenerator::get_y(double x) {
    return 2 * x - 3.3 * x * cos(9.3 * x) - 2.3 * sin(1.7 * x);
}

double DataGenerator::fitness_function(double x) {
    return 25 - get_y(x);
}

void DataGenerator::get_function(QXYSeries *series, bool is_target) {
    if (!series) return;
    double x = -5, y = 0;
    QList<QPointF> points;
    for (int i = 1; i <= 200; i++) {
        y = is_target ? get_y(x) : fitness_function(x);
        points.append(QPointF(x, y));
        x += 0.05;
    }

    series->replace(points);
}

void DataGenerator::generate_population(QXYSeries *series_start, QXYSeries *series_third, QXYSeries *series_last) { //0 - начальная популяция, 1 - третья популяция, 3 - последняя популяция
    if (!series_start && !series_last && !series_third) return;

    QList<QPointF> points_start;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-5.0, 5.0);

    for (int i = 1; i <= 50; i++) {
        double x = dis(gen);
        double y = get_y(x);
        double F = fitness_function(x);
        int X = x * 100000; //переводим в целое число с сохранением дробной части до 5 знаков для записи хромомсомы
        std::bitset<20> chrom(X);
        Individual Individ({i, x, chrom, y, F});
        prev_population->append(Individ);
        points_start.append(QPointF(x, y));
    }

    // for (const auto &ind : *prev_population) {
    //     std::cout << ind.i << " "
    //               << ind.x << " "
    //               << ind.chromosome.to_string() << " "
    //               << ind.y_targ_func << " "
    //               << ind.fitn_func << "\n";
    // }

    series_start->replace(points_start);
    for (int i = 0; i < 10; i++) {
        choice_parent();

    }
}

void DataGenerator::choice_parent() {
    QList<Individual> popup = *prev_population;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(popup.begin(), popup.end(), gen);

    for (int i = 0; i < 50; i += 2) {
        Individual parent1 = popup[i];
        Individual parent2 = popup[i + 1];
        parents->append({parent1, parent2});
    }

    // for (const auto &[ind, iind] : *parents) {
    //     std::cout << "-----\n";
    //     std::cout << ind.i << " "
    //               << ind.x << " "
    //               << ind.chromosome.to_string() << " "
    //               << ind.y_targ_func << " "
    //               << ind.fitn_func << "\n";
    //     std::cout << iind.i << " "
    //               << iind.x << " "
    //               << iind.chromosome.to_string() << " "
    //               << iind.y_targ_func << " "
    //               << iind.fitn_func << "\n";
    // }

}

