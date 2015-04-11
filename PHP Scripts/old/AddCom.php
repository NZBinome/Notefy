<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
  $id=$_POST['IdComp'];
  $nom=$_POST['NomComp'];
  $origine=$_POST['Origine'];

$sql = "INSERT INTO Compagnie (NomComp, Origine) VALUES ('$nom','$origine')";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}

mysqli_close($con);
?>