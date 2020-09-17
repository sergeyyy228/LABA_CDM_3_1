#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QItemDelegate>
#include <QLineEdit>
#include <iostream>
#include <QGraphicsScene>
using namespace std;
class DelegateOnlyPlus: public QItemDelegate
{
public:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem & option,
                          const QModelIndex & index) const
    {
        QLineEdit *lineEdit = new QLineEdit(parent);
        QIntValidator *validator = new QIntValidator(0,INT_MAX , lineEdit);
        lineEdit->setValidator(validator);
        return lineEdit;
    }
};
class DelegateOnlyNumbers: public QItemDelegate
{
public:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem & option,
                          const QModelIndex & index) const
    {
        QLineEdit *lineEdit = new QLineEdit(parent);
        QIntValidator *validator = new QIntValidator(INT_MIN,INT_MAX , lineEdit);
        lineEdit->setValidator(validator);
        return lineEdit;
    }
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QStringList MainWindow::horisontalHeaders(int columns,bool isAdjacency){
    QStringList hheaders;
    hheaders.clear();
    if(!isAdjacency){
        for(int i=1;i<=columns;i++){
            hheaders+="y"+QString::number(i)+" ";
        }
    }else{
        for(int i=1;i<=columns;i++){
            hheaders+="x"+QString::number(i)+" ";
        }
    }
    return hheaders;
}
QStringList MainWindow::verticalHeaders(int rows){
    QStringList vheaders;
    vheaders.clear();
    for(int i=1;i<=rows;i++){
        vheaders+="x"+QString::number(i)+" ";
    }
    return vheaders;
}
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index==0){
        return;
    }

    ui->tableWidget->setRowCount(ui->spinBox->text().toInt());
    ui->tableWidget_2->setRowCount(ui->spinBox->text().toInt());
    ui->tableWidget->setVerticalHeaderLabels(verticalHeaders(ui->spinBox->text().toInt()));
    ui->tableWidget_2->setVerticalHeaderLabels(verticalHeaders(ui->spinBox->text().toInt()));

    if(index==1){
        ui->tableWidget->setItemDelegate(new DelegateOnlyPlus);
        ui->matrix1label->clear();
        ui->matrix1label->setText("Incidence");
        ui->matrix2label->clear();
        ui->matrix2label->setText("Adjacent ");
        ui->infoLabel->clear();
        ui->infoLabel->setText("Non-Oriented");


        ui->spinBox_2->setDisabled(0);
        ui->tableWidget->setColumnCount(ui->spinBox_2->text().toInt());
        ui->tableWidget->setHorizontalHeaderLabels(horisontalHeaders(ui->spinBox_2->text().toInt(),0));

        ui->tableWidget_2->setColumnCount(ui->spinBox->text().toInt());
        ui->tableWidget_2->setHorizontalHeaderLabels(horisontalHeaders(ui->spinBox->text().toInt(),1));
    }
    if(index==2){
        ui->tableWidget->setItemDelegate(new DelegateOnlyNumbers);
        ui->matrix1label->clear();
        ui->matrix1label->setText("Incidence");
        ui->matrix2label->clear();
        ui->matrix2label->setText("Adjacent ");
        ui->infoLabel->clear();
        ui->infoLabel->setText("Oriented");


        ui->spinBox_2->setDisabled(0);
        ui->tableWidget->setColumnCount(ui->spinBox_2->text().toInt());
        ui->tableWidget->setHorizontalHeaderLabels(horisontalHeaders(ui->spinBox_2->text().toInt(),0));

        ui->tableWidget_2->setColumnCount(ui->spinBox->text().toInt());
        ui->tableWidget_2->setHorizontalHeaderLabels(horisontalHeaders(ui->spinBox->text().toInt(),1));
    }
    if(index==3){
        ui->tableWidget->setItemDelegate(new DelegateOnlyNumbers);
        ui->matrix2label->clear();
        ui->matrix2label->setText("Incidence");
        ui->matrix1label->clear();
        ui->matrix1label->setText("Adjacent ");
        ui->infoLabel->clear();
        ui->infoLabel->setText("Non-Oriented");


        ui->spinBox_2->setDisabled(1);
        ui->tableWidget->setColumnCount(ui->spinBox->text().toInt());
        ui->tableWidget->setHorizontalHeaderLabels(horisontalHeaders(ui->spinBox->text().toInt(),1));

        ui->tableWidget_2->setHorizontalHeaderLabels(horisontalHeaders(ui->spinBox->text().toInt(),0));
    }
    if(index==4){
        ui->tableWidget->setItemDelegate(new DelegateOnlyPlus);
        ui->matrix2label->clear();
        ui->matrix2label->setText("Incidence");
        ui->matrix1label->clear();
        ui->matrix1label->setText("Adjacent ");
        ui->infoLabel->clear();
        ui->infoLabel->setText("Oriented");


        ui->spinBox_2->setDisabled(1);
        ui->tableWidget->setColumnCount(ui->spinBox->text().toInt());
        ui->tableWidget->setHorizontalHeaderLabels(horisontalHeaders(ui->spinBox->text().toInt(),1));


        ui->tableWidget_2->setHorizontalHeaderLabels(horisontalHeaders(ui->spinBox->text().toInt(),0));
    }


}

