#ifndef SHOWCARSWINDOW_H
#define SHOWCARSWINDOW_H

#include <QMainWindow>

namespace Ui {
class ShowCarsWindow;
}

class ShowCarsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowCarsWindow(QWidget *parent = nullptr);
    ~ShowCarsWindow();

private:
    Ui::ShowCarsWindow *ui;
};

#endif // SHOWCARSWINDOW_H
