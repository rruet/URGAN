<?php
	header("Content-type: text/json");

	$file = file('coor.txt');
	$ligne = $file[count($file)-1];
	$n = sscanf($ligne,"%f,%f;%f,%f;%f,%f;%f,%f;%f,%f,%f,%f,%f,%f,%f,%f;%s",$x1,$y1,$x2,$y2,$x3,$y3,$x4,$y4,$r0,$r1,$r2,$r3,$m0,$m1,$m2,$m3,$id);
	$res=array($x1,$y1,$x2,$y2,$x3,$y3,$x4,$y4,$r0,$r1,$r2,$r3,$m0,$m1,$m2,$m3);
	echo json_encode($res);
	
?>
