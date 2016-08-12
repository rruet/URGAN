<?php

	$x0 = $_POST['postx0'];
	$y0 = $_POST['posty0'];
	$x1 = $_POST['postx1'];
        $y1 = $_POST['posty1'];
	$x2 = $_POST['postx2'];
        $y2 = $_POST['posty2'];
	$x3 = $_POST['postx3'];
        $y3 = $_POST['posty3'];
	$x4 = $_POST['postx4'];
        $y4 = $_POST['posty4'];
	$x5 = $_POST['postx5'];
        $y5 = $_POST['posty5'];

	$res=array($x0,$y0,$x1,$y1,$x2,$y2,$x3,$y3,$x4,$y4,$x5,$y5);

        echo json_encode($res);


?>
