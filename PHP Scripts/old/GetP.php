<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $IdVol= $_POST['IdVol'];
$result = mysqli_query($con,"SELECT * FROM Passager WHERE IdVol='$IdVol'");
echo "<Nest>";
while($row = mysqli_fetch_array($result))
 {
  echo "<Passager>";
  echo "<IdPass>" . $row['IdPass'] . "</IdPass>" ;
  echo "<IdVol>" . $row['IdVol'] . "</IdVol>" ;
  echo "<NomPass>" . $row['NomPass'] . "</NomPass>" ;
  echo "<NumPass>" . $row['NumPass'] . "</NumPass>" ;
  echo "<PrenomPass>" . $row['PrenomPass'] . "</PrenomPass>" ;
  echo "<CheckIn>" . $row['CheckIn'] . "</CheckIn>" ;
  echo "<CheckOut>" . $row['CheckOut'] . "</CheckOut>" ;
  echo "<OnBoard>" . $row['OnBoard'] . "</OnBoard>" ;
  echo "</Passager>";
 }
 echo "</Nest>";

mysqli_close($con);
?>