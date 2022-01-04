#include "PickerWidget.h"

#include <QMessageBox>
#include <QComboBox>
#include <QLabel>
#include <QRadioButton>
#include <QFileInfo>
#include "JsonCharacterReader.h"

#include <QDebug>

PickerWidget::PickerWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Выбор чемпиона в League of Legends");
    //setAttribute(Qt::WA_DeleteOnClose);

    //Заполнение списка чемпионов
    QString inputFileName = "champions.json";
    if (!JsonCharacterReader::ReadCharactersFromFile(inputFileName, m_championList))
    {
        QMessageBox msgBox(this);
        msgBox.setText("Ошибка!");
        msgBox.setInformativeText("Ошибка открытия или парсинга файла. Подробности в qWarning.");
        msgBox.setIcon(QMessageBox::Icon::Critical);
        msgBox.exec();
    }

    fillLayout();

    pickChampion();
}

void PickerWidget::fillLayout()
{
    QHBoxLayout* mainLayout = new QHBoxLayout();
    this->setLayout(mainLayout);

    QVBoxLayout* userChoiceLayout = new QVBoxLayout();
    mainLayout->addLayout(userChoiceLayout);
    fillUserChoiceLayout(userChoiceLayout);

    QVBoxLayout* chosenChampionLayout = new QVBoxLayout();
    mainLayout->addLayout(chosenChampionLayout);
    fillChosenChampionLayout(chosenChampionLayout);

    m_layoutInitialized = true;
}

void PickerWidget::fillUserChoiceLayout(QVBoxLayout* userChoiceLayout)
{
    QComboBox* criteriaComboBox = new QComboBox();
    userChoiceLayout->addWidget(criteriaComboBox);
    criteriaComboBox->addItem("Линия", static_cast<int>(ChampionPicker::ChoiceVariant::Position));
    criteriaComboBox->addItem("Класс", static_cast<int>(ChampionPicker::ChoiceVariant::ChampionClass));

    connect(criteriaComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [this](int index)
    {
        this->changeChoiceVariant(static_cast<ChampionPicker::ChoiceVariant>(index));
    });

    //Виджет позиций
    {
        QWidget* positionWidget = new QWidget();
        positionWidget->hide();
        userChoiceLayout->addWidget(positionWidget);
        QVBoxLayout* positionLayout = new QVBoxLayout();
        positionWidget->setLayout(positionLayout);
        m_choiceVariantWidgetsMap[ChampionPicker::ChoiceVariant::Position] = positionWidget;
        {
            std::map<Champion::ChampionPositions, QRadioButton*> positionRadioButtonMap;

            QRadioButton* topRadioButton = new QRadioButton("Верхняя");
            positionLayout->addWidget(topRadioButton);
            QRadioButton* jungleRadioButton = new QRadioButton("Лес");
            positionLayout->addWidget(jungleRadioButton);
            QRadioButton* midRadioButton = new QRadioButton("Средняя");
            positionLayout->addWidget(midRadioButton);
            QRadioButton* bottomRadioButton = new QRadioButton("Нижняя");
            positionLayout->addWidget(bottomRadioButton);
            QRadioButton* supportRadioButton = new QRadioButton("Поддержка");
            positionLayout->addWidget(supportRadioButton);
            QRadioButton* anyRadioButton = new QRadioButton("Любая");
            positionLayout->addWidget(anyRadioButton);

            positionRadioButtonMap[Champion::ChampionPositions::Top] = topRadioButton;
            positionRadioButtonMap[Champion::ChampionPositions::Jungle] = jungleRadioButton;
            positionRadioButtonMap[Champion::ChampionPositions::Mid] = midRadioButton;
            positionRadioButtonMap[Champion::ChampionPositions::Bottom] = bottomRadioButton;
            positionRadioButtonMap[Champion::ChampionPositions::Support] = supportRadioButton;
            positionRadioButtonMap[Champion::ChampionPositions::Any] = anyRadioButton;

            for (auto positionRadioButtonPair : positionRadioButtonMap)
            {
                if (!positionRadioButtonPair.second)
                    continue;

                auto pos = positionRadioButtonPair.first;
                connect(positionRadioButtonPair.second, &QAbstractButton::clicked, [this, pos](bool checked){
                    if (checked) this->changePosition(pos);
                });
            }

            if (positionRadioButtonMap.count(m_position) && positionRadioButtonMap[m_position])
                positionRadioButtonMap[m_position]->setChecked(true);
        }
    }

    //Виджет класса
    {
        QWidget* championClassWidget = new QWidget();
        championClassWidget->hide();
        userChoiceLayout->addWidget(championClassWidget);
        QVBoxLayout* championClassLayout = new QVBoxLayout();
        championClassWidget->setLayout(championClassLayout);
        m_choiceVariantWidgetsMap[ChampionPicker::ChoiceVariant::ChampionClass] = championClassWidget;
        {
            std::map<Champion::ChampionClass, QRadioButton*> championClassRadioButtonMap;

            QRadioButton* mageRadioButton = new QRadioButton("Маг");
            championClassLayout->addWidget(mageRadioButton);
            QRadioButton* assassinRadioButton = new QRadioButton("Убийца");
            championClassLayout->addWidget(assassinRadioButton);
            QRadioButton* marksmanRadioButton = new QRadioButton("Стрелок");
            championClassLayout->addWidget(marksmanRadioButton);
            QRadioButton* tankRadioButton = new QRadioButton("Танк");
            championClassLayout->addWidget(tankRadioButton);
            QRadioButton* fighterRadioButton = new QRadioButton("Воин");
            championClassLayout->addWidget(fighterRadioButton);
            QRadioButton* supportRadioButton = new QRadioButton("Поддержка");
            championClassLayout->addWidget(supportRadioButton);
            QRadioButton* anyRadioButton = new QRadioButton("Любой");
            championClassLayout->addWidget(anyRadioButton);

            championClassRadioButtonMap[Champion::ChampionClass::Mage] = mageRadioButton;
            championClassRadioButtonMap[Champion::ChampionClass::Assassin] = assassinRadioButton;
            championClassRadioButtonMap[Champion::ChampionClass::Marksman] = marksmanRadioButton;
            championClassRadioButtonMap[Champion::ChampionClass::Tank] = tankRadioButton;
            championClassRadioButtonMap[Champion::ChampionClass::Fighter] = fighterRadioButton;
            championClassRadioButtonMap[Champion::ChampionClass::Support] = supportRadioButton;
            championClassRadioButtonMap[Champion::ChampionClass::Any] = anyRadioButton;

            for (auto championClassRadioButtonPair : championClassRadioButtonMap)
            {
                if (!championClassRadioButtonPair.second)
                    continue;

                auto cl = championClassRadioButtonPair.first;
                connect(championClassRadioButtonPair.second, &QAbstractButton::clicked, [this, cl](bool checked){
                    if (checked) this->changeChampionClass(cl);
                });
            }

            if (championClassRadioButtonMap.count(m_championClass) && championClassRadioButtonMap[m_championClass])
                championClassRadioButtonMap[m_championClass]->setChecked(true);
        }
    }

    userChoiceLayout->addStretch(1);

    changeChoiceVariant(m_choiceVariant);
}

