<!DOCTYPE HTML>
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<title>Projet URGAN</title>

		<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js"></script>
		<style type="text/css">
${demo.css}
		</style>
		<link rel="stylesheet" type="text/css" href="style.css">
		<script type="text/javascript">

var x=0, chart, grssi0, grssi1, grssi2, grssi3, y0=0, y1=0, y2=0, y3=0,
m0=0,m1=0,m2=0,m3=0,b00,b01,b10,b11,b20,b21;
//Cette fonction rafraichit les valeurs des coordonnees des badges avec celles
//contenues dans le fichier coor.txt, lui meme traité par le script traitement.php

function refreshval(){
	$.ajax({
                url: 'traitement2.php',
                success: function(point){
                        /*var serie2 = chart.series[2],
                        point1=[point[0],point[1]],
                        point2=[point[2],point[3]],
                        point3=[point[4],point[5]],
                        point4=[point[6],point[7]],
                        shift1 = serie1.data.length > 1,
                        shift2 = serie2.data.length > 1,
                        rssi0 = grssi0.series[0];
                        
                        serie2.points[0].update({x: point[0], y: point[1]}, true, {duration : 750, easing: 'linear'});
                        serie2.points[1].update({x: point[2], y: point[3]}, true, {duration : 750, easing: 'linear'});
                        serie2.points[2].update({x: point[4], y: point[5]}, true, {duration : 750, easing: 'linear'});
                        serie2.points[3].update({x: point[6], y: point[7]}, true, {duration : 750, easing: 'linear'});
			*/

			b00=point[0];
			b01=point[1];
			b10=point[2];
			b11=point[3];
			b20=point[4];
			b21=point[5];
			b30=point[6];
			b31=point[7];

		},
                cache: false
        });

	
	$.ajax({
		url: 'traitement.php',
		success: function(point){
			var serie1 = chart.series[1],
			serie2 = chart.series[2],
			point1=[point[0],point[1]],
			point2=[point[2],point[3]],
			point3=[point[4],point[5]],
			point4=[point[6],point[7]],
			shift1 = serie1.data.length > 1,
			shift2 = serie2.data.length > 1,
			rssi0 = grssi0.series[0];
			
			serie1.points[0].update({x: point[0], y: point[1]}, true, {duration : 750, easing: 'linear'});
			serie1.points[1].update({x: point[2], y: point[3]}, true, {duration : 750, easing: 'linear'});
			serie1.points[2].update({x: point[4], y: point[5]}, true, {duration : 750, easing: 'linear'});
			serie1.points[3].update({x: point[6], y: point[7]}, true, {duration : 750, easing: 'linear'});

			y0=point[8];
			y1=point[9];
			y2=point[10];
			y3=point[11];
			m0=point[12];
			m1=point[13];
			m2=point[14];
			m3=point[15];

			serie2.points[0].update({x: b00, y: b01}, true, {duration : 750, easing: 'linear'});
                        serie2.points[1].update({x: b10, y: b11}, true, {duration : 750, easing: 'linear'});
                        serie2.points[2].update({x: b20, y: b21}, true, {duration : 750, easing: 'linear'});
                        serie2.points[3].update({x: b30, y: b31}, true, {duration : 750, easing: 'linear'});

			
			//setTimeout(refreshval,3000);
		},
		cache: false
	});

	setTimeout(refreshval,3000);

}

//On crée le nuage de points qui représentera les positions des balises (fixes) et des badges (dynamiques)

