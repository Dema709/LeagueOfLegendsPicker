#ifndef PICKERWIDGET_H
#define PICKERWIDGET_H

#include <QMainWindow>

#include "Champion.h"

class PickerWidget : public QMainWindow
{
    Q_OBJECT

public:
    PickerWidget(QWidget *parent = nullptr);
    ~PickerWidget() = default;;

private:
    QList<Champion> m_championList;
};
#endif // PICKERWIDGET_H
