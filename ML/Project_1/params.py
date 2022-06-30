import csv
import numpy as np
import random
import sys
import time
from matplotlib import pyplot as plt


class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


# y = mx + b
m = 6
b = 1
num_samples = 2000
rand_param = 2000
pos_num = int(num_samples / 2)
mistake = 50
early_stop = 10000
random_path = "./random.csv"
