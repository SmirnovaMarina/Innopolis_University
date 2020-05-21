# -*- coding: utf-8 -*-
"""Updated_Lab11_G6_Smirnova.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1I_ZLL7nkeOwgF2qk7D19BB_39Ejt-RHE

***Task 1.***

Assume a function $f(t) = asin(wt) + bcos(wt)$ and add random noise.
Filter using Kalman Filter. Plot the noisy and filtered signal.
"""

import numpy as np
import matplotlib.pyplot as plt
import math
from random import random, gauss


# initialization
# f(t) = a*sin(wt) + b*cos(wt) + noise
w = 1
n = 1001
time = np.linspace(0, 10, n)
dt = 0.01
x = np.empty([n, 2, 1])
y = np.empty([n, 1])
y_hat = np.empty([n, 1])

B = np.full((2,1), 0)
W = np.full((2,1), 0)
V = np.empty([1,])
V[0] = 1

a = 1
b = 1
C = np.empty([1, 2])
C[0][0] = a
C[0][1] = b


def get_A(dt):
  return np.asarray([[math.cos(w*dt), math.sin(w*dt)],
                  [-math.sin(w*dt), math.cos(w*dt)]])


def get_P_i(t, dt, P_prev):
  A = get_A(dt)
  A_tr = np.transpose(A)
  return (np.matmul((np.matmul(A, P_prev)), A_tr) + W)

def get_x_i(t):
  return np.asarray([[math.sin(w*t)],
                     [math.cos(w*t)]])
  
def get_x_i_1(x_i, dt):
  return (np.matmul(get_A(dt), x_i) + W)


def get_x_i_hat(x_hat_prev):
  return (np.matmul(get_A(dt), x_hat_prev) + W)


# initial x state and covariance matrix
x[0] = get_x_i(0)
P0 = np.asarray([[0, 0],
                 [0, 1]])
y[0] = np.matmul(C, x[0]) + gauss(0, 1)
y_hat[0] = np.matmul(C, x[0])


def get_Y_i(t, dt, P_i):
  C_tr = np.transpose(C)
  return (np.matmul((np.matmul(C, P_i)), C_tr) + V)


def get_K_i(t, P_i, Y_i):
  C_tr = np.transpose(C)
  Y_inv = np.linalg.inv(Y_i)
  return np.matmul((np.matmul(P_i, C_tr)), Y_inv)


def get_y_i(t):
  return np.matmul(C, get_x_i(t)) + gauss(0, 1)

P_i = P0
for i in range(1, n):
  t = time[i]
  P_i = get_P_i(t, dt, P_i)
  x[i] = get_x_i_1(x[i-1], dt)

  y[i] = get_y_i(t)
  y_hat[i] = np.matmul(C, x[i])

  err_i = y[i] - y_hat[i]
  Y_i = get_Y_i(t, dt, P_i)
  K_i = get_K_i(t, P_i, Y_i)
  x[i] = x[i] + np.matmul(K_i, err_i)

  I = np.identity(2)
  P_i = (np.matmul((I - np.matmul(K_i, C)), P_i))
  

plt.plot(time, y[:, 0], 'b', label='actual')
plt.plot(time, y_hat[:, 0], 'r', label='estimated')
plt.legend()
plt.xlabel('time')
plt.grid()
plt.show()

"""***Task 2.***

Assume a unit step function and add random noise. Filter
using Kalman Filter. Plot the noisy and filtered signal.
"""

import numpy as np
import matplotlib.pyplot as plt
import math
from random import random, gauss


# initialization
# f(t) = (a*sin(wt) + b*cos(wt)) * Indicator + noise
# Indicator = 1, if (a*sin(wt) + b*cos(wt)) > 0
# Indicator = -1, otherwise
w = 1
n = 1001
time = np.linspace(0, 10, n)
dt = 0.01
x = np.empty([n, 2, 1])
y = np.empty([n, 1])
y_hat = np.empty([n, 1])

B = np.full((2,1), 0)
W = np.full((2,1), 0)
V = np.empty([1,])
V[0] = 1

a = 1
b = 1
C = np.empty([1, 2])
C[0][0] = a
C[0][1] = b


def get_A(dt):
  return np.asarray([[1, 0],
                     [0, 1]])

def get_P_i(t, dt, P_prev):
  A = get_A(dt)
  A_tr = np.transpose(A)
  return (np.matmul((np.matmul(A, P_prev)), A_tr) + W)

def get_Y_i(t, dt, P_i):
  C_tr = np.transpose(C)
  return (np.matmul((np.matmul(C, P_i)), C_tr) + V)

def get_K_i(t, P_i, Y_i):
  C_tr = np.transpose(C)
  Y_inv = np.linalg.inv(Y_i)
  return np.matmul((np.matmul(P_i, C_tr)), Y_inv)


def get_y_i_step(t):
  if np.asscalar(np.matmul(C, get_x_i(t))) > 0:
    return (1 + gauss(0,1))
  else:
    return (-1 + gauss(0,1))

