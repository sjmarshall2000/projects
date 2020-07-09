//Wood
woodThickness = 5.5;//mm
holeDiameter = 38.42;//mm ~1.5inch
woodScrewDiameter=3;//arbitrary, to be measured
//MTG LED
ledThickness= 1.14;
ledHoleDiameter= 1.588 * 2; //results in ~3mm ~metric m3 screw
screwDist = 19.050; // distance between screw centers in each pair
//Printed Mount
screwOffsetRatio = 0.75;//how far down bar the screw shows up, 1 is at tip, 0, at base
printThickness=5;//arbitrary //thicker lets screw self-tap
overhang = 15;//how far print extends over wood on each side
barThickness = 10;
barLength=holeDiameter + (2 * overhang);
centerDiameter=28; //changed from 30 -> 28 for time/size
minRadScrew = 5;//how much wider plastic must surround screw
//Misc
$fn = 100;

module wood(sideLength= 100){
    translate([0,0,woodThickness/2]){
        difference(){
            cube([sideLength,sideLength, woodThickness], center=true);
            cylinder(d=holeDiameter, h=woodThickness + 1, center=true);
        }
    }
}

module mtgScrew(length, rad = ledHoleDiameter/2, addCubes=true){
    //rad passed as parameter for overriding
    cylinder(length, r=rad, center = true);
    translate([rad/2, 0, 0]){
        if(addCubes){
            cube([rad,rad*2, length], center=true);
        }
    }
}
module screwSet(screwLength, rad = ledHoleDiameter/2, addCubes = true){
    //distance between centers of 
    //screw hole pairs: 19.050mm
    for(i = [0:6]){
        rotate([0,0,60 * i]){
            translate([screwDist / 2, 0, 0]){
                mtgScrew(screwLength, rad, addCubes);
            }
        }
    }
}
module mtgBase(thickness){
    //each bar is rectangle of 
    //length    19.900mm
    //width     7.823mm
    //
    l = 19.900;
    w = 7.823;
    
    rotate([0,0,0]){
       cube([w,l, thickness], center = true);
    }
    rotate([0,0,60]){
        cube([w,l, thickness], center=true);
    }
    rotate([0,0,-60]){
        cube([w,l, thickness], center=true);
    }
}
module mtg(thickness=ledThickness){ 
    translate([0,0,thickness/2]){
        cube([5,5,thickness + 0.1], center=true);
        difference(){
            mtgBase(thickness);
            screwSet(thickness + 1);
        }
    }
}
module wireHolder(){
    union(){
        difference(){
            intersection(){
                cylinder(d=centerDiameter+10, h=printThickness);
                translate([0, -10, 2])cube([20, centerDiameter, printThickness+2], center=true);
            }
            translate([0,0,-1])cylinder(d=centerDiameter + 3, h=printThickness+2);
        }
        translate([-20/2, -centerDiameter/2, 0])
                cube([printThickness/2,5, printThickness]);
    }
    
}
module mount(){
    translate([0,0,printThickness/2]){
        difference(){
            union(){ //everything in here gets screw holes punched out
                //main bar
                cube([barLength, barThickness, printThickness], center=true);
                //center cylinder
                cylinder(d=centerDiameter, h=printThickness, center=true);
                //extra safety cylinders
                translate([(holeDiameter/2)+(overhang * screwOffsetRatio),0,0]){
                    cylinder(d=woodScrewDiameter+(minRadScrew*2), h=printThickness, center=true);
                }
                translate([-((holeDiameter/2)+(overhang * screwOffsetRatio)),0,0]){
                    cylinder(d=woodScrewDiameter+(minRadScrew*2), h=printThickness, center=true);
                }
//                translate([0,0,-printThickness/2]) wireHolder();
            }
            screwSet(printThickness + 1, addCubes=false);
            
            translate([(holeDiameter/2)+(overhang * screwOffsetRatio),0,0]){
                cylinder(d=woodScrewDiameter, h=printThickness + 1, center=true);
            }
            translate([-((holeDiameter/2)+(overhang * screwOffsetRatio)),0,0]){
                cylinder(d=woodScrewDiameter, h=printThickness + 1, center=true);
            }
        }
    }
}
/*
translate([0,0,woodThickness]){
    mount();
}
#wood(200);
*/


//mtg();
//#wood(200);
mount();
