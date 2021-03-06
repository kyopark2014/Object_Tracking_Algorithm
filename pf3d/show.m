close all
clear all;

load object.txt;
load estimate.txt;
x = load('px.txt');
y = load('py.txt');
z = load('pz.txt');

N = 200;

figure(1);
plot3(object(:,1),object(:,2),object(:,3),'b*');
hold;
plot3(estimate(:,1),estimate(:,2),estimate(:,3),'r.-');
legend('object','estimate',4);
%axis([-2 2 -2 2]);
grid;


figure(2);
plot3(object(:,1),object(:,2),object(:,3),'b-');
hold;
plot3(estimate(:,1),estimate(:,2),estimate(:,3),'r-');
legend('object','estimate',4);

color = 1;
for t=1:N
	if color==1
		plot3(x(t,:),y(t,:),z(t,:),'r.');
	elseif color == 2
		plot3(x(t,:),y(t,:),z(t,:),'b.');
	elseif color == 3
		plot3(x(t,:),y(t,:),z(t,:),'k.');
	elseif color == 4
		plot3(x(t,:),y(t,:),z(t,:),'c.');
	elseif color == 5
		plot3(x(t,:),y(t,:),z(t,:),'m.');
	end
	
	color = color+1;
	if color==6
		color = 1;
	end
end
grid;

figure(3);
plot(object(:,1),object(:,2),'b-');
hold;
plot(estimate(:,1),estimate(:,2),'r-');
legend('object','estimate',4);

color = 1;
for t=1:N
	if color==1
		plot(x(t,:),y(t,:),'r.');
	elseif color == 2
		plot(x(t,:),y(t,:),'b.');
	elseif color == 3
		plot(x(t,:),y(t,:),'k.');
	elseif color == 4
		plot(x(t,:),y(t,:),'c.');
	elseif color == 5
		plot(x(t,:),y(t,:),'m.');
	end
	
	color = color+1;
	if color==6
		color = 1;
	end
end
grid;

xlabel('x');
ylabel('y');
title('xy plane');

figure(4);
plot(object(1),object(3),'b-');
hold;
plot(estimate(1),estimate(3),'r-');
legend('object','estimate',4);

color = 1;
for t=1:N
	if color==1
		plot(x(t,:),z(t,:),'r.');
	elseif color == 2
		plot(x(t,:),z(t,:),'b.');
	elseif color == 3
		plot(x(t,:),z(t,:),'k.');
	elseif color == 4
		plot(x(t,:),z(t,:),'c.');
	elseif color == 5
		plot(x(t,:),z(t,:),'m.');
	end
	
	color = color+1;
	if color==6
		color = 1;
	end
end
grid;
xlabel('x');
ylabel('z');
title('xz plane');

figure(5);
plot(object(2),object(3),'b-');
hold;
plot(estimate(2),estimate(3),'r-');
legend('object','estimate',4);

color = 1;
for t=1:N
	if color==1
		plot(y(t,:),z(t,:),'r.');
	elseif color == 2
		plot(y(t,:),z(t,:),'b.');
	elseif color == 3
		plot(y(t,:),z(t,:),'k.');
	elseif color == 4
		plot(y(t,:),z(t,:),'c.');
	elseif color == 5
		plot(y(t,:),z(t,:),'m.');
	end
	
	color = color+1;
	if color==6
		color = 1;
	end
end
grid;
xlabel('y');
ylabel('z');
title('yz plane');


load mn_th.txt;
load mn_ph.txt;
figure(6)  % dtheta
plot(mn_th*180/pi);
grid;
title('theta');

figure(7) % dphi
plot(mn_ph*180/pi);
grid;
title('phi');
