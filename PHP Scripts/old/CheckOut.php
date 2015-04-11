<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $IdVol= $_POST['IdVol'];
       $IdProg=$_POST['IdProg'];


 $result = mysqli_query($con,"SELECT Direction FROM Programme WHERE IdProg='$IdProg'");
while($row = mysqli_fetch_array($result))
 {
 	$Dir=$row['Direction'];
 	if($Dir=='Arrivee'){
 		      $sql = "UPDATE Passager SET CheckOut='1' WHERE IdVol='$IdVol'";
				if (!mysqli_query($con,$sql))
				{
  				die('Error: ' . mysqli_error($con));
				}
 	}
 }


mysqli_close($con);
?>