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
    layers.Dense(10, activation='sigmoid', input_shape=[6,]),
    layers.Dense(10, activation='sigmoid'),
    layers.Dense(6)
  ])

  optimizer = tf.keras.optimizers.RMSprop(0.001)

  model.compile(loss='mse',
                optimizer=optimizer,
                metrics=['mae', 'mse'])
  return model

# Import data
dataset_path = "C:/Users/aniyo/Documents/Honours_Code/ML_models/music_synths/data.csv"
dataset = pd.read_csv(dataset_path)
inputs = ['in1','in2','in3','in4','in5','in6']
outputs = ['out1','out2','out3','out4','out5','out6']

#Split dataset
train_dataset = dataset.sample(frac=0.8,random_state=0)
test_dataset = dataset.drop(train_dataset.index)

#Get test and train_labels
x_train = train_dataset[inputs]
y_train = train_dataset[outputs]

x_test = test_dataset[inputs]
y_test = test_dataset[outputs]
print(x_train)

#Make into pandas array
x_train = pd.DataFrame(x_train,columns=inputs)
y_train = pd.DataFrame(y_train,columns=outputs)
x_test = pd.DataFrame(x_test,columns=inputs)
y_test = pd.DataFrame(y_test,columns=outputs)

#Make dataset
train_dataset = tf.data.Dataset.from_tensor_slices((x_train, y_train))
# Shuffle and slice the dataset.
train_dataset = train_dataset.shuffle(buffer_size=1024).batch(32)

# Now we get a test dataset.
test_dataset = tf.data.Dataset.from_tensor_slices((x_test, y_test))
test_dataset = test_dataset.batch(64)

#Build model
model = build_model()

#Compile model
model.compile(loss='mse',
              optimizer=tf.keras.optimizers.RMSprop(0.001),
              metrics=['mae', 'mse'])

#Train Model
history = model.fit(train_dataset,epochs=300)

# Test model
test_scores = model.evaluate(test_dataset, verbose=2)
print("Test loss:", test_scores[0])
print("Test accuracy:", test_scores[1])

# Convert the model.
converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

# Save the TF Lite model
with tf.io.gfile.GFile('model.tflite', 'wb') as f:
  f.write(tflite_model)

#Visualize it
test_predictions = model.predict(x_test)
#Plot results so I can see whats up(show how well it predicts outputs)
fig,axs = plt.subplots(2,3)
idx = 0
for ax in axs.flatten():
    header = outputs[idx]
    ax.scatter(y_test[header], test_predictions[:,idx])
    x_str = f'True Values [{header}]'
    y_str = f'Predictions [{header}]'
    ax.set_xlabel(x_str)
    ax.set_ylabel(y_str)
    lims = [0, 1]
    ax.set_xlim(lims)
    ax.set_ylim(lims)
    ax.plot(lims, lims)
    idx += 1
plt.show()

#Plot results so I can see whats up(show range of inputs)
# fig,axs = plt.subplots(1,3)
# idx = 0
# for ax in axs.flatten():
#     header = inputs[idx]
#     ax.scatter(np.linspace(0,len(x_test),num=len(x_test)),x_test[header])
#     x_str = f'True Values [{header}]'
#     y_str = f'Predictions [{header}]'
#     ax.set_xlabel(x_str)
#     ax.set_ylabel(y_str)
#     idx += 1
# plt.show()

#Plot results so I can see whats up(plot an input to all the outputs)
# fig,axs = plt.subplots(2,4)
# idx = 0
# for ax in axs.flatten():
#     header = outputs[idx]
#     ax.scatter(x_test['in3'], test_predictions[:,idx])
#     x_str = f'True Values [{header}]'
#     y_str = f'Predictions [{header}]'
#     ax.set_xlabel(x_str)
#     ax.set_ylabel(y_str)
#     idx += 1
# plt.show()
