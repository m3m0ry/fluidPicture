from PyQt5.QtCore import QAbstractTableModel, QVariant
from PyQt5.QtGui import QColor


class PictureModel(QAbstractTableModel):
    def __init__(self, image=None, file=None):
        super.__init__()
        self.image = image
        self.file = file

    def rowCount(self, parent):
        if self.image is None:
            return 0
        return self.image.height()

    def columnCount(self, parent):
        if self.image is None:
            return 0
        return self.image.width()

    def data(self, index, role):
        if role == Qt.BackgroundRole:
            rgb = self.image.pixel(index.column(), index.row())
            return QColor(rgb)
        return QVariant()

    def open_image(self, file_name):
        pass

    def save_image(self, file_name=None):
        pass
