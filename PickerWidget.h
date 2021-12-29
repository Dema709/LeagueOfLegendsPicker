#ifndef PICKERWIDGET_H
#define PICKERWIDGET_H

#include <QWidget>
#include <QGridLayout>

#include "Champion.h"
#include "ChampionPicker.h"

class PickerWidget : public QWidget
{
    Q_OBJECT

public:
    PickerWidget(QWidget *parent = nullptr);
    ~PickerWidget() = default;

signals:
    void changeChosenChampionIconName(const QPixmap& iconPixmap);
    void changeChosenChampionLocalizedName(const QString& localizedName);
    void changeChosenChampionLocalizedTitle(const QString& localizedTitle);

private:
    void fillLayout();
    void fillUserChoiceLayout(QVBoxLayout* userChoiceLayout);
    void fillChosenChampionLayout(QVBoxLayout* chosenChampionLayout);

    //Скрыть лишние виджеты, оставить только нужный
    void changeChoiceVariant(ChampionPicker::ChoiceVariant choiceVariant);

    //Изменение позиции для поиска по линии
    void changePosition(Champion::ChampionPositions position);

    //Подбор чемпиона по заданным критериям
    void pickChampion();

    //Отображение выбранного чемпиона
    void changeChosenChampion(Champion& champion);

private:
    ChampionPicker::ChoiceVariant m_choiceVariant = ChampionPicker::ChoiceVariant::Position;
    Champion::ChampionPositions m_position = Champion::ChampionPositions::Any;

    bool m_layoutInitialized = false;
    QList<Champion> m_championList;
    std::map<ChampionPicker::ChoiceVariant, QWidget*> m_choiceVariantWidgetsMap;
};
#endif // PICKERWIDGET_H
