#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "signinwindow.h"
#include "subwindow_addmember.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_Login_clicked();

    void on_Signup_clicked();

private:
    Ui::MainWindow *ui;
    SignInWindow* signInWindow;
    subWindow_AddMember* addMemberWindow;
};
#endif // MAINWINDOW_H
