#pragma once

#include <QDialog>
#include <QCheckBox>
#include <QList>
#include "ui_dialog_country_filter.h"
#include <QStringList>

namespace Ui {
class DialogCountryFilter;
}

class DialogCountryFilter : public QDialog {
    Q_OBJECT

public:
    explicit DialogCountryFilter(const QStringList &selectedCodes,
                                 QWidget *parent = nullptr);
    ~DialogCountryFilter();
    QStringList selectedCountries() const;

private:
    Ui::DialogCountryFilter *ui;
    QStringList initialSelectedCodes; // например, {"DE", "FR"}

    QList<QCheckBox*> countryBoxes;

    void loadCountries();
    void filterCountries(const QString& text);

private slots:
    void selectAll();
    void deselectAll();
};
