ispdf=0

cp README.md hw5.md
typora hw5.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./hw5.pdf" ]; then
    mkdir 408410120
    cp -r Makefile pi.c hw5.pdf ./408410120/.
    tar jcvf 408410120.tar.bz2 408410120
    rm -rf 408410120
    rm -f hw5.md hw5.pdf
    echo "Success."
else
    echo "hw5.pdf not found."
	rm -f hw5.md
    exit 1
fi

unset ispdf
exit 0
