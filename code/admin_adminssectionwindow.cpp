#include "admin_adminssectionwindow.h"
#include "ui_admin_adminssectionwindow.h"
#include "global.h"
#include "stylesSheetGlobal.h"


int admin_AdminsSectionWindow::x=0;
int admin_AdminsSectionWindow::current_memberID = 0;
int admin_AdminsSectionWindow::current_window=0;

QString admin_AdminsSectionWindow::background_path="";





QPushButton* push_button[1000];
QString buttonText;



admin_AdminsSectionWindow::admin_AdminsSectionWindow(QWidget *parent, QString Member_id, bool is_Admin)
    : QDialog(parent)
    , ui(new Ui::admin_AdminsSectionWindow)
{
    ui->setupUi(this);


    this->x=0; //button_counter
    this->current_memberID = 0;
    this->current_window=0;

    this->background_path="";


    this->member_id=Member_id;
    this->is_admin=is_Admin;

    //set the text of the buttons admin, or member
    if(this->is_admin)
    {
        ui->Admins_Button->setText("Employees");
        ui->Members_Button->setText("Members");
    }
    else
    {
        ui->Admins_Button->setText("Borroowd List");
        ui->Members_Button->setText("Books");
    }

    SetStyleSheetForWindowItems();
    on_Profile_Button_clicked();

}

admin_AdminsSectionWindow::~admin_AdminsSectionWindow()
{
    delete ui;
}

void admin_AdminsSectionWindow::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(this->background_path);
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    this->setPalette(p);


    this->setAutoFillBackground(true);

    QDialog::resizeEvent(event);
}

/*Dashboard Buttons Functions*/

void admin_AdminsSectionWindow::on_Profile_Button_clicked()
{

    int futureWindow=this->is_admin?4:6;

    if(this->current_window!=4 | this->current_window!=6)
    {
        PrepareWindow(futureWindow);

        int startIndex = 0;
        populateDynamicGrid(
            ui->scrollArea_account,
            "members",
            &startIndex,
            {"Name", "ID","Role","Phone","Start Date","End Date"},
            {"member_name", "member_id", "member_type","member_phone","sub_startDate","sub_endDate"},
            " WHERE member_id='"+this->member_id+"'",
            this,
            true
            );

    }

}



void admin_AdminsSectionWindow::on_Admins_Button_clicked()
{

    int futureWindow=this->is_admin?1:7;

    if(this->current_window!=1 | this->current_window!=7)
    {

        PrepareWindow(futureWindow);
        int startIndex = 1;

        if(this->is_admin)
        {
            SetRoleFiler(this->current_window);

            populateDynamicGrid(
                ui->scrollArea,
                "members",
                &startIndex,
                {"ID", "Role"},
                {"member_name", "member_id", "member_type"},
                " WHERE member_type <> 'Member'",
                this
                );
        }
        else
        {
            populateDynamicGrid(
                ui->scrollArea,
                "borrow",
                &startIndex,
                {"ID", "Author", "Genre","Returned"},
                {"books.book_title", "books.book_id","books.author_name", "books.genre","borrow.is_returned"},
                " join books on borrow.book_id=books.book_id WHERE member_id = '"+this->member_id+"'",
                this
                // false,
                // "",
                // "book_id"
                );
        }
    }
}



void admin_AdminsSectionWindow::on_Members_Button_clicked()
{

    if(this->current_window!=2)
    {

        int startIndex = 1;

        if(this->is_admin)
        {

            PrepareWindow(2);

            SetRoleFiler(current_window);


            populateDynamicGrid(
                ui->scrollArea,
                "members",
                &startIndex,
                {"ID", "Role"},
                {"member_name", "member_id", "member_type"},
                " WHERE member_type = 'Member'",
                this
                );
        }
        else
        {
            ui->AddMember_Button->hide();
            on_Books_Button_clicked();
        }

    }

}


void admin_AdminsSectionWindow::on_Books_Button_clicked()
{
    if(this->current_window!=3 | this->current_window!=5)
    {
        int future_window=this->is_admin?3:5;
        PrepareWindow(future_window);
        SetRoleFiler(current_window);

        int startIndex = 1;
        populateDynamicGrid(
            ui->scrollArea,
            "books",
            &startIndex,
            {"ID", "Author", "Genre"},
            {"book_title", "book_id","author_name", "genre"},
            "",
            this
            // false,
            // "",
            // "book_id"
            );
    }

}

