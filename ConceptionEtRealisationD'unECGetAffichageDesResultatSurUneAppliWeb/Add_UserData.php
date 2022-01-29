 <?php
// on se connecte a la basede donnes 
 $servername = "localhost";
 $username = "root";
 $password = "";
 $dbname = "test";
 
 // si y a un problem au niveau de la connexion y affiche error
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

//on insere les valeurs dans le tableau temperature on insere les valeur de la collone VALEUR les autre se remplie automatiquement	
$sql = "INSERT INTO ".$_GET["graph"]." (value) VALUES (".$_GET['v'].")";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}
$conn->close();
?> 

