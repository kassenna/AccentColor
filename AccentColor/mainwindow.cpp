#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cmake-build-debug/JA_autogen/include/ui_mainwindow.h"
#include <ctime>
#include <ratio>
#include <chrono>
#include "model.h"
#include <qimage.h>
#include <string>
#include <cmath>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QGraphicsScene>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->threads->setMaximum(64);
    ui->spinBox->setMaximum(100);
    ui->spinBox->setValue(100);
    model = new Model();
    ui->threads->setValue(1);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_choose_clicked() {
    imagePath = QFileDialog::getOpenFileName(0, tr("Open Image"),
            "../data", tr("Image Files (*.png *.jpg *.bmp)"));
       imageObject = new QImage();
       imageObject->load(imagePath);
       image = QPixmap::fromImage(*imageObject);
       scene = new QGraphicsScene(this);
       scene->addPixmap(image);
       ui->before->setScene(scene);
   }

void MainWindow::on_run_clicked() {
    if (imageObject != nullptr) {
        imageObject2 = new QImage();
        imageObject2->load(imagePath);
        bits = imageObject2->bits();
        size = imageObject2->byteCount();
        if(ui->library->currentText() == "CPP") {
         auto t1 = std::chrono::high_resolution_clock::now();
         model->byCPP(bits, size, hue, (int) (ui->spinBox->value() * 3.6f), ui->threads->value());
         auto t2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        ui->timee->setText(QString ("time: ") + QString( std::to_string(time_span.count()).c_str()));
        }else {
           auto t1 = std::chrono::high_resolution_clock::now();
            model->byASM(bits, size, hue, (int) (ui->spinBox->value() * 3.6f), ui->threads->value());
            auto t2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
            ui->timee->setText(QString ("time: ") + QString( std::to_string(time_span.count()).c_str()));

        }image2 = QPixmap::fromImage(*imageObject2);
        scene2 = new QGraphicsScene(this);
        scene2->addPixmap(image2);
        ui->after->setScene(scene2);
    }
}



void MainWindow::on_threads_sliderMoved(int position) {
    threads = floor(position * 0.64) + 1;
    ui->numberThreads->setText((QString::number(position)));
    if(position == Model::numberOfThread())
    {
        ui->threadsOptimise->setText("thread optimalize");
    }
    else
        ui->threadsOptimise->setText("   ");
}

void MainWindow::on_colorChoise_clicked() {
    chosenColor = QColorDialog::getColor();
    hue = (float)chosenColor.hsvHue();
    QPalette pal = ui->colorChoise->palette();
    pal.setColor(QPalette::Button, QColor(chosenColor));
    ui->colorChoise->setAutoFillBackground(true);
    ui->colorChoise->setPalette(pal);
    ui->colorChoise->update();
    chosenColor = chosenColor.toHsv();
}
