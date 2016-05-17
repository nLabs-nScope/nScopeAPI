import sys
sys.path.append('../')
from nScopePy import *
import matplotlib.animation as animation
from pylab import *

nScope = nScopeObj()

sampleRate = 44100.0
numSamples = 1152

fig = figure(figsize=(8,8))
timeAx = subplot(2,1,1)
data = nScope.readCh1(numSamples,sampleRate)
time = arange(numSamples)/sampleRate*1000.0
axis([0,max(time),-2,2])
xlabel('time (ms)')
ylabel('voltage (v)')

voltage, = plot(time,data)

freqAx = subplot(2,1,2)
freq = rfftfreq(numSamples)*sampleRate
fftdata = abs(rfft(data))
xlabel('frequency (Hz)')
ylabel('magnitude')
spectrum, = plot(freq,fftdata)
axis([20,20000,0,numSamples])
freqAx.set_xscale('log')
freqAx.set_yscale('log')


def update(event):
    data = nScope.readCh1(numSamples,sampleRate)
    fftdata = abs(rfft(data))
    voltage.set_ydata(data)
    spectrum.set_ydata(fftdata)


ani = animation.FuncAnimation(fig, update, interval=16)

show()
