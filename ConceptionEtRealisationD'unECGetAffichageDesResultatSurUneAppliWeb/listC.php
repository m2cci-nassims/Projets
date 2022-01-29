<!DOCTYPE html>
<?php
$con=mysqli_connect("localhost","root","","test");
// Check connection
if (mysqli_connect_errno())
{
echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

$result = mysqli_query($con,"SELECT * FROM patients");


?>
<html lang="en">
<head>
   <meta charset="UTF-8"  />
    <title>List Users</title>
    <!--Import Google Icon Font-->
    <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
    <!--Import materialize.css-->
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.99.0/css/materialize.min.css">
</head>
<body>
<div class="container">

    <div class="card-panel green darken">
        <span class="white-text text-darken-2">
            <h4 class="center-align">Users</h4>
        </span>
    </div>
    <table class="striped highlight" id="posts_table">
        <thead>
        <tr>
            <th>ID</th>
            <th>Time</th>
            <th>Nom</th> 
            <th>Reference</th>
            <th>Status</th>
			<th>Heart Graph</th>
        </tr>
        </thead>

        <tbody>
			<?php 
			while($row = mysqli_fetch_array($result))
				{
			    echo "<tr>";
                echo "<td>" . $row['ID'] . "</td>";
				echo "<td>" . $row['time'] . "</td>";
				echo "<td>" . $row['nom'] . "</td>";
				echo "<td>" . $row['reference'] . "</td>";
				echo "<td>" . $row['status'] . "</td>";
				echo "<td> <a href='http://localhost/projet.php/printer.php?graph_name=".$row['graph_name']."' >See Graph</a> </td>";
				echo "</tr>";
				}
			
			?>
        </tbody>
    </table>
    
</div>
</body>
</html>