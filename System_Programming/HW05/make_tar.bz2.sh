ispdf=0

cp README.md HW05_408410120.md
typora HW05_408410120.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./HW05_408410120.pdf" ]; then
    mkdir HW05_408410120
    cp -r preBirthday.c makefile HW05_408410120.pdf ./HW05_408410120/.
    tar jcvf HW05_408410120.tar.bz2 HW05_408410120
    rm -r HW05_408410120
    rm HW05_408410120.md HW05_408410120.pdf
    echo "Success."
else
    echo "HW05_408410120.pdf not found."
    unset ispdf
    exit 1
fi

unset ispdf
exit 0