    <?php
     
    $dataPoints = array();
    //Best practice is to create a separate file for handling connection to database
    try{
         // Creating a new connection.
        // Replace your-hostname, your-db, your-username, your-password according to your database
        $link = new \PDO(   'mysql:host=localhost;dbname=test;charset=utf8mb4', //'mysql:host=localhost;dbname=canvasjs_db;charset=utf8mb4',
                            'root',
                            '',
                            array(
                                \PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
                                \PDO::ATTR_PERSISTENT => false
                            )
                        );
    	
        $handle = $link->prepare("SELECT value FROM  ".$_GET["graph_name"]." "); 
        $handle->execute(); 
        $result = $handle->fetchAll(\PDO::FETCH_OBJ);
    	$i = 0;
        foreach($result as $row){
            array_push($dataPoints, array("y"=> $row->value));
        }
    	$link = null;
    }
    catch(\PDOException $ex){
        print($ex->getMessage());
    }
    	
    ?>
    <!DOCTYPE HTML>
    <html>
    <head>
        <meta http-equiv="refresh" content="2" />

    <script>
    window.onload = function () {
     
    var chart = new CanvasJS.Chart("chartContainer", {
    	animationEnabled: true,
    	exportEnabled: true,
    	theme: "light2", // "light1", "light2", "dark1", "dark2"
    	title:{
    		text: "Heartbeat Graph "
    	},
    	data: [{
    		type: "spline", //change type to bar, line, area, pie, etc  
    		dataPoints: <?php echo json_encode($dataPoints, JSON_NUMERIC_CHECK); ?>
    	}]
    });
    chart.render();
     
    }
    </script>
    </head>
    <body>
    <div id="chartContainer" style="height: 370px; width: 100%;"></div>
    <script src="https://canvasjs.com/assets/script/canvasjs.min.js"></script>
    </body>
    </html>                              