<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
  $IdOp=$_POST['IdOp'];
  $Remarque=$_POST['Remarque'];
  $Gravite=$_POST['Gravite'];
 $entier=mysqli_query($con,"SELECT IdRapport FROM Rapport WHERE IdRapport=(SELECT max(IdRapport) FROM Rapport)");
while ($rang=mysqli_fetch_array($entier)) {
  $a=$rang['IdRapport'];
}
$sql = "INSERT INTO contient (IdOp, IdRapport, Remarque, Gravite) VALUES ('$IdOp','$a','$Remarque',$Gravite)";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}
mysqli_close($con);
?>