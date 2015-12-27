#pragma once

#include <QAbstractTableModel>
#include <QImage>
#include <QColor>
#include <Qt>

class PictureModel : public QAbstractTableModel
{
public:
    PictureModel(QObject *parent, QImage *image);
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    void setImage(QImage *image);

private:
    QImage *image_;
};
