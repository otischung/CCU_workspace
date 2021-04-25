ispdf=0

cp README.md HW02_408410120.md
typora HW02_408410120.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./HW02_408410120.pdf" ]; then
    mkdir HW02_408410120
    cp -r makefile sortperf.c HW02_408410120.pdf ./HW02_408410120/.
    tar jcvf HW02_408410120.tar.bz2 HW02_408410120
    rm -r HW02_408410120
    rm HW02_408410120.md HW02_408410120.pdf
    echo "Success."
else
    echo "HW02_408410120.pdf not found."
    rm HW02_408410120.md
    unset ispdf
    exit 1
fi

unset ispdf
exit 0
