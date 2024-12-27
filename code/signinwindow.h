#ifndef SIGNINWINDOW_H
#define SIGNINWINDOW_H

#include <QDialog>
#include "admin_adminssectionwindow.h"


namespace Ui {
class SignInWindow;
}

class SignInWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SignInWindow(QWidget *parent = nullptr);
    ~SignInWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_login_button_clicked();

private:
    Ui::SignInWindow *ui;
    admin_AdminsSectionWindow* AdminWindow;



};

#endif // SIGNINWINDOW_H
