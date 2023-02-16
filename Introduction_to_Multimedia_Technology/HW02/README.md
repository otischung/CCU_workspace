**Introduction to Multimedia Technology HW02 \-  CSIE 4B 408410120  鍾博丞**

---

Environment required

Parallel Computing Toolbox - `parfor()`

*This MarkDown file is edited by Typora*

# Mandelbrot Set

We set the iteration to be exponential growing starting from 5000 to 100K.

We set the saturation to 1 (maximum value).

We set the value to 0 (totally black) if this point can do the same iteration as we set. Otherwise, we set the value to 1 (it will have color).

The hue starts from 200 degrees (blue) and changes by the maximum iteration of this point divided by the maximum total iteration.

Then, we have the HSV value of a point. Repeat all points (pixels) of 800 \* 800 matrix (image) and we will get an image (frame).

# Video Information

Because of the copyright of the music, we upload this video to our Google drive instead of YouTube.

- Link: https://drive.google.com/file/d/1Angr2wLb_Fwjg2zTx6KFDeu3q8XSWj0U/view?usp=share_link
- Created images link: https://drive.google.com/file/d/1Xi9a4pQG0Tf0CIlhunDy6VW87hKeCGdW/view?usp=share_link
  - 31GB
  - Compression ratio: 33%
- 30 fps, 10 min. 29 sec.
- Music: Blue Water
  - Artist: 広橋真紀子 Makiko Hirohashi
  - Album: Water - 水
- The video starts after 30 seconds, which is the start of the music.

## Forward pass (zoom in)

- 13320 frames.
- Center = -1.159292284831 + 0.285367031673*i*.

## Backward pass (zoom out)

- 4050 frames.

# Discussion

Hue adjusting and iteration determination are the hardest part of this project.

