#!/bin/bash

errexit()
{
  echo ""
  echo "$1"
  echo ""
  exit 1
}

fsckerr()
{
  losetup -d "${LOOP}"
  errexit "Filesystem appears corrupted "$1" resize2fs"
}

if [ $(id -u) -ne 0 ]; then
  errexit "$0 must be run as root user"
fi

IMG="$1"

if [ "${IMG}" = "" ]; then
  errexit "Usage: $0 imagefile [Additional MB]"
fi

if [ ! -f "${IMG}" ] || [ ! -s "${IMG}" ]; then
  errexit "${IMG} is missing or empty"
fi

answer="$2"
if [[ ! "${answer}" =~ ^[0-9]+$ ]]; then
  echo ""
  while :
  do
    read -r -e -i "${answer}" -p "Additional MB? " answer
    if [[ "${answer}" =~ ^[0-9]*$ ]]; then
      break
    fi
  done
fi
while [ "${answer:0:1}" = "0" ]; do
  answer="${answer:1}"
done
if [ ${#answer} -eq 0 ]; then
  answer=0
fi
ADDMB=${answer}

echo ""
echo -n "Shrink ${IMG} [Additional MB = ${ADDMB}] (y/n)? "
while read -r -n 1 -s answer; do
  if [[ "${answer}" = [yYnN] ]]; then
    echo "${answer}"
    if [[ "${answer}" = [yY] ]]; then
      break
    else
      errexit "Aborted"
    fi
  fi
done
echo ""

INFO="$(fdisk -lu "${IMG}")"
START="$(grep Linux <<< "${INFO}" | awk '{print $2}')"
SIZE="$(grep Linux <<< "${INFO}" | awk '{print $4}')"
LOOP="$(losetup -f --show -o $((${START} * 512)) --sizelimit $((${SIZE} * 512)) "${IMG}")"
e2fsck -f "${LOOP}"
if [ $? -ne 0 ]; then
  fsckerr "before"
fi
echo ""
resize2fs -M "${LOOP}"
resize2fs -M "${LOOP}"
resize2fs -M "${LOOP}"
e2fsck -f "${LOOP}"
if [ $? -ne 0 ]; then
  fsckerr "after"
fi
INFO="$(tune2fs -l "${LOOP}" 2>/dev/null)"
losetup -d "${LOOP}"
NEWSIZE=$(grep '^Block count:' <<< "${INFO}" | awk '{print $3}')
BLKSIZE=$(grep '^Block size:' <<< "${INFO}" | awk '{print $3}')
NEWEND=$((${START} + (${NEWSIZE} * (${BLKSIZE} / 512)) + ((${ADDMB} * 1024 * 1024) / 512) - 1))
truncate -s $(((${NEWEND} + 1) * 512)) "${IMG}"
fdisk "${IMG}" <<EOF > /dev/null
p
d
2
n
p
2
${START}
${NEWEND}
p
w
EOF
if [ ${ADDMB} -ne 0 ]; then
  echo ""
  INFO="$(fdisk -lu "${IMG}")"
  START="$(grep Linux <<< "${INFO}" | awk '{print $2}')"
  SIZE="$(grep Linux <<< "${INFO}" | awk '{print $4}')"
  LOOP="$(losetup -f --show -o $((${START} * 512)) --sizelimit $((${SIZE} * 512)) "${IMG}")"
  e2fsck -f "${LOOP}"
  if [ $? -ne 0 ]; then
    fsckerr "before"
  fi
  echo ""
  resize2fs "${LOOP}"
  e2fsck -f "${LOOP}"
  if [ $? -ne 0 ]; then
    fsckerr "after"
  fi
  losetup -d "${LOOP}"
fi
echo ""
