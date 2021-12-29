# Запуск через py.exe .\generate.py

# Генератор json файла для чемпионов

import json

# Данные о чемпионе
class Champion():
    def __init__(self):
        self.iconName = ""
        self.localizedName = ""
        self.localizedTitle = ""
        self.positions = []
    
    def convertToDict(self):
        return dict(iconName=self.iconName,
        localizedName=self.localizedName,
        localizedTitle=self.localizedTitle,
        positions=self.positions)
champions = []

# Входной файл с чемпионами и его структура
championsInputFileName = "champions.txt"
linesForOneChampion = 4

# Заполнение первичных данных о чемпионах из https://leagueoflegends.fandom.com/ru/wiki/Список_чемпионов
print("-> Заполнение первичных данных о чемпионах")
inputFile = open(championsInputFileName, encoding='utf-8')
lineNumber = 0
try:
    # работа с файлом
    champion = Champion()
    for line in inputFile:
        rem = lineNumber % linesForOneChampion
        line = line.replace('\n', '')
        #Иконка
        if rem == 0:
            champion.iconName = line.replace(' ', '_')
        elif rem == 1:
            champion.localizedName = line
        elif rem == 2:
            champion.localizedTitle = line
        elif rem == 3:
            #print(champion.convertToDict())
            champions.append(champion)
            champion = Champion()
        
        lineNumber = lineNumber + 1
finally:
    inputFile.close()

#Проверка
everythingOk = False
for champion in champions:
    if champion.localizedName == "Наутилус":
        everythingOk = True
if not everythingOk:
    print("Что-то не так с первичными данными")
    exit

# Входной файл с позициями и его структура
positionsInputFileName = "championPositions.txt"

# Добавление позиций из https://ru.op.gg/champion/statistics
# Т.к. давно не обновлялся сайт https://leagueoflegends.fandom.com/ru/wiki/Список_чемпионов/Позиции
print("-> Добавление позиций")
inputFile = open(positionsInputFileName, encoding='utf-8')
lineNumber = 0
currentChampionName = ""
try:
    # работа с файлом
    for line in inputFile:
        line = line.replace('\n', '')
        isChampion = False
        
        # Статистика имени текущего чемпиона
        for champion in champions:
            if champion.localizedName not in line:
                continue
            currentChampionName = champion.localizedName
            isChampion = True
        
        # Добавление позиции
        if not isChampion and line and line.strip():
            position = ""
            if "Верхняя" in line:
                position = "Top"
            elif "Лес" in line:
                position = "Jungle"
            elif "Средняя" in line:
                position = "Mid"
            elif "Bottom" in line:
                position = "Bottom"
            elif "Поддержка" in line:
                position = "Support"
            else:
                print("Что-то не так с данными о позиции:", currentChampionName, line)
            
            if position:
                for champion in champions:
                    if currentChampionName != champion.localizedName:
                        continue
                    currentChampionName = champion.localizedName
                    champion.positions.append(position)
        
finally:
    inputFile.close()

#Формирование json
print("-> Формирование json")
outputFileName = "champions.json"
with open(outputFileName, 'w') as outfile:
    #Конвертация в список словарей
    championsDict = []
    for champion in champions:
        #print(champion.convertToDict())
        championsDict.append(champion.convertToDict())
    #Запись в json
    #indent - количество отступов на уровень / строка вместо отступа
    json.dump(championsDict, outfile, ensure_ascii=False, indent=2)#dict(champions=championsDict)
