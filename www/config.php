<?php
//recuperation de la configuration postée par la page de calibration

$xb0 = $_GET['x0'];
$yb0 = $_GET['y0'];
$xb1 = $_GET['x1'];
$yb1 = $_GET['y1'];
$xb2 = $_GET['x2'];
$yb2 = $_GET['y2'];
$xb3 = $_GET['x3'];
$yb3 = $_GET['y3'];
$xb4 = $_GET['x4'];
$yb4 = $_GET['y4'];
$xb5 = $_GET['x5'];
$yb5 = $_GET['y5'];
$xb6 = $_GET['x6'];
$yb6 = $_GET['y6'];
$xb7 = $_GET['x7'];
$yb7 = $_GET['y7'];
$scale = $_GET['scale'];

// ouverture du fichier de configuration et écriture des infos dedans
$config = fopen('config.txt','w');

fputs($config,$xb0.','.$yb0.','.$xb1.','.$yb1.','.$xb2.','.$yb2.','.$xb3.','.$yb3.','.$xb4.','.$yb4.','.$xb5.','.$yb5.','.$xb6.','.$yb6.','.$xb7.','.$yb7.','.$scale."\n".'');

fclose($config);

echo ("Configuration enregistr&eacute;e</br></br>Maintenant lancez l'algorithme que vous souhaitez.</br>");
echo ("</br><a href=\"affich_urgan.php\">Visualiser (algo normal)</a>\n");
echo ("</br><a href=\"svgtest.php\">Visualiser (algo de test)</a>");

?>