def get_x_i(t):
  return np.asarray([[math.sin(w*t)],
                     [math.cos(w*t)]])
  
def get_x_i_1(x_i, dt):
  return (np.matmul(get_A(dt), x_i) + W)


# initial x state and covariance matrix
x[0] = get_x_i(0)
P0 = np.asarray([[0, 0],
                 [0, 1]])
P_i = P0
y[0] = np.matmul(C, x[0]) + gauss(0, 1)
y_hat[0] = np.matmul(C, x[0])


for i in range(1, n):
  t = time[i]
  P_i = get_P_i(t, dt, P_i)
  x[i] = get_x_i_1(x[i-1], dt)

  y[i] = get_y_i_step(t)
  y_hat[i] = np.matmul(C, x[i])

  err_i = y[i] - np.matmul(C, x[i])
  Y_i = get_Y_i(t, dt, P_i)
  K_i = get_K_i(t, P_i, Y_i)
  x[i] = x[i] + np.matmul(K_i, err_i)

  I = np.identity(2)
  P_i = (np.matmul((I - np.matmul(K_i, C)), P_i))


plt.plot(time, y[:, 0], 'b', label='actual')
plt.plot(time, y_hat[:, 0], 'r', label='estimated')
plt.legend()
plt.xlabel('time')
plt.grid()
plt.show()

"""***Task 3.***

Assume a spring mass damper system with noise in the
measured states. Implement Kalman Filter to filter out the
noise. Plot the results with and without the Filter.
"""

from scipy.integrate import odeint
import numpy as np
import matplotlib.pyplot as plt
import math
from random import random, gauss


# initialization
# assume no additional external forces: u(t) = 0
# x''(t) = (-b/m)*x' + (-k/m)*x + noise
n = 201
time = np.linspace(0, 20, n)
dt = 0.1
x = np.empty([n, 2, 1])
y = np.empty([n, 1])
y_hat = np.empty([n, 1])

B = np.full((2,1), 0)
V = np.empty([1,])
V[0] = 1
var = 0.1  # variance of process noise 

# matrix C to sense measurements
# C = [1, 0] to sense the position
# C = [0, 1] to sense the velocity
C = np.empty([1, 2])
C[0][0] = 1
C[0][1] = 0

# parameters of the system: m, b, k
m = 1.0
b = 0.5
k = 1.0


# solve the system using odeint() to find real values of position and velocity
def spring_sys(x_state, t):
  dx_dt = [0, 0]
  dx_dt[0] = x_state[1]
  dx_dt[1] = (-b/m)*x_state[1] - (k/m)*x_state[0]
  return dx_dt

x_init = np.asarray([0, 1])
solution = odeint(spring_sys, x_init, time)
for i in range(0, n):
  y[i][0] = solution[i][0] + gauss(0, 1)


# functions to calculate needed matrices
def get_W(dt):
  return np.asarray([[var*0.25*math.pow(dt, 4), var*0.5*math.pow(dt, 3)],
                     [var*0.5*math.pow(dt, 3), var*dt*dt]])

def get_A(dt):
  return np.asarray([[1, dt],
                     [(-k/m)*dt, (1-(b/m)*dt)]])
  
def get_Y_i(t, dt, P_i):
  C_tr = np.transpose(C)
  return (np.matmul((np.matmul(C, P_i)), C_tr) + V)

def get_K_i(t, P_i, Y_i):
  C_tr = np.transpose(C)
  Y_inv = np.linalg.inv(Y_i)
  return np.matmul((np.matmul(P_i, C_tr)), Y_inv)

def get_P_i(t, dt, P_prev):
  A = get_A(dt)
  A_tr = np.transpose(A)
  return (np.matmul((np.matmul(A, P_prev)), A_tr) + get_W(dt))
  
def get_x_i_1(x_i, dt):
  return (np.matmul(get_A(dt), x_i))


# initial x state and covariance matrix
x[0] = [[0], 
        [1]]
P0 = np.asarray([[0.1, 0],
                 [0, 0.1]])
P_i = P0
y_hat[0] = np.matmul(C, x[0])


# iterative calculations of state x_i+1 and y_hat_i+1
for i in range(1, n):
  t = time[i]
  P_i = get_P_i(t, dt, P_i)
  x[i] = get_x_i_1(x[i-1], dt)

  y_hat[i] = np.matmul(C, x[i])

  err_i = y[i] - y_hat[i]
  Y_i = get_Y_i(t, dt, P_i)
  K_i = get_K_i(t, P_i, Y_i)
  x[i] = x[i] + np.matmul(K_i, err_i)

  I = np.identity(2)
  P_i = (np.matmul((I - np.matmul(K_i, C)), P_i))

  

plt.plot(time, solution[:, 0], 'y', label='without noise')
plt.plot(time, y, 'b', label='noisy')
plt.plot(time, y_hat, 'r', label='filtered')
plt.legend()
plt.xlabel('time')
plt.grid()
plt.show()