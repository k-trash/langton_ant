loop = csvRead("../loop.csv");
loop_fft = fft(loop);

data_size = size(loop, '*');
f_data = (1:data_size/2) / data_size;

clf;
plot(f_data, abs(loop_fft(1:size(f_data,'*'))));
