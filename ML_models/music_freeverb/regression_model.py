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
  # Create layers
  inputs = keras.Input(shape=(3,))
  dense = layers.Dense(10, activation="sigmoid")
  x1 = dense(inputs)
  x2 = layers.Dense(10, activation="sigmoid")(x1)
  x3 = layers.Dense(10, activation="sigmoid")(x2)
  outputs = layers.Dense(8)(x3)

  model = keras.Model(inputs=inputs, outputs=outputs, name="reverb")

  optimizer = tf.keras.optimizers.RMSprop(0.001)

  model.compile(loss='mse',
                optimizer=optimizer,
                metrics=['mae', 'mse'])
  return model

# Import data
dataset_path = "C:/Users/aniyo/Documents/Honours_Code/ML_models/music_freeverb/data.csv"
dataset = pd.read_csv(dataset_path)

#Split dataset
train_dataset = dataset.sample(frac=0.8,random_state=0)
test_dataset = dataset.drop(train_dataset.index)

#Get test and train_labels
x_train = np.array([train_dataset['in1'],train_dataset['in2'],train_dataset['in3']])
y_train = np.array([train_dataset['out1'],train_dataset['out2'],train_dataset['out3'],train_dataset['out4'],train_dataset['out5'],train_dataset['out6'],train_dataset['out7'],train_dataset['out8']])

x_test = np.array([test_dataset['in1'],test_dataset['in2'],test_dataset['in3']])
y_test = np.array([test_dataset['out1'],test_dataset['out2'],test_dataset['out3'],test_dataset['out4'],test_dataset['out5'],test_dataset['out6'],test_dataset['out7'],test_dataset['out8']])

#Reshape inputs
x_train = x_train.reshape(x_train.shape[1],x_train.shape[0])
y_train = y_train.reshape(y_train.shape[1],y_train.shape[0])

x_test = x_test.reshape(x_test.shape[1],x_test.shape[0])
y_test = y_test.reshape(y_test.shape[1],y_test.shape[0])


#Build Model
model = build_model()
model.summary()

EPOCHS = 100

history = model.fit(x_train, y_train, epochs=EPOCHS, batch_size=10, validation_split = 0.2, verbose=0,callbacks=[tfdocs.modeling.EpochDots()])

# Test model
test_scores = model.evaluate(x_test, y_test, verbose=2)
print("Test loss:", test_scores[0])
print("Test accuracy:", test_scores[1])

# # Convert the model.
# converter = tf.lite.TFLiteConverter.from_keras_model(model)
# tflite_model = converter.convert()

# # Save the TF Lite model.
# with tf.io.gfile.GFile('model.tflite', 'wb') as f:
#   f.write(tflite_model)

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
