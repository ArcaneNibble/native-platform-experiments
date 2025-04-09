#!/bin/sh

echo "[merge] Extracting messages"
find . -name '*.cpp' -o -name '*.h' -o -name '*.c' -o -name '*.qml' | sort > infiles.list

xgettext \
    --files-from=infiles.list \
    --from-code=UTF-8 \
    --width=400 \
    --add-location=file \
    -C -kde -ci18n -ki18n:1 -ki18nc:1c,2 -ki18np:1,2 -ki18ncp:1c,2,3 -ktr2i18n:1 -kI18N_NOOP:1 \
    -kI18N_NOOP2:1c,2  -kN_:1 -kaliasLocale -kki18n:1 -kki18nc:1c,2 -kki18np:1,2 -kki18ncp:1c,2,3 \
    --package-name="kde-dice" \
    -o "template.pot.new" \
    || \
    { echo "[merge] error while calling xgettext. aborting."; exit 1; }

sed -i 's/"Content-Type: text\/plain; charset=CHARSET\\n"/"Content-Type: text\/plain; charset=UTF-8\\n"/' "template.pot.new"
sed -i 's/# SOME DESCRIPTIVE TITLE./'"# Translation of demo dice app in LANGUAGE"'/' "template.pot.new"
sed -i 's/# Copyright (C) YEAR THE PACKAGE'"'"'S COPYRIGHT HOLDER/'"# Copyright (C) $(date +%Y)"'/' "template.pot.new"

# whatever
mv template.pot.new po/template.pot
rm infiles.list
echo "[merge] Done extracting messages"

echo "[merge] Merging messages"
catalogs=`find . -name '*.po' | sort`
for cat in $catalogs; do
    echo "[merge] $cat"
    catLocale=`basename ${cat%.*}`
    msgmerge \
        --width=400 \
        --add-location=file \
        --no-fuzzy-matching \
        -o "$cat.new" \
        "$cat" "po/template.pot"
    sed -i 's/# SOME DESCRIPTIVE TITLE./'"# Translation of demo dice app in ${catLocale}"'/' "$cat.new"
    sed -i 's/# Translation of '"demo dice app"' in LANGUAGE/'"# Translation of demo dice app in ${catLocale}"'/' "$cat.new"
    sed -i 's/# Copyright (C) YEAR THE PACKAGE'"'"'S COPYRIGHT HOLDER/'"# Copyright (C) $(date +%Y)"'/' "$cat.new"

    mv "$cat.new" "$cat"
done

echo "[merge] Done merging messages"
