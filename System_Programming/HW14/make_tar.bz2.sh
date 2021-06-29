ispdf=0

cp README.md HW14_408410120.md
typora HW14_408410120.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./HW14_408410120.pdf" ]; then
    mkdir HW14_408410120
    cp -r makefile pi.c mypi.c HW14_408410120.pdf ./HW14_408410120/.
    tar jcvf HW14_408410120.tar.bz2 HW14_408410120
    rm -rf HW14_408410120
    rm -f HW14_408410120.md HW14_408410120.pdf
    echo "Success."
else
    echo "HW14_408410120.pdf not found."
	rm -f HW14_408410120.md
    exit 1
fi

unset ispdf
exit 0
