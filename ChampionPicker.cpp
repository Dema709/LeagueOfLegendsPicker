#include "ChampionPicker.h"
#include "random.hpp"

bool ChampionPicker::GetChampionByPosition(Champion::ChampionPositions position, const QList<Champion> &championList, Champion &championToReturn)
{
    //Формирование списка подходящих чемпионов
    QList<Champion> candidates;
    for (auto& champion : championList)
    {
        if (champion.GetPositions().count(position))
            candidates.push_back(champion);
    }

    if (candidates.empty())
    {
        qWarning("Список подходящих чемпионов пуст.");
        return false;
    }

    //Выбор случайного чемпиона из списка подходящих
    auto candidateNum = effolkronium::random_static::get<int>(0, candidates.size()-1);
    championToReturn = candidates[candidateNum];
    return true;
}
