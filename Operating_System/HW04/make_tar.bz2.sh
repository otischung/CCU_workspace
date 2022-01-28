ispdf=0

cp README.md hw4.md
typora hw4.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./hw4.pdf" ]; then
    mkdir 408410120
    cp -r Makefile stdin_read.c hw4.pdf ./408410120/.
    tar jcvf 408410120.tar.bz2 408410120
    rm -rf 408410120
    rm -f hw4.md hw4.pdf
    echo "Success."
else
    echo "hw4.pdf not found."
	rm -f hw4.md
    exit 1
fi

unset ispdf
exit 0
