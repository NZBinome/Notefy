<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
  $IdProg=$_POST['IdProg'];
  $IdAvion=$_POST['IdAvion'];
  $IdEquipe=$_POST['IdEquipe'];
  $IdVol=$_POST['IdVol'];
  $IdEq=$_POST['IdEq'];
  $DatPreVol=$_POST['DatPreVol'];
  $HeurPreVol=$_POST['HeurPreVol'];
  $DatReVol=$_POST['DatReVol'];
  $HeurReVol=$_POST['HeurReVol'];
  $EtatVol=$_POST['EtatVol'];
  $RefComp=$_POST['RefComp'];


$sql = "INSERT INTO Vol (IdEquipe, IdEq,IdProg, IdAvion, DatPreVol, HeurPreVol, DatReVol, HeurReVol, EtatVol, RefComp) VALUES ($IdEquipe,$IdEq,$IdProg,$IdAvion,'$DatPreVol','$HeurPreVol','$DatReVol','$HeurReVol','$EtatVol','$RefComp')";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}

mysqli_close($con);
?>