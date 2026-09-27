#include "include/global/CountryHelper.hpp"

#include "include/database/entities/Profile.h"

QString CountryNameToCode(const QString& countryName) {
    return CountryMap.value(countryName, "");
}

QString CountryCodeToFlag(const QString& countryCode) {
    QVector<uint> ucs4 = countryCode.toUcs4();
    for (uint& code : ucs4) {
        code += 0x1F1A5;
    }
    return QString::fromUcs4(ucs4.data(), countryCode.length());
}

QString countryCodeFromFlag(const QString& text) {
    constexpr uint regionalIndicatorA = 0x1F1E6;
    constexpr uint regionalIndicatorZ = 0x1F1FF;

    const QVector<uint> codePoints = text.toUcs4();
    for (qsizetype i = 0; i + 1 < codePoints.size(); ++i) {
        const uint first = codePoints.at(i);
        const uint second = codePoints.at(i + 1);
        if (first < regionalIndicatorA || first > regionalIndicatorZ ||
            second < regionalIndicatorA || second > regionalIndicatorZ) {
            continue;
        }

        QString countryCode;
        countryCode.append(QChar(u'A' + first - regionalIndicatorA));
        countryCode.append(QChar(u'A' + second - regionalIndicatorA));

        if (CountryMap.values().contains(countryCode)) {
            return countryCode;
        }
    }

    return {};
}

QString effectiveCountryCode(const Configs::Profile& profile) {
    const QString testedCountryCode = profile.test_country.trimmed().toUpper();
    if (CountryMap.values().contains(testedCountryCode)) {
        return testedCountryCode;
    }

    const QString profileName = profile.outbound
        ? profile.outbound->name
        : profile.name;
    return countryCodeFromFlag(profileName);
}
