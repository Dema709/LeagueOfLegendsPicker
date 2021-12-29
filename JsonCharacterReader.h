#ifndef JSONCHARACTERREADER_H
#define JSONCHARACTERREADER_H

#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include "Champion.h"

class JsonCharacterReader
{
public:
    JsonCharacterReader() = default;
    ~JsonCharacterReader() = default;

    //Возвращает успешность операции
    static bool ReadCharactersFromFile(const QString& filename, QList<Champion>& listToFill);

private:
    static bool readFile(const QString& filename, QJsonDocument& documentToFill);
    static bool parseJson(const QJsonDocument& document, QList<Champion>& listToFill);
};

#endif // JSONCHARACTERREADER_H
