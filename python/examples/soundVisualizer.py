import sys
sys.path.append('../')
from nScopePy import *
import matplotlib.animation as animation
from pylab import *

nScope = nScopeObj()

sampleRate = 44100.0
numSamples = 1152

data = ones(numSamples)
time = arange(numSamples)/sampleRate*1000.0
freq = rfftfreq(numSamples)*sampleRate

axis([0,max(time),-2,2])
xlabel('time (ms)')
ylabel('voltage (v)')

voltage, = plot(time,data)

def update(event):
    data = nScope.readCh1(numSamples,sampleRate)
    voltage.set_ydata(data)

ani = animation.FuncAnimation(fig, update, interval=16)

show()
