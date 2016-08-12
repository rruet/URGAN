<?php

	$config = fopen("config.txt","r");
	$ligne = fgets($config);
	echo $ligne;
	sscanf($ligne,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",$xb0,$yb0,$xb1,$yb1,$xb2,$yb2,$xb3,$yb3,$xb4,$yb4,$xb5,$yb5,$scale);
	echo("coucou");
	echo $xb0;	
	fclose($config);

?>
