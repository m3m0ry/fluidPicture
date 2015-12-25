#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    image_(QImage())
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Picture"),
                                                    QDir::homePath(),
                                                    tr("Images (*.png *.jpg)"));
    qDebug() << fileName;
    bool status = image_.load(fileName);
    if(status == false)
        QMessageBox::warning(this, "Image could not be loaded", "Image could not be loaded, wtf!??!?!");
    // TODO delete scene? delete scene_;
    scene_ = new QGraphicsScene();
    pixmap_ = QPixmap::fromImage(image_);

    scene_->addPixmap(pixmap_);
    scene_->setSceneRect(pixmap_.rect());
    ui->graphicsView->setScene(scene_);

}
