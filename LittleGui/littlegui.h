#ifndef LITTLEGUI_H
#define LITTLEGUI_H

#include <QDialog>

namespace Ui {
class LittleGui;
}

class LittleGui : public QDialog
{
    Q_OBJECT

public:
    explicit LittleGui(QWidget *parent = 0);
    ~LittleGui();

private slots:
    void on_liveImage_clicked();

private:
    Ui::LittleGui *ui;
};

#endif // LITTLEGUI_H
