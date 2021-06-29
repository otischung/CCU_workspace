ispdf=0

cp README.md HW11_408410120.md
typora HW11_408410120.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./HW11_408410120.pdf" ]; then
    mkdir HW11_408410120
    cp -r makefile *.c HW11_408410120.pdf ./HW11_408410120/.
    tar jcvf HW11_408410120.tar.bz2 HW11_408410120
    rm -r HW11_408410120
    rm HW11_408410120.md HW11_408410120.pdf
    echo "Success."
else
    echo "HW11_408410120.pdf not found."
    exit 1
fi

unset ispdf
exit 0
