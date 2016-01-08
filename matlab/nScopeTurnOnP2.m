function nScopeTurnOnP2( frequency, duty )
%nScopeTurnOnP2( frequency, duty )
%
%   Turn on the P2 output of nScope
%
%   frequency: the frequency of the pulse in Hz
%   duty: duty percentage of the pulse
%
%   nScope must have a connection open before running
%   run nScopeAPI('open',1) to open

warning ('off','all'); 
nScopeAPI('setP2frequencyInHz',frequency);      %Set the frequency of P1
nScopeAPI('setP2dutyPercentage',duty);          %Set the P1 duty percentage
nScopeAPI('setP2on',1);                         %Set P1 on


end

