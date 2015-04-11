<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
  $idPDM=$_POST['IdPDM'];
  $NomPDM=$_POST['NomPDM'];
  $PrenomPDM=$_POST['PrenomPDM'];

$sql = "INSERT INTO PDM (NomPDM, PrenomPDM) VALUES ('$NomPDM','$PrenomPDM')";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}

mysqli_close($con);
?>