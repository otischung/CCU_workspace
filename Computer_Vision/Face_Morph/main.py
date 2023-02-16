import os.path

import cv2
import dlib_shape_predictor_downloader
import draw_points_demo
import face_morph
import frame_extration
import glob
import keypoint_label
import shutil
import sys

from bcolors import Bcolors
from tqdm import tqdm

if __name__ == "__main__":
    # Parameters
    filename = {
        "former": "35_409410003_李文翔-00.00.00.000-00.03.06.013.mp4",
        "latter": "408410120-00.00.02.394-00.00.08.688.mp4"
    }
    path = {
        "source": "./Source_Video/",
        "extraction": "./Frame_Extraction/",
        "result": "./Result_Frame/"
    }
    name = {
        0: "A",
        1: "B"
    }
    num_frame = 15

    # Reset Frame Extraction and Result Frame Folders
    if os.path.isdir(path["extraction"]):
        shutil.rmtree(path["extraction"])
    if os.path.isdir(path["result"]):
        shutil.rmtree(path["result"])
    os.mkdir(path["extraction"])
    os.mkdir(path["result"])

    # Download the pre-trained model "shape_predictor_68_face_landmarks.dat"
    ret = dlib_shape_predictor_downloader.download()
    if not ret:
        print(f"{Bcolors.FAIL}Something wrong with downloader.{Bcolors.ENDC}", file=sys.stderr)
        quit(1)

    # Extract frames.
    frame_extration.frameEx(f"{path['source']}{filename['former']}", savedir=path["extraction"], name=name[0], frame=-num_frame)
    frame_extration.frameEx(f"{path['source']}{filename['latter']}", savedir=path["extraction"], name=name[1], frame=num_frame)

    # Create frame lists and dictionary.
    former_frame_list = glob.glob(f"{path['extraction']}{name[0]}*")
    former_frame_list.sort()
    latter_frame_list = glob.glob(f"{path['extraction']}{name[1]}*")
    latter_frame_list.sort()
    frame_list = dict(zip(former_frame_list, latter_frame_list))

    # Compute Morphing Images.
    print("Now we start to morph images.", file=sys.stderr)
    cnt = 0
    for frame in tqdm(frame_list):
        # Label the key points using dlib.
        img1 = cv2.imread(frame)
        img2 = cv2.imread(frame_list[frame])
        points1 = keypoint_label.label(img1)
        points2 = keypoint_label.label(img2)

        face_morph.faceMorph(img1, img2, points1, points2, cnt / num_frame, f"{path['result']}R_{cnt:04d}.jpg")
        cnt += 1
