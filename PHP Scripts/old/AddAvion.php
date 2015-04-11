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

echo $IdAvion . ";" . $IdModele . ";" . $IdComp ;

$sql = "INSERT INTO Avion (IdModele, IdComp, IdAvCom, Gare) VALUES ($IdModele,$IdComp,'$IdAvCom',$Gare)";

if (!mysqli_query($con,$sql))
{
  //die('Error: ' . mysqli_error($con));
}

mysqli_close($con);
?>