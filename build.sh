#!/bin/sh

BUILD_DIR="build"

[ ! -d "$BUILD_DIR" ] && mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake .. -DCMAKE_BUILD_TYPE=DEBUG

if [ $? -eq 0 ]; then
	make
	if [ $? -eq 0 ]; then

		if [ "$1" = "run" ]; then
			EFILE=$(find . -maxdepth 1 -type f -executable | head -n 1)
			if [ -n "$EFILE" ]; then
				./"$EFILE"

			else
				echo "=== EXECUTABLE FILE NOT FOUND ==="
			
			fi

		fi

	else
		echo "=== ERRORS FOUND IN YOUR PROJECT ==="

	fi

else
	echo "=== CMAKE BUILD FAILED ==="

fi
