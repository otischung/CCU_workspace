if [ -f "./README.md" ]; then
    mkdir 408410120
    cp -r partA partB README.md ./408410120/.
    tar jcvf 408410120.tar.bz2 408410120
    rm -r 408410120
    echo "Success."
else
    echo "README.md not found."
    exit 1
fi
