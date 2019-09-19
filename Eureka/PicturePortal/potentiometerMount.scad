heightToHoleCenter = 22;//mm //EDITED
potHoleWidth = 7; 

screwD =4;//screw //measured: ~3.5mm

totalHeight = heightToHoleCenter+(potHoleWidth/2)+5 + 2;//+x makes cutout deeper
totalWidth = 25+ 10;
totalLength = 30;
thickness = 4;
curveRes = 50;

module potBracket(){
    bracket(braces=true, holeDiam=7, sideMount=true,notch=true);
}

module boltBracket(){
    bracket(holeDiam = 6.5,braces=true,notch=false);
}

module bracket(holeDiam = 7, braces=false, sideMount=false, notch = false){  
    //totalHeight = heightToHoleCenter+(10.5 - (holeDiam / 2)); //what was I thinking here?
    
    //for side-mounted screw-holes:
    sideExtension = 10;//how far to extend out
    sideLength = thickness * 2 + screwD;
    sideWidth  =  totalWidth + sideExtension * 2;
    //sideWidth  =  totalWidth + thickness * 4 + screwD * 2;
    sideHeight = thickness - 1;
    
    minkowOffset = 3; //also means edge curve radius
    
    difference() {
        //two halves & joint curve fill-in
        union(){
            cube([totalLength,totalWidth,thickness]);
            cube([thickness,totalWidth, totalHeight]);
            cube([thickness * 2, totalWidth, thickness * 2]);
            //sidemount cube
            if(sideMount){
                
                translate([minkowOffset,-1*(sideExtension),1])
                
                minkowski(){
                    cube([sideLength, sideWidth, sideHeight - 1]);
                    cylinder(h=2, r=minkowOffset, center=true, $fn=curveRes);
                }
            }
            
        }
        
        //potentiometer hole
        translate([thickness, totalWidth / 2, heightToHoleCenter])
        rotate([0,90,0])
        #cylinder(h=thickness * 2, d=holeDiam, center=true, $fn=curveRes);
        
        //notch at top
        if(notch){
            translate([0,(totalWidth / 2) -1,heightToHoleCenter + (holeDiam/2) + 4])
            #cube([thickness, 2, totalHeight]);
        }
        //curve @ joint
        
        translate([thickness * 2,totalWidth/2, thickness * 2])
        rotate([90,0,0])
        cylinder(h=totalWidth, r=thickness, center=true, $fn=curveRes);
        
        //2 screw holes
        if(sideMount){
            translate([(sideLength / 2) + minkowOffset, 0 , thickness / 2]){
                translate([0,-1 * (sideExtension / 2),0])
                    #screw();
                
                translate([0,totalWidth + (sideExtension / 2),0])
                    #screw();
            }
            
        } else {        
            translate([totalLength / 2, 0, thickness / 2]){
                translate([0, totalWidth / 3, 0])
                #screw();
                translate([0, 2 *(totalWidth / 3), 0])
                #screw();
            }
        }
        
        //slice off the top
        translate([0,0,totalHeight])
        #cube([thickness * 2, totalWidth, thickness]);
    }
    if(braces){
        translate([0, 0, thickness]){
            brace();
            translate([0,totalWidth - thickness, 0])
            brace();
        }
    }
        
}

module brace(){
    crossLength = sqrt(pow(totalHeight, 2) + pow(totalLength,2));
    angle = asin(totalHeight/crossLength);
    d = (sin(angle) * totalLength)  - totalHeight / 2;
    
    difference(){
        
        intersection(){
            //base cube
            translate([thickness, 0, 0])
            cube([totalLength - thickness,thickness, totalHeight]);
            
            //angled cube
            rotate([0,angle,0])
            translate([0,0,d])
            cube(center=true,[crossLength * 1.2, thickness * 2, totalHeight]);
        }
        
        //cube for clipping the top:
        translate([0,0, totalHeight - thickness])
        cube([totalLength, thickness, thickness]);
    }
    
}

module screw(){
    translate([0,0,thickness / 2])
    cylinder(h=thickness * 2, d=screwD, center=true, $fn=curveRes);
}
//translate([thickness*0, 0, thickness])
//brace();
translate([0, -1 * (totalWidth / 2), 0])
//potBracket();
bracket(braces=true, holeDiam=12.5);
//screw();
//boltBracket();