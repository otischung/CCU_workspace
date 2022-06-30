if [ -f "./README.pdf" ]; then
    mkdir 408410120_proj2_v1
    cp -r img bcolors.py dataloader.py Download_Dataset.sh hyperparameters.py image_show.py import_package.py main.py model.py requirements.txt train_model.py visualize_model.py README.pdf ./408410120_proj2_v1/.
    zip -r 408410120_proj2_v1.zip 408410120_proj2_v1
    rm -r 408410120_proj2_v1
    echo "Success."
else
    echo "README.pdf not found."
    exit 1
fi
