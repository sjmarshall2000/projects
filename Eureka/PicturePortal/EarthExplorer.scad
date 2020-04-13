D=4.5*25.4;//mm
Wall=2;//mm
DMount=22.5;//mmr
RBolt=22;//mm
DBolt=3.5;//mm
DSeed=10;//mm
PipeID=.75*25.4;//mm
curveRes = 100;

module wireLoop(up=5,LoopDiameter=7/*mm*/,WireDiameter=2/*mm*/) {
N=16;
C=LoopDiameter*PI;
H=C*1.2/N;
    hull() {
      translate([-up,(LoopDiameter-WireDiameter)/2,0])
        cylinder(d=WireDiameter,h=30,$fn=curveRes,center=true);
      translate([-up,-(LoopDiameter-WireDiameter)/2,0])
        cylinder(d=WireDiameter,h=30,$fn=curveRes,center=true);
    }
}

module setScrew() {
    AxleD=19;//mm
    boltD=4;//mm
    boltFlat=9;//mm
    boltNutT=4;//mm
    boltHoleT=12;//mm
    MotorAxleD=25.4*5/16;//mm
    MotorAxleT=25.4*19/32;//mm
     translate([0,MotorAxleD/2+boltNutT/2,-AxleD/3]){
            cube([boltFlat,boltNutT,boltFlat*1.4],center=true);
            translate([0,AxleD/4,0])  
              rotate([90,0,0])
                cylinder(d=boltD,h=AxleD/2,center=true,$fn=curveRes);
     }  
}

 module wireWheel(){
  H=25.4*5/8;
  difference(){  
      cylinder(d=22.4,h=H,$fn=curveRes);
    translate([0,0,-.5])  
      cylinder(h=H+1,d=8+.5,$fn=curveRes);
    translate([0,-.95,12])  
          setScrew();
  }
}

module potAttach(outerDiameter=25.4, innerDiameter=25.4*7/32+.5) {
  H=25.4*1/4;
  difference(){  
    cylinder(d=outerDiameter,h=H,$fn=curveRes); 
    #cylinder(h=H,d=innerDiameter,$fn=curveRes);
  }
}

module potSide(includeRod = true, outerDiameter=25.4, innerDiameter=25.4*7/32+.5) {
  difference() {
    potAttach(outerDiameter, innerDiameter); 
    if(includeRod){
        rotate([90,90,0]) 
            wireLoop(up=25.4*2/16,LoopDiameter=13.3);
    }
  }
}
module motorSide() {
  difference() {
    wireWheel();
    translate([0,0,3])
    rotate([90,90,90]) 
      wireLoop(up=25.4*5/8/2,LoopDiameter=13.3);
  }
}


module glassSlide() {
Offset=12;
Width=20;
Wall=3;
boltD=4;
resize=1.2;

difference() {
  translate([0,0,Offset/2])
    cube([Wall,Width,Offset*1.25],center=true);
  rotate([0,90+15,0])
    scale([resize,resize,resize])
      wireLoop(up=Offset*.65,LoopDiameter=13.3,WireDiameter=3);
}

translate([-Offset/2-Wall/2,0,0])
  difference() {
    rotate([0,90,0])
      cube([Wall,Width,Offset*1.25],center=true);
    translate([0,Width/4,0])  
      cylinder(d=boltD,h=Wall+.5,center=true,$fn=curveRes);  
    translate([0,-Width/4,0])  
      cylinder(d=boltD,h=Wall+.5,center=true,$fn=curveRes);  
  }
}
module potentiometerMotorMount(){
potSide(false, outerDiameter=22.4);
translate([0, 0, (25.4*5/8) +(25.4*1/4)]) 
    rotate([180,0,0])
        motorSide();    
}
//glassSlide();
potentiometerMotorMount();
//translate([0,30,0])
scale([1,1,1.1]){
    //potSide(innerDiameter = 6);
}
//potAttach();