void admin_AdminsSectionWindow::on_Logout_Button_clicked()
{
    mainWindow =new MainWindow();
    mainWindow->show();
    hide();
}


/*fucntion buttons*/


void admin_AdminsSectionWindow::on_EditAccount_Button_clicked()
{
    on_EditMember_Button_clicked();
}

void admin_AdminsSectionWindow::on_DeleteAccount_Button_clicked()
{
    on_DeleteMember_Button_clicked();
}



void admin_AdminsSectionWindow::On_MemberName_Clicked()
{

    push_button[x]=new QPushButton;

    push_button[x]=qobject_cast<QPushButton*>(sender());


    if(x>0)
    {
        push_button[x-1]->setObjectName("btnName");
        push_button[x-1]->setStyleSheet(NameButton_Style("btnName"));
    }

    //set the style cheet
    push_button[x]->setStyleSheet(pushButton_Style());

    QString choosen_Name =push_button[x]->text();//book title
    QString current_id = push_button[x]->property("id").toString();



    int startIndex = 0;


    switch (this->current_window)
    {
    //admins windows
    case 1:
    case 2:
        populateDynamicGrid(
            ui->scrollArea_2,
            "members",
            &startIndex,
            {"Name", "ID","Role","Phone","Start Date","End Date"},
            {"member_name", "member_id", "member_type","member_phone","sub_startDate","sub_endDate"},
            " WHERE member_id='"+current_id+"'",
            this,
            true
            );

        break;

        //members window
    case 3:
        populateDynamicGrid(
            ui->scrollArea_2,
            "books",
            &startIndex,
            {"Title", "ID","Author","Genra","Location","Available Quantity","Borrowed Quanitity"},
            {"book_title", "book_id", "author_name","genre","book_place","available_quantity","borrowed_quantity"},
            " WHERE book_id='"+current_id+"'",
            this,
            true,
            "",
            "book_id"
            );
        break;
    case 5:
        populateDynamicGrid(
            ui->scrollArea_2,
            "books",
            &startIndex,
            {"Title", "ID","Author","Genra","Location","Available Quantity"},
            {"book_title", "book_id", "author_name","genre","book_place","available_quantity"},
            " WHERE book_id='"+current_id+"'",
            this,
            true,
            "",
            "book_id"
            );
        break;
    case 7:
        populateDynamicGrid(
            ui->scrollArea_2,
            "borrow",
            &startIndex,
            {"Title", "ID","Author","Genra","Borrowed Date","Return Date", "Returned"},
            {"books.book_title", "books.book_id", "books.author_name","books.genre","borrow.borrowed_date","borrow.return_date","borrow.is_return"},
            " join books on borrow.book_id=books.book_id WHERE borrow.book_id = '"+current_id+"'"+ " AND borrow.member_id= "+this->member_id +" ",
            this,
            true,
            "",
            "book_id"
            );
        break;

    default:
        qDebug() << "Unexpected value for which_window:" << this->current_window;
        break;
    }

    this->current_memberID=current_id.toInt();



}



void admin_AdminsSectionWindow::on_EditMember_Button_clicked()
{
    //current_choosenId
    if(this->current_memberID==0 && this->current_window!=4 && this->current_window!=6 )
    {
        QMessageBox::critical(this,"Edit Member Info","Error: Please, Choose a member!");

    }
    else
    {
        if(this->current_window==4 | this->current_window==6 )
        {
            editMemberWindow =new subWindow_EditMember(this,(this->member_id).toInt(),this->current_window);
        }

        else
        {
            editMemberWindow =new subWindow_EditMember(this,this->current_memberID,this->current_window);
        }

        editMemberWindow->show();
    }



}




void admin_AdminsSectionWindow::on_DeleteMember_Button_clicked()
{

    QString MemberId=this->current_window==4?this->member_id:QString::number(this->current_memberID);

    switch (this->current_window)
    {
    //admins windows
    case 1:
    //members window
    case 2:
    //profile window
    case 4:
    case 6:
        deleteField("Member",
                    "members",
                    " WHERE member_id ="+MemberId+";",
                    this,
                    (MemberId).toInt());

        if(this->current_window==4 | this->current_window==6)
        {
            mainWindow =new MainWindow();
            mainWindow->show();
            hide();
        }
        break;

        //members window
    case 3:
        deleteField("Book",
                    "books",
                    " WHERE book_id ="+MemberId+";",
                    this,
                    (MemberId).toInt());
        break;

    default:
        qDebug() << "Unexpected value for which_window:" << this->current_window;
        break;
    }


}


