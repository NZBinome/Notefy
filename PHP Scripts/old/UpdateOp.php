<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
  $IdOp=$_POST['IdOp'];
  $DescOp=$_POST['DescOp'];
  $DA=$_POST['DA'];


$sql = "UPDATE Operations SET DescOp='$DescOp', DA='$DA' WHERE IdOp='$IdOp'";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}

mysqli_close($con);
?>