function a = visualize(index)
global X;
arr = X;
new_arr = zeros(1,784);
	global pixels;
for i=1:length(arr(index,:))
	new_arr(pixels(1,i)) = arr(index,i);
end
colormap(gray);
image_mat = reshape(new_arr, 28, 28);
imagesc(transpose(image_mat));