void admin_AdminsSectionWindow::on_AddMember_Button_clicked()
{

    addMemberWindow =new subWindow_AddMember(this, this->current_window);
    addMemberWindow->show();
}



void admin_AdminsSectionWindow::on_Search_Button_clicked()
{

    int startIndex = 1;

    QString SearchName, memberRole, QueryRoleFilter="";

    SearchName=ui->Search_LineEdit->text();
    memberRole=ui->Role_Search->currentText();


    switch (this->current_window)
    {
    //admins windows
    case 1:
        if(memberRole!="All")
        {
            QueryRoleFilter=" WHERE member_type = '"+memberRole+"' AND member_name LIKE '%" +SearchName+"%';";
        }
        else
        {
            QueryRoleFilter=" WHERE member_type <> 'Member' AND member_name LIKE '%" +SearchName+"%';";
        }
        populateDynamicGrid(
            ui->scrollArea,
            "members",
            &startIndex,
            {"ID", "Role"},
            {"member_name", "member_id", "member_type"},
            QueryRoleFilter,
            this
            );

        break;
    case 2:
        if(memberRole=="All")
        {
            QueryRoleFilter=" WHERE member_type = 'Member' AND member_name LIKE '%" +SearchName+"%' ;";
        }
        else if(memberRole=="Borrowed")
        {
            QueryRoleFilter=" inner join borrow on members.member_id=borrow.member_id"
                " WHERE members.member_type = 'Member' AND members.member_name LIKE '%" +SearchName+"%';";
        }
        else
        {
            QueryRoleFilter=" inner join borrow on members.member_id=borrow.member_id"
            " WHERE borrow.member_id IS NULL AND members.member_type = 'Member' AND members.member_name LIKE '%" +SearchName+"%';";
        }
        populateDynamicGrid(
            ui->scrollArea,
            "members",
            &startIndex,
            {"ID", "Phone"},
            {"members.member_name", "members.member_id", "members.member_phone"},
            QueryRoleFilter,
            this,
            false,
            " DISTINCT "
            );

        break;

        //members window
    case 3:
    case 5:
    case 7:

        if(memberRole=="All")
        {
            QueryRoleFilter=" WHERE book_title LIKE '%" +SearchName+"%' ;";
        }
        else if(memberRole=="Available")
        {
            QueryRoleFilter=" WHERE available_quantity > 0 AND book_title LIKE '%" +SearchName+"%' ;";
        }
        else
        {
            QueryRoleFilter=" WHERE available_quantity = 0 AND book_title LIKE '%" +SearchName+"%' ;";
        }

        if(this->current_window==7)
        {
            QueryRoleFilter =" join books on borrow.book_id=books.book_id WHERE member_id = '"+this->member_id+"'" +" AND "+QueryRoleFilter;
        }
        else
        {
            QueryRoleFilter =" WHERE "+QueryRoleFilter;
        }
        populateDynamicGrid(
            ui->scrollArea,
            "books",
            &startIndex,
            {"ID", "Author", "Genre"},
            {"book_title", "book_id","author_name", "genre"},
            QueryRoleFilter,
            this
            );

        break;

    default:
        qDebug() << "Unexpected value for which_window:" << this->current_window;
        break;
    }



}



