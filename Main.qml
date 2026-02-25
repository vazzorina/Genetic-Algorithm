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
                    titleText: "Приспособленность"
                }

                SplineSeries {
                    id: fx
                    name: "Целевая функция"
                    color: "blue"
                    axisX: axisX
                    axisY: axisY
                    width: 2
                    Component.onCompleted: {
                        dataGenerator.target_function(fx)
                    }
                }

                // ScatterSeries {
                //     id: _Fx
                //     name: "Начальная популяция"
                //     color: "green"
                //     markerSize: 5
                //     borderWidth: 0
                //     Component.onCompleted: {
                //         dataGenerator.target_function(_Fx)
                //     }
                // }

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
                    titleText: "Приспособленность"
                }

                SplineSeries {
                    id: _Fx
                    name: "Функция приспособленности"
                    color: "green"
                    axisX: axisX2
                    axisY: axisY2
                    width: 2
                    Component.onCompleted: {
                        dataGenerator.generate_population(_Fx)
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
                    max: 50
                    titleText: "Приспособленность"
                }

                SplineSeries {
                    id: _Fx3
                    name: "Функция приспособленности"
                    color: "green"
                    axisX: axisX3
                    axisY: axisY3
                    width: 2
                    Component.onCompleted: {
                        dataGenerator.generate_population(_Fx3)
                    }
                }

                SplineSeries {
                    id: _fx3
                    name: "Целевая функция"
                    color: "blue"
                    axisX: axisX3
                    axisY: axisY3
                    width: 2
                    Component.onCompleted: {
                        dataGenerator.target_function(_fx3)
                    }
                }

            }

        }
    }

}
