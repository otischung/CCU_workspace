ispdf=0

typora README.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./README.pdf" ]; then
    mkdir 408410120
    cp -r makefile lazybox.c README.pdf ./408410120/.
    tar jcvf 408410120.tar.bz2 408410120
    rm -r 408410120
    rm README.pdf
    echo "Success."
else
    echo "README.pdf not found."
    unset ispdf
    exit 1
fi

unset ispdf
exit 0
