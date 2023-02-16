clear;
clc;

% Ref: https://www.codingame.com/playgrounds/2358/how-to-plot-the-mandelbrot-set/adding-some-colors
% Ref: https://sciencedemos.org.uk/mandelbrot.php
%% Hyper Parameters
useFixIter = false;
useExpIter = true;

MIN_ITER = 5000;
TERM_ITER = 1e5;
FIX_ITER = 1e4;
FORWARD_FRAME = 13320;
BACKWARD_FRAME = 4050;

% Size of image
% WIDTH = 3840;
% HEIGHT = 2160;
WIDTH = 800;
HEIGHT = 800;
imageHSV = zeros(HEIGHT, WIDTH, 3);

% Plot range
LEFT = -2;
RIGHT = 2;
BOTTOM = -2;
TOP = 2;

% Zoom center
% Select by hand
RE = -1.159292284831;
IM = 0.285367031673;
% Fine tune
% RE = -1.1591748585;
% IM = 0.2854009995;

% Scale factor
SCALE = 0.002 * FORWARD_FRAME;

if useFixIter
    FORWARD_ITER = ones(1, FORWARD_FRAME) * FIX_ITER;
    BACKWARD_ITER = ones(1, BACKWARD_ITER) * FIX_ITER;
elseif useExpIter
    FORWARD_ITER = zeros(1, FORWARD_FRAME);
    parfor i = 1:FORWARD_FRAME
        FORWARD_ITER(1,i) = expIter(i, MIN_ITER, TERM_ITER, FORWARD_FRAME);
    end
    BACKWARD_ITER = zeros(1, BACKWARD_FRAME);
    parfor i = 1:BACKWARD_FRAME
        BACKWARD_ITER(1,i) = expIter(i, MIN_ITER, TERM_ITER, BACKWARD_FRAME);
    end
    BACKWARD_ITER = flip(BACKWARD_ITER);
else  % Linear iteration
    FORWARD_ITER = zeros(1, FORWARD_FRAME);
    step = (TERM_ITER - MIN_ITER) / FORWARD_FRAME;
    parfor i = 1:FORWARD_FRAME
        FORWARD_ITER(1,i) = MIN_ITER + i * step;
    end
    BACKWARD_ITER = zeros(1, BACKWARD_FRAME);
    step = (TERM_ITER - MIN_ITER) / BACKWARD_FRAME;
    parfor i = 1:BACKWARD_FRAME
        BACKWARD_ITER(1,i) = MIN_ITER + i * step;
    end
    BACKWARD_ITER = flip(BACKWARD_ITER);
end

if WIDTH >= HEIGHT
    MINSIZE = HEIGHT;
else
    MINSIZE = WIDTH;
end

% Image folder
folder = "Images";

%% CLEAR FOLDER OR NOT
if exist(fullfile(pwd, folder), "dir")
    prompt = "Warning: " + folder + " exists, do you want to delete it? [y/N]: ";
    yn = input(prompt, "s");
    if isempty(yn)
        yn = "N";
    end
    if yn == "Y" || yn == "y"
        fprintf(2, "Deleting folder " + folder);
        rmdir(folder, "s");
        fprintf(2, "Delete folder " + folder + " complete");
        mkdir(folder);
    end
else
    mkdir(folder);
end

%% Forward Pass
LEFT = LEFT + SCALE * abs(LEFT - RE) / FORWARD_FRAME;
RIGHT = RIGHT - SCALE * abs(RIGHT - RE) / FORWARD_FRAME;
BOTTOM = BOTTOM + SCALE * abs(BOTTOM - IM) / FORWARD_FRAME;
TOP = TOP - SCALE * abs(TOP - IM) / FORWARD_FRAME;
bar = waitbar(0, sprintf("Creating forward frame, 0/%d\nL=%f, R=%f\nB=%f, T=%f, I=%d", FORWARD_FRAME, LEFT, RIGHT, BOTTOM, TOP, FORWARD_ITER(1,1)), ...
    "CreateCancelBtn", "setappdata(gcbf, ""canceling"", true)");
