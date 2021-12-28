#ifndef PICKERWIDGET_H
#define PICKERWIDGET_H

#include <QMainWindow>

class PickerWidget : public QMainWindow
{
    Q_OBJECT

public:
    PickerWidget(QWidget *parent = nullptr);
    ~PickerWidget();
};
#endif // PICKERWIDGET_H
