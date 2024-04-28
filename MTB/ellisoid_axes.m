% for ii=0:0.1:5

c = [0; 0; 0]; % Ellipsoid center
%c = [0;0;0]
r = [3; 2; 5]; % Semiaxis radii

[x,y,z] = ellipsoid(c(1),c(2),c(3),r(1),r(2),r(3),20);
D = [x(:),y(:),z(:)];


theta_ang = 0.25*pi;
phi_ang = 0.0*pi;

Rx = [1 0 0; 0 cos(phi_ang) -sin(phi_ang); 0 sin(phi_ang) cos(phi_ang)];
Ry = [cos(theta_ang) 0 sin(theta_ang); 0 1 0; -1*sin(theta_ang) 0 cos(theta_ang)];

D = D*Rx;
D = D*Ry;


[~,~,beta] = svd(D, "econ")
beta(:,end)

ellip_axes(:,1) = beta(:,1)*sig(1);

D_corrected = D*beta;


figure(1)
plot3(D(:,1),D(:,2),D(:,3),"LineStyle","none","Marker","X","MarkerSize",8)
hold on
plot3(D_corrected(:,1),D_corrected(:,2),D_corrected(:,3),"LineStyle","none","Marker","X","MarkerSize",8)

plot3([0 5], [0 0], [0 0])
plot3([0 0], [0 5], [0 0])
plot3([0 0], [0 0], [0 5])
plot3([0 beta(1,1)],[0 beta(2,1)],[0 beta(3,1)])
plot3([0 beta(1,2)],[0 beta(2,2)],[0 beta(3,2)])
plot3([0 beta(1,3)],[0 beta(2,3)],[0 beta(3,3)])
grid(gca,"on")
axis equal
xlabel("uT")
ylabel("uT")
zlabel("uT")
xlim([-10 10])
ylim([-10 10])
zlim([-10 10])
hold off
pause(0.2)
% end