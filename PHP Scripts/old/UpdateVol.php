<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
  $IdVol=$_POST['IdVol'];
  $IdEquipe=$_POST['IdEquipe'];
  $IdEq=$_POST['IdEq'];
  $IdProg=$_POST['IdProg'];
  $IdAvion=$_POST['IdAvion'];
  $DatPreVol=$_POST['DatPreVol'];
  $HeurPreVol=$_POST['HeurPreVol'];
  $DatReVol=$_POST['DatReVol'];
  $HeurReVol=$_POST['HeurReVol'];
  $EtatVol=$_POST['EtatVol'];
/*
  if($EtatVol=='Retarde'){
    $result = mysqli_query($con,"SELECT Code FROM Programme WHERE IdProg='$IdProg'");
while($row = mysqli_fetch_array($result))
 {
  $Code=$row['Code'];
  $File=$Code . $DatPreVol . $HeurPreVol . ".xml";
  $sql = "UPDATE Vol SET IdEquipe='$IdEquipe', IdEq='$IdEq',IdProg='$IdProg', IdAvion='$IdAvion', DatPreVol='$DatPreVol', HeurPreVol='$HeurPreVol', DatReVol='$DatReVol', HeurReVol='$HeurReVol', EtatVol='$EtatVol', File='$File' WHERE IdVol='$IdVol' ";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}
 }
 include('LoadPass.php');
  }

else{*/
$sql = "UPDATE Vol SET IdEquipe=$IdEquipe, IdEq=$IdEq ,IdProg=$IdProg, IdAvion=$IdAvion, DatPreVol='$DatPreVol', HeurPreVol='$HeurPreVol', DatReVol='$DatReVol', HeurReVol='$HeurReVol', EtatVol='$EtatVol' WHERE IdVol='$IdVol' ";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
//}
}

mysqli_close($con);
?>