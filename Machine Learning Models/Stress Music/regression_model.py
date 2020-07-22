import tensorflow as tf

from tensorflow import keras
from tensorflow.keras import layers

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

print(tf.__version__)

import tensorflow_docs as tfdocs
import tensorflow_docs.plots
import tensorflow_docs.modeling

def build_model():
  model = keras.Sequential([
    layers.Dense(3, activation='sigmoid', input_shape=[1]),
    layers.Dense(3, activation='sigmoid'),
    layers.Dense(1)
  ])

  optimizer = tf.keras.optimizers.RMSprop(0.001)

  model.compile(loss='mse',
                optimizer=optimizer,
                metrics=['mae', 'mse'])
  return model

# Import data
dataset_path = "C:/Users/aniyo/Documents/Honours_Code/Machine Learning Models/Stress Music/stress_data_2.csv"
column_names = ['Input','Calm','Stress','Speed']
dataset = pd.read_csv(dataset_path)

#Split dataset
train_dataset = dataset.sample(frac=0.8,random_state=0)
test_dataset = dataset.drop(train_dataset.index)

#Get test and train_labels
train_labels = train_dataset['Calm']
test_labels = test_dataset['Calm']

train_dataset = train_dataset.pop('Input')
test_dataset = test_dataset.pop('Input')

#Build Model
model = build_model()
model.summary()

# test_model = train_dataset[:5]
# print(test_model)
# result = model.predict(test_model)
# print(result)

EPOCHS = 1000

history = model.fit(
  train_dataset, train_labels,
  epochs=EPOCHS, validation_split = 0.2, verbose=0,
  callbacks=[tfdocs.modeling.EpochDots()])

# Test model
test_predictions = model.predict(test_dataset)

# Convert the model.
converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

# Save the TF Lite model.
with tf.io.gfile.GFile('model.tflite', 'wb') as f:
  f.write(tflite_model)

# plt.plot(test_labels,test_predictions)
# plt.show()
# #Plot results so I can see whats up
# fig,axs = plt.subplots(1,3)
# idx = 1
# for ax in axs.flatten():
#     header = column_names[idx]
#     ax.scatter(test_labels[header], test_predictions[:,idx-1])
#     x_str = f'True Values [{header}]'
#     y_str = f'Predictions [{header}]'
#     ax.set_xlabel(x_str)
#     ax.set_ylabel(y_str)
#     lims = [0, 1]
#     ax.set_xlim(lims)
#     ax.set_ylim(lims)
#     ax.plot(lims, lims)
#     idx += 1
# plt.show()
