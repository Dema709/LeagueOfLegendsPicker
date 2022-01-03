# Запуск через py.exe .\generateJson.py

# Генератор json файла для чемпионов

import json
# Библиотека для класса Enum
from enum import Enum, auto

# Данные о линии чемпиона
class ChampionPosition(Enum):
    Top     = 0
    Jungle  = auto()
    Mid     = auto()
    Bottom  = auto()
    Support = auto()
    Any     = auto()

# Данные о чемпионе
class Champion():
    def __init__(self):
        self.iconName = ""
        self.localizedName = ""
        self.localizedTitle = ""
        self.positions = set()
    
    def convertToDict(self):
        positionList = [pos.name for pos in list(self.positions)]
        
        return dict(iconName=self.iconName,
        localizedName=self.localizedName,
        localizedTitle=self.localizedTitle,
        positions=sorted(positionList))
        
    def addPosition(self, position):
        r = 0
        if position not in self.positions:
            r = r + 1
        self.positions.add(position)
        return r
        
    def addPositions(self, positions):
        r = 0
        for position in positions:
            if position not in self.positions:
                r = r + 1
            self.positions.add(position)
        return r
champions = []

# Входной файл с чемпионами и его структура
championsInputFileName = "ChampionsInfo/1. champions leagueoflegendsfandom.txt"
linesForOneChampion = 4

# Заполнение первичных данных о чемпионах из https://leagueoflegends.fandom.com/ru/wiki/Список_чемпионов
print("-> Заполнение первичных данных о чемпионах")
addedChampionsCount = 0
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
            line = line.replace(' ', '')
            line = line.replace("OriginalSquare", "Square")
            line = line.replace('\'', "")
            champion.iconName = line
        elif rem == 1:
            champion.localizedName = line
        elif rem == 2:
            champion.localizedTitle = line
        elif rem == 3:
            #print(champion.convertToDict())
            champions.append(champion)
            addedChampionsCount = addedChampionsCount + 1
            champion = Champion()
        
        lineNumber = lineNumber + 1
finally:
    inputFile.close()

#Проверка
nautilusFound = False
for champion in champions:
    if champion.localizedName == "Наутилус":
        nautilusFound = True
if not nautilusFound or addedChampionsCount == 0:
    print("Что-то не так с первичными данными")
    exit
else:
    print("Добавлено", addedChampionsCount, "чемпионов")
    
# Входной файл с позициями и его структура (первый)
positionsInputFileName = "ChampionsInfo/2. championPositions ruopgg.txt"

# Добавление позиций из https://ru.op.gg/champion/statistics
# Т.к. давно не обновлялся сайт https://leagueoflegends.fandom.com/ru/wiki/Список_чемпионов/Позиции
print("-> Добавление позиций")
addedChampionPositionsCount = 0
inputFile = open(positionsInputFileName, encoding='utf-8')
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
            isPositionOk = True
            if "Верхняя" in line:
                position = ChampionPosition.Top
            elif "Лес" in line:
                position = ChampionPosition.Jungle
            elif "Средняя" in line:
                position = ChampionPosition.Mid
            elif "Bottom" in line:
                position = ChampionPosition.Bottom
            elif "Поддержка" in line:
                position = ChampionPosition.Support
            else:
                print("Что-то не так с данными о позиции:", currentChampionName, line)
                isPositionOk = False
            
            if isPositionOk:
                for champion in champions:
                    if currentChampionName != champion.localizedName:
                        continue
                    currentChampionName = champion.localizedName
                    addedChampionPositionsCount = addedChampionPositionsCount + champion.addPosition(position)
finally:
    inputFile.close()

#Проверка
if addedChampionPositionsCount == 0:
    print("Что-то не так с вторичными данными")
    exit
else:
    print("Добавлено", addedChampionPositionsCount, "позиций чемпионов")

# Входной файл с позициями и его структура (второй)
positionsInputFileName = "ChampionsInfo/3. championPositions leagueofgraphs.txt"
# Добавление позиций из https://www.leagueofgraphs.com/ru/champions/builds
print("-> Добавление позиций")
addedChampionPositionsCount = 0
inputFile = open(positionsInputFileName, encoding='utf-8')
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
            positions = set()
            if "Топ" in line:
                positions.add(ChampionPosition.Top)
            if "Лес" in line:
                positions.add(ChampionPosition.Jungle)
            if "Мид" in line:
                positions.add(ChampionPosition.Mid)
            if "Бот" in line:
                positions.add(ChampionPosition.Bottom)
            if "Поддержка" in line:
                positions.add(ChampionPosition.Support)
            
            if len(positions) != 0:
                for champion in champions:
                    if currentChampionName != champion.localizedName:
                        continue
                    currentChampionName = champion.localizedName
                    addedChampionPositionsCount = addedChampionPositionsCount + champion.addPositions(positions)
finally:
    inputFile.close()

print("Добавлено", addedChampionPositionsCount, "позиций чемпионов")

#Формирование json
print("-> Формирование json")
outputFileName = "../champions.json"
with open(outputFileName, 'w') as outfile:
    #Конвертация в список словарей
    championsDict = []
    for champion in champions:
        #print(champion.convertToDict())
        championsDict.append(champion.convertToDict())
    #Запись в json
    #indent - количество отступов на уровень / строка вместо отступа
    json.dump(championsDict, outfile, ensure_ascii=False, indent=2)#dict(champions=championsDict)
