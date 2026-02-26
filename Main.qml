import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtCharts
import QtQuick.Layouts

Window {
    width: 800
    height: 800
    visible: true
    title: qsTr("Генетический алгоритм")


    ColumnLayout {
        anchors.fill: parent

        spacing: 0

        TabBar {
            id: bar
            Layout.fillWidth: true
            TabButton { text: "Целевая функция" }
            TabButton { text: "Функция приспособленности" }
            TabButton { text: "Начальная популяция" }
            TabButton { text: "Третья популяция" }
            TabButton { text: "Последняя популяция" }
            TabButton { text: "Средняя приспособленность" }
        }

        StackLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: bar.currentIndex

            ChartView {
                id: chart
                title: "График целевой функции"
                width: 800
                height: 800
                anchors.fill: parent
                antialiasing: true

                ValueAxis {
                    id: axisX
                    min: -5
                    max: 5
                    titleText: "Фенотипы"
                }
                ValueAxis {
                    id: axisY
                    min: -25
                    max: 25
                    titleText: "f(x)"
                }

                SplineSeries {
                    id: fx
                    name: "Целевая функция"
                    color: "blue"
                    axisX: axisX
                    axisY: axisY
                    width: 2
                    Component.onCompleted: {
                        dataGenerator.get_function(fx, true)
                    }
                }

            }

            ChartView {
                id: chart2
                title: "График функции приспособленности"
                width: 800
                height: 800
                anchors.fill: parent
                antialiasing: true

                ValueAxis {
                    id: axisX2
                    min: -5
                    max: 5
                    titleText: "Фенотипы"
                }

                ValueAxis {
                    id: axisY2
                    min: 0
                    max: 50
                    titleText: "F(x)"
                }

                SplineSeries {
                    id: _Fx
                    name: "Функция приспособленности"
                    color: "green"
                    axisX: axisX2
                    axisY: axisY2
                    width: 2
                    Component.onCompleted: {
                        dataGenerator.get_function(_Fx, false)
                    }
                }

            }

            ChartView {
                id: chart3_start_population
                title: "Начальная популяция"
                width: 800
                height: 800
                anchors.fill: parent
                antialiasing: true

                ValueAxis {
                    id: axisX3
                    min: -5
                    max: 5
                    titleText: "Фенотипы"
                }

                ValueAxis {
                    id: axisY3
                    min: -25
                    max: 25
                    titleText: "f(x)"
                }

                SplineSeries {
                    id: _fx3
                    name: "Целевая функция"
                    color: "blue"
                    axisX: axisX3
                    axisY: axisY3
                    width: 2
                    Component.onCompleted: {
                        dataGenerator.get_function(_fx3, true)
                    }
                }

                ScatterSeries {
                    id: _popup1
                    name: "Начальная популяция"
                    color: "red"
                    markerSize: 5
                    borderWidth: 0
                    borderColor: "red"
                }

            }

            ChartView {
                id: chart4_third_population
                title: "Третья популяция"
                width: 800
                height: 800
                anchors.fill: parent
                antialiasing: true

                ValueAxis {
                    id: axisX4
                    min: -5
                    max: 5
                    titleText: "Фенотипы"
                }

                ValueAxis {
                    id: axisY4
                    min: -25
                    max: 25
                    titleText: "f(x)"
                }

                SplineSeries {
                    id: _fx4
                    name: "Целевая функция"
                    color: "blue"
                    axisX: axisX4
                    axisY: axisY4
                    width: 2
                    Component.onCompleted: {
                        dataGenerator.get_function(_fx4, true)
                    }
                }

                ScatterSeries {
                    id: _popup3
                    name: "Третья популяция"
                    color: "red"
                    markerSize: 5
                    borderWidth: 0
                    borderColor: "red"
                }

            }

            ChartView {
                id: chart5_last_population
                title: "Последняя популяция"
                width: 800
                height: 800
                anchors.fill: parent
                antialiasing: true

                ValueAxis {
                    id: axisX5
                    min: -5
                    max: 5
                    titleText: "Фенотипы"
                }

                ValueAxis {
                    id: axisY5
                    min: -25
                    max: 25
                    titleText: "f(x)"
                }

                SplineSeries {
                    id: _fx5
                    name: "Целевая функция"
                    color: "blue"
                    axisX: axisX5
                    axisY: axisY5
                    width: 2
                    Component.onCompleted: {
                        dataGenerator.get_function(_fx5, true)
                    }
                }

                ScatterSeries {
                    id: _popup_last
                    name: "Последняя популяция"
                    color: "red"
                    markerSize: 5
                    borderWidth: 0
                    borderColor: "red"
                }

            }

            ChartView {
                id: average_Fx
                title: "Среднее значение функции приспособлености"
                width: 800
                height: 800
                anchors.fill: parent
                antialiasing: true

                ValueAxis {
                    id: axisX6
                    min: 0
                    max: 50
                    titleText: "Номер популяции"
                }

                ValueAxis {
                    id: axisY6
                    min: 25
                    max: 50
                    titleText: "F(x)"
                }

                SplineSeries {
                    id: _Fx6
                    name: "Среднее значение F(x)"
                    color: "blue"
                    axisX: axisX6
                    axisY: axisY6
                    width: 2
                }

            }

        }

        Button {
            width: 40;
            height: 20;
            text: "Запуск эволюции"
            font.pixelSize: 12;
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20;
            onClicked: {
                dataGenerator.generate_population(_popup1, _popup3, _popup_last, _Fx6)
            }
        }
    }

}
