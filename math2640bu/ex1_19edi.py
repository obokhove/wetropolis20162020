##################################################################
#
# Plots for Exercise No.1 MATH2460; 26-09-2019 by Onno Bokhove
#
# Used to plot graphs in exercise; 
# none of this programming material is mandatory, of course.
#
##################################################################
# GENERIC MODULES REQUIRED
#
import numpy as np
import os
import errno
from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt
import time
import matplotlib.mlab as mlab
import matplotlib.gridspec as gridspec
from math import pi, e
#
#
# Parameters
#
nchf = 5 # choice of function to be plotted
if nchf==1:
    # Exercise A1(i) plot: 
    plt.figure(1)
    plt.gcf().clear()
    xmin = 0.0 # -1.0
    xmax = 1.5
    Nx = 200
    dx = (xmax-xmin)/Nx
    x0 = np.arange(xmin,xmax,dx)
    x1 = 2.0/3.0
    x2 = 1
    x3 = 2
    xo = 0.0
    def f(x):
        return 2*x+x**3-2.5*x**2
    xx = x0
    print("minimum and maximum of function $f(x)$:",np.amin(f(xx)),np.amax(f(xx)))
    # Cut out! plt.title("Plot of function $f(x)=2 x+ x^3 - 2.5 x^2$.")
if nchf==2:
    # Exercise A1(ii) plot: 
    plt.figure(1)
    plt.gcf().clear()
    ymin = -1.0
    ymax = 1.0
    Ny = 200
    dy = (ymax-ymin)/Ny
    y0 = np.arange(ymin,ymax,dy)
    def x(y,c):
        return c-y**2
    yy = y0
    # Cut out! plt.title("Plot of function $z(x,y)=c=x+y^2$ for $c=-1,0,1,2$.")
#
if nchf==3:
    def f(x, y):
        return (x + y**2)
    #
    xrang = 2
    yrang = 1
    x = np.linspace(-xrang, xrang, 30)
    y = np.linspace(-xrang, xrang, 30)
    # Cut out
if nchf==4:
    def f(x, y):
        return (x**2-y**2)
    #
    xrang = 2
    yrang = 1
    x = np.linspace(-xrang, xrang, 100)
    y = np.linspace(-xrang, xrang, 100)
    #
    X, Y = np.meshgrid(x, y)
    Z = f(X, Y)
    fig = plt.figure()
    ax = plt.axes(projection='3d')
    cm = [-1, -0.5, 0, 0.5, 1, 1.5, 2]
    ax.contour3D(X, Y, Z, cm, cmap='viridis')
    # ax.plot_trisurf(x, y, f(x,y),cmap='viridis', edgecolor='none')
    # ax.plot_wireframe(X, Y, Z, color='black')
    # ax.set_title('wireframe');
    # plt.colorbar()
    plt.title("Plot of function $z(x,y)=c=x^2-y^2$ for $c=-1,-0.5,0,0.5,1,1.5,2$. ")
    ax.set_xlim3d(-2,2)
    ax.set_ylim3d(-2,2)
    ax.set_zlim3d(-2,4)
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z');
if nchf==5:
    # Example in notes lecture 1:
    plt.figure(1)
    plt.gcf().clear()
    xmin = -2.0 # -1.0
    xmax = 4.0
    Nx = 200
    dx = (xmax-xmin)/Nx
    x0 = np.arange(xmin,xmax,dx)
    x1 = -1.0
    x2 = 0.0
    x3 = 2.0
    x4 = 3.0
    def f(x):
        return -0.25*x**4+(4.0/3.0)*x**3-0.5*x**2-6.0*x+1.0
    xx = x0
    print("minimum and maximum of function $f(x)$:",np.amin(f(xx)),np.amax(f(xx)))
    plt.plot(xx,f(xx),'-k',lw=2)
    plt.plot(x4,f(x4),'xk',lw=2)
    plt.plot(x1,f(x1),'xk',lw=2)
    plt.plot(x2,f(x2),'xk',lw=2)
    plt.plot(x3,f(x3),'xk',lw=2)
    plt.grid(True)
    plt.xlabel('x')
    plt.ylabel('f(x)')    
    # plt.axis([xmin, xmax, -0.2, 1])
    plt.title("Plot of function $f(x)= -(1/4) x^4 + (4/3) x^3- (1/2) x^2 - 6 x + 1$.")
#
plt.show(block=True)
plt.pause(1)
plt.gcf().clear()
plt.show(block=False)


