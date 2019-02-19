%
%
% Length: 4.27m canal is 0.01m from river and 0.02m wide
% Canal length side: 4.114m
% 
% R1inside = 0.2m R1outside = 0.3m
% R2inside = 0.3m R2outside = 0.4m
% R3inside = 0.2m R3outside = 0.3m
% Three canal sections
% Bottom canal section 3 is 0.02m from top
% Weir 3 at beginning second bend 1.692m; drop 
% Weir 2
% Weir 1
% 
%
% River, Canal, Hele Shaw moor, Hele-Shaw reservoir, city street and sewer grid, Table-top flood model
%
% (i) Canal: s=0,...,Lc2 (Lock 2), s=Lc2, ..., Lc1 (lock 1 into river)
% (a) Simple kinetic model with variables: h1=h1(t) in first canal section and h2=h2(t) in section canal section
% (b) Shallow water model 1D or 2D
%
% Solid wall at s=0.
% 
nfac = 3.5583;		  
g = 9.81;          % m/s^2
Lc2 = 0.9*nfac;    % distance along canal of second lock & length second canal section in m
Lsec2 = Lc2;       % length second canal section in m
Lc1 = 1*nfac;      % distance along canal of first lock in m
Lsec1 = Lc1-Lc2;   % length first canal section
wc = 0.02;         % width of canal in m
Cf = (2/3)^(3/2);
Pw2 = 0.0125;      % depth weir in canal
Pw1 = 0.01;
% (ii) River: x=0...Lx; variables h=h(x,t)			  			  
% (a) simple river slope approximation: dh/dt	+d Q(h)/dx = f			  
% Q(h) = h (wr*h/(2*h+wr))^2/3 sqrt(-db/dx)/Cm (simple rectangular river profile)
% wr*h/(2*h+wr) is area/wetted perimeter with wr width of river and h its depth
% (b) shallow water equations 1D
%
% 			  
Lx = 1.2*nfac; % m
dmean = 0.04; % 0.01*nfac; % was 0.04        % mean height difference across river bed in m
dbdxmean = -dmean/Lx; % mean sloep river bed
Cm = 0.02;            % Manning coefficient, see Table in Munson and ...; this is for glass
wr = 0.05;            % width of square river bed
Nx = 100;
dx = Lx/Nx;
xx = 0:dx:Lx;
hr0 = 0.01;
Kk = xx(2:Nx+1)-xx(1:Nx);
xxm  = 0.5*(xx(2:Nx+1)+xx(1:Nx));
hr = 0*xx(1:Nx); % hr river depth defined as finite volumes, so one less than no grid points
Ar = wr*hr; % cross-sectional area for ractangular case
Vr = 0*hr;
bx = dmean*(Lx-xxm)/Lx;
canalmaxdepth = 0.0175;
Hcc2 = 0.06; % 0.04; % 0.06;    % dike height along canal segment 2, canal max depth 0.0175m before overflow in river
Hcc1 = 0.032; % 0.022; % 0.032; % dike height along canal segment 1, canal max depth 0.0175m before overflow in river
Hcx = Hcc2*0.5*(1+sign(Lc2-xxm))+Hcc1*0.5*(1+sign(xxm-Lc2));
Hcxb = Hcx-canalmaxdepth;
% 
% 
%			  			  			  
% (iii) Moor water inflow in canal at s=Lv<Lc2 gam-fraction and river x=Lv (1-gam) -fraction with gam=gam(t) <=1	 
%	Orthogonal to canal
%       Option a) canal bottom coincide with Hele-Shaw moor bottom such that hm(1) = hc1
% hm = hm(y,t) for y=0,...,Ly
%			  
Ly = nfac*0.4; % m
wv = 0.01; % width Hele-Shaw moor cell in m
Ny = 20;
dy = Ly/Ny;
yy = 0:dy:Ly;  % Regular FD or FV grid
hm = 0*yy;     % Define moor depth variable on grid
sigm = 0.8;    % fraction of moor pores filled
sigm0 = 0.1;   % fraction of water remaining in moor pores after water has seeped out
sigme = sigm;  % 
mpor = 0.3;    % porosity moor
nu = 10^(-6);  % viscosity water m^2/s
kperm = 10^-8; % permeability
alph = kperm/(mpor*nu*sigm);
Rain0 = 0.00175; % m/s
Rain0 = 0.002; % 0.002 works m/s
Rain = Rain0;
%
TimeUnit = 10; % 9 hrs from Kildwick till Armley times 3 is 27hrs; 12-20s across
Train = Lc2*wc*0.01/(Ly*wv*Rain);
gam = 0.0;
%
% 
Vrate = Ly*wv*Rain0*[1,2,4,8,16]*TimeUnit*1000; % flow rates in liters/TimeUnit
%
%
% (iv) Reservoir Hele-Shaw cell with adjustable weir
%
Lrer = 0.6*nfac;   % m
nrer = ceil(Lrer/dx);
wres = 0.01;  % m	
Lyy  = 0.4;  % length reservoir in m	
Pwr  = 0.10; % weir height
hres = 0;
%	  
% (v)  canal weirs at s=Lc1 and s=Lc2 critical flow
%
%			  
Lv = 0.4*nfac; % inflow of water off the Hele-Shaw moor in m 
nxLv = ceil(Lv/dx);    % grid box in which moor water is added in the river
nxLc1 = ceil(Lc1/dx);  % grid box for regular grid in which canal water segment one is added
%			  
Tend = 100*TimeUnit;
dtmeas = 5;
tmeas = dtmeas;
% nmeas = dtmeas/dt;
%
%
% Initialisation
%
%
figure(11); clf;
tijd = 0;
ini = 1
switch ini
case 1 % Mass check starting from absolute drought conditions and then it starts raining
  % canal sections
  h1c = 0;
  h2c = 0;
  % Hele-Shaw moor
  hm = 0*yy;
  % River
  Ar = hr0*wr*ones(1,Nx);
