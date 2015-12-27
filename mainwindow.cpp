#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    image_(0)
{
    ui->setupUi(this);

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newPicture()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionSaveAs, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exit()));

    model_ = new PictureModel(this, image_);

    connect(ui->pushButtonApply, SIGNAL(clicked()), this,
            SLOT(resizePicture()));


    ui->tableView->setModel(model_);
    ui->tableView->show();
}

MainWindow::~MainWindow()
{
    delete model_;
    delete image_;
    delete ui;
}

void MainWindow::open()
{
   if(not ifAllowedSaveAs())
       return;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Picture"),
                                                    QDir::homePath(),
                                                    tr("Images (*.png)"));
    if(fileName == "")
        return;

    if(image_ !=0)
        delete image_;
    image_ = new QImage(fileName);
    if(image_->isNull()){
        QMessageBox::warning(this, "Image could not be loaded", "Image could not be loaded!");
        delete image_;
        return;
    }

    openedFile_ = fileName;
    if(image_->format() != QImage::Format_RGB32){
        QImage* form = new QImage(image_->convertToFormat(QImage::Format_RGB32));
        delete image_;
        image_ = form;
    }

    model_->setImage(image_);

    ui->actionSave->setEnabled(true);
    ui->actionSaveAs->setEnabled(true);
    ui->spinBoxXSize->setValue(image_->width());
    ui->spinBoxYSize->setValue(image_->height());
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Picture"),
                               openedFile_,
                               tr("Images (*.png)"));
    if(fileName == "")
        return false;
    image_->save(fileName);
    openedFile_ = fileName;
    ui->actionSave->setEnabled(true);
    return true;
}

void MainWindow::save()
{
    qDebug() << "Saving to: " << openedFile_;
    if(openedFile_ == "")
        return;
    image_->save(openedFile_);
}


void MainWindow::on_pushButtonAir_clicked()
{
    QItemSelectionModel *selModel = ui->tableView->selectionModel();
    QModelIndexList list = selModel->selectedIndexes();
    for (int i = 0; i < list.size(); ++i) {
        QModelIndex index = list.at(i);
        image_->setPixel(index.column(), index.row(), QColor(Qt::white).rgb());
        emit model_->dataChanged(index,index);
    }
}

void MainWindow::on_pushButtonObstacle_clicked()
{
    QItemSelectionModel *selModel = ui->tableView->selectionModel();
    QModelIndexList list = selModel->selectedIndexes();
    for (int i = 0; i < list.size(); ++i) {
        QModelIndex index = list.at(i);
        image_->setPixel(index.column(), index.row(), QColor(Qt::black).rgb());
        emit model_->dataChanged(index,index);
    }
}

void MainWindow::on_pushButtonFluid_clicked()
{
    QItemSelectionModel *selModel = ui->tableView->selectionModel();
    QModelIndexList list = selModel->selectedIndexes();
    for (int i = 0; i < list.size(); ++i) {
        QModelIndex index = list.at(i);
        image_->setPixel(index.column(), index.row(), QColor(Qt::blue).rgb());
        emit model_->dataChanged(index,index);
    }
}

void MainWindow::newPicture()
{
    if(not ifAllowedSaveAs())
        return;

    image_ = new QImage(ui->spinBoxXSize->value(), ui->spinBoxYSize->value(), QImage::Format_RGB32);
    image_->fill(Qt::white);
    model_->setImage(image_);

    ui->actionSave->setEnabled(false);
    openedFile_ = "";
    ui->actionSaveAs->setEnabled(true);
    ui->spinBoxXSize->setValue(image_->width());
    ui->spinBoxYSize->setValue(image_->height());

}

void MainWindow::resizePicture()
{
    if(image_ == 0)
        newPicture();
    QImage *scaled = new QImage(image_->scaled(ui->spinBoxXSize->value(), ui->spinBoxYSize->value()));
    delete image_;
    image_ = scaled;
    model_->setImage(image_);
}

void MainWindow::exit()
{
    if(ifAllowedSaveAs())
        QApplication::quit();
}

bool MainWindow::ifAllowedSaveAs()
{
    if(image_ != 0){
        QMessageBox::StandardButton button = QMessageBox::question(this, "Save current picture", "A picture is already opened. Would you like to save it?",
                QMessageBox::StandardButtons(QMessageBox::Save|QMessageBox::No|QMessageBox::Cancel), QMessageBox::StandardButton(QMessageBox::Cancel));
        if( button == QMessageBox::Save){
            if(openedFile_ == "")
                return saveAs();
            save();
            QMessageBox::information(this, "", "Saved!");
            return true;
        }
        else if( button == QMessageBox::No){
            return true;
        }
        else{
            return false;
        }
    }
    return true;
}
