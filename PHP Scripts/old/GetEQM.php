<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $IdEquipe= $_POST['Id'];
$result = mysqli_query($con,"SELECT * FROM EquipeMaint");
echo "<Nest>";
while($row = mysqli_fetch_array($result))
 {
  echo "<EDM>";
  echo "<IdEquipe>" . $row['IdEquipe'] . "</IdEquipe>" ;
  echo "</EDM>";
 }
 echo "</Nest>";

mysqli_close($con);
?>