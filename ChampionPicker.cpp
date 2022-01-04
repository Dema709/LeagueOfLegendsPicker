#include "ChampionPicker.h"
#include "random.hpp"

bool ChampionPicker::GetChampionByPosition(Champion::ChampionPositions position, const QList<Champion> &championList, Champion &championToReturn)
{
    if (championList.empty())
    {
        qWarning("Список чемпионов пуст.");
        return false;
    }

    if (position == Champion::ChampionPositions::Any)
    {
        //Выбор случайного чемпиона из списка
        auto candidateNum = effolkronium::random_static::get<int>(0, championList.size()-1);
        championToReturn = championList[candidateNum];
        return true;
    }
    else
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
}

bool ChampionPicker::GetChampionByChampionClass(Champion::ChampionClass cl, const QList<Champion> &championList, Champion &championToReturn)
{
    if (championList.empty())
    {
        qWarning("Список чемпионов пуст.");
        return false;
    }

    if (cl == Champion::ChampionClass::Any)
    {
        //Выбор случайного чемпиона из списка
        auto candidateNum = effolkronium::random_static::get<int>(0, championList.size()-1);
        championToReturn = championList[candidateNum];
        return true;
    }
    else
    {
        //Формирование списка подходящих чемпионов
        QList<Champion> candidates;
        for (auto& champion : championList)
        {
            if (champion.GetChampionClasses().count(cl))
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
}
