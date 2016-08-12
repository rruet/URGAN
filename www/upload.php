<?php

	if(isset($_POST['upload'])){
	
		$content_dir = 'uploads/';

		if(!is_writable($content_dir))
			die('Impossible d\'ecrire dans le repertoire cible.');
		
		$tmp_file = $_FILES['map']['tmp_name'];
		
		if(!is_uploaded_file($tmp_file))
			exit("le fichier est introuvable.");

		$name_file = "map.jpg";
		
		if(!move_uploaded_file($tmp_file,$content_dir . $name_file))
			exit("Impossible de copier le fichier dans $content_dir");

		echo "le plan a bien été télécharg&eacute;";
		echo "</br></br><a href=\"calibration.html\">Passer a la calibration du plan</a>";
		
	}

?>
