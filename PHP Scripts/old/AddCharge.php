<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
  $IdOp=$_POST['IdOp'];
  $IdPDM=$_POST['IdPDM'];

$sql = "INSERT INTO charge (IdOp, IdPDM) VALUES ($IdOp, $IdPDM)";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}

mysqli_close($con);
?>