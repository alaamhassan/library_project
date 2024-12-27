#include "subwindow_editmember.h"
#include "ui_subwindow_editmember.h"
#include "global.h"
#include "stylesSheetGlobal.h"

subWindow_EditMember::subWindow_EditMember(QWidget *parent, int fieldID, int current_window)
    : QDialog(parent)
    , ui(new Ui::subWindow_EditMember)
{
    ui->setupUi(this);

    this->fieldID= fieldID;
    this->current_window=current_window;


    QMap<QString, QVariant> fieldInfo;
    QString conditionQuery;

    switch (this->current_window)
    {
    //admins windows
    case 1:
    case 2:

        this->lineEditMap=createDynamicLineEdits(this, {"Name","Role","Phone","Subscribtion Start Date","Subscribtion End Date"});

        break;

    //books window
    case 3:

        this->lineEditMap=createDynamicLineEdits(this, {"Title","Author","Genre","Location","Available Quanity"});

        break;

    case 4:
        this->lineEditMap=createDynamicLineEdits(this, {"Name","Password","Phone"});

        break;
    default:
        qDebug() << "Unexpected value for which_window:" << this->current_window;
        break;
    }

    ui->editMember_Button->setStyleSheet(nonFilled_button_Style());


}

subWindow_EditMember::~subWindow_EditMember()
{
    delete ui;
}

void subWindow_EditMember::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/resources/images/infoCard_Button.png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    this->setPalette(p);


    this->setAutoFillBackground(true);

    QDialog::resizeEvent(event);
}


void subWindow_EditMember::on_editMember_Button_clicked()
{

    QMap<QString, QVariant> fieldInfo;
    QString conditionQuery;

    switch (this->current_window)
    {
    //admins windows
    case 1:
    //members window
    case 2:


        fieldInfo["member_name"] = this->lineEditMap["Name"]->text();
        fieldInfo["member_type"] = this->lineEditMap["Role"]->text();
        fieldInfo["member_phone"] = this->lineEditMap["Phone"]->text();
        fieldInfo["sub_startDate"] =  this->lineEditMap["Subscribtion Start Date"]->text();
        fieldInfo["sub_endDate"] = this->lineEditMap["Subscribtion End Date"]->text();

        conditionQuery=" Where member_id= "+QString::number(this->fieldID)+";";

        UpdateField("Member",
                    "members",
                    fieldInfo,
                    conditionQuery,
                    this);

        break;


    case 3:


        fieldInfo["book_title"] = this->lineEditMap["Title"]->text();
        fieldInfo["author_name"] = this->lineEditMap["Author"]->text();
        fieldInfo["genre"] = this->lineEditMap["Genre"]->text();
        fieldInfo["book_place"] = this->lineEditMap["Location"]->text();
        fieldInfo["available_quantity"] = this->lineEditMap["Available Quanity"]->text();

        conditionQuery=" Where book_id= "+QString::number(this->fieldID)+";";

        UpdateField("Book",
                    "books",
                    fieldInfo,
                    conditionQuery,
                    this);
        break;

    //profile window
    case 4:


        fieldInfo["member_name"] = this->lineEditMap["Name"]->text();
        fieldInfo["member_password"] = this->lineEditMap["Password"]->text();
        fieldInfo["member_phone"] = this->lineEditMap["Phone"]->text();

        conditionQuery=" Where member_id= "+QString::number(this->fieldID)+";";

        UpdateField("Member",
                    "members",
                    fieldInfo,
                    conditionQuery,
                    this);

        break;

    default:
        qDebug() << "Unexpected value for which_window:" << this->current_window;
        break;
    }
}


