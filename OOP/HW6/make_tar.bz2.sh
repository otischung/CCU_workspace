if [ -f "./README.md" ]; then
    mkdir 408410120
    cp -r GameHandle.cpp GameHandle.h main main.cpp Makefile README.md ./408410120/.
    tar jcvf 408410120.tar.bz2 408410120
    rm -r 408410120
    echo "Success."
else
    echo "README.md not found."
    exit 1
fi
