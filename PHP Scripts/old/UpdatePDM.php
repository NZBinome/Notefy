<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
  $IdPDM=$_POST['IdPDM'];
  $NomPDM=$_POST['NomPDM'];
  $PrenomPDM=$_POST['PrenomPDM'];

$sql = "UPDATE PDM SET NomPDM='$NomPDM', PrenomPDM='$PrenomPDM' WHERE IdPDM='$IdPDM'";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}

mysqli_close($con);
?>