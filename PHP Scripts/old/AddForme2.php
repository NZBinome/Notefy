<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }

  $IdEq=$_POST['IdEq'];
  $IdEDL=$_POST['IdEDL'];

$sql = "INSERT INTO forme2 (IdEq, IdEDL) VALUES ($IdEq, $IdEDL)";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}

mysqli_close($con);
?>