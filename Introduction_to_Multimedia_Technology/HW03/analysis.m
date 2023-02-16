clear;
clc;

audio_folder = ".\Records\";
img_folder = ".\Img\";
speak_voice = "語聲_PCM_signed_32bit_96kHz.wav";
laugh_voice = "大笑_PCM_signed_32bit_96kHz.wav";
scream_voice = "尖叫_PCM_signed_32bit_96kHz.wav";
my_song = "我們的愛_PCM_signed_32bit_96kHz.wav";
male_song = "409410047_呂耀承.wav";
female_song = "408125029_王禮芳_唱歌.wav";
music = "936Hz - Clear Your Mind   Healing Tone - Boost Positive Energy - Third Eye Activation   Solfeggio.mp3";
plot_resolution = 600;

%% Read the WAV file into a matrix
fprintf("Reading speak voice.\n");
[speak_voice_data,  speak_voice_sampleRate]  = audioread(fullfile(audio_folder, speak_voice));
fprintf("Reading laugh voice.\n");
[laugh_voice_data,  laugh_voice_sampleRate]  = audioread(fullfile(audio_folder, laugh_voice));
fprintf("Reading scream voice.\n");
[scream_voice_data, scream_voice_sampleRate] = audioread(fullfile(audio_folder, scream_voice));
fprintf("Reading my song.\n");
[my_song_data,      my_song_sampleRate]      = audioread(fullfile(audio_folder, my_song));
fprintf("Reading male song.\n");
[male_song_data,    male_song_sampleRate]    = audioread(fullfile(audio_folder, male_song));
fprintf("Reading female song.\n");
[female_song_data,  female_song_sampleRate]  = audioread(fullfile(audio_folder, female_song));
fprintf("Reading music.\n");
[music_data,  music_sampleRate]  = audioread(fullfile(audio_folder, music));
fprintf("----- Reading Complete -----\n\n");
% Play the audio data
% sound(audioData, sampleRate);

%% Generate a time-domain plot of the audio data
fprintf("Generating Time Domain Plot of Speak voice.\n");
f = figure("Visible", "off");
plot(speak_voice_data);
title("Time Domain Plot of Speak voice");
exportgraphics(f, fullfile(img_folder, "Time_Domain_Plot_speak_voice.png"), "Resolution", plot_resolution);
close(f);

fprintf("Generating Time Domain Plot of Laugh voice.\n");
f = figure("Visible", "off");
plot(laugh_voice_data);
title("Time Domain Plot of Laugh voice");
exportgraphics(f, fullfile(img_folder, "Time_Domain_Plot_laugh_voice.png"), "Resolution", plot_resolution);
close(f);

fprintf("Generating Time Domain Plot of Scream Voice.\n");
f = figure("Visible", "off");
plot(scream_voice_data);
title("Time Domain Plot of Scream Voice");
exportgraphics(f, fullfile(img_folder, "Time_Domain_Plot_scream_voice.png"), "Resolution", plot_resolution);
close(f);

fprintf("Generating Time Domain Plot of My Song.\n");
f = figure("Visible", "off");
plot(my_song_data);
title("Time Domain Plot of My Song");
exportgraphics(f, fullfile(img_folder, "Time_Domain_Plot_my_song.png"), "Resolution", plot_resolution);
close(f);

fprintf("Generating Time Domain Plot of Male Song.\n");
f = figure("Visible", "off");
plot(male_song_data);
title("Time Domain Plot of Male Song");
exportgraphics(f, fullfile(img_folder, "Time_Domain_Plot_male_song.png"), "Resolution", plot_resolution);
close(f);

fprintf("Generating Time Domain Plot of Female Song.\n");
f = figure("Visible", "off");
plot(female_song_data);
title("Time Domain Plot of Female Song");
exportgraphics(f, fullfile(img_folder, "Time_Domain_Plot_female_song.png"), "Resolution", plot_resolution);
close(f);
fprintf("----- Generating Complete -----\n\n");

%% Generate a spectrogram of the audio data
fprintf("Generating Spectrogram of Speak Voice.\n");
Nx = length(speak_voice_data(:,1));
nsc = floor(Nx / 100);  % Divide the signal into sections of length nsc
nov = floor(nsc / 2); % Specify 50% overlap between contiguous sections.
nff = max(256, 2 ^ nextpow2(nsc));  % Use nff points to compute FFT.
f = figure("Visible", "off");
spectrogram(speak_voice_data(:,1), hamming(nsc), nov, nff, speak_voice_sampleRate);
title("Spectrogram of Speak Voice");
exportgraphics(f, fullfile(img_folder, "Spectrogram_speak_voice.png"), "Resolution", plot_resolution);
close(f);

