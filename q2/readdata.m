f = fopen('data/digitdata.txt');
line = fgetl(f);
line = strsplit(line, ' ');
global pixels;
pixelsx = zeros(1,157);
for i=1:length(line)
	t = line{i};
	t = t(:,7:length(t)-1);
	t = str2num(t);
	pixels(i) = t;
end
n = 157;
global X;
X = [];
num=0;
while ~feof(f)
	line = fgetl(f);
	line = strsplit(line, ' ');
	line = line(:,2:end);
	temp = zeros(1, n);
	for i=1:n
		line{i};
		temp(i) = str2num(line{i});
	end
	%num+1
	X = [X;temp];
end

m = size(X,1);
fprintf('read the data\n');

f2 = fopen('data/digitlabels.txt');
line = fgetl(f2);
global y;
y = zeros(m,1);
i=1;
while ~feof(f2)
	line = fgetl(f2);
	line = strsplit(line, ' ');
	line = line(:,2:end);
	y(i) = str2num(line{1});
	i = i+1;

end