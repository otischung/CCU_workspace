ispdf=0

cp README.md hw3.md
typora hw3.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./hw3.pdf" ]; then
    mkdir 408410120
    cp -r Makefile rdtsc.c hw3.pdf ./408410120/.
    tar jcvf 408410120.tar.bz2 408410120
    rm -rf 408410120
    rm -f hw3.md hw3.pdf
    echo "Success."
else
    echo "hw3.pdf not found."
	rm -f hw3.md
    exit 1
fi

unset ispdf
exit 0
