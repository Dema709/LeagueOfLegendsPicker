#include "PickerWidget.h"

#include <QMessageBox>
#include <QComboBox>
#include <QLabel>
#include <QRadioButton>
#include "JsonCharacterReader.h"

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
    criteriaComboBox->addItem("Тип урона", static_cast<int>(ChampionPicker::ChoiceVariant::DamageType));

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
                connect(positionRadioButtonPair.second, &QAbstractButton::toggled, [this, pos](bool checked){
                    if (checked) this->changePosition(pos);
                });
            }

            if (positionRadioButtonMap.count(m_position))
                positionRadioButtonMap[m_position]->setChecked(true);
        }
    }

    //Виджет урона
    {
        QWidget* damageTypeWidget = new QWidget();
        damageTypeWidget->hide();
        userChoiceLayout->addWidget(damageTypeWidget);
        QVBoxLayout* damageTypeLayout = new QVBoxLayout();
        damageTypeWidget->setLayout(damageTypeLayout);
        m_choiceVariantWidgetsMap[ChampionPicker::ChoiceVariant::DamageType] = damageTypeWidget;
        {
            QLabel* label = new QLabel("еуеу");
            label->setPixmap(QPixmap("Icons/Positions/Top_icon.png"));
            damageTypeLayout->addWidget(label);
        }
    }

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
}

void PickerWidget::changeChoiceVariant(ChampionPicker::ChoiceVariant choiceVariant)
{
    m_choiceVariant = choiceVariant;
    for (auto choiceVariantWidgetPair : m_choiceVariantWidgetsMap)
    {
        if (!choiceVariantWidgetPair.second)
            continue;
        if (choiceVariantWidgetPair.first == m_choiceVariant)
            choiceVariantWidgetPair.second->show();
        else
            choiceVariantWidgetPair.second->hide();
    }
    pickChampion();
}

void PickerWidget::changePosition(Champion::ChampionPositions position)
{
    m_position = position;
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

        qDebug() << "picked" << pickedChampion.GetLocalizedName();
        changeChosenChampion(pickedChampion);
    }
    else if (m_choiceVariant == ChampionPicker::ChoiceVariant::DamageType)
    {
        qDebug() << "todo pick with DamageType";
    }
}

void PickerWidget::changeChosenChampion(Champion &champion)
{
    //Заготовка под загрузку иконок из ресурсов
    /*
    QString iconPath = QString("Icons/Positions/") + champion.GetIconName();
    qDebug() << "iconPath" << iconPath;
    QPixmap iconPixmap(iconPath);

    emit changeChosenChampionIconName(iconPixmap);
    */
    emit changeChosenChampionLocalizedName(champion.GetLocalizedName());
    emit changeChosenChampionLocalizedTitle(champion.GetLocalizedTitle());
}
