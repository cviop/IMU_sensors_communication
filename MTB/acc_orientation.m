
clear nuc
nuc = serialport("/dev/tty.usbmodem14203", 230400);

buffer_len = 10000;
plot_len = 1000;
lim3Dplot = 2;



acc_buffer = NaN(3,buffer_len);
phi_est = NaN(3,buffer_len);
theta_est = NaN(3,buffer_len);




figure(1)
hold on
for i = 1:3
    accplot(i) = plot(1:plot_len, acc_buffer(i,1:plot_len));
end
hold off

figure(2)
phiplot = plot(1:plot_len, phi_est(1:plot_len));
hold on
thetaplot = plot(1:plot_len, theta_est(1:plot_len));
hold off





tic
while(1)
    
    %% accel(6)gyro(6)mag(6)temp(2) - 20 bytes
    
    while((read(nuc, 1, "uint8")))
    end
    fprintf("dt = %.5f\n", toc*1000);
    tic
   %%Parsing
    data = read(nuc, 20, "uint8"); 
    data;
    read_time = toc*1000;

    accact = zeros(3,1);
    for i = 1:3
        accact(i) = typecast(uint16(data(2*i-1)*2^8 + data(2*i)), 'int16');
    end

    %%Buffer update
    acc_buffer = circshift(acc_buffer, 1,2);
    acc_buffer(:,1) = double(accact)./16384;

    phi_est = real(atan(acc_buffer(2,:)./acc_buffer(3,:)));
    theta_est = real(asin(acc_buffer(1,:)));


    %%Plot update
    for i = 1:3
        accplot(i).YData = acc_buffer(i,1:plot_len);
    end
    phiplot.YData = phi_est(1:plot_len);
    thetaplot.YData = theta_est(1:plot_len);


    
    total_time = toc*1000;
    fprintf("read: %.2f, total: %.2f, comp: %.2f\n", read_time, total_time,total_time-read_time)
    
end
