import os


def download() -> bool:
    if not os.path.isfile("./shape_predictor_68_face_landmarks.dat"):
        bz2_filename = "shape_predictor_68_face_landmarks.dat.bz2"
        ret = os.system("wget http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2")
        if ret != 0:
            return False
        # wget.download("http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2", out=bz2_filename)
        ret = os.system(f"bzip2 -dk {bz2_filename}")
        if ret != 0:
            return False
        # with bz2.open(bz2_filename, mode="rb") as f_in:
        #     data = bz2.decompress(f_in.read())
        #     with open(data_filename, "wb") as f_out:
        #         f_out.write(data)
        os.remove(bz2_filename)
    return True