end
figure(12); clf;
hro = hr(1);
hrLo = hr(nxLc1);
tijdo = tijd;
%
%
% Time loop
%
%
nc1 = 0;
nc2 = 0;
nc4 = 0;
nc8 = 0;
nc16 = 0;
nt = 0;
nswitch = 0;
nswitch2 = 1;
tunit = 1;
nrain = 4;
R(1:Ny+1) = nrain*Rain0*ones(1,Ny+1);
R2(1:Ny+1) = nrain*Rain0*ones(1,Ny+1);
nrainc = 1;
ncc = 0;
while (tijd  <= Tend) % All simple explicit time stepping
  % (3, 7, 5, 1)/16; [0,3]/16, [3,10]/16, [10,15]/16, [15,16]/16		       
  switch nrainc
  case 1
   while (tijd >= tunit)
     ncc = ncc+1;
     tunit  = tunit+TimeUnit;
     trand1 = rand; trand2 = rand;
     if (trand1 < 3/16)
       nrain = 1; % Rain0
     else
       if (trand1 < 10/16)
         nrain = 2; % 2*Rain0
       else
         if (trand1 < 15/16)
           nrain = 4; % 3*Rain0
         else
           nrain = 8; % 4*Rain0
         end
       end
     end
     if (trand2 < 3/16)
       nloc = 1; % Reservoir
       R(1:Ny+1) = 0*Rain0*ones(1,Ny+1);
       R2(1:Ny+1) = nrain*Rain0*ones(1,Ny+1);
       not = nrain;
     else
       if (trand2 < 10/16)
         nloc = 2; % Moor and reservoir
         R(1:Ny+1) = nrain*Rain0*ones(1,Ny+1);
         R2(1:Ny+1) = nrain*Rain0*ones(1,Ny+1);
         not = 2*nrain;
       else
         if (trand2 < 15/16)
           nloc = 3; % Moor
           R(1:Ny+1) = nrain*Rain0*ones(1,Ny+1);
           R2(1:Ny+1) = 0*Rain0*ones(1,Ny+1);
           not = nrain;
         else
           nloc = 4; % No rain in catchment
           R(1:Ny+1) = 0*Rain0*ones(1,Ny+1);
           R2(1:Ny+1) = 0*Rain0*ones(1,Ny+1);
           not = 0;
         end
       end
     end
     switch not
     case 0
       nc1 = nc1+1;
     case 2
       nc2 = nc2+1;
     case 4
       nc4 = nc4+1;
     case 8
       nc8 = nc8+1;
     case 16
       nc16 = nc16+1;
     end
     nchisto(ncc) = not;
     fprintf('tunit: %g nrain: %d noloc: %d not:%d\n',tunit,nrain,nloc,not);
   end
  case 2
   if (tijd > Train)
     R(1:Ny+1) = Rain0*ones(1,Ny+1); % 1mm/s
     R2(1:Ny+1) = Rain0*ones(1,Ny+1); % 1mm/s
   else
     R(1:Ny+1) = Rain0*ones(1,Ny+1);
     R2(1:Ny+1) = Rain0*ones(1,Ny+1); % 1mm/s
   end
  end
  %
  hmg = max(0.5*(hm(3:Ny+1)+hm(2:Ny)+0.5*(hm(2:Ny)+hm(1:Ny-1))));
  hmg = max(hmg,hm(Ny)+hm(Ny+1));
  Vr = (wr*hr(1:Nx)./(2*hr(1:Nx)+wr)).^(2/3)*sqrt(-dbdxmean)/Cm; % velocity
  dt2 = dx/max(abs(Vr));
  dt = dy^2/(alph*g*max(hmg,0.001));
  dt = min(dt,dt2);
  tijd = tijd+dt;
  nt=nt+1;
  %
  % Update two canal sections
  %
  h2co = h2c; h1co = h1c;
  tesfac = 0.5*(1+sign(h1co-hr(nxLc1)));
  tesfac = 1;
  Qc2 = wc*sqrt(g)*Cf*max(h2co-Pw2,0)^(3/2);         % units: m m^(1/2)/s m^(3/2) = m^3/s
  Qc1 = wc*sqrt(g)*Cf*max(h1co-Pw1,0)^(3/2)*tesfac; % units: m m^(1/2)/s m^(3/2) = m^3/s
  h2c = h2co+(dt/(Lc2*wc))*( gam*mpor*sigme*wv*alph*g*0.5*(hm(2)^2-h2co^2)/dy-Qc2 ); % first order approximation to flux
  h1c = h1co+(dt/(Lc1*wc))*( Qc2-Qc1 );
  tes = 0.5*(1+sign(bx(1:Nx)+hr(1:Nx)-Hcxb(1:Nx)-h1co));
  h1c = h1c+nswitch*(dt/(Lc1*wc))*Cf*sqrt(g)*max(bx(1:Nx)+hr(1:Nx)-Hcc1,0).^(3/2).*(1+sign(xxm-Lc2)).*tes*0.5*transpose(Kk); % addition of river water wrong
  % Update Hele-Shaw moor
  %
  num = dt/dy^2;
  %
  % first grid point
  % Option a) canal bottom coincide with Hele-Shaw moor bottom such that hm(1) = hc1; b) hm(1) = hm(1)+num;
  hmo = hm;
  hm(1) = h2co;
  % interior points
  hm(2:Ny) = hmo(2:Ny)+num*alph*g*(0.5*(hmo(3:Ny+1)+hmo(2:Ny)).*(hmo(3:Ny+1)-hmo(2:Ny))-0.5*(hmo(2:Ny)+hmo(1:Ny-1)).*(hmo(2:Ny)-hmo(1:Ny-1)))+dt*R(2:Ny)/(mpor*sigme);
  % wall at last grid point so no flux
  hm(Ny+1) = hmo(Ny+1)+num*alph*g*(hmo(Ny)+hmo(Ny+1))*(hmo(Ny)-hmo(Ny+1))+dt*R(Ny+1)/(mpor*sigme);
  %
  % Update reservoir hres(t)
  %
  hreso = hres;
  Qresw = Cf*wres*sqrt(g)*max(hreso-Pwr,0)^(3/2);
  hres = hreso+dt*R2(1)-(dt/(Lyy*wres))*Qresw;
  %
  % Update river
  %
  Ar0 = hr0*wr; % in m hrofunc(tijd,wr);
  Aro = Ar;
  Qh12(1) = Ar0*(hr*wr/(2*hr+wr))^(2/3)*sqrt(-dbdxmean)/Cm;
  Qh12(2:Nx+1) = Aro(1:Nx).*(wr*hr(1:Nx)./(2*hr(1:Nx)+wr)).^(2/3)*sqrt(-dbdxmean)/Cm; % upwind
  Ar(1:Nx) = Aro(1:Nx)-dt*(Qh12(2:Nx+1)-Qh12(1:Nx))./Kk;
  % Flooding river terms
  Ar(nxLv) = Ar(nxLv) + dt*((1-gam)*mpor*sigme*wv*alph*g*0.5*(hmo(2)^2-h2co^2)/dy)/Kk(nxLv); % addition of moor water
  Ar(nrer) = Ar(nrer) + dt*Qresw/Kk(nrer);                                                            % addition of reservoir water
  Ar(nxLc1)= Ar(nxLc1)+ nswitch2*dt*Qc1/Kk(nxLc1);                                           % addition of canal water
  %
  Ar(1:Nx) = Ar(1:Nx) - nswitch*dt*Cf*sqrt(g)*max(bx(1:Nx)+hr(1:Nx)-Hcc1,0).^(3/2).*(1+sign(xxm-Lc2))*0.5.*tes; % addition of overflown canal banl wrong
  %
  hr = Ar/wr;
  Vr = (wr*hr(1:Nx)./(2*hr(1:Nx)+wr)).^(2/3)*sqrt(-dbdxmean)/Cm; % velocity
  %
  %
  % Plotting:
  %
  % if (mod(nt,nmeas)==0)
  while (tijd >= tmeas) 
   tmeas = tmeas+dtmeas;
   % nt
   figure(11);
   subplot(2,2,1);
   plot(tijd,h1c,'ok','linewidth',1); hold on;
   plot(tijd,h2c,'xb','linewidth',1); hold on;
   plot(tijd,hres/10,'*r','linewidth',1); hold on;
   xlabel('t (s)');
   ylabel('h_{1c}(t) (black), h_{2c}(t) (blue), h_{resr}(t)/10','linewidth',1); hold on;
   %
   subplot(2,2,2);
   plot([tijdo,tijd],[hro,hr(1)],'b','linewidth',1); hold on;
   plot([tijdo,tijd],[hrLo,hr(nxLc1)],'k','linewidth',1); hold on;
   % axis([0 Tend 0 max(h2c)]);
   xlabel('t (s)');
   ylabel('h(0,t), h(L_{1c} (black),t)');
   %
   subplot(2,2,3);
   plot(yy,hm,'-','linewidth',2);
   xlabel('y (m)');
   ylabel('h_m(y,t)');
   subplot(2,2,4);
   plot(tijd,R(1)/Rain0,'ok','linewidth',1); hold on;
   plot(tijd,R2(1)/Rain0,'xb','linewidth',1); hold on;
   plot(tijd,(R(1)+R2(1))/Rain0,'*r','linewidth',1); hold  on;
   xlabel('t (s)');
   ylabel('Rain unit moor (black), res., both (red) ');
   %
   figure(12);
   subplot(2,1,1);
   plot(xxm,Vr/5,'-k','linewidth',2); hold on;
   plot(xxm,hr,'-b','linewidth',2); hold off;
   xlabel('x (m)');
   ylabel('h_r(x,t) (blue), V_r(x,t)/5 (black)');
   subplot(2,1,2);
   plot(xxm,bx,'-r','linewidth',3); hold on
   plot(xxm(1:nxLc1),Hcx(1:nxLc1),'-r','linewidth',3);  hold on
   plot(xxm(1:nxLc1),Hcxb(1:nxLc1),'--b','linewidth',2);  hold on
   Hcxb12 = (Hcc2+h2c)*0.5*(1+sign(Lc2-xxm(1:nxLc1)))+(Hcc1+h1c)*0.5*(1+sign(xxm(1:nxLc1)-Lc2))-canalmaxdepth;
   plot(xxm(1:nxLc1),Hcxb12(1:nxLc1),'-b','linewidth',2);  hold on
   plot(xxm,bx+hr,'-k','linewidth',2); hold off
   xlabel('x (m)');
   ylabel('b(x), b(x)+h_r(x,t), H_{dike}(x) ');
   %
   drawnow;
   hro = hr(1);
   hrLo = hr(nxLc1);
   tijdo = tijd;
  end
end
figure(13);
ntot = Tend/TimeUnit;
histogram(nchisto);

