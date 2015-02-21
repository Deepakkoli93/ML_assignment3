function p= q5d(num,ureduced)
	while(length(num) < 5)
		num = strcat('0',num);
	end
x_i = reshape(double(imread(strcat('data/face',num,'.pgm'))),361,1);
imshow(reshape(uint8(x_i(:,:)),19,19));
z_i = ureduced' * x_i;
p_i = ureduced * z_i;
figure();
imshow(reshape(uint8(p_i(:,:)),19,19));
p = 1;
end
