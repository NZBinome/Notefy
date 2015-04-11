<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "<Nest>";
  echo "<erreure>" . "Impossible d'ouvrir la base de donnees" . "</erreure>";
  echo "</Nest>";
  }

  $IdEquipe=$_POST['IdEquipe'];

$sql = "INSERT INTO EquipeMaint (IdEquipe) VALUES ('')";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}

mysqli_close($con);
?>