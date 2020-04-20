

module mtgScrew(length, rad = 1.588, addCubes=true){
    //rad passed as parameter for overriding
    cylinder(length, r=rad, center = true,$fn=50);
    translate([rad/2, 0, 0]){
        if(addCubes){
            cube([rad,rad*2, length], center=true);
        }
    }
}
module screwSet(screwLength, rad = 1.588, addCubes = true){
    //distance between centers of 
    //screw hole pairs: 19.050mm
    screw_dist = 19.050;
    for(i = [0:6]){
        rotate([0,0,60 * i]){
            translate([screw_dist / 2, 0, 0]){
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
module mtg(thickness, depth){ 
    #cube([5,5,thickness + 0.1], center=true);
    difference(){
        mtgBase(thickness);
        screwSet(thickness);
    }
}

mtg(2, 50);
