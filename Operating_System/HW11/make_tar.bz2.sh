ispdf=0

cp README.md hw11.md
typora hw11.md &
echo "Please use typora to make pdf file."
read -p "After finish, press enter." ispdf

if [ -f "./hw11.pdf" ]; then
    mkdir 408410120
    cp -r hw11.pdf HW11.xlsx ./408410120/.
    tar jcvf 408410120.tar.bz2 408410120
    rm -rf 408410120
    rm -f hw11.md hw11.pdf
    echo "Success."
else
    echo "hw11.pdf not found."
	rm -f hw11.md
    exit 1
fi

unset ispdf
exit 0
