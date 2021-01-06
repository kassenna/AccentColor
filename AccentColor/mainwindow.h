#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <qgraphicswidget.h>
#include <qgraphicsview.h>
#include <QColorDialog>
#include "model.h"

namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Model * model = nullptr;
    uchar* bits = nullptr;
    int size{};
    QString imagePath;
    QPixmap image;
    QPixmap image2;
    QImage* imageObject{};
    QImage* imageObject2{};
    QGraphicsScene* scene{};
    QGraphicsScene* scene2{};
    QColor chosenColor;
    int range = 360;
    float hue = 0;
    int threads=1;
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_choose_clicked();
    void on_run_clicked();
    void on_threads_sliderMoved(int position);
    void on_colorChoise_clicked();
private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
