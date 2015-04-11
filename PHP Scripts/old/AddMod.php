<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
  $IdModele=$_POST['IdModele'];
  $Reservoire=$_POST['Reservoire'];
  $DistMax=$_POST['DistMax'];
  $VitCrois=$_POST['VitCrois'];
  $NomModel=$_POST['NomModel'];


$sql = "INSERT INTO Modele (Reservoire, DistMax, VitCrois, NomModel) VALUES ($Reservoire,$DistMax,$VitCrois,'$NomModel')";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}

mysqli_close($con);
?>