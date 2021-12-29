#include "PickerWidget.h"

//temp:
#include "JsonCharacterReader.h"

PickerWidget::PickerWidget(QWidget *parent)
    : QMainWindow(parent)
{
    //temp:
    QString inputFileName = "champions.json";
    QList<Champion> championList;
    if (!JsonCharacterReader::ReadCharactersFromFile(inputFileName, championList))
        qWarning("ReadCharactersFromFile failed");

}

PickerWidget::~PickerWidget()
{
}

