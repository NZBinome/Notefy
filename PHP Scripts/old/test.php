<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "<erreure>" . "Impossible d'ouvrir la base de donnees" . "</erreure>";
  }

$sql = "INSERT INTO EquipeMaint (IdEquipe) VALUES ('')";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}
mysqli_close($con);
?>