$(document).ready(function () {

	Highcharts.setOptions({
		global : {
			useUTC:false
		}
	});

	chart= new Highcharts.Chart({
		chart:{
			renderTo: 'container', //graphe insere dans la balise 'container' du script html
			type: 'scatter',
			zoomtype: 'xy',
		//	plotBackgroundImage : 'http://www.plan-de-maison.eu/wp-content/uploads/2015/03/plan-d-architecte-maison.jpg',
			events: { load: refreshval }
		},
		title: {
			text: 'Localisation Indoor IRCICA'
		},
		subtitle: {
			text: 'projet URGAN'
		},
		xAxis: {
			startOnTick :true,
			endOnTick: true,
		},
		plotOptions: {
			scatter: {
				marker: {
					radius:7
				}
			}
		},
		series: [{
			name: 'balises', //positions des balises
			color: 'black',
			data: [[0,0],[0,5],[4,0],[4,5]]
			},
			{
			name: 'badge a', //a partir d'ici, les coordonnées des badges
			color: 'blue',
			data : [[0,0],[0,0],[0,0],[0,0]]
			},
			{
			name: 'badge b',
			color: 'green',
			data: [[0,0],[0,0],[0,0],[0,0]]
			}]
	});

	grssi0= new Highcharts.Chart({
		chart: {
		renderTo : 'container2',
                type: 'spline',
                animation: Highcharts.svg, // don't animate in old IE
                marginRight: 10,
                events: {
                    load: function () {

                        // set up the updating of the chart each second
                        var series0 = this.series[0], series1 = this.series[1];
                        setInterval(function () {
                            var x = (new Date()).getTime(); // current time
                            series0.addPoint([x, y0], true, true);
			    series1.addPoint([x, m0], true, true);
                        }, 1000);
                    }
                }
            },
            title: {
                text: 'RSSI Balise 0'
            },
            xAxis: {
                type: 'datetime',
                tickPixelInterval: 150
            },
            yAxis: {
                title: {
                    text: 'Value'
                },
                plotLines: [{
                    value: 0,
                    width: 1,
                    color: '#808080'
                }]
            },
            tooltip: {
                formatter: function () {
                    return '<b>' + this.series.name + '</b><br/>' +
                        Highcharts.dateFormat('%Y-%m-%d %H:%M:%S', this.x) + '<br/>' +
                        Highcharts.numberFormat(this.y, 2);
                }
            },
            legend: {
                enabled: false
            },
            exporting: {
                enabled: false
            },
            series: [{
                name: 'rssi inst',
                data: (function () {
                    // generate an array of random data
                    var data = [],
                        time = (new Date()).getTime(),
                        i;

                    for (i = -19; i <= 0; i += 1) {
                        data.push({
                            x: time + i * 1000,
                            y: Math.random()
                        });
                    }
                    return data;
                }())
            },
	    {
		name: 'rssi moy',
		data: (function () {
                    // generate an array of random data
                    var data = [],
                        time = (new Date()).getTime(),
                        i;

                    for (i = -19; i <= 0; i += 1) {
                        data.push({
                            x: time + i * 1000,
                            y: Math.random()
                        });
                    }
                    return data;
                }())
	    }]
        });	
	
	grssi1 = new Highcharts.Chart({
		chart:{
                        renderTo: 'container3', 
                        type: 'spline',
                animation: Highcharts.svg, // don't animate in old IE
                marginRight: 10,
                events: {
                    load: function () {

                        // set up the updating of the chart each second
                        var series0 = this.series[0], series1= this.series[1];
                        setInterval(function () {
                            var x = (new Date()).getTime(); // current time
                            series0.addPoint([x, y1], true, true);
                            series1.addPoint([x,m1], true, true);
                        }, 1000);
                    }
                }
            },
            title: {
                text: 'RSSI Balise 1'
            },
            xAxis: {
                type: 'datetime',
                tickPixelInterval: 150
            },
            yAxis: {
                title: {
                    text: 'Value'
                },
                plotLines: [{
                    value: 0,
                    width: 1,
                    color: '#808080'
                }]
            },
            tooltip: {
                formatter: function () {
                    return '<b>' + this.series.name + '</b><br/>' +
                        Highcharts.dateFormat('%Y-%m-%d %H:%M:%S', this.x) + '<br/>' +
                        Highcharts.numberFormat(this.y, 2);
                }
            },
		legend: {
                enabled: false
            },
            exporting: {
                enabled: false
            },
            series: [{
                name: 'rssi inst',
                data: (function () {
                    // generate an array of random data
                    var data = [],
                        time = (new Date()).getTime(),
                        i;

                    for (i = -19; i <= 0; i += 1) {
                        data.push({
                            x: time + i * 1000,
                            y: Math.random()
                        });
                    }
                    return data;
                }())
            },
                {
                        name: 'rssi moy',
                data: (function () {
                    // generate an array of random data
                    var data = [],
                        time = (new Date()).getTime(),
                        i;

                    for (i = -19; i <= 0; i += 1) {
                        data.push({
                            x: time + i * 1000,
                            y: Math.random()
                        });
                    }
                    return data;
                }())

                }]
        });     


	
	grssi2= new Highcharts.Chart({
                chart:{
                        renderTo: 'container4', 
			type: 'spline',
                animation: Highcharts.svg, // don't animate in old IE
                marginRight: 10,
                events: {
                    load: function () {

                        // set up the updating of the chart each second
                        var series0 = this.series[0], series1= this.series[1];
                        setInterval(function () {
                            var x = (new Date()).getTime(); // current time
                            series0.addPoint([x, y2], true, true);
			    series1.addPoint([x,m2], true, true);
                        }, 1000);
                    }
                }
            },
            title: {
                text: 'RSSI Balise 2'
            },
            xAxis: {
                type: 'datetime',
                tickPixelInterval: 150
            },
            yAxis: {
                title: {
                    text: 'Value'
                },
                plotLines: [{
                    value: 0,
                    width: 1,
                    color: '#808080'
                }]
            },
            tooltip: {
                formatter: function () {
                    return '<b>' + this.series.name + '</b><br/>' +
                        Highcharts.dateFormat('%Y-%m-%d %H:%M:%S', this.x) + '<br/>' +
                        Highcharts.numberFormat(this.y, 2);
                }
            },
            legend: {
                enabled: false
            },
            exporting: {
                enabled: false
            },
            series: [{
                name: 'rssi inst',
                data: (function () {
                    // generate an array of random data
                    var data = [],
                        time = (new Date()).getTime(),
                        i;

                    for (i = -19; i <= 0; i += 1) {
                        data.push({
                            x: time + i * 1000,
                            y: Math.random()
                        });
                    }
                    return data;
                }())
            },
		{
			name: 'rssi moy',
                data: (function () {
                    // generate an array of random data
                    var data = [],
                        time = (new Date()).getTime(),
                        i;

                    for (i = -19; i <= 0; i += 1) {
                        data.push({
                            x: time + i * 1000,
                            y: Math.random()
                        });
                    }
                    return data;
                }())

		}]
        });     

	grssi3= new Highcharts.Chart({
                chart:{
                        renderTo: 'container5', 
			type: 'spline',
                animation: Highcharts.svg, // don't animate in old IE
                marginRight: 10,
                events: {
                    load: function () {

                        // set up the updating of the chart each second
                        var series0 = this.series[0], series1=this.series[1];
                        setInterval(function () {
                            var x = (new Date()).getTime(); // current time
                            series0.addPoint([x, y3], true, true);
			    series1.addPoint([x, m3], true , true);	
                        }, 1000);
                    }
                }
            },
            title: {
                text: 'RSSI Balise 3'
            },
            xAxis: {
                type: 'datetime',
                tickPixelInterval: 150
            },
            yAxis: {
                title: {
                    text: 'Value'
                },
                plotLines: [{
                    value: 0,
                    width: 1,
                    color: '#808080'
                }]
            },
            tooltip: {
                formatter: function () {
                    return '<b>' + this.series.name + '</b><br/>' +
                        Highcharts.dateFormat('%Y-%m-%d %H:%M:%S', this.x) + '<br/>' +
                        Highcharts.numberFormat(this.y, 2);
                }
            },
            legend: {
                enabled: false
            },
            exporting: {
                enabled: false
            },
            series: [{
                name: 'rssi inst',
                data: (function () {
                    // generate an array of random data
                    var data = [],
                        time = (new Date()).getTime(),
                        i;

                    for (i = -19; i <= 0; i += 1) {
                        data.push({
                            x: time + i * 1000,
                            y: Math.random()
                        });
                    }
                    return data;
                }())
            },
		{
			name: 'rssi moy',
                data: (function () {
                    // generate an array of random data
                    var data = [],
                        time = (new Date()).getTime(),
                        i;

                    for (i = -19; i <= 0; i += 1) {
                        data.push({
                            x: time + i * 1000,
                            y: Math.random()
                        });
                    }
                    return data;
                }())

		}]
        });     


});


		</script>
	</head>
	<body>
		<script src="https://code.highcharts.com/highcharts.js"></script>

		<div id="container" style="min-width: 700px; height:600px; max-width: 700px; margin:0 auto"></div> 
		
		<div>
		<div id="container2"></div>
		<div id="container3"></div>
		<div id="container4"></div>
		<div id="container5"></div>
		</div>

		</body>
</html>
