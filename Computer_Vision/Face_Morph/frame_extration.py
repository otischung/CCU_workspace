import cv2
import sys


def frameEx(src: str, savedir: str, name: str, frame: int):
    print(f"Extracting {src}.", file=sys.stderr)
    reverse = False
    video = cv2.VideoCapture(src)
    tot_frame = int(video.get(cv2.CAP_PROP_FRAME_COUNT))
    # fps = video.get(cv2.CAP_PROP_FPS)
    frame_cnt = 0
    output_cnt = 0
    if frame < 0:
        frame = tot_frame + frame + 1
        reverse = True

    success, image = video.read()
    while success:
        frame_cnt += 1
        if not reverse:
            if frame_cnt <= frame:
                cv2.imwrite(f"{savedir}/{name}_{output_cnt:04d}.jpg", image)
                output_cnt += 1
                success, image = video.read()
            else:
                break
        else:
            if frame_cnt >= frame:
                cv2.imwrite(f"{savedir}/{name}_{output_cnt:04d}.jpg", image)
                output_cnt += 1
                success, image = video.read()
            else:
                success, image = video.read()
                continue
