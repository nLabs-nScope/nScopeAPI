function nScopeTurnOnP1( frequency, duty )
%nScopeTurnOnP1( frequency, duty )
%
%   Turn on the P1 output of nScope
%
%   frequency: the frequency of the pulse in Hz
%   duty: duty percentage of the pulse
%
%   nScope must have a connection open before running
%   run nScopeAPI('open',1) to open

warning ('off','all'); 
nScopeAPI('setP1frequencyInHz',frequency);      %Set the frequency of P1
nScopeAPI('setP1dutyPercentage',duty);          %Set the P1 duty percentage
nScopeAPI('setP1on',1);                         %Set P1 on


end

