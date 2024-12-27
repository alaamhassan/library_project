#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "global.h"
#include "stylesSheetGlobal.h"
#include <QMessageBox>


QSqlDatabase library_db=*new QSqlDatabase();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // QString styleSheet=
    //     "QPushButton{"
    //     "font-size:30px;"
    //     "border-radius:38px;"
    //     "border: 3px solid #1E3706;"
    //     "border-color:#1E3706;"

    //     "background-color:#E8E8E8;"
    //     "color:#1E3706;"
    //     "}"
    //     "QPushButton:hover{"
    //     "background-color:#1E3706;"
    //     "color:#E8E8E8;"
    //     "}"

    //     "QPushButton:pressed{"
    //     "background-color:#1E3706;"
    //     "color:#E8E8E8;"
    //     "}"
    //     ;

    ui->Login->setStyleSheet(filled_button_Style());
    ui->Signup->setStyleSheet(nonFilled_button_Style());



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/resources/images/main_background.png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    this->setPalette(p);


    this->setAutoFillBackground(true);

    QMainWindow::resizeEvent(event);
}

void MainWindow::on_Login_clicked()
{
    signInWindow =new SignInWindow(this);

    signInWindow->show();

    hide();
}


void MainWindow::on_Signup_clicked()
{
    addMemberWindow =new subWindow_AddMember(this, 5);
    addMemberWindow->show();

}

