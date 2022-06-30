if [ -f "./README.pdf" ]; then
    mkdir 408410120_proj1_v1
    cp -r gen_mistake_samples.py gen_samples.py params.py PLA.py plot_samples.py pocket_algorithm.py requirements.txt README.pdf ./408410120_proj1_v1/.
    zip -r 408410120_proj1_v1.zip 408410120_proj1_v1
    rm -r 408410120_proj1_v1
    echo "Success."
else
    echo "README.pdf not found."
    exit 1
fi
