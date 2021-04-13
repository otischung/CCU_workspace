ispdf=0

cp README.md HW07_408410120.md
typora HW07_408410120.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./HW07_408410120.pdf" ]; then
    mkdir HW07_408410120
    cp -r makefile *.c HW07_408410120.pdf ./HW07_408410120/.
    tar jcvf HW07_408410120.tar.bz2 HW07_408410120
    rm -r HW07_408410120
    rm HW07_408410120.md HW07_408410120.pdf
    echo "Success."
else
    echo "HW07_408410120.pdf not found."
    exit 1
fi

unset ispdf
exit 0
