import sys
sys.path.append('../')
from nScopePy import *
import matplotlib.animation as animation
from pylab import *

nScope = nScopeObj()

sampleRate = 44100.0
numSamples = 1152

nScope.setChannelsOn(1,1,0,0)
nScope.setSampleRateInHz(sampleRate)

fig = figure(figsize=(8,8))
timeAx = subplot(2,1,1)

nScope.requestData(numSamples)
inputSig = []
outputSig = []
while nScope.requestHasData():
    inputSig.append(nScope.readData(2))
    outputSig.append(-nScope.readData(1))


time = arange(numSamples)/sampleRate*1000.0
axis([0,max(time),-2,2])
xlabel('time (ms)')
ylabel('voltage (v)')

inVolts, = plot(time,inputSig,color='green')
outVolts, = plot(time,outputSig,color='red')

freqAx = subplot(2,1,2)
freq = rfftfreq(numSamples)*sampleRate
xlabel('frequency (Hz)')
ylabel('magnitude')

inFFT = abs(rfft(inputSig))
outFFT = abs(rfft(outputSig))

inSpec, = plot(log10(freq),log10(inFFT),color='green')
outSpec, = plot(log10(freq),log10(outFFT),color='red')


ylim([-1,log10(numSamples)])
xt = log10(logspace(1,4,5)*2)
xl = ['%3.0f' % x for x in 10**xt]
xticks(xt,xl)


def update(event):
    nScope.requestData(numSamples)
    inputSig = []
    outputSig = []
    while nScope.requestHasData():
        inputSig.append(nScope.readData(2))
        outputSig.append(-nScope.readData(1))

    inVolts.set_ydata(inputSig)
    outVolts.set_ydata(outputSig)

    inFFT = abs(rfft(inputSig))
    outFFT = abs(rfft(outputSig))

    inSpec.set_ydata(log10(inFFT))
    outSpec.set_ydata(log10(outFFT))


ani = animation.FuncAnimation(fig, update, interval=16)

show()
