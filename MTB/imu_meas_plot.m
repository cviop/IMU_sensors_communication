
clear nuc
nuc = serialport("/dev/tty.usbmodem14203", 230400);

buffer_len = 10000;
plot_len = 1000;
lim3Dplot = 2;




acc_buffer = NaN(3,buffer_len);

gyro_buffer = NaN(3,buffer_len);

mag_buffer = NaN(3,buffer_len);


figure(1)
tiledlayout(3,1)
nexttile
hold on
for i = 1:3
    accplot(i) = plot(1:plot_len, acc_buffer(i,1:plot_len));
end
hold off
nexttile
hold on
for i = 1:3
    gyroplot(i) = plot(1:plot_len, gyro_buffer(i,1:plot_len));
end
hold off
nexttile
hold on
for i = 1:3
    magplot(i) = plot(1:plot_len, mag_buffer(i,1:plot_len));
end
hold off


%% Plot 2 - 3D position based on values
figure(2)
plot3D_data = plot3(mag_buffer(1,:), mag_buffer(2,:), mag_buffer(3,:), ...
    "LineStyle","none","Marker","X","MarkerSize",4);
xlabel("X");ylabel("Y");zlabel("Z")
hold on

mag_direction_plot = plot3([0, 1], [0, 1], [0, 1], LineWidth=3);

% XZ proj
plotXZ_shadow = plot3(mag_buffer(1,:), lim3Dplot*ones(1,numel(mag_buffer(2,:))), mag_buffer(3,:));
% XY proj
plotXY_shadow = plot3(mag_buffer(1,:), mag_buffer(2,:), -lim3Dplot*ones(1,numel(mag_buffer(3,:))));
%ZY
plotZY_shadow = plot3(lim3Dplot*ones(1,numel(mag_buffer(1,:))), mag_buffer(2,:), mag_buffer(3,:));
axis("equal")
xlim([-lim3Dplot lim3Dplot])
ylim([-lim3Dplot lim3Dplot])
zlim([-lim3Dplot lim3Dplot])
grid on
grid minor
axis("vis3d")
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

    gyroact = zeros(3,1);
    for i = 1:3
        gyroact(i) = typecast(uint16(data(2*i-1+6)*2^8 + data(2*i+6)), 'int16');
    end

    magact = zeros(3,1);
    for i = 1:3
        magact(i) = typecast(uint16(data(2*i-1+12)*2^8 + data(2*i+12)), 'int16');
    end

    temp_act = typecast(uint16(data(19)*2^8 + data(20)), 'int16');

    %%Buffer update
    acc_buffer = circshift(acc_buffer, 1,2);
    acc_buffer(:,1) = double(accact)./16384;

    gyro_buffer = circshift(gyro_buffer, 1,2);
    gyro_buffer(:,1) = double(gyroact)./131;

    mag_buffer = circshift(mag_buffer, 1,2);
    mag_buffer(:,1) = double(magact)./1370;

    

    %%Plot update
    for i = 1:3
        accplot(i).YData = acc_buffer(i,1:plot_len);
    end

    for i = 1:3
        gyroplot(i).YData = gyro_buffer(i,1:plot_len);
    end

    for i = 1:3
        magplot(i).YData = mag_buffer(i,1:plot_len);
    end

    plot3D_data.XData = mag_buffer(1,:);
    plot3D_data.YData = mag_buffer(2,:);
    plot3D_data.ZData = mag_buffer(3,:);

    plotXZ_shadow.XData = mag_buffer(1,:);
    plotXZ_shadow.ZData = mag_buffer(3,:);

    plotXY_shadow.XData = mag_buffer(1,:);
    plotXY_shadow.YData = mag_buffer(2,:);

    plotZY_shadow.YData = mag_buffer(2,:);
    plotZY_shadow.ZData = mag_buffer(3,:);

    mag_direction_plot.XData = [0 mag_buffer(1,1)];
    mag_direction_plot.YData = [0 mag_buffer(2,1)];
    mag_direction_plot.ZData = [0 mag_buffer(3,1)];

    
    total_time = toc*1000;
    fprintf("read: %.2f, total: %.2f, comp: %.2f\n", read_time, total_time,total_time-read_time)
    
end
