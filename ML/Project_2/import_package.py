from __future__ import print_function, division

import copy
import os
import os.path
import sys
import time

import torch
import torch.nn as nn
import torch.optim as optim
from torch.optim import lr_scheduler
from torch.hub import load_state_dict_from_url
import torchvision
from torchvision import datasets, models, transforms
from torchvision.models import alexnet, resnet18, resnet34, resnet50, resnet101, resnet152, resnext50_32x4d, resnext101_32x8d, googlenet, vgg11, vgg11_bn, vgg13, vgg13_bn, vgg16, vgg16_bn, vgg19, vgg19_bn

import numpy as np
import matplotlib.pyplot as plt
from tqdm import tqdm
from bcolors import *
from hyperparameters import *