void PickerWidget::fillChosenChampionLayout(QVBoxLayout* chosenChampionLayout)
{
    QLabel* iconLabel = new QLabel();
    chosenChampionLayout->addWidget(iconLabel);
    connect(this, &PickerWidget::changeChosenChampionIconName, [iconLabel](const QPixmap& iconPixmap){
        iconLabel->setPixmap(iconPixmap);
    });

    QLabel* localizedNameLabel = new QLabel();
    chosenChampionLayout->addWidget(localizedNameLabel);
    connect(this, &PickerWidget::changeChosenChampionLocalizedName, [localizedNameLabel](const QString& localizedName){
        localizedNameLabel->setText(localizedName);
    });

    QLabel* localizedTitleLabel = new QLabel();
    chosenChampionLayout->addWidget(localizedTitleLabel);
    connect(this, &PickerWidget::changeChosenChampionLocalizedTitle, [localizedTitleLabel](const QString& localizedTitle){
        localizedTitleLabel->setText(localizedTitle);
    });

    chosenChampionLayout->addStretch(1);
}

void PickerWidget::changeChoiceVariant(ChampionPicker::ChoiceVariant choiceVariant)
{
    m_choiceVariant = choiceVariant;
    //Спрятать всё
    for (auto choiceVariantWidgetPair : m_choiceVariantWidgetsMap)
    {
        if (!choiceVariantWidgetPair.second)
            continue;
        choiceVariantWidgetPair.second->hide();
    }
    //Показать выбранное
    if (m_choiceVariantWidgetsMap.count(m_choiceVariant) && m_choiceVariantWidgetsMap[m_choiceVariant])
        m_choiceVariantWidgetsMap[m_choiceVariant]->show();
    pickChampion();
}

void PickerWidget::changePosition(Champion::ChampionPositions position)
{
    m_position = position;
    pickChampion();
}

void PickerWidget::changeChampionClass(Champion::ChampionClass championClass)
{
    m_championClass = championClass;
    pickChampion();
}

void PickerWidget::pickChampion()
{
    if (!m_layoutInitialized)
        return;

    if (m_choiceVariant == ChampionPicker::ChoiceVariant::Position)
    {
        Champion pickedChampion;
        if (!ChampionPicker::GetChampionByPosition(m_position, m_championList, pickedChampion))
        {
            QMessageBox msgBox(this);
            msgBox.setText("Ошибка!");
            msgBox.setInformativeText("Ошибка выбора чемпиона. Подробности в qWarning.");
            msgBox.setIcon(QMessageBox::Icon::Critical);
            msgBox.exec();
            return;
        }

        //qDebug() << "picked" << pickedChampion.GetLocalizedName();
        changeChosenChampion(pickedChampion);
    }
    else if (m_choiceVariant == ChampionPicker::ChoiceVariant::ChampionClass)
    {
        Champion pickedChampion;
        if (!ChampionPicker::GetChampionByChampionClass(m_championClass, m_championList, pickedChampion))
        {
            QMessageBox msgBox(this);
            msgBox.setText("Ошибка!");
            msgBox.setInformativeText("Ошибка выбора чемпиона. Подробности в qWarning.");
            msgBox.setIcon(QMessageBox::Icon::Critical);
            msgBox.exec();
            return;
        }

        //qDebug() << "picked" << pickedChampion.GetLocalizedName();
        changeChosenChampion(pickedChampion);
    }
}

void PickerWidget::changeChosenChampion(Champion &champion)
{
    //Загрузка иконки
    bool iconFound = false;
    auto iconName = champion.GetIconName();
    QString iconsDir = "Icons/Champions/";
    QString iconPath = iconsDir + iconName;

    //Проверка файла на существование
    {
        QFileInfo iconFile(iconPath);
        if (iconFile.exists() && iconFile.isFile())
            iconFound = true;
    }


    if (iconFound)
    {
        QPixmap iconPixmap(iconPath);
        emit changeChosenChampionIconName(iconPixmap);
    }
    else
    {
        qDebug() << iconPath;
    }
    emit changeChosenChampionLocalizedName(champion.GetLocalizedName());
    emit changeChosenChampionLocalizedTitle(champion.GetLocalizedTitle());
}
