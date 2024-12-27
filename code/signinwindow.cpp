#include "signinwindow.h"
#include "ui_signinwindow.h"
#include "mainwindow.h"
#include "global.h"
#include "stylesSheetGlobal.h"
#include "subwindow_addmember.h"
#include <QMessageBox>

MainWindow *mainWindow;

SignInWindow::SignInWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignInWindow)
{
    ui->setupUi(this);

    QString LevelListStyleSheet=
        "QComboBox"
        "{"
        "border-radius:2px;"
        "border:2px solid #1E3706;"
        "border-color:#1E3706;"
        "background: #F1F1F1;"
        "}"
        "QComboBox QScrollBar"
        "{"
        " QListView : solid #1E3706;"
        "width:15px;"
        "}"
        "QComboBox::drop-down"
        "{"
        "border-radius:1px;"
        "border:1px solid #1E3706;"
        "border-color:#1E3706;"
        "background: #90978E;"
        "}"
        "QComboBox::down-arrow"
        "{"
        "image:url(:/computerVScomputerPage/computerVsComputerPage/dropArrow.png);"
        "width:30px;"
        "height:30px;"
        "}"
        "QListView:item"
        "{"
        "border:1px solid #1E3706;"
        "background-color:#F1F1F1;"
        "color:#1E3706;"
        "}"
        "QListView:item:hover"
        "{"
        "border:1px solid #1E3706;"
        "background-color:#1E3706;"
        "color:#F1F1F1;"
        "}"
        "QListView:item:selected"
        "{"
        "border:1px solid #1E3706;"
        "background-color:#1E3706;"
        "color:#F1F1F1;"
        "}"
        ;




    ui->login_button->setStyleSheet(filled_button_Style());



}

SignInWindow::~SignInWindow()
{
    delete ui;
}

void SignInWindow::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/resources/images/signIn_backgroun.png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    this->setPalette(p);


    this->setAutoFillBackground(true);

    QDialog::resizeEvent(event);
}


void SignInWindow::on_login_button_clicked()
{
    //get the username entered by the user
    QString username = ui->username_lineEdit->text();

    //get the password entered by the user
    QString password = ui->password_lineEdit->text();

    initialize_database();
    open_connection();

    QSqlQuery query;

    query.prepare("select member_type, member_id from members where member_name='"+username+"' and member_password='"+password+"';");


    if(query.exec())
    {
        query.next();

        QVariant member_type=query.value(0);


        if(member_type.toString()=="Manager" || member_type.toString()=="Staff")
        {

            AdminWindow =new admin_AdminsSectionWindow(this,query.value(1).toString());


        }

        else if(member_type.toString()=="Member")
        {
            AdminWindow =new admin_AdminsSectionWindow(this,query.value(1).toString(),false);

        }

        AdminWindow->show();

        hide();
    }
    //dispaly error message if the username or password aren't correct
    else
    {
        QMessageBox::critical(this,"SignIn","Username Or Password isn't correct!");

    }

    close_connection();
}

