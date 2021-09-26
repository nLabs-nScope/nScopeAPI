function [ data ] = nScopeReadAllChannels( sampleRate, numSamples, gains )
%[ data ] = nScopeReadAllChannels( sampleRate, numSamples )
%
%   read data from all channels of nScope
%
%   requires nScope connection to be open with nScopeAPI('open',1);
%
%   sampleRate: the sample rate in Hz of the channel
%   numSamples: the number of samples to take
%   gains:      [ch1 ch2 ch3 ch4] vector input amplification gains
%
%   nScope must have a connection open before running
%   run nScopeAPI('open',1) to open

nScopeAPI('setChannelsOn',1,1,1,1);         % turn on all Channels
nScopeAPI('setChannelGains',gains(1),gains(2),gains(3),gains(4));       % set all channels with a gain of 1
nScopeAPI('setSampleRateInHz',sampleRate);  % set the sample rate
nScopeAPI('requestData',numSamples);        % request the samples from nScope
nScopeAPI('sendP1Pulse',100000);
data = zeros(numSamples,4);
i = 0;
while(nScopeAPI('requestHasData'))
    i=i+1;
    data(i,1) = nScopeAPI('readData',1);
    data(i,2) = nScopeAPI('readData',2);
    data(i,3) = nScopeAPI('readData',3);
    data(i,4) = nScopeAPI('readData',4);
end

nScopeAPI('releaseRequest');
end

