<?php 
  header("Content-type: image/svg+xml"); 
  print('<?xml version="1.0" encoding="iso-8859-1"?>');
  
  shell_exec('sudo ~\Documents\old_versions\svg');

	//On recupere les coordonnees des balises configurees via l'application

  $config=fopen('config.txt','r+');
  
  $l = fgets($config);
  $scan = sscanf($l,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",$xb0,$yb0,$xb1,$yb1,$xb2,$yb2,$xb3,$yb3,$xb4,$yb4,$xb5,$yb5,$xb6,$yb6,$xb7,$yb7,$scale);		 
  fclose($config); 

	//On recupere les donnees envoyees par l'algorithme pour le badge a

  $file = file('files/badge_a.txt');
  $ligne = $file[count($file)-1];
  $n = sscanf($ligne,"%f,%f",$ax,$ay);

	//On recupere les donnees envoyees par l'algorithme pour le badge b

  $file = file('files/badge_b.txt');
  $ligne = $file[count($file)-1];
  $n = sscanf($ligne,"%f,%f",$bx,$by);


  	//Coordonnees reelles du badge (manuelles)

  $xb= 661.26;
  $yb= 670.65;
  $d=sqrt(pow($xb-$cx,2) + pow($yb-$cy,2));
  
?>
<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">
<html>
<head>
</head>
<body  style="margin : 0">
<svg version="1.1"
     baseProfile="full"
     xmlns="http://www.w3.org/2000/svg"
     height="1000px"
     width="2000px"
     style="background:url(uploads/map.jpg);background-repeat:no-repeat">

                  <!--Positions des balises (decommenter pour les voir sur le plan) -->

  <!--<circle cx="<?=$xb0;?>" cy="<?=$yb0;?>" r="5" fill="green"/>

  <circle cx="<?=$xb1;?>" cy="<?=$yb1;?>" r="5" fill="red"/>

  <circle cx="<?=$xb2;?>" cy="<?=$yb2;?>" r="5" fill="grey"/>

  <circle cx="<?=$xb3;?>" cy="<?=$yb3;?>" r="5" fill="blue"/>

  <circle cx="<?=$xb4;?>" cy="<?=$yb4;?>" r="5" fill="orange"/>

  <circle cx="<?=$xb5;?>" cy="<?=$yb5;?>" r="5" fill="black"/>

  <circle cx="<?=$xb6;?>" cy="<?=$yb6;?>" r="5" fill="brown"/>

  <circle cx="<?=$xb7;?>" cy="<?=$yb7;?>" r="5" fill="#33CCFF"/>  -->


		<!--Position réelle du badge(a rentrer manuellement pour verif)-->

<!--<circle cx="<?=$xb;?>" cy="<?=$yb;?>" r="5" fill="yellow"/> -->


		<!--Poistion calculee des badge-->

<circle cx="<?=$ax;?>" cy="<?=$ay;?>" r="5" fill="#33CCFF" />
<circle cx="<?=$bx;?>" cy="<?=$by;?>" r="5" fill="green" />



       <!-- Cercles correspondants à la position du badge potentielle autour de chaque balise (valeur moyenne, minimum et maximum)-->

<!--  <circle cx="<?=$xb0;?>" cy="<?=$yb0;?>" r="<?=$r0;?>" fill="transparent" stroke="green" stroke-width="2"/>-->
 <!-- <circle cx="247.35" cy="309" r="<?=$min0;?>" fill="transparent" stroke="green" stroke-width="3"/>
  <circle cx="247.35" cy="309" r="<?=$max0;?>" fill="transparent" stroke="green" stroke-width="3"/>-->

<!-- <circle cx="<?=$xb1;?>" cy="<?=$yb1;?>" r="<?=$r1;?>" fill="transparent" stroke="red" stroke-width="2"/>-->
 <!-- <circle cx="691.35" cy="309" r="<?=$min1;?>" fill="transparent" stroke="red" stroke-width="3"/>
  <circle cx="691.35" cy="309" r="<?=$max1;?>" fill="transparent" stroke="red" stroke-width="3"/>-->

  <!--<circle cx="<?=$xb2;?>" cy="<?=$yb2;?>" r="<?=$r2;?>" fill="transparent" stroke="grey" stroke-width="2"/>-->
  <!-- <circle cx="691.35" cy="623" r="<?=$min2;?>" fill="transparent" stroke="grey" stroke-width="3"/>
  <circle cx="691.35" cy="623" r="<?=$max2;?>" fill="transparent" stroke="grey" stroke-width="3"/>-->


<!--  <circle cx="<?=$xb3;?>" cy="<?=$yb3;?>" r="<?=$r3;?>" fill="transparent" stroke="blue" stroke-width="2"/>-->
 <!--  <circle cx="279.35" cy="643" r="<?=$min3;?>" fill="transparent" stroke="blue" stroke-width="3"/>
  <circle cx="279.35" cy="643" r="<?=$max3;?>" fill="transparent" stroke="blue" stroke-width="3"/>-->


<!--  <circle cx="<?=$xb4;?>" cy="<?=$yb4;?>" r="<?=$r4;?>" fill="transparent" stroke="orange" stroke-width="2"/>-->
  <!-- <circle cx="100" cy="150" r="<?=$min4;?>" fill="transparent" stroke="orange" stroke-width="3"/>
  <circle cx="100" cy="150" r="<?=$max4;?>" fill="transparent" stroke="orange" stroke-width="3"/>-->


  <!--<circle cx="<?=$xb5;?>" cy="<?=$yb5;?>" r="<?=$r5;?>" fill="transparent" stroke="black" stroke-width="2"/>-->
 <!--  <circle cx="1092" cy="150" r="<?=$min5;?>" fill="transparent" stroke="black" stroke-width="3"/>
  <circle cx="1092" cy="150" r="<?=$max5;?>" fill="transparent" stroke="black" stroke-width="3"/>-->

<!--  <circle cx="<?=$xb6;?>" cy="<?=$yb6;?>" r="<?=$r6;?>" fill="transparent" stroke="brown" stroke-width="2"/>-->
  <!-- <circle cx="100" cy="150" r="<?=$min4;?>" fill="transparent" stroke="orange" stroke-width="3"/>
  <circle cx="100" cy="150" r="<?=$max4;?>" fill="transparent" stroke="orange" stroke-width="3"/>-->


<!--  <circle cx="<?=$xb7;?>" cy="<?=$yb7;?>" r="<?=$r7;?>" fill="transparent" stroke="#33CCFF" stroke-width="2"/>-->
 <!--  <circle cx="1092" cy="150" r="<?=$min5;?>" fill="transparent" stroke="black" stroke-width="3"/>
  <circle cx="1092" cy="150" r="<?=$max5;?>" fill="transparent" stroke="black" stroke-width="3"/>-->


		<!-- Erreur entre la position reelle du badge et celle calculee -->

 <!-- <text x="1092" y="800">Distance badge reel/badge exp = <?=$d;?> cm</text>-->

</svg>
</body>
</html>
