if [ -d "./ans.txt" ]; then
	rm ans.txt
fi
if [ -d "./test" ]; then
	rm test
fi
iverilog -o test A19760319.v test_brench.v
vvp test | cat > ans.txt
cat ans.txt
