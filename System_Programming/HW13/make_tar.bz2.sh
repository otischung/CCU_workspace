ispdf=0

cp README.md HW13_408410120.md
typora HW13_408410120.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./HW13_408410120.pdf" ]; then
    mkdir HW13_408410120
    cp -r makefile *.c HW13_408410120.pdf ./HW13_408410120/.
    tar jcvf HW13_408410120.tar.bz2 HW13_408410120
    rm -r HW13_408410120
    rm HW13_408410120.md HW13_408410120.pdf
    echo "Success."
else
    echo "HW13_408410120.pdf not found."
    exit 1
fi

unset ispdf
exit 0
