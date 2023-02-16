# http://dlib.net/face_landmark_detection.py.html
# https://hardliver.blogspot.com/2017/07/dlib-dlib.html
import dlib
import numpy as np


def label(img: np.ndarray) -> list:
    # Label the key points using dlib.
    detector = dlib.get_frontal_face_detector()
    predictor = dlib.shape_predictor("shape_predictor_68_face_landmarks.dat")
    faces1 = detector(img, 1)
    points = []
    for landmarks, parts in enumerate(faces1):
        points = [[p.x, p.y] for p in predictor(img, parts).parts()]

    # corner point
    points.append([0, 0])
    points.append([img.shape[1] - 1, 0])
    points.append([0, img.shape[0] - 1])
    points.append([img.shape[1] - 1, img.shape[0] - 1])
    return points
