ispdf=0

cp README.md hw9.md
typora hw9.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./hw9.pdf" ]; then
    mkdir 408410120
    cp -r Makefile fair.c GNU_fair.c hw9.pdf ./408410120/.
    tar jcvf 408410120.tar.bz2 408410120
    rm -rf 408410120
    rm -f hw9.md hw9.pdf
    echo "Success."
else
    echo "hw9.pdf not found."
	rm -f hw9.md
    exit 1
fi

unset ispdf
exit 0
