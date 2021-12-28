#ifndef CHAMPION_H
#define CHAMPION_H

#include <QString>

//Структура взята согласована с https://leagueoflegends.fandom.com/ru/wiki/Список_чемпионов

class Champion
{
public:
    Champion() = default;
    ~Champion() = default;

    const QString &GetLocalizedName() const;
    void SetLocalizedName(const QString &newLocalizedName);

    const QString &GetIconName() const;
    void SetIconName(const QString &newIconName);

    const QString &GetLocalizedTitle() const;
    void SetLocalizedTitle(const QString &newLocalizedTitle);

private:

    QString m_localizedName;
    QString m_iconName;
    QString m_localizedTitle;
};

#endif // CHAMPION_H
