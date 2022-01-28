ispdf=0

cp README.md hw6.md
typora hw6.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./hw6.pdf" ]; then
    mkdir 408410120
    cp -r Makefile waitTemp.c hw6.pdf ./408410120/.
    tar jcvf 408410120.tar.bz2 408410120
    rm -rf 408410120
    rm -f hw6.md hw6.pdf
    echo "Success."
else
    echo "hw6.pdf not found."
	rm -f hw6.md
    exit 1
fi

unset ispdf
exit 0