void admin_AdminsSectionWindow::on_ReturnOrReserveBook_Button_clicked()
{
    QString BookId=QString::number(this->current_memberID);//current_choosenID

    QMap<QString, QVariant> fieldInfo;
    QStringList is_not_member_retuned_every_book_in_the_specified_period={"0"};
    QStringList does_have_book_with_the_same_id_already_reserved={"0"};



    if(this->current_memberID==0)
    {
        QMessageBox::critical(this,"Edit Member Info","Error: Please, Choose a Book!");

    }
    else
    {
        switch (this->current_window)
        {
        //borrow list
        //return
        case 7:
            fieldInfo["is_returned"]=1;
            fieldInfo["return_date"]=QDate::currentDate().toString("yyyy-MM-dd");

            UpdateField("Book",
                        "borrow",
                        fieldInfo,
                        " WHERE book_id ="+BookId+";",
                        this);
            break;
        //books list
        //reserve
        case 5:
            is_not_member_retuned_every_book_in_the_specified_period= SelectField(  "borrow",
                                                                                    {"count(*)"},
                                                                                    " WHERE member_id ="+this->member_id+" AND is_returned=0 AND DATE(return_date) > '"+ QDate::currentDate().toString("yyyy-MM-dd") + "' ;");

            does_have_book_with_the_same_id_already_reserved=SelectField(  "borrow",
                                                                           {"count(*)"},
                                                                           " WHERE book_id ="+BookId +" AND  member_id ="+this->member_id+";");
            //member can reserve more books
            if(!is_not_member_retuned_every_book_in_the_specified_period[0].toInt() | !does_have_book_with_the_same_id_already_reserved[0].toInt())
            {
                fieldInfo["member_id"]=this->member_id;
                fieldInfo["book_id"]=BookId;
                fieldInfo["borrowed_date"]=QDate::currentDate().toString("yyyy-MM-dd");
                fieldInfo["return_date"]=QDate::currentDate().addDays(15).toString("yyyy-MM-dd");

                //insert it in the borrow list
                AddField("Book",
                        "borrow",
                        fieldInfo,
                        this);
            }
            //member can't reserve more book
            else
            {
                QMessageBox::critical(this,"Reserve Books","Error: Please, Return your books before reserving a new one!");
            }


            break;

        default:
            qDebug() << "Unexpected value for which_window:" << this->current_window;
            break;
        }
    }
}


void admin_AdminsSectionWindow::SetRoleFiler(int which_window)
{
    switch (which_window)
    {
        //admins windows
        case 1:
            //set the Role Fileter
            ui->Role_Search->addItems({"All","Manager","Staff"});
            break;

         //members window
         case 2:
            ui->Role_Search->clear();
            ui->Role_Search->addItems({"All","Borrowed","Non-Borrowed"});
             break;

         //books window
         case 3:
             ui->Role_Search->clear();
             ui->Role_Search->addItems({"All","Available","Not-Available"});
             break;

         default:
             qDebug() << "Unexpected value for which_window:" << which_window;
             break;
    }
}



void admin_AdminsSectionWindow::SetBackgroundPath(int what_background)
{
    if (what_background==1)
    {
        this->background_path=":/resources/images/ProfileBackground.png";
    }
    else if(what_background==2)
    {
        this->background_path=":/resources/images/dashboard-2.png";
    }
    else if(what_background==3)
    {
        this->background_path=":/resources/images/user_profileBackground.png";
    }
    else if(what_background==4)
    {
        this->background_path=":/resources/images/user_Dashboard.png";
    }


    this->resizeEvent(nullptr);
}

void admin_AdminsSectionWindow::SetStyleSheetForWindowItems()
{

    ui->Profile_Button->setStyleSheet(dashboard_button_Style());
    ui->Admins_Button->setStyleSheet(dashboard_button_Style());
    ui->Members_Button->setStyleSheet(dashboard_button_Style());
    ui->Logout_Button->setStyleSheet(dashboard_button_Style());

    ui->AddMember_Button->setStyleSheet(filled_button_Style());
    ui->EditMember_Button->setStyleSheet(filled_button_Style());
    ui->EditAccount_Button->setStyleSheet(filled_button_Style());
    ui->ReturnOrReserveBook_Button->setStyleSheet(filled_button_Style());

    ui->Search_Button->setStyleSheet(nonFilled_button_Style());
    ui->DeleteMember_Button->setStyleSheet(nonFilled_button_Style());
    ui->DeleteAccount_Button->setStyleSheet(nonFilled_button_Style());

    ui->scrollArea_2->setStyleSheet(scrollArea_Style());
    ui->scrollArea_account->setStyleSheet(scrollArea_Style());


    ui->Books_Button->setStyleSheet(dashboard_button_Style());
}


void admin_AdminsSectionWindow::HideDashboardItems()
{
    ui->AddMember_Button->hide();
    ui->EditMember_Button->hide();
    ui->ReturnOrReserveBook_Button->hide();

    ui->Search_Button->hide();
    ui->DeleteMember_Button->hide();
    ui->scrollArea_2->hide();
    ui->scrollArea->hide();
    ui->Search_Button->hide();
    ui->Role_Search->hide();
    ui->Search_LineEdit->hide();
    ui->role_filter_label->hide();

    if(this->is_admin==false)
    {
        ui->EditMember_Button->hide();
        ui->DeleteMember_Button->hide();

    }

}

