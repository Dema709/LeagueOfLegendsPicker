#include "JsonCharacterReader.h"

#include <QFile>
#include <QJsonArray>
#include <QTextStream>

bool JsonCharacterReader::ReadCharactersFromFile(const QString& filename, QList<Champion>& listToFill)
{
    QJsonDocument jsonDocument;
    if (!readFile(filename, jsonDocument))
    {
        qWarning("Ошибка чтения файла.");
        return false;
    }

    if (!parseJson(jsonDocument, listToFill))
    {
        qWarning("Ошибка парсинга данных.");
        return false;
    }

    return true;
}

bool JsonCharacterReader::readFile(const QString& filename, QJsonDocument& documentToFill)
{
    QFile file;
    file.setFileName(filename);

    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning("Ошибка чтения файла.");
        return false;
    }

    QTextStream in(&file);
    in.setCodec("Windows-1251");

    QString allFileString = in.readAll();

    QByteArray saveData = allFileString.toUtf8();
    QJsonParseError err;
    documentToFill = QJsonDocument::fromJson(saveData, &err);

    if(err.error != QJsonParseError::NoError)
    {
        qWarning("QJsonParseError");
        return false;
    }

    return true;
}

bool JsonCharacterReader::parseJson(const QJsonDocument& document, QList<Champion> &listToFill)
{
    if (!document.isArray())
    {
        qWarning("Не найден массив чемпионов в json");
        return false;
    }

    auto championsArray = document.array();
    if (championsArray.empty())
    {
        qWarning("Пустой массив");
        return false;
    }

    //Наименования нод свойств чемпиона
    QString iconNameNode = "iconName";
    QString localizedNameNode = "localizedName";
    QString localizedTitleNode = "localizedTitle";
    QString positionsNode = "positions";
    //Наименования атрибутов по предпочитаемым позициям
    QString topAttribute = "Top";
    QString jungleAttribute = "Jungle";
    QString midAttribute = "Mid";
    QString bottomAttribute = "Bottom";
    QString supportAttribute = "Support";

    //Заполнение и добавление информации о чемпионах
    for (int i = 0; i < championsArray.size(); i++)
    {
        QJsonObject championObject = championsArray[i].toObject();
        Champion currentChampion;

        if (championObject.contains(iconNameNode) && championObject[iconNameNode].isString())
        {
            currentChampion.SetIconName(championObject[iconNameNode].toString());
        }
        else
        {
            qWarning("Ошибка парсинга json: не найдена нода iconNameNode");
            return false;
        }

        if (championObject.contains(localizedNameNode) && championObject[localizedNameNode].isString())
        {
            currentChampion.SetLocalizedName(championObject[localizedNameNode].toString());
        }
        else
        {
            qWarning("Ошибка парсинга json: не найдена нода localizedNameNode");
            return false;
        }

        if (championObject.contains(localizedTitleNode) && championObject[localizedTitleNode].isString())
        {
            currentChampion.SetLocalizedTitle(championObject[localizedTitleNode].toString());
        }
        else
        {
            qWarning("Ошибка парсинга json: не найдена нода localizedTitleNode");
            return false;
        }

        if (championObject.contains(positionsNode) && championObject[positionsNode].isArray())
        {
            auto positions = championObject[positionsNode].toArray();
            for (int j = 0; j < positions.size(); j++)
            {
                auto position = positions[j].toString();

                if (position == topAttribute)
                    currentChampion.AddPosition(Champion::ChampionPositions::Top);
                else if (position == jungleAttribute)
                    currentChampion.AddPosition(Champion::ChampionPositions::Jungle);
                else if (position == midAttribute)
                    currentChampion.AddPosition(Champion::ChampionPositions::Mid);
                else if (position == bottomAttribute)
                    currentChampion.AddPosition(Champion::ChampionPositions::Bottom);
                else if (position == supportAttribute)
                    currentChampion.AddPosition(Champion::ChampionPositions::Support);
                else
                {
                    qWarning("Ошибка парсинга json: необрабатываемое значение в positions:");
                    qWarning() << position;
                    return false;
                }
            }
        }
        else
        {
            qWarning("Ошибка парсинга json: не найдена нода positionsNode");
            return false;
        }

        listToFill.push_back(currentChampion);
    }

    return true;
}
