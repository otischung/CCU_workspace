ispdf=0

cp README.md HW09_408410120.md
typora HW09_408410120.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./HW09_408410120.pdf" ]; then
    mkdir HW09_408410120
    cp -r makefile *.c HW09_408410120.pdf ./HW09_408410120/.
    tar jcvf HW09_408410120.tar.bz2 HW09_408410120
    rm -r HW09_408410120
    rm HW09_408410120.md HW09_408410120.pdf
    echo "Success."
else
    echo "HW09_408410120.pdf not found."
    exit 1
fi

unset ispdf
exit 0
