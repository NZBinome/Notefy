<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $IdVol= $_POST['IdVol'];
$result = mysqli_query($con,"SELECT IdProg FROM Vol WHERE IdVol='$IdVol'");

while($row = mysqli_fetch_array($result)){
  $Prog=$row['IdProg'];
  $nresult = mysqli_query($con,"SELECT Direction FROM Programme WHERE IdProg='$Prog'");
  while ($nrow=mysqli_fetch_array($nresult)) {
  	$DA=$nrow['Direction'];
  	$nnresult = mysqli_query($con,"SELECT DescOp FROM Operations WHERE DA='$DA'");
  	while ($nnrow=mysqli_fetch_array($nnresult)) {
  		echo $nnrow['DescOp'] . ";";
  	}
  }
 }

mysqli_close($con);
?>