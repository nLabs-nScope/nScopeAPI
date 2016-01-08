function [ data ] = nScopeReadCh1( sampleRate, numSamples, gain)
%[ data ] = nScopeReadCh1( sampleRate, numSamples, gain )
%
%   read data from Channel 1 of nScope
%
%   requires nScope connection to be open with nScopeAPI('open',1);
%
%   sampleRate: the sample rate in Hz of the channel
%   numSamples: the number of samples to take
%   gain:       input amplification gain
%
%   nScope must have a connection open before running
%   run nScopeAPI('open',1) to open

nScopeAPI('setChannelsOn',1,0,0,0);         % turn on Channel 1, and no others
nScopeAPI('setCh1gain',gain);               % set the gain on Channel 1
nScopeAPI('setSampleRateInHz',sampleRate);  % set the sample rate
nScopeAPI('requestData',numSamples);        % request the samples from nScope

data = zeros(numSamples,1);
i = 0;
while(nScopeAPI('requestHasData'))
    i=i+1;
    data(i) = nScopeAPI('readData',1);
end


end

