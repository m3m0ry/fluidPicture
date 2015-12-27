#pragma once

#include <QMainWindow>
#include <QImage>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QPixmap>

#include "picturemodel.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void open();

    bool saveAs();

    void save();

    void exit();

    bool ifAllowedSaveAs();

    void on_pushButtonAir_clicked();

    void on_pushButtonObstacle_clicked();

    void on_pushButtonFluid_clicked();

    void newPicture();

    void resizePicture();

private:
    Ui::MainWindow *ui;
    QImage *image_;
    QGraphicsScene *scene_;
    QString openedFile_;
    PictureModel *model_;
};
