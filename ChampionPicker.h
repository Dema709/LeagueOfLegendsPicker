#ifndef CHAMPIONPICKER_H
#define CHAMPIONPICKER_H

#include <QList>
#include "Champion.h"

class ChampionPicker
{
public:

    enum class ChoiceVariant
    {
        Position = 0,
        ChampionClass
    };

public:
    ChampionPicker() = default;
    ~ChampionPicker() = default;

    static bool GetChampionByPosition(Champion::ChampionPositions position, const QList<Champion>& championList, Champion& championToReturn);
    static bool GetChampionByChampionClass(Champion::ChampionClass cl, const QList<Champion>& championList, Champion& championToReturn);
};

#endif // CHAMPIONPICKER_H