fprintf("Generating Spectrogram of Laugh Voice.\n");
Nx = length(laugh_voice_data(:,1));
nsc = floor(Nx / 100);  % Divide the signal into sections of length nsc
nov = floor(nsc / 2); % Specify 50% overlap between contiguous sections.
nff = max(256, 2 ^ nextpow2(nsc));  % Use nff points to compute FFT.
f = figure("Visible", "off");
spectrogram(laugh_voice_data(:,1), hamming(nsc), nov, nff, laugh_voice_sampleRate);
title("Spectrogram of Laugh Voice");
exportgraphics(f, fullfile(img_folder, "Spectrogram_laugh_voice.png"), "Resolution", plot_resolution);
close(f);

fprintf("Generating Spectrogram of Scream Voice.\n");
Nx = length(scream_voice_data(:,1));
nsc = floor(Nx / 100);  % Divide the signal into sections of length nsc
nov = floor(nsc / 2); % Specify 50% overlap between contiguous sections.
nff = max(256, 2 ^ nextpow2(nsc));  % Use nff points to compute FFT.
f = figure("Visible", "off");
spectrogram(scream_voice_data(:,1), hamming(nsc), nov, nff, scream_voice_sampleRate);
title("Spectrogram of Scream Voice");
exportgraphics(f, fullfile(img_folder, "Spectrogram_scream_voice.png"), "Resolution", plot_resolution);
close(f);

fprintf("Generating Spectrogram of My Song.\n");
Nx = length(my_song_data(:,1));
nsc = floor(Nx / 100);  % Divide the signal into sections of length nsc
nov = floor(nsc / 2); % Specify 50% overlap between contiguous sections.
nff = max(256, 2 ^ nextpow2(nsc));  % Use nff points to compute FFT.
f = figure("Visible", "off");
spectrogram(my_song_data(:,1), hamming(nsc), nov, nff, my_song_sampleRate);
title("Spectrogram of My Song");
exportgraphics(f, fullfile(img_folder, "Spectrogram_my_song.png"), "Resolution", plot_resolution);
close(f);

fprintf("Generating Spectrogram of Male Song.\n");
Nx = length(male_song_data(:,1));
nsc = floor(Nx / 100);  % Divide the signal into sections of length nsc
nov = floor(nsc / 2); % Specify 50% overlap between contiguous sections.
nff = max(256, 2 ^ nextpow2(nsc));  % Use nff points to compute FFT.
f = figure("Visible", "off");
spectrogram(male_song_data(:,1), hamming(nsc), nov, nff, male_song_sampleRate);
title("Spectrogram of Male Song");
exportgraphics(f, fullfile(img_folder, "Spectrogram_male_song.png"), "Resolution", plot_resolution);
close(f);

fprintf("Generating Spectrogram of Female Song.\n");
Nx = length(female_song_data(:,1));
nsc = floor(Nx / 100);  % Divide the signal into sections of length nsc
nov = floor(nsc / 2); % Specify 50% overlap between contiguous sections.
nff = max(256, 2 ^ nextpow2(nsc));  % Use nff points to compute FFT.
f = figure("Visible", "off");
spectrogram(female_song_data(:,1), hamming(nsc), nov, nff, female_song_sampleRate);
title("Spectrogram of Female Song");
exportgraphics(f, fullfile(img_folder, "Spectrogram_female_song.png"), "Resolution", plot_resolution);
close(f);
fprintf("----- Generating Complete -----\n\n");

%% Compute the FFT of the audio data
% ----- Speak Voice -----
fprintf("Generating Frequency Analysis of Speak Voice.\n");
Y = fft(speak_voice_data);
Yshift = fftshift(Y);

% Compute the frequencies corresponding to the FFT data
Nx = length(speak_voice_data(:,1));
freq = (0:(Nx - 1)) * speak_voice_sampleRate / Nx;
freqshift = ((-Nx / 2):(Nx / 2 - 1)) * speak_voice_sampleRate / length(Y);

% Plot the frequency spectrum of the audio signal
f = figure("Visible", "off");
plot(freqshift, abs(Yshift) + 1);
title("Frequency Analysis of Speak Voice");
xticks(-50000:5000:50000);
xlabel("Frequency (Hz)");
ylabel("Amplitude");
exportgraphics(f, fullfile(img_folder, "Frequency_Analysis_speak_voice.png"), "Resolution", plot_resolution);
close(f);
% Plot the frequency spectrum of the audio signal
f = figure("Visible", "off");
plot(freqshift, log(abs(Yshift) + 1));
title("Frequency Analysis of Speak Voice");
xticks(-50000:5000:50000);
xlabel("Frequency (Hz)");
ylabel("Amplitude (log)");
exportgraphics(f, fullfile(img_folder, "Frequency_Analysis_Log_speak_voice.png"), "Resolution", plot_resolution);
close(f);

