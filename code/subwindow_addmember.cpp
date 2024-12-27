#include "subwindow_addmember.h"
#include "ui_subwindow_addmember.h"
#include "global.h"
#include "stylesSheetGlobal.h"



subWindow_AddMember::subWindow_AddMember(QWidget *parent, int current_window)
    : QDialog(parent)
    , ui(new Ui::subWindow_AddMember)
{
    ui->setupUi(this);
    this->current_window=current_window;


    // QMap<QString, QVariant> fieldInfo;
    // QString conditionQuery;

    switch (this->current_window)
    {
    //admins windows
    case 1:

        this->lineEditMap=createDynamicLineEdits(this, {"Name","Password","Role","Phone","Subscribtion Start Date","Subscribtion End Date"});

        break;

        //"name":alaa

    case 2:
   // case 5:

        this->lineEditMap=createDynamicLineEdits(this, {"Name","Password","Phone","Subscribtion Start Date","Subscribtion End Date"});

        break;

        //members window
    case 3:

        this->lineEditMap=createDynamicLineEdits(this, {"Title","Author","Genre","Location","Available Quanity"});

        break;

    default:
        qDebug() << "Unexpected value for which_window:" << this->current_window;
        break;
    }


    ui->addMember_Button->setStyleSheet(nonFilled_button_Style());
}

subWindow_AddMember::~subWindow_AddMember()
{
    delete ui;
}

void subWindow_AddMember::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/resources/images/infoCard_Button.png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    this->setPalette(p);


    this->setAutoFillBackground(true);

    QDialog::resizeEvent(event);
}

void subWindow_AddMember::on_addMember_Button_clicked()
{

    QMap<QString, QVariant> fieldInfo;
    QString conditionQuery;

    switch (this->current_window)
    {
    //admins windows
    case 1:

        fieldInfo["member_name"] = this->lineEditMap["Name"]->text();
        fieldInfo["member_password"] = this->lineEditMap["Password"]->text();
        fieldInfo["member_type"] = this->lineEditMap["Role"]->text();
        fieldInfo["member_phone"] = this->lineEditMap["Phone"]->text();
        fieldInfo["sub_startDate"] = this->lineEditMap["Subscribtion Start Date"]->text();
        fieldInfo["sub_endDate"] = this->lineEditMap["Subscribtion End Date"]->text();


        AddField("Member",
                 "members",
                 fieldInfo,
                 this);

        break;

    case 2:
    //case 5:

        fieldInfo["member_name"] = this->lineEditMap["Name"]->text();
        fieldInfo["member_password"] = this->lineEditMap["Password"]->text();
        fieldInfo["member_phone"] = this->lineEditMap["Phone"]->text();
        fieldInfo["sub_startDate"] = this->lineEditMap["Subscribtion Start Date"]->text();
        fieldInfo["sub_endDate"] = this->lineEditMap["Subscribtion End Date"]->text();


        AddField("Member",
                  "members",
                  fieldInfo,
                  this);

        break;

        //members window
    case 3:


        fieldInfo["book_title"] = this->lineEditMap["Title"]->text();
        fieldInfo["author_name"] = this->lineEditMap["Author"]->text();
        fieldInfo["genre"] = this->lineEditMap["Genre"]->text();
        fieldInfo["book_place"] = this->lineEditMap["Location"]->text();
        fieldInfo["available_quantity"] =this->lineEditMap["Available Quanity"]->text();

        AddField("Book",
                  "books",
                  fieldInfo,
                  this);

        break;

    default:
        qDebug() << "Unexpected value for which_window:" << this->current_window;
        break;
    }

}









// QString memberName, memberPassword, memberRole, memberPhone, memberStartDate, memberEndDate;

// memberName=ui->memberName_LineEdit->text();
// memberPassword=ui->memberPassword_LineEdit->text();
// memberRole=ui->memberRole_LineEdit->text();
// memberPhone=ui->memberPhone_LineEdit->text();
// memberStartDate=ui->memberStartDate_LineEdit->text();
// memberEndDate=ui->memberEndDate_LineEdit->text();


// open_connection();

// QSqlQuery* addMemberInfo_query =new QSqlQuery(library_db);



// addMemberInfo_query->prepare("INSERT INTO members "
//                                 "(member_name,member_password,member_phone,sub_startDate,sub_endDate,member_type)VALUES"
//                                 "('"+memberName+"','"+memberPassword+"','"+memberPhone+"','"+memberStartDate+"','"+memberEndDate+"','"+memberRole+"');");

// if(!addMemberInfo_query->exec())
// {
//     QMessageBox::critical(this,"Add Member","Error: Couldn't add the member!");
// }
// else
// {
//     QMessageBox::information(this,"Add Member","Success: Member was added!");
// }



// close_connection();

