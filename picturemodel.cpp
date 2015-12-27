#include "picturemodel.h"
#include <QDebug>

PictureModel::PictureModel(QObject *parent, QImage *image) : QAbstractTableModel(parent), image_(image)
{
}

int PictureModel::rowCount(const QModelIndex &parent) const
{
    if(image_ == 0){
        return 0;
    }
    return image_->height();
}

int PictureModel::columnCount(const QModelIndex &parent) const
{
    if(image_ == 0)
        return 0;
    return image_->width();
}


QVariant PictureModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::BackgroundRole){
            QRgb rgb = image_->pixel(index.column(), index.row());
            return QColor(rgb);
    }
    return QVariant();
}

void PictureModel::setImage(QImage *image)
{
    image_ = image;
    //for(int i = 0; i < rowCount(); ++i){
    //    qDebug() <<
    //}
    emit layoutChanged();
}
