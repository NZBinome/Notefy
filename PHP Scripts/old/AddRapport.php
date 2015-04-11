<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
  $IdRapport=$_POST['IdRapport'];
  $IdEquipe=$_POST['IdEquipe'];
  $IdAvion=$_POST['IdAvion'];
  $IdVol=$_POST['IdVol'];
  //$DA=$_POST['DA'];
  $DateRap=$_POST['DateRap'];

$sql = "INSERT INTO Rapport (IdEquipe, IdAvion,IdVol,DateRap) VALUES ($IdEquipe,$IdAvion,$IdVol,'$DateRap')";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}

mysqli_close($con);
?>