void admin_AdminsSectionWindow::ShowDashboardItems(int future_window)
{

    ui->Search_Button->show();    
    ui->scrollArea_2->show();
    ui->scrollArea->show();
    ui->Search_Button->show();
    ui->Role_Search->show();
    ui->Search_LineEdit->show();
    ui->role_filter_label->show();

    if(this->is_admin)
    {
        ui->EditMember_Button->show();
        ui->DeleteMember_Button->show();

        ui->AddMember_Button->show();
    }
    else
    {
        //reserve list window
        if(future_window==7)
        {
            ui->ReturnOrReserveBook_Button->setText("Return");
        }
        //book list window
        else
        {
            ui->ReturnOrReserveBook_Button->setText("Reserve");
        }
        ui->ReturnOrReserveBook_Button->show();
    }
}

void admin_AdminsSectionWindow::HideProfileItems()
{
    ui->EditAccount_Button->hide();
    ui->DeleteAccount_Button->hide();
    ui->scrollArea_account->hide();

    if(this->is_admin==false)
    {
        ui->Books_Button->hide();
    }
}
void admin_AdminsSectionWindow::ShowProfileItems()
{
    ui->EditAccount_Button->show();
    ui->DeleteAccount_Button->show();
    ui->scrollArea_account->show();

    if(this->is_admin==false)
    {
        ui->Books_Button->hide();
    }


}

void admin_AdminsSectionWindow::checkIfTheCurrentBackgroundChanged(int future_window)
{
    /*

    admin section:
    profile:4
    admin:1
    members:2
    books:4

    member section:
    profile: 6
    books: 5
    borrowed list:7

    */

    //othor windows for admin section
    //if the current window is admin-profile and the next is not admin-profile
    if(this->current_window==4 &&future_window !=4)
    {
        SetBackgroundPath(2);
        HideProfileItems();
        ShowDashboardItems(future_window);


    }
    //profile window for admin section
    //if the current window is not admin-profile and the next is admin-profile
    else if(this->current_window!=4 &&future_window ==4)
    {
        SetBackgroundPath(1);
        HideDashboardItems();
        ShowProfileItems();
    }
    //if the current window is member-profile and the next is not member-profile
    else if(this->current_window==6 && future_window !=6)
    {
        SetBackgroundPath(4);
        HideProfileItems();
        ShowDashboardItems(future_window);
    }
    //member window =>books,members
    //if the current window is not member-profile and the next is member-profile
    else if(this->current_window!=6 &&future_window ==6)
    {
        SetBackgroundPath(3);
        HideDashboardItems();
        ShowProfileItems();
    }
    //if this is borrow or book list window
    else if(this->current_window==7 | this->current_window==5)
    {
        //reserve list window
        if(future_window==7)
        {
            ui->ReturnOrReserveBook_Button->setText("Return");
        }
        //book list window
        else
        {
            ui->ReturnOrReserveBook_Button->setText("Reserve");
        }
        ui->ReturnOrReserveBook_Button->show();
    }

}


void admin_AdminsSectionWindow::SetButtonPressedToTrueForDashboard(int current_window, int future_window)
{

    if(future_window==5)
    {
        int a=1;
    }

    //set the current button to false
    if(current_window==4 | current_window==6)
    {
        ui->Profile_Button->setDown(false);
    }
    else if(current_window==1 | current_window==7)
    {
        ui->Admins_Button->setDown(false);
    }
    else if(current_window==2 | current_window==5)
    {
        ui->Members_Button->setDown(false);
    }
    else if(current_window==3)
    {
        ui->Books_Button->setDown(false);
    }


   //set the future button to true
    if(future_window==4 | future_window==6)
    {
        ui->Profile_Button->setDown(true);
    }
    else if(future_window==1 | future_window==7)
    {
        ui->Admins_Button->setDown(true);
    }
    else if(future_window==2 | future_window==5)
    {
        ui->Members_Button->setDown(true);
    }
    else if(future_window==3)
    {
        ui->Books_Button->setDown(true);
    }

}


void admin_AdminsSectionWindow::PrepareWindow(int future_window_num)
{
    checkIfTheCurrentBackgroundChanged(future_window_num);
    SetButtonPressedToTrueForDashboard(this->current_window,future_window_num);
    this->current_window=future_window_num;
}







