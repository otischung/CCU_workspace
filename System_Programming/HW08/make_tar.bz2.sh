ispdf=0

cp README.md HW08_408410120.md
typora HW08_408410120.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./HW08_408410120.pdf" ]; then
    mkdir HW08_408410120
    cp -r makefile *.c HW08_408410120.pdf ./HW08_408410120/.
    tar jcvf HW08_408410120.tar.bz2 HW08_408410120
    rm -r HW08_408410120
    rm HW08_408410120.md HW08_408410120.pdf
    echo "Success."
else
    echo "HW08_408410120.pdf not found."
    exit 1
fi

unset ispdf
exit 0
