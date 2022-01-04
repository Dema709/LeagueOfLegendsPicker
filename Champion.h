#ifndef CHAMPION_H
#define CHAMPION_H

#include <QString>
#include <set>

class Champion
{
public:
    //Предпочитаемые позиции
    enum class ChampionPositions
    {
        Top = 0,
        Jungle,
        Mid,
        Bottom,
        Support,
        Any
    };

    //Класс персонажа
    enum class ChampionClass
    {
        Mage,
        Assassin,
        Marksman,
        Tank,
        Fighter,
        Support,
        Any
    };

public:
    Champion() = default;
    ~Champion() = default;

    const QString& GetLocalizedName() const;
    void SetLocalizedName(const QString &newLocalizedName);

    const QString& GetIconName() const;
    void SetIconName(const QString &newIconName);

    const QString& GetLocalizedTitle() const;
    void SetLocalizedTitle(const QString &newLocalizedTitle);

    const std::set<ChampionPositions>& GetPositions() const;
    void AddPosition(ChampionPositions newPosition);

    const std::set<ChampionClass>& GetChampionClasses() const;
    void AddChampionClass(ChampionClass newChampionClass);

private:
    QString m_localizedName;
    QString m_iconName;
    QString m_localizedTitle;
    std::set<ChampionPositions> m_positions;
    std::set<ChampionClass> m_championClasses;
};

#endif // CHAMPION_H
