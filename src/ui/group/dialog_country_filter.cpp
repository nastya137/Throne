#include "include/ui/group/dialog_country_filter.h"
#include "include/global/CountryHelper.hpp"

DialogCountryFilter::DialogCountryFilter(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::DialogCountryFilter)
{
    ui->setupUi(this);
    loadCountries();

    connect(
        ui->find_country,
        &QLineEdit::textChanged,
        this,
        &DialogCountryFilter::filterCountries
    );

    connect(
        ui->select_all,
        &QPushButton::clicked,
        this,
        &DialogCountryFilter::selectAll
    );


    connect(
            ui->deselect_all,
            &QPushButton::clicked,
            this,
            &DialogCountryFilter::deselectAll
    );

    connect(
        ui->ok_button,
        &QPushButton::clicked,
        this,
        &QDialog::accept
    );
}

DialogCountryFilter::~DialogCountryFilter()
{
    delete ui;
}

void DialogCountryFilter::loadCountries()
{
    for(auto it = CountryMap.begin();
        it != CountryMap.end();
        ++it)
    {
        QString countryName = it.key();
        QString countryCode = it.value();

        auto *box = new QCheckBox(countryName, this);

        box->setProperty(
            "countryCode",
            countryCode
        );

        ui->countries_layout->addWidget(box);

        countryBoxes.append(box);
        countryChecks[countryName] = box;
    }
}

void DialogCountryFilter::filterCountries(
        const QString& text)
{
    for(auto box : countryBoxes)
    {
        bool visible =
            box->text()
            .contains(
                text,
                Qt::CaseInsensitive
            );

        box->setVisible(visible);
    }
}

void DialogCountryFilter::selectAll()
{
    for(auto box : countryBoxes)
        box->setChecked(true);
}

void DialogCountryFilter::deselectAll()
{
    for(auto box : countryBoxes)
        box->setChecked(false);
}

QStringList DialogCountryFilter::selectedCountries() const
{
    QStringList result;

    for (auto it = countryChecks.begin();
         it != countryChecks.end();
         ++it)
    {
        if (it.value()->isChecked())
        {
            result.append(it.key());
        }
    }

    return result;
}