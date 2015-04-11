<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $NumAero= $_POST['NumAero'];
$result = mysqli_query($con,"SELECT * FROM Aeroport WHERE NumAero='$NumAero'");
echo "<Nest>";
while($row = mysqli_fetch_array($result))
 {
  echo "<Aeroport>";
  echo "<NumAero>" . $row['NumAero'] . "</NumAero>" ;
  echo "<NomAero>" . $row['NomAero'] . "</NomAero>" ;
  echo "<Ville>" . $row['Ville'] . "</Ville>" ;
  echo "</Aeroport>";
 }
 echo "</Nest>";

mysqli_close($con);
?>