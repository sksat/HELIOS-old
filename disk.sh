EDIMG="tolset/z_tools/edimg"

add() {
	${EDIMG} imgin:${DISK} copy from:${FILE} to:@: imgout:${DISK}
}

create() {
	if [ ${TYPE} = "fd" ]; then
		dd if=/dev/zero of=${DISK} bs=1k count=1440
	fi
	if [ ${TYPE} = "cd" ]; then
		dd if=/dev/zero of=${DISK} bs=1M count=512
	fi
	mkdosfs ${DISK}
}

addmbr() {
	${EDIMG} imgin:${DISK} wbinimg src:${FILE} len:512 from:0 to:0 imgout:${DISK}
}

DISK=$1

if [ $2 = "add" ]; then
	FILE=$3
	add
fi

if [ $2 = "create" ]; then
	TYPE=$3
	create
fi

if [ $2 = "addmbr" ]; then
	FILE=$3
	addmbr
fi

