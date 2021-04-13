ispdf=0

cp README.md HW10_408410120.md
typora HW10_408410120.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./HW10_408410120.pdf" ]; then
    mkdir HW10_408410120
    cp -r makefile *.c HW10_408410120.pdf ./HW10_408410120/.
    tar jcvf HW10_408410120.tar.bz2 HW10_408410120
    rm -r HW10_408410120
    rm HW10_408410120.md HW10_408410120.pdf
    echo "Success."
else
    echo "HW10_408410120.pdf not found."
    exit 1
fi

unset ispdf
exit 0
