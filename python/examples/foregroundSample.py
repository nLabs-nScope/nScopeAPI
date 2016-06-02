# First we need to import the library

import sys
sys.path.append('../')      # add the path to the library to our path

import nScopePy as ns       # import the nScopePy module

# open a connection to nScope
nScope = ns.nScopeObj()

sampleRate = 5000.0         # Hz
numSamples = 1000           # number of samples per channel

# Turn on the appropriate channels (ch1,ch2,ch3,ch4)
nScope.setChannelsOn(1,1,0,0)

# Set the sample rate
nScope.setSampleRateInHz(sampleRate)

# Issue a data request to nScope
nScope.requestData(numSamples)

'''
Note that if sample rate is faster than 16k samples/sec
a 3200 (total) sample limit is enforced.

In this case, the above function will return an invalid request error
'''
# initialize data lists
ch1 = []
ch2 = []

while nScope.requestHasData():

    # read from channel 1
    voltage = nScope.readData(1)
    ch1.append(voltage)

    # read from channel 2
    voltage = nScope.readData(2)
    ch2.append(voltage)

# do something with the returned data
print ch1,ch2