for i = 1:FORWARD_FRAME
    if getappdata(bar, "canceling")
        break;
    end
    ITER = FORWARD_ITER(1,i);
    waitbar(i / FORWARD_FRAME, bar, sprintf("Creating forward frame, %d/%d\nL=%f, R=%f\nB=%f, T=%f, I=%d", i, FORWARD_FRAME, LEFT, RIGHT, BOTTOM, TOP, int32(ITER)));
%     if i > 7281  % ------- ONLY IF YOU WANT TO CREATE PARTICULAR RANGE -------
        for x = 1:WIDTH
            parfor y = 1:HEIGHT
                c = (LEFT + (x / MINSIZE) * (RIGHT - LEFT)) + (BOTTOM + (y / MINSIZE) * (TOP - BOTTOM)) * 1i;
                m = mandelbrot(c, uint32(ITER));
                HUE_SCALE = 0.004 * ITER;
                hue = 0.55 + HUE_SCALE * m / ITER;
%                 hue = 0.55 + 20 * m / ITER;
                while hue > 1
                    hue = hue - 1;
                end
                if m < uint32(ITER)
                    value = 1;
                else
                    value = 0;
                end
                imageHSV(y,x,:) = [hue, 1, value];
            end
        end
        imageRGB = hsv2rgb(imageHSV);
        name = sprintf("A_%d.bmp", i);
        name = fullfile(pwd, folder, name);
        imwrite(imageRGB, name);
%     end  % ------- ONLY IF YOU WANT TO CREATE PARTICULAR RANGE -------

    LEFT = LEFT + SCALE * abs(LEFT - RE) / FORWARD_FRAME;
    RIGHT = RIGHT - SCALE * abs(RIGHT - RE) / FORWARD_FRAME;
    BOTTOM = BOTTOM + SCALE * abs(BOTTOM - IM) / FORWARD_FRAME;
    TOP = TOP - SCALE * abs(TOP - IM) / FORWARD_FRAME;
end
delete(bar);

%% Backward Pass
RE = (LEFT + RIGHT) / 2;
IM = (BOTTOM + TOP) / 2;

bar = waitbar(0, sprintf("Creating backward frame, 0/%d\nL=%f, R=%f\nB=%f, T=%f, I=%d", BACKWARD_FRAME, LEFT, RIGHT, BOTTOM, TOP, BACKWARD_ITER(1,1)), ...
    "CreateCancelBtn", "setappdata(gcbf, ""canceling"", true)");
for i = 1:BACKWARD_FRAME
    if getappdata(bar, "canceling")
        break;
    end
    ITER = BACKWARD_ITER(1,i);
    waitbar(i / BACKWARD_FRAME, bar, sprintf("Creating backward frame, %d/%d\nL=%f, R=%f\nB=%f, T=%f, I=%d", i, BACKWARD_FRAME, LEFT, RIGHT, BOTTOM, TOP, int32(ITER)));
%     if i > 2000  % ------- ONLY IF YOU WANT TO CREATE PARTICULAR RANGE -------
        for x = 1:WIDTH
            parfor y = 1:HEIGHT
                c = (LEFT + (x / MINSIZE) * (RIGHT - LEFT)) + (BOTTOM + (y / MINSIZE) * (TOP - BOTTOM)) * 1i;
                m = mandelbrot(c, uint32(ITER));
                HUE_SCALE = 0.004 * ITER;
                hue = 0.55 + HUE_SCALE * m / ITER;
%                 hue = 0.55 + 20 * m / ITER;
                while hue > 1
                    hue = hue - 1;
                end
                if m < uint32(ITER)
                    value = 1;
                else
                    value = 0;
                end
                imageHSV(y,x,:) = [hue, 1, value];
            end
        end
        imageRGB = hsv2rgb(imageHSV);
        name = sprintf("B_%d.bmp", i);
        name = fullfile(pwd, folder, name);
        imwrite(imageRGB, name);
%     end  % ------- ONLY IF YOU WANT TO CREATE PARTICULAR RANGE -------

    LEFT = LEFT - SCALE * abs(LEFT - RE) / BACKWARD_FRAME;
    RIGHT = RIGHT + SCALE * abs(RIGHT - RE) / BACKWARD_FRAME;
    BOTTOM = BOTTOM - SCALE * abs(BOTTOM - IM) / BACKWARD_FRAME;
    TOP = TOP + SCALE * abs(TOP - IM) / BACKWARD_FRAME;
end
delete(bar);
