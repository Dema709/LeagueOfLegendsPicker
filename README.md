# Общая информация
Программа предназначена для помощи в выборе чемпиона League of Legends по определённым критериям.
Поддерживаемые критерии:
- предпочитаемая линия

# Сборка
1. Сформировать текстовые файлы исходных данных по чемпионам в папке PythonScripts\ChampionsInfo:
- основной файл "1. champions leagueoflegendsfandom.txt"
Для этого открыть сайт https://leagueoflegends.fandom.com/ru/wiki/Список_чемпионов и скопировать таблицу в txt файл.
- дополнительный файл с данными о линиях "2. championPositions ruopgg.txt"
Для этого открыть сайт https://ru.op.gg/champion/statistics и скопировать таблицу в txt файл.
- дополнительный файл с данными о линиях "3. championPositions leagueofgraphs.txt"
Для этого открыть сайт https://www.leagueofgraphs.com/ru/champions/builds и скопировать таблицу в txt файл.
- дополнительный файл с данными о линиях и классах "4. championPositions app.mobalytics.txt"
Для этого открыть сайт https://app.mobalytics.gg/ru_ru/lol/champions и скопировать таблицу в txt файл.
2. С помощью python скрипта generateJson.py сгенерировать файл champions.json.
3. Загрузить иконки чемпионов и линий (с помощью сохранения сайта https://leagueoflegends.fandom.com/ru/wiki/Список_чемпионов как html в браузере) и копировать их в папки Icons\Champions и Icons\Positions соответственно.
4. Запустить скрипт correctIconNames.py для формирования корректных наименований иконок.
5. Собрать проект в Qt.
6. Скопировать в папку с собранным проектом:
- информацию о чемпионах - champions.json
- иконки чемпионов и линий - папка Icons