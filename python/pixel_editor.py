#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QAction, qApp, QWidget, QPushButton,\
    QLabel, QSpinBox, QGridLayout, QVBoxLayout, QSplitter, QTableView
from PyQt5.QtGui import QIcon, QKeySequence

import picture_model


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        new_action = QAction('&New', self, shortcut=QKeySequence.New,
                             statusTip='Create new picture', triggered=self.new_file)
        open_action = QAction('&Open', self, shortcut=QKeySequence.Open,
                              statusTip='Open picture', triggered=self.open_file)
        save_action = QAction('&Save', self, shortcut=QKeySequence.Save,
                              statusTip='Save picture', triggered=self.save_file)
        save_action.setEnabled(False)
        save_as_action = QAction('&Save as...', self, shortcut=QKeySequence.SaveAs,
                                 statusTip='Save picture as...', triggered=self.save_file_as)
        save_as_action.setEnabled(False)
        exit_action = QAction('&Exit', self, shortcut=QKeySequence.Quit,
                              statusTip='Exit application', triggered=qApp.quit)

        self.statusBar()

        # Menu Bar
        menu_bar = self.menuBar()
        file_menu = menu_bar.addMenu('&File')
        file_menu.addAction(new_action)
        file_menu.addAction(open_action)
        file_menu.addSeparator()
        file_menu.addAction(save_action)
        file_menu.addAction(save_as_action)
        file_menu.addSeparator()
        file_menu.addAction(exit_action)

        # Setup main window
        splitter = QSplitter(self)
        left = QWidget(splitter)
        # Size widget
        size = QWidget(left)
        size_layout = QGridLayout()
        size.setLayout(size_layout)
        label_x = QLabel(size)
        label_x.setText('x Size')
        spinbox_x = QSpinBox(size)
        spinbox_x.setMaximum(1000000)
        label_y = QLabel(size)
        label_y.setText('y Size')
        spinbox_y = QSpinBox(size)
        spinbox_y.setMaximum(1000000)
        apply_button = QPushButton("Apply", size)
        size_layout.addWidget(label_x, 0, 0)
        size_layout.addWidget(spinbox_x, 0, 1)
        size_layout.addWidget(label_y, 1, 0)
        size_layout.addWidget(spinbox_y, 1, 1)
        size_layout.addWidget(apply_button, 2, 1)
        # Buttons
        left_layout = QVBoxLayout()
        left.setLayout(left_layout)
        empty_button = QPushButton("Set to emtpy", left)
        fluid_button = QPushButton("Set to fluid", left)
        obstacle_button = QPushButton("Set to obstacle", left)
        left_layout.addWidget(size)
        left_layout.addWidget(empty_button)
        left_layout.addWidget(fluid_button)
        left_layout.addWidget(obstacle_button)
        left_layout.addStretch()

        # Table
        table = QTableView()

        splitter.addWidget(left)
        splitter.addWidget(table)

        # Set window
        self.setCentralWidget(splitter)
        # self.setGeometry(500, 500, 300, 200)
        self.setWindowTitle('Pixel editor')

    def new_file(self):
        pass

    def open_file(self):
        pass

    def save_file(self):
        pass

    def save_file_as(self):
        pass

if __name__ == '__main__':

    app = QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec_())
