#pragma once

#include <QDialog>
#include <QCheckBox>
#include <QList>
#include "ui_dialog_country_filter.h"

namespace Ui {
class DialogCountryFilter;
}

class DialogCountryFilter : public QDialog {
    Q_OBJECT

public:
    explicit DialogCountryFilter(QWidget *parent = nullptr);
    ~DialogCountryFilter();
    QStringList selectedCountries() const;

private:
    Ui::DialogCountryFilter *ui;

    QList<QCheckBox*> countryBoxes;
    QMap<QString, QCheckBox*> countryChecks;

    void loadCountries();
    void filterCountries(const QString& text);  

    
private slots:

    void selectAll();
    void deselectAll();
};