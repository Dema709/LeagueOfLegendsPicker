# Запуск через py.exe .\correctIconNames.py

# Починка имён картинок, полученных с сайта путём загрузки страниц
# Сайт - https://leagueoflegends.fandom.com/ru/wiki/Список_чемпионов

import os

path = "../Icons/Champions"

for root, dirs, files in os.walk(path):
    for file in files:
        shouldReplace = False
        newName = file
        if " " in file:
            newName = newName.replace(" ", "")
            shouldReplace = True
        if "_" in file:
            newName = newName.replace("_", "")
            shouldReplace = True
        if "%27" in file:
            newName = newName.replace("%27", "")
            shouldReplace = True
        if "(1)" in file:
            newName = newName.replace("(1)", "")
            shouldReplace = True
        if "OriginalSquare" in file:
            newName = newName.replace("OriginalSquare", "Square")
            shouldReplace = True
        
        if shouldReplace:
            oldPath = os.path.join(root,file)
            newPath = os.path.join(root,newName)
            os.rename(oldPath, newPath)