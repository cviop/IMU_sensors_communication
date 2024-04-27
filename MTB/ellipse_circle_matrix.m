

%%ellipse creation

nelements = 20;

t = linspace(0,2*pi,nelements);

a = 1;
b = 0.5;
ang = 0;

cent_off_x = 4;
cent_off_y = 3;

xxt = cos(t);
yyt = sin(t);
circle = [xxt;yyt];
R = [a*cos(ang) -a*sin(ang);b*sin(ang) b*cos(ang)];

x = R*circle+[cent_off_x; cent_off_y];



corrected = x-[xcenter; ycenter];
corrected = [-1/aaxis 0; 0  -1/baxis]*corrected;

figure(5)
plot(x(1,:), x(2,:))
hold on
plot(0,0,Marker="x", MarkerSize=20)
plot(corrected(1,:), corrected(2,:))
for m = 1:nelements
plot([x(1,m) corrected(1,m)], [x(2,m) corrected(2,m)],Marker="x",LineStyle="-")
end
hold off
axis equal
xlim([-10 10])
ylim([-10 10])
grid on