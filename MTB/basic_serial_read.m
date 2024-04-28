clear all
 clear data


buffer_len = 10000;
plot_len = 1000;

lim3Dplot = 2000;
 
% 

magX_buffer = NaN(1,buffer_len);
magY_buffer = NaN(1,buffer_len);
magZ_buffer = NaN(1,buffer_len);
magLen_buffer = NaN(1,buffer_len);
a = 0;

%% Plot 1 - basic rolling graph xyz
figure(1)
xplot = plot(1:plot_len,magX_buffer(1:plot_len));
hold on
yplot = plot(1:plot_len,magY_buffer(1:plot_len));
zplot = plot(1:plot_len,magZ_buffer(1:plot_len));
lenplot = plot(1:plot_len,magLen_buffer(1:plot_len));
hold off
legend({"X" "Y" "Z" "length"})


%% Plot 2 - 3D position based on values
figure(2)
plot3D_data = plot3(magX_buffer, magY_buffer, magZ_buffer);
xlabel("X");ylabel("Y");zlabel("Z")

hold on
% XZ proj
plotXZ_shadow = plot3(magX_buffer, lim3Dplot*ones(1,numel(magY_buffer)), magZ_buffer);
% XY proj
plotXY_shadow = plot3(magX_buffer, magY_buffer, -lim3Dplot*ones(1,numel(magZ_buffer)));
%ZY
plotZY_shadow = plot3(lim3Dplot*ones(1,numel(magX_buffer)), magY_buffer, magZ_buffer);
axis("equal")
xlim([-lim3Dplot lim3Dplot])
ylim([-lim3Dplot lim3Dplot])
zlim([-lim3Dplot lim3Dplot])
grid on
grid minor
axis("vis3d")
hold off

%% Plot 3 - visualisation of mag. vector
figure(3)
mag_direction_plot = plot3([0 0], [0 0], [0 800]);

axis("equal")
xlim([-lim3Dplot lim3Dplot])
ylim([-lim3Dplot lim3Dplot])
zlim([-lim3Dplot lim3Dplot])
grid on
grid minor
axis("vis3d")
xlabel("X");ylabel("Y");zlabel("Z")
title("Magnetic vector orientation")


%%three 2D plots

% figure(3)
% tiledlayout(2,2)
% nexttile
% plot(magX_buffer, magY_buffer)
% xlim([-800 800])
% ylim([-800 800])
% nexttile
% plot(magY_buffer, magZ_buffer)
% xlim([-800 800])
% ylim([-800 800])
% nexttile
% plot(magZ_buffer, magY_buffer)
% xlim([-800 800])
% ylim([-800 800])




nuc = serialport("COM6", 9600);
while(1)
    tic
    while((read(nuc, 1, "uint8")))
    end
    data = read(nuc, 6, "uint8");    

    data;
    magXact = typecast(uint16(data(1)*2^8 + data(2)), 'int16');
    magZact = typecast(uint16(data(3)*2^8 + data(4)), 'int16');
    magYact = typecast(uint16(data(5)*2^8 + data(6)), 'int16');
    magLenAct = sqrt((double(magXact)^2)+(double(magYact)^2)+(double(magZact)^2));

    %%fprintf("raw: %d %d %d %d %d %d, Mx: %d, My: %d, Mz: %d\n", data, magXact, magYact, magZact)
    
    magX_buffer = circshift(magX_buffer, 1,2);
    magX_buffer(1) = magXact;
    magY_buffer = circshift(magY_buffer, 1,2);
    magY_buffer(1) = magYact;
    magZ_buffer = circshift(magZ_buffer, 1,2);
    magZ_buffer(1) = magZact;
    magLen_buffer = circshift(magLen_buffer, 1, 2);
    magLen_buffer(1) = magLenAct;

    % plots update
    
    xplot.YData = magX_buffer(1:plot_len);
    yplot.YData = magY_buffer(1:plot_len);
    zplot.YData = magZ_buffer(1:plot_len);
    lenplot.YData = magLen_buffer(1:plot_len);

    plot3D_data.XData = magX_buffer;
    plot3D_data.YData = magY_buffer;
    plot3D_data.ZData = magZ_buffer;

    plotXZ_shadow.XData = magX_buffer;
    plotXZ_shadow.ZData = magZ_buffer;

    plotXY_shadow.XData = magX_buffer;
    plotXY_shadow.YData = magY_buffer;

    plotZY_shadow.YData = magY_buffer;
    plotZY_shadow.ZData = magZ_buffer;

    mag_direction_plot.XData(2) = magXact;
    mag_direction_plot.YData(2) = magYact;
    mag_direction_plot.ZData(2) = magZact;

    %%fprintf("%f\n", sqrt(double(magXact)^2+double(magZact)^2+double(magZact)^2))

    
end




