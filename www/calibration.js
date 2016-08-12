/* Dnas ce programme javascript, on incrémente un compteur à chaque clic de la souris.
Suivant la valeur du compteur, le traitement ne sera pas le même.*/      


 var cpt=0;
	
	//on récupère le canvas de la page

	var canvas = document.getElementById('myCanvas');
	var context = canvas.getContext('2d');
	
	canvas.width = window.innerWidth;
	canvas.height = window.innerHeight;

        function clickHandler(e){
                if(cpt==0){ //On récupère les coordonnées de l'origine du plan (en haut à gauche de la page)
                        var x_result=document.getElementById('xorg');
                        var y_result=document.getElementById('yorg');
                        
                        x_result.innerHTML = e.clientX;
                        y_result.innerHTML = e.clientY;
                        cpt=1;
                        window.alert("Maintenant, definissez l'echelle de votre plan. Cliquez sur deux point distant d'1 metre.");
                }
                else if(cpt==1){ //on récupère l'abscisse du premier point définissant l'échelle
                        var x_scale1=document.getElementById('x_scale1');
                        x_scale1.innerHTML=e.clientX;
                        cpt=2;
                }
                else if(cpt==2){ //puis l'abscisse du deuxième
                        var scale=document.getElementById('scale');
                        var x_scale2=document.getElementById('x_scale2');
                        x_scale2.innerHTML=e.clientX;
                        scale.innerHTML=x_scale2.innerHTML - document.getElementById('x_scale1').innerHTML;
                        cpt=3;
                        window.alert("Maintenant, cliquez surl'emplacement de chaque balise."); 
                }
                else if(cpt==3){ // on place la balise 0
                        var x_result=document.getElementById('x0');
                        var y_result=document.getElementById('y0');
			context.fillStyle="green";
                        x_result.innerHTML = e.clientX - document.getElementById('xorg').innerHTML;
                        y_result.innerHTML = e.clientY - document.getElementById('yorg').innerHTML;
                        cpt=4;
                }
                else if(cpt==4){ // puis la 1 [...]
                        var x_result=document.getElementById('x1');
                        var y_result=document.getElementById('y1');
			context.fillStyle="red";
                        x_result.innerHTML = e.clientX - document.getElementById('xorg').innerHTML;
                        y_result.innerHTML = e.clientY - document.getElementById('yorg').innerHTML;
                        cpt=5;
                }
                else if(cpt==5){
                        var x_result=document.getElementById('x2');
                        var y_result=document.getElementById('y2');
			context.fillStyle="grey";
                        x_result.innerHTML = e.clientX - document.getElementById('xorg').innerHTML;
                        y_result.innerHTML = e.clientY - document.getElementById('yorg').innerHTML;
                        cpt=6;
                }
                else if(cpt==6){
                        var x_result=document.getElementById('x3');
                        var y_result=document.getElementById('y3');
			context.fillStyle="blue";
                        x_result.innerHTML = e.clientX - document.getElementById('xorg').innerHTML;
                        y_result.innerHTML = e.clientY - document.getElementById('yorg').innerHTML;
                        cpt=7;
                }
		else if(cpt==7){
                        var x_result=document.getElementById('x4');
                        var y_result=document.getElementById('y4');
			context.fillStyle="orange";
                        x_result.innerHTML = e.clientX - document.getElementById('xorg').innerHTML;
                        y_result.innerHTML = e.clientY - document.getElementById('yorg').innerHTML;
                        cpt=8;
                }
                else if(cpt==8){
                        var x_result=document.getElementById('x5');
                        var y_result=document.getElementById('y5');
			context.fillStyle="black";
                        x_result.innerHTML = e.clientX - document.getElementById('xorg').innerHTML;
                        y_result.innerHTML = e.clientY - document.getElementById('yorg').innerHTML;
                        cpt=9;
                }
		else if(cpt==9){
                        var x_result=document.getElementById('x6');
                        var y_result=document.getElementById('y6');
                        context.fillStyle="brown";
                        x_result.innerHTML = e.clientX - document.getElementById('xorg').innerHTML;
                        y_result.innerHTML = e.clientY - document.getElementById('yorg').innerHTML;
                        cpt=10;
                }
		else if(cpt==10){
                        var x_result=document.getElementById('x7');
                        var y_result=document.getElementById('y7');
                        context.fillStyle="#33CCFF";
                        x_result.innerHTML = e.clientX - document.getElementById('xorg').innerHTML;
                        y_result.innerHTML = e.clientY - document.getElementById('yorg').innerHTML;
                        cpt=11;
                        window.alert("Calibration terminee!");
                }

		context.beginPath();
                context.arc(x_result.innerHTML,y_result.innerHTML,5,0,2*3.14); // a chaque clic, on place un cercle sur le plan pour faciliter la visualisation
                context.fill();


        }

	function post(){ //lorsqu'on clique sur "terminer la calibration" on envoit toutes les coordonnées récupérées à la page "config.php" puis on affiche le lien vers cette page en dessous du bouton.
		var x0 = document.getElementById('x0').innerHTML;
		var y0 = document.getElementById('y0').innerHTML; 
		var x1 = document.getElementById('x1').innerHTML;
		var y1 = document.getElementById('y1').innerHTML;
		var x2 = document.getElementById('x2').innerHTML;
		var y2 = document.getElementById('y2').innerHTML;
		var x3 = document.getElementById('x3').innerHTML;
		var y3 = document.getElementById('y3').innerHTML;
		var x4 = document.getElementById('x4').innerHTML;
		var y4 = document.getElementById('y4').innerHTML;
		var x5 = document.getElementById('x5').innerHTML;
		var y5 = document.getElementById('y5').innerHTML;
		var x6 = document.getElementById('x6').innerHTML;
                var y6 = document.getElementById('y6').innerHTML;
		var x7 = document.getElementById('x7').innerHTML;
                var y7 = document.getElementById('y7').innerHTML;

		var scale = document.getElementById('scale').innerHTML;


		$.post('config.php',{postx0:x0,posty0:y0,postx1:x1,posty1:y1,postx2:x2,posty2:y2,postx3:x3,posty3:y3,postx4:x4,posty4:y4,postx5:x5,posty5:y5,postx6:x6,posty6:y6,postx7:x7,posty7:y7}, function(){
		$("#result").html("<a href=\"config.php?x0="+x0+"&y0="+y0+"&x1="+x1+"&y1="+y1+"&x2="+x2+"&y2="+y2+"&x3="+x3+"&y3="+y3+"&x4="+x4+"&y4="+y4+"&x5="+x5+"&y5="+y5+"&x6="+x6+"&y6="+y6+"&x7="+x7+"&y7="+y7+"&scale="+scale+"\">Acceder</a>");
			}
		);

	}
        window.alert("Pour commencer, cliquez en haut a gauche du plan.");
                
        document.onclick = clickHandler;
	


