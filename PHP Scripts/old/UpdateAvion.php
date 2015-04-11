<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
  $IdAvion=$_POST['IdAvion'];
  $IdModele=$_POST['IdModele'];
  $IdComp=$_POST['IdComp'];
  $IdAvCom=$_POST['IdAvCom'];
  $Gare=$_POST['Gare'];


$sql = "UPDATE Avion SET IdModele='$IdModele', IdComp='$IdComp', IdAvCom='$IdAvCom', Gare='$Gare' WHERE IdAvion='$IdAvion'";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}

mysqli_close($con);
?>