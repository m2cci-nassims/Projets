 <?php
function recordExists($table, $name, $ref, $mysqli) {
        $query = "SELECT * FROM `$table` WHERE nom = '".$name."' and reference = '".$ref."'";
        $result = $mysqli->query($query);

        if($result->num_rows > 0) {
                return false; // The record(s) do exist
        }
        return true; // No record found
}

// on se connecte a la basede donnes 
 $servername = "localhost";
 $username = "root";
 $password = "";
 $dbname = "test";
 $table = "patients";
 // si y a un problem au niveau de la connexion y affiche error
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
if(recordExists($table,$_GET['n'],$_GET['ref'],$conn)){
//on insere les valeurs dans le tableau temperature on insere les valeur de la collone VALEUR les autre se remplie automatiquement	
$sql = "INSERT INTO ".$_GET['c']." (nom,reference,status,graph_name) VALUES ('".$_GET['n']."','".$_GET['ref']."','".$_GET['a']."','graph_".$_GET['n']."_".$_GET['ref']."')";


if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}


$create_user_table = "CREATE TABLE graph_".$_GET['n']."_".$_GET['ref']." (
time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
value INT  NOT NULL
)";

if ($conn->query($create_user_table) === TRUE) {
    echo "New tabel for user , created successfully";
} else {
    echo "Error: " . $create_user_table . "<br>" . $conn->error;
}

}
else 
echo $_GET['n']." Record already exist !";
$conn->close();
?> 

