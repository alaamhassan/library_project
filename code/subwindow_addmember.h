#ifndef SUBWINDOW_ADDMEMBER_H
#define SUBWINDOW_ADDMEMBER_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class subWindow_AddMember;
}

class subWindow_AddMember : public QDialog
{
    Q_OBJECT

public:
    explicit subWindow_AddMember(QWidget *parent = nullptr,int current_window=0);
    ~subWindow_AddMember();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_addMember_Button_clicked();

private:
    Ui::subWindow_AddMember *ui;
    int current_window;
    QMap<QString, QLineEdit*> lineEditMap;

};

#endif // SUBWINDOW_ADDMEMBER_H
