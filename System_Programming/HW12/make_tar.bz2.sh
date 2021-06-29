ispdf=0

cp README.md HW12_408410120.md
typora HW12_408410120.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./HW12_408410120.pdf" ]; then
    mkdir HW12_408410120
    cp -r makefile *.c HW12_408410120.pdf ./HW12_408410120/.
    tar jcvf HW12_408410120.tar.bz2 HW12_408410120
    rm -r HW12_408410120
    rm HW12_408410120.md HW12_408410120.pdf
    echo "Success."
else
    echo "HW12_408410120.pdf not found."
    exit 1
fi

unset ispdf
exit 0
