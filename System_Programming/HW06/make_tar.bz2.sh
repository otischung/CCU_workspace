ispdf=0

cp README.md HW06_408410120.md
typora HW06_408410120.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./HW06_408410120.pdf" ]; then
    mkdir HW06_408410120
    cp -r makefile myBusybox.c HW06_408410120.pdf ./HW06_408410120/.
    tar jcvf HW06_408410120.tar.bz2 HW06_408410120
    rm -r HW06_408410120
    rm HW06_408410120.md HW06_408410120.pdf
    echo "Success."
else
    echo "HW06_408410120.pdf not found."
    exit 1
fi

unset ispdf
exit 0