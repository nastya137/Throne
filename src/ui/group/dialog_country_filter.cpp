#include "include/ui/group/dialog_country_filter.h"
#include "include/global/CountryHelper.hpp"

#include <QCollator>

#include <algorithm>

DialogCountryFilter::DialogCountryFilter(const QStringList &selectedCodes,
                                         QWidget *parent)
    : QDialog(parent),
      ui(new Ui::DialogCountryFilter),
      initialSelectedCodes(selectedCodes)
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
    QList<QPair<QString, QString>> countries;
    countries.reserve(CountryMap.size());
    for (auto it = CountryMap.cbegin(); it != CountryMap.cend(); ++it) {
        countries.append({CountryCodeToName(it.value()), it.value()});
    }

    QCollator collator;
    collator.setCaseSensitivity(Qt::CaseInsensitive);
    std::sort(countries.begin(), countries.end(), [&collator](const auto& left, const auto& right) {
        return collator.compare(left.first, right.first) < 0;
    });

    for (const auto& [countryName, countryCode] : countries) {

        auto *box = new QCheckBox(countryName, this);

        box->setProperty(
            "countryCode",
            countryCode
        );

        box->setChecked(
            initialSelectedCodes.contains(countryCode, Qt::CaseInsensitive)
        );

        ui->countries_layout->addWidget(box);

        countryBoxes.append(box);
    }
}

void DialogCountryFilter::filterCountries(
        const QString& text)
{
    for(auto box : countryBoxes)
    {
        const bool visible =
            box->text().contains(text, Qt::CaseInsensitive) ||
            box->property("countryCode").toString().contains(
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

    for (auto box : countryBoxes)
    {
        if (box->isChecked()) {
            result.append(box->property("countryCode").toString());
        }
    }

    return result;
}
