#ifndef ADMIN_ADMINSSECTIONWINDOW_H
#define ADMIN_ADMINSSECTIONWINDOW_H

#include <QDialog>
#include "qsqlquerymodel.h"
#include "subwindow_editmember.h"
#include "subwindow_addmember.h"
//#include "profilewindow.h"

namespace Ui {
class admin_AdminsSectionWindow;
}

class admin_AdminsSectionWindow : public QDialog
{
    Q_OBJECT

public:
    static int x;
    QString queryCondition="member_type <> 'Member'";

public:
    explicit admin_AdminsSectionWindow(QWidget *parent = nullptr, QString member_id=0, bool is_Admin=true);
    ~admin_AdminsSectionWindow();

    void SetRoleFiler(int which_window);
    void SetBackgroundPath(int what_background);

    void HideDashboardItems();
    void HideProfileItems();
    void ShowDashboardItems(int future_window);
    void ShowProfileItems();

    void SetStyleSheetForWindowItems();

    void checkIfTheCurrentBackgroundChanged(int future_window);
    void SetButtonPressedToTrueForDashboard(int current_window, int future_window);
    void PrepareWindow(int future_window_num);


private slots:

    void on_Books_Button_clicked();
    void on_Members_Button_clicked();
    void On_MemberName_Clicked();
    void on_EditMember_Button_clicked();
    void on_DeleteMember_Button_clicked();
    void on_AddMember_Button_clicked();
    void on_Search_Button_clicked();

    void on_Admins_Button_clicked();

    void on_Profile_Button_clicked();

    void on_Logout_Button_clicked();

    void on_EditAccount_Button_clicked();

    void on_DeleteAccount_Button_clicked();

    void on_ReturnOrReserveBook_Button_clicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::admin_AdminsSectionWindow *ui;
    subWindow_EditMember* editMemberWindow;
    subWindow_AddMember* addMemberWindow;
   // ProfileWindow* profileWindow;
    static int current_memberID; //current_choosenID
    // QSqlQueryModel* memberId_model;
    // QSqlQueryModel* memberName_model;
    // QSqlQueryModel* memberType_model;
    static int current_window;
    static QString background_path;
    QString member_id; //
    bool is_admin;

};

#endif // ADMIN_ADMINSSECTIONWINDOW_H
