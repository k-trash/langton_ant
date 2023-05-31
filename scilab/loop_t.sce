loop = csvRead("../loop.csv");
loop_fft = fft(loop);

data_size = size(loop, '*');
f_data = data_size ./ (1:data_size/2);

clf;
plot(f_data, abs(loop_fft(size(f_data,'*'):-1:1)));
