if [ ! -f "./antlr-4.9.3-complete.jar" ]; then
    wget https://www.antlr.org/download/antlr-4.9.3-complete.jar
else
    echo "The target file 'antlr-4.9.3-complete.jar' exists."
fi
