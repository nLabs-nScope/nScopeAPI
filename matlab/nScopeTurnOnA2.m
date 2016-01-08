function nScopeTurnOnA2( frequency, iSunipolar, amplitude )
%nScopeTurnOnA2( frequency, iSunipolar, amplitude )
%
%   Turn on the A2 output of nScope
%   frequency: the frequency of the wave in Hz
%   isUnipolar: 1, output is positive with max amplitude
%               0, output is bipolar with peak-to-peak amplitude twice the
%               given
%
%   amplitude:  peak voltage of output, bipolar output will swing to
%               negative levels
%
%   nScope must have a connection open before running
%   run nScopeAPI('open',1) to open


nScopeAPI('setA2frequencyInHz',frequency);  % Set the frequency of A2 output
nScopeAPI('setA2unipolar',iSunipolar);      % Set the output to be unipolar or not
nScopeAPI('setA2amplitude',amplitude);      % Set the amplitude
nScopeAPI('setA2on',1);                     % Set the A2 output on


end

