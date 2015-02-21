data = load('ll_graph.txt');
plot(data(:,1), data(:,2));
title('log likelihood vs amount of missing information');
xlabel('%age of missing information');
ylabel('log likelihood of data');

%ML for part a = -8044.14