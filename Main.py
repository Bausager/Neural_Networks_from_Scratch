# -*- coding: utf-8 -*-
"""
Created on Sat Oct 16 14:35:54 2021

@author: Bausa
"""

from nnfs.datasets import spiral_data
from nnfs.datasets import sine_data

import OwnLib

import nnfs
import matplotlib.pyplot as plt
import numpy as np
from tqdm import tqdm

import os
import urllib
import urllib.request
import cv2

nnfs.init()

def load_mnist_dataset(dataset, path):
    # Scan all the directories and create a list of labels
    labels = os.listdir(os.path.join(path, dataset))
    # Create lists for samples and labels
    X = []
    y = []
    # For each label folder
    for label in labels:
        # And for each image in given folder
        for file in os.listdir(os.path.join(path, dataset, label)):
            # Read the image
            image = cv2.imread(os.path.join(
                        path, dataset, label, file
                    ), cv2.IMREAD_UNCHANGED)
            # And append it and a label to the lists
            X.append(image)
            y.append(label)
    # Convert the data to proper numpy arrays and return
    return np.array(X), np.array(y).astype('uint8')

# MNIST dataset (train + test)
def create_data_mnist(path):
    # Load both sets separately
    X, y = load_mnist_dataset('train', path)
    X_test, y_test = load_mnist_dataset('test', path)
    # And return all the data
    return X, y, X_test, y_test


# Create dataset
X, y, X_test, y_test = create_data_mnist('fashion_mnist_images')

# Shuffle the training dataset
keys = np.array(range(X.shape[0]))
np.random.shuffle(keys)
X = X[keys]
y = y[keys]

# Scale and reshape samples
X = (X.reshape(X.shape[0], -1).astype(np.float32) - 127.5) / 127.5
X_test = (X_test.reshape(X_test.shape[0], -1).astype(np.float32) -
              127.5) / 127.5

#%%
model = OwnLib.Model()

model.add(OwnLib.Layer_Dense(X.shape[1], 4))
model.add(OwnLib.Activation_ReLU())
model.add(OwnLib.Layer_Dense(4, 10))
model.add(OwnLib.Activation_Softmax())

model.set(
        loss=OwnLib.Loss_CategoricalCrossentropy(),
        optimizer=OwnLib.Optimizer_Adam(decay=1e-3),
        accuracy=OwnLib.Accuracy_Categorical())

model.finalize()

model.train(X, y, epochs=2, print_every=100, batch_size=32, validation_data=(X_test, y_test))

model.save_parameters('try.params')

#%%
model = OwnLib.Model()

model.add(OwnLib.Layer_Dense(X.shape[1], 4))
model.add(OwnLib.Activation_ReLU())
model.add(OwnLib.Layer_Dense(4, 10))
model.add(OwnLib.Activation_Softmax())

model.set(
        loss=OwnLib.Loss_CategoricalCrossentropy(),
        optimizer=OwnLib.Optimizer_Adam(decay=1e-3),
        accuracy=OwnLib.Accuracy_Categorical())

model.finalize()

model.load_parameters('try.params')

model.evaluate(X_test, y_test, batch_size=32)

#%%

model = OwnLib.Model()

model.add(OwnLib.Layer_Dense(X.shape[1], 4))
model.add(OwnLib.Activation_ReLU())
model.add(OwnLib.Layer_Dense(4, 10))
model.add(OwnLib.Activation_Softmax())

model.set(
        loss=OwnLib.Loss_CategoricalCrossentropy(),
        optimizer=OwnLib.Optimizer_Adam(decay=1e-3),
        accuracy=OwnLib.Accuracy_Categorical())

model.finalize()

model.train(X, y, epochs=2, print_every=100, batch_size=32, validation_data=(X_test, y_test))

model.save('Full.model')

#%%

model = OwnLib.Model.load('Full.model')

confidence = model.predict(X_test[1])
print(confidence)


#model.evaluate(X_test, y_test, batch_size=32)
    













































