#!/bin/sh
#Ime arhive (bez ekstenzije)
BASE_NAME=NSK19
SRC_DIR=..
TMP_ROOT_DIR=.tmp

echo "Kompajliram ..."
if ! make; then
	echo "Kod se nemoze kompajlirati, prekidam pakiranje ..."
	exit 1
fi

# Stvori pomocni direktorij
rm -rf ${TMP_ROOT_DIR}
mkdir -p ${TMP_ROOT_DIR}/src

# Kopiraj izvorni kod
echo -n "Kopiram izvorni kod ..."
tar cvf ".${BASE_NAME}.tar.tmp" "${SRC_DIR}" --exclude "${SRC_DIR}/Debug" --exclude "${SRC_DIR}/Release" --exclude ".svn" >/dev/null
tar xvf ".${BASE_NAME}.tar.tmp" --directory "${TMP_ROOT_DIR}/src/" >/dev/null
rm -f ".${BASE_NAME}.tar.tmp"
echo "OK"

# Kopiraj izvrsni kod
cp *.exe runall.bat README ${TMP_ROOT_DIR}/


# Prepravi relativni path source direktorija u makefile-u, te makni staticko linkanje
echo -n "Prepravljam makefile ..."
sed 's/\(^SRC_DIR=\).*/\1src/g' makefile > "${TMP_ROOT_DIR}/makefile"
sed -i 's/\(^LINKFLAGS=\).*/\1/' "${TMP_ROOT_DIR}/makefile"
echo "OK"

SRC_ARCHIVE_CONTENTS="src/ makefile README"
ARCHIVE_CONTENTS="src/ makefile README *.exe runall.bat delete-txt.bat"

# Spakiraj u .tar.gz
cd ${TMP_ROOT_DIR}
TAR_GZ_NAME=${BASE_NAME}.tar.gz
SRC_TAR_GZ_NAME=${BASE_NAME}-src.tar.gz
echo -n "Pakiram u ${TAR_GZ_NAME} ..."
rm -f "../${TAR_GZ_NAME}" "../${SRC_TAR_GZ_NAME}"
tar zcvf "../${TAR_GZ_NAME}" ${ARCHIVE_CONTENTS}
tar zcvf "../${SRC_TAR_GZ_NAME}" ${SRC_ARCHIVE_CONTENTS}
echo "Spakirao u ${TAR_GZ_NAME}"

# Spakiraj u .zip
ZIP_NAME=${BASE_NAME}.zip
SRC_ZIP_NAME=${BASE_NAME}-src.zip
echo -n "Pakiram u ${ZIP_NAME} ..."
rm -f "../${ZIP_NAME}" "../${SRC_ZIP_NAME}"
zip -r "../${ZIP_NAME}" ${ARCHIVE_CONTENTS}
zip -r "../${SRC_ZIP_NAME}" ${SRC_ARCHIVE_CONTENTS}
echo "Spakirao u ${ZIP_NAME}"

# izbrisi privremene direktorije
cd ..
rm -rf ${TMP_ROOT_DIR}

