neckLength = 150;
neckWidth = 15;
armLength = 30;
armWidth = 4;





difference(){
    translate([0,0,0]){
        cube([neckWidth,neckLength,4]);
        translate([neckWidth / 2,neckLength - armWidth,0]){
            //cylinder(h=4,r=8,$fn=50);
            translate([(neckWidth / 2)  -(armWidth / 2), 0, 0]){
                cube([4,armLength, 4]);
            }
        
            translate([-(neckWidth / 2) - (armWidth / 2) , 0, 0]){
                cube([4,armLength, 4]);
            }
        }
    }
    
    translate([0 -1, neckWidth, 0]){
        #cube([neckWidth / 3, neckLength / 2, armWidth]);
        
    }
    translate([neckWidth - armWidth , 15, 0]){
        #cube([neckWidth / 3, neckLength / 2, armWidth]);
        
    }
    
    translate([neckWidth / 2,neckLength + 5,0])
    #cylinder(h=4,r=neckWidth * 0.5,$fn=50);
}