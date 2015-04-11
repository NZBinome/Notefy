<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
  $idOp=$_POST['IdOp'];
  $DescOp=$_POST['DescOp'];
  $DA=$_POST['DA'];

$sql = "INSERT INTO Operations (DescOp, DA) VALUES ('$DescOp','$DA')";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}

mysqli_close($con);
?>