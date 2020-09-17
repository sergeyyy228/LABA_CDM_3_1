#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void fromItoA();
    void fromAtoI();
    void fromAtoIor();
    void fromItoAor();
    void set0();
    ~MainWindow();

private slots:
    void on_comboBox_currentIndexChanged(int index);
    QStringList horisontalHeaders(int,bool);
    QStringList verticalHeaders(int );

    void on_spinBox_valueChanged();

    void on_spinBox_2_valueChanged();

    void on_tableWidget_cellChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