% ----- Laugh Voice -----
fprintf("Generating Frequency Analysis of Laugh Voice.\n");
Y = fft(laugh_voice_data);
Yshift = fftshift(Y);

% Compute the frequencies corresponding to the FFT data
Nx = length(laugh_voice_data(:,1));
freq = (0:(Nx - 1)) * laugh_voice_sampleRate / Nx;
freqshift = ((-Nx / 2):(Nx / 2 - 1)) * laugh_voice_sampleRate / length(Y);

% Plot the frequency spectrum of the audio signal
f = figure("Visible", "off");
plot(freqshift, abs(Yshift) + 1);
title("Frequency Analysis of Laugh Voice");
xticks(-50000:5000:50000);
xlabel("Frequency (Hz)");
ylabel("Amplitude");
exportgraphics(f, fullfile(img_folder, "Frequency_Analysis_laugh_voice.png"), "Resolution", plot_resolution);
close(f);
% Plot the frequency spectrum of the audio signal
f = figure("Visible", "off");
plot(freqshift, log(abs(Yshift) + 1));
title("Frequency Analysis of Laugh Voice");
xticks(-50000:5000:50000);
xlabel("Frequency (Hz)");
ylabel("Amplitude (log)");
exportgraphics(f, fullfile(img_folder, "Frequency_Analysis_Log_laugh_voice.png"), "Resolution", plot_resolution);
close(f);

% ----- Scream Voice -----
fprintf("Generating Frequency Analysis of Scream Voice.\n");
Y = fft(scream_voice_data);
Yshift = fftshift(Y);

% Compute the frequencies corresponding to the FFT data
Nx = length(scream_voice_data(:,1));
freq = (0:(Nx - 1)) * scream_voice_sampleRate / Nx;
freqshift = ((-Nx / 2):(Nx / 2 - 1)) * scream_voice_sampleRate / length(Y);

% Plot the frequency spectrum of the audio signal
f = figure("Visible", "off");
plot(freqshift, abs(Yshift) + 1);
title("Frequency Analysis of Scream Voice");
xticks(-50000:5000:50000);
xlabel("Frequency (Hz)");
ylabel("Amplitude");
exportgraphics(f, fullfile(img_folder, "Frequency_Analysis_scream_voice.png"), "Resolution", plot_resolution);
close(f);
% Plot the frequency spectrum of the audio signal
f = figure("Visible", "off");
plot(freqshift, log(abs(Yshift) + 1));
title("Frequency Analysis of Scream Voice");
xticks(-50000:5000:50000);
xlabel("Frequency (Hz)");
ylabel("Amplitude (log)");
exportgraphics(f, fullfile(img_folder, "Frequency_Analysis_Log_scream_voice.png"), "Resolution", plot_resolution);
close(f);

% ----- My Song -----
fprintf("Generating Frequency Analysis of My Song.\n");
Y = fft(my_song_data);
Yshift = fftshift(Y);

% Compute the frequencies corresponding to the FFT data
Nx = length(my_song_data(:,1));
freq = (0:(Nx - 1)) * my_song_sampleRate / Nx;
freqshift = ((-Nx / 2):(Nx / 2 - 1)) * my_song_sampleRate / length(Y);

% Plot the frequency spectrum of the audio signal
f = figure("Visible", "off");
plot(freqshift, abs(Yshift) + 1);
title("Frequency Analysis of My Song");
xticks(-50000:5000:50000);
xlabel("Frequency (Hz)");
ylabel("Amplitude");
exportgraphics(f, fullfile(img_folder, "Frequency_Analysis_my_song.png"), "Resolution", plot_resolution);
close(f);
% Plot the frequency spectrum of the audio signal
f = figure("Visible", "off");
plot(freqshift, log(abs(Yshift) + 1));
title("Frequency Analysis of My Song");
xticks(-50000:5000:50000);
xlabel("Frequency (Hz)");
ylabel("Amplitude (log)");
exportgraphics(f, fullfile(img_folder, "Frequency_Analysis_Log_my_song.png"), "Resolution", plot_resolution);
close(f);

