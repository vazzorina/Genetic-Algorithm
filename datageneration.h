#include <QObject>
#include <QChart>
#include <QXYSeries>
#include <bitset>
#include <random>

struct Individual {
    double x;
    std::bitset<20> chromosome;
    double y_targ_func;
    double fitn_func;
};

class DataGenerator : public QObject
{
    Q_OBJECT
public:
    explicit DataGenerator(QObject *parent = nullptr);
    ~DataGenerator();

    Q_INVOKABLE void get_function(QXYSeries *series, bool is_target); //получение графиков целевой функции и приспособленности
    Q_INVOKABLE void generate_population(QXYSeries *series, QXYSeries *series_third, QXYSeries *series_last, QXYSeries *av_Fx); //основная функция эволюции

private:
    QList<Individual> *prev_population = new QList<Individual>; //список предыдущей популяции
    QList<Individual> *population = new QList<Individual>; //список текущей популяции
    QList<std::pair<Individual, Individual>> *parents = new QList<std::pair<Individual, Individual>>; //временный список для формирования родителей
    QList<Individual> *children = new QList<Individual>; //временный список для потомков
    QList<QPointF> *av_Fx_points = new QList<QPointF>;

    std::mt19937 gen;

    double Pc = 0.9; //вероятность скрещивания
    double Pm = 0.2; //вероятность мутации

    double get_y(double x);
    double fitness_function(double x);
    void choice_parent(); //функция для случайного выбора родителей
    void generate_children(); //функция для генерации детей и их мутации
    void turnir(); //функция реализующая турнир для особей
    void write_csv(std::string file_name, QList<Individual> *popup); //функция для записи данных особей в файл сsv
    void average_Fx(int i); //возвращает среднее значение функции приспособленности
    double get_dx(); //функция расчета относительной прибавки к приспособленности
};