void MainWindow::on_spinBox_valueChanged()
{
    on_comboBox_currentIndexChanged(ui->comboBox->currentIndex());

}


void MainWindow::on_spinBox_2_valueChanged()
{
    on_comboBox_currentIndexChanged(ui->comboBox->currentIndex());
}

void MainWindow::set0(){
    for (int i = 0;i < ui->tableWidget_2->rowCount();i++){
        for (int j = 0; j < ui->tableWidget_2->columnCount(); j++){
            if(ui->tableWidget_2->item(i,j)==0){
                QTableWidgetItem * item = new QTableWidgetItem();
                item->setText("0");
                ui->tableWidget_2->setItem(i, j, item);
            }
        }
    }
}
void MainWindow::fromItoAor(){

    int num;
    for (int i = 0;i < ui->tableWidget->columnCount();i++){
        num=0;
        for (int j = 0; j < ui->tableWidget->rowCount(); j++){

            if (ui->tableWidget->item(j,i)->text() == "2"){
                QTableWidgetItem * item = new QTableWidgetItem();
                item->setText("1");
                ui->tableWidget_2->setItem(j, j, item);
            }
            if(ui->tableWidget->item(j,i)->text() == "1"){
                for(int n=0;n<ui->tableWidget->rowCount();n++){
                    if(ui->tableWidget->item(n,i)->text() == "-1"){
                        if(n>j){
                            if(ui->tableWidget_2->item(j,n)!=0){
                                QTableWidgetItem * item = new QTableWidgetItem();
                                num=ui->tableWidget_2->item(j,n)->text().toInt();
                                num++;
                                item->setText(QString::number(num));
                                ui->tableWidget_2->setItem(j, n, item);

                            }
                            else{
                                QTableWidgetItem * item = new QTableWidgetItem();
                                item->setText(QString::number(1));

                                ui->tableWidget_2->setItem(j, n, item);

                            }
                        }else{
                            if(ui->tableWidget_2->item(j,n)!=0){
                                QTableWidgetItem * item = new QTableWidgetItem();
                                num=ui->tableWidget_2->item(j,n)->text().toInt();
                                num++;
                                item->setText(QString::number(num));
                                ui->tableWidget_2->setItem(j, n, item);

                            }
                            else{
                                QTableWidgetItem * item = new QTableWidgetItem();
                                item->setText(QString::number(1));

                                ui->tableWidget_2->setItem(j, n, item);

                            }
                        }
                    }
                }
            }
        }
    }
    set0();
}



