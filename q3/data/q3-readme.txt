The data represents physiological variables (e.g. blood pressure, skin 
conductance, respiratory rate, etc) measured while subjects in groups 
of two were discussing an emotional movie (nuclear bombing). The variables
are sampled every second and the data in this file comprises several 
subjects. The variable we would like to predict is the "emotional 
experience" of the subject during the conversation. This variable is
obtained by asking each subject to turn a continuous dial (-1.5 to 1.5)
after the converasation to specify how they felt at each point in time
during the discussion. 

The data is continuous, however for this homework it has been discretized. 

Researchers do not know which variables are related to the emotional 
experience. We thus do not know what the true underlying distribution is
(this is on-going research).

In this homework you will compare performance of classifying the 
experience using categorical Naive Bayes and Logistic regression.

%%%%%%%%%%%%%%%%%%%%%%%%% Loading the Data in Matlab %%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Load data (in Matlab) - part 1
% to load the data for Question 3, Part 1, use the command:

% load('q3-sub.mat');

%this will load the struct "data" with the following fields:
% data = 
% 
%     raw: [9000x7 double]
%       n: 9000
%       d: 6
%       X: [9000x6 double]
%       Y: [9000x1 double]
      
      
% data.raw is all the data, each row is an observation (data point), each
%          column is a different physio variable; the last column is the
%          variable we want to predict;

% data.X   are the predictors (columns 1 though 6 from the raw data); 
%          they are 6-dimensional, with values in [1,5];

% data.Y   is the variable we want to predict; 0 or 1; (last column of the
%          raw data);


%% Load data - Question 3, Part 3
% to load the data for problem 4.3, use the command:

% load('q3-all.mat');

%this will load the struct "data" with the following fields:
% data = 
% 
%     raw: [9000x20 double]
%       n: 9000
%       d: 19
%       X: [9000x19 double]
%       Y: [9000x1 double]

%The description of the fields is the same as the above, except that now X
%has 19 dimensions; Y is again the last column of the raw data.


