if [ -f "./README.md" ]; then
    mkdir 408410120
    cp -r Makefile Grid.cpp Grid.h hw4.cpp hw4 main.cpp README.md ./408410120/.
    tar jcvf 408410120.tar.bz2 408410120
    rm -r 408410120
    echo "Success."
else
    echo "README.md not found."
    exit 1
fi
