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
        Support
    };

public:
    Champion() = default;
    ~Champion() = default;

    const QString &GetLocalizedName() const;
    void SetLocalizedName(const QString &newLocalizedName);

    const QString &GetIconName() const;
    void SetIconName(const QString &newIconName);

    const QString &GetLocalizedTitle() const;
    void SetLocalizedTitle(const QString &newLocalizedTitle);

    const std::set<ChampionPositions> &GetPositions() const;
    void AddPosition(ChampionPositions newPosition);

private:

    QString m_localizedName;
    QString m_iconName;
    QString m_localizedTitle;
    std::set<ChampionPositions> m_positions;
};

#endif // CHAMPION_H
