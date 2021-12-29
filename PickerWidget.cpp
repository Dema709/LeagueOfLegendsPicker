#include "PickerWidget.h"

#include <QMessageBox>
#include "JsonCharacterReader.h"
#include "ChampionPicker.h"

PickerWidget::PickerWidget(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Выбор чемпиона в League of Legends");
    //setAttribute(Qt::WA_DeleteOnClose);

    //Заполнение списка чемпионов
    QString inputFileName = "champions.json";
    if (!JsonCharacterReader::ReadCharactersFromFile(inputFileName, m_championList))
    {
        QMessageBox msgBox(this);
        msgBox.setText("Ошибка!");
        msgBox.setInformativeText("Ошибка открытия или парсинга файла. Подробности в qWarning.");
        msgBox.setIcon(QMessageBox::Icon::Critical);
        msgBox.exec();
    }

    //temp:
    Champion pickedChampion;
    if (!ChampionPicker::GetChampionByPosition(Champion::ChampionPositions::Mid, m_championList, pickedChampion))
    {
        QMessageBox msgBox(this);
        msgBox.setText("Ошибка!");
        msgBox.setInformativeText("Ошибка выбора чемпиона. Подробности в qWarning.");
        msgBox.setIcon(QMessageBox::Icon::Critical);
        msgBox.exec();
    }
    qDebug() << pickedChampion.GetLocalizedName();
}
