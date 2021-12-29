#include "Champion.h"

const QString &Champion::GetLocalizedName() const
{
    return m_localizedName;
}

void Champion::SetLocalizedName(const QString &newLocalizedName)
{
    m_localizedName = newLocalizedName;
}

const QString &Champion::GetIconName() const
{
    return m_iconName;
}

void Champion::SetIconName(const QString &newIconName)
{
    m_iconName = newIconName;
}

const QString &Champion::GetLocalizedTitle() const
{
    return m_localizedTitle;
}

void Champion::SetLocalizedTitle(const QString &newLocalizedTitle)
{
    m_localizedTitle = newLocalizedTitle;
}

const std::set<Champion::ChampionPositions> &Champion::GetPositions() const
{
    return m_positions;
}

void Champion::AddPosition(ChampionPositions newPosition)
{
    m_positions.insert(newPosition);
}