void MainWindow::fromItoA(){
    int num;
    for (int i = 0;i < ui->tableWidget->columnCount();i++){
        int index = -1;
        num=0;
        for (int j = 0; j < ui->tableWidget->rowCount(); j++){
            if (ui->tableWidget->item(j,i)->text() == "2"){
                QTableWidgetItem * item = new QTableWidgetItem();
                item->setText("1");
                ui->tableWidget_2->setItem(j, j, item);
            }
            if (ui->tableWidget->item(j,i)->text() == "1"){
                if (index > -1){
                    if(ui->tableWidget_2->item(index,j)!=0&&ui->tableWidget_2->item(j,index)!=0){
                        QTableWidgetItem * item = new QTableWidgetItem();
                        QTableWidgetItem * item1 = new QTableWidgetItem();
                        num=ui->tableWidget_2->item(index,j)->text().toInt();
                        num++;
                        item->setText(QString::number(num));
                        item1->setText(QString::number(num));
                        ui->tableWidget_2->setItem(index, j, item);
                        ui->tableWidget_2->setItem(j, index, item1);
                    }
                    else{
                        QTableWidgetItem * item = new QTableWidgetItem();
                        item->setText(QString::number(1));
                        QTableWidgetItem * item1 = new QTableWidgetItem();
                        item1->setText(QString::number(1));

                        ui->tableWidget_2->setItem(index, j, item);
                        ui->tableWidget_2->setItem(j, index, item1);
                    }
                } else index = j;


            }
        }
    }
    set0();

}
void MainWindow::fromAtoIor(){
    int ColumnCount=0;
    for(int i=0;i<ui->tableWidget->columnCount();i++){
        for(int j=0;j<ui->tableWidget->rowCount();j++){
            if(ui->tableWidget->item(i,j)->text()!=0){
                ColumnCount+=ui->tableWidget->item(i,j)->text().toInt();
            }
        }
    }
    ui->tableWidget_2->setColumnCount(ColumnCount);
    ui->tableWidget_2->setHorizontalHeaderLabels(horisontalHeaders(ui->spinBox->text().toInt(),0));

    int col=0;

    for(int i=0;i<ui->tableWidget->columnCount();i++){
        for(int j=0;j<ui->tableWidget->rowCount();j++){
            if(ui->tableWidget->item(i,j)->text()!=0){
                for(int num=0;num<ui->tableWidget->item(i,j)->text().toInt();num++){
                    if(j==i){
                        QTableWidgetItem * item = new QTableWidgetItem();
                        item->setText("2");
                        QTableWidgetItem * item1 = new QTableWidgetItem();
                        item1->setText("2");
                        ui->tableWidget_2->setItem(i, col, item);
                        ui->tableWidget_2->setItem(j, col, item1);
                    }
                    else {
                        QTableWidgetItem * item = new QTableWidgetItem();
                        item->setText("1");
                        QTableWidgetItem * item1 = new QTableWidgetItem();
                        item1->setText("-1");
                        ui->tableWidget_2->setItem(i, col, item);
                        ui->tableWidget_2->setItem(j, col, item1);
                    }
                    col++;
                }
            }
        }
    }
    set0();
}

void MainWindow::fromAtoI(){

    int help=0;
    int ColumnCount=0;
    for(int i=0;i<ui->tableWidget->columnCount();i++){
        for(int j=help;j<ui->tableWidget->rowCount();j++){
            if(ui->tableWidget->item(i,j)->text()!=0){
                ColumnCount+=ui->tableWidget->item(i,j)->text().toInt();
            }
        }
        help++;
    }
    ui->tableWidget_2->setColumnCount(ColumnCount);
    ui->tableWidget_2->setHorizontalHeaderLabels(horisontalHeaders(ui->spinBox->text().toInt(),0));

    help=0;
    int col=0;

    for(int i=0;i<ui->tableWidget->columnCount();i++){
        for(int j=help;j<ui->tableWidget->rowCount();j++){
            if(ui->tableWidget->item(i,j)->text()!=0){

                if(ui->tableWidget->item(i,j)->text().toInt()!=ui->tableWidget->item(j,i)->text().toInt()){
                    QDialog * d = new QDialog;
                    QMessageBox::critical(d,"Error","Matrix is not symmetrical");
                    return;
                }
                if(ui->tableWidget->item(j,i)->text()==ui->tableWidget->item(i,j)->text()){
                    for(int num=0;num<ui->tableWidget->item(i,j)->text().toInt();num++){
                        if(j==i){
                            QTableWidgetItem * item = new QTableWidgetItem();
                            item->setText("2");
                            QTableWidgetItem * item1 = new QTableWidgetItem();
                            item1->setText("2");
                            ui->tableWidget_2->setItem(i, col, item);
                            ui->tableWidget_2->setItem(j, col, item1);

                        }
                        else {
                            QTableWidgetItem * item = new QTableWidgetItem();
                            item->setText("1");
                            QTableWidgetItem * item1 = new QTableWidgetItem();
                            item1->setText("1");
                            ui->tableWidget_2->setItem(i, col, item);
                            ui->tableWidget_2->setItem(j, col, item1);
                        }
                        col++;
                    }
                }
            }
        }
        help++;
    }
    set0();

}
void MainWindow::on_tableWidget_cellChanged()
{
    QTableWidgetItem * item;

    for (int i = 0; i < ui->tableWidget->rowCount();i++)
    {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            item = ui->tableWidget->item(i,j);

            if (item == NULL)
                return;
        }
    }
    int i=ui->comboBox->currentIndex();
    switch(i){
    case 0:{
        return;
        break;
    }
    case 1:{
        fromItoA();
        break;
    }
    case 2:{
        fromItoAor();
        break;
    }
    case 3:{
        fromAtoI();
        break;
    }
    case 4:{
        fromAtoIor();
        break;
    }
    }
    return;
}
