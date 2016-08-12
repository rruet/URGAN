<?php
	header("Content-type: text/json");

        $fileb = file('coorb.txt');
	$ligneb = $fileb[count($fileb)-1];
	$nb = sscanf($ligneb,"%f;%f;%f,%f;%f,%f;%f,%f;%d,%d,%d,%d,%d,%d,%d,%d",$x1b,$y1b,$x2b,$y2b,$x3b,$y3b,$x4,$y4,$r0b,$r1b,$r2b,$r3b,$m0b,$m1b,$m2b,$m3b);
	
	$res=array($x1b,$y1b,$x2b,$y2b,$x3b,$y3b,$x4,$y4);
		
	echo json_encode($res);
?>
