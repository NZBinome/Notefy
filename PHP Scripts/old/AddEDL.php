<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
  $IdEDL=$_POST['IdEDL'];
  $IdComp=$_POST['IdComp'];
  $NomEDL=$_POST['NomEDL'];
  $PrenomEDL=$_POST['PrenomEDL'];
  $Poste=$_POST['Poste'];


$sql = "INSERT INTO EDL (IdComp, NomEDL, PrenomEDL, Poste) VALUES ($IdComp,'$NomEDL','$PrenomEDL','$Poste')";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}

mysqli_close($con);
?>