% ----- Male Song -----
fprintf("Generating Frequency Analysis of Male Song.\n");
Y = fft(male_song_data);
Yshift = fftshift(Y);

% Compute the frequencies corresponding to the FFT data
Nx = length(male_song_data(:,1));
freq = (0:(Nx - 1)) * male_song_sampleRate / Nx;
freqshift = ((-Nx / 2):(Nx / 2 - 1)) * male_song_sampleRate / length(Y);

% Plot the frequency spectrum of the audio signal
f = figure("Visible", "off");
plot(freqshift, abs(Yshift) + 1);
title("Frequency Analysis of Male Song");
xticks(-30000:3000:30000);
xlabel("Frequency (Hz)");
ylabel("Amplitude");
exportgraphics(f, fullfile(img_folder, "Frequency_Analysis_male_song.png"), "Resolution", plot_resolution);
close(f);
% Plot the frequency spectrum of the audio signal
f = figure("Visible", "off");
plot(freqshift, log(abs(Yshift) + 1));
title("Frequency Analysis of Male Song");
xticks(-30000:3000:30000);
xlabel("Frequency (Hz)");
ylabel("Amplitude (log)");
exportgraphics(f, fullfile(img_folder, "Frequency_Analysis_Log_male_song.png"), "Resolution", plot_resolution);
close(f);

% ----- Female Song -----
fprintf("Generating Frequency Analysis of Female Song.\n");
Y = fft(female_song_data);
Yshift = fftshift(Y);

% Compute the frequencies corresponding to the FFT data
Nx = length(female_song_data(:,1));
freq = (0:(Nx - 1)) * female_song_sampleRate / Nx;
freqshift = ((-Nx / 2):(Nx / 2 - 1)) * female_song_sampleRate / length(Y);

% Plot the frequency spectrum of the audio signal
f = figure("Visible", "off");
plot(freqshift, abs(Yshift) + 1);
title("Frequency Analysis of Female Song");
xticks(-30000:3000:30000);
xlabel("Frequency (Hz)");
ylabel("Amplitude");
exportgraphics(f, fullfile(img_folder, "Frequency_Analysis_female_song.png"), "Resolution", plot_resolution);
close(f);
% Plot the frequency spectrum of the audio signal
f = figure("Visible", "off");
plot(freqshift, log(abs(Yshift) + 1));
title("Frequency Analysis of Female Song");
xticks(-30000:3000:30000);
xlabel("Frequency (Hz)");
ylabel("Amplitude (log)");
exportgraphics(f, fullfile(img_folder, "Frequency_Analysis_Log_female_song.png"), "Resolution", plot_resolution);
close(f);

% ----- Music -----
fprintf("Generating Frequency Analysis of Music.\n");
Y = fft(music_data);
Yshift = fftshift(Y);

% Compute the frequencies corresponding to the FFT data
Nx = length(music_data(:,1));
freq = (0:(Nx - 1)) * music_sampleRate / Nx;
freqshift = ((-Nx / 2):(Nx / 2 - 1)) * music_sampleRate / length(Y);

% Plot the frequency spectrum of the audio signal
f = figure("Visible", "off");
plot(freqshift, abs(Yshift) + 1);
title("Frequency Analysis of Music");
xticks(-30000:3000:30000);
xlabel("Frequency (Hz)");
ylabel("Amplitude");
exportgraphics(f, fullfile(img_folder, "Frequency_Analysis_music.png"), "Resolution", plot_resolution);
close(f);
% Plot the frequency spectrum of the audio signal
f = figure("Visible", "off");
plot(freqshift, log(abs(Yshift) + 1));
title("Frequency Analysis of Music");
xticks(-30000:3000:30000);
xlabel("Frequency (Hz)");
ylabel("Amplitude (log)");
exportgraphics(f, fullfile(img_folder, "Frequency_Analysis_Log_music.png"), "Resolution", plot_resolution);
close(f);
fprintf("----- Generating Complete -----\n\n");

%% Earth Mover s Distance (EMD)
emd_male = emd(my_song_data(1:1000, 1), male_song_data(1:1000, 1), my_song_data(1:1000, 1) / sum(my_song_data(1:1000, 1), "all"), male_song_data(1:1000, 1) / sum(male_song_data(1:1000, 1), "all"), @gdf);
disp(emd_male);

emd_female = emd(my_song_data(1:1000, 1), female_song_data(1:1000, 1), my_song_data(1:1000, 1) / sum(my_song_data(1:1000, 1), "all"), female_song_data(1:1000, 1) / sum(female_song_data(1:1000, 1), "all"), @gdf);
disp(emd_female);
