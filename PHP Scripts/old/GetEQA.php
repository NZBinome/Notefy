<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $Id= $_POST['Id'];
$result = mysqli_query($con,"SELECT * FROM EquipA");
echo "<Nest>";
while($row = mysqli_fetch_array($result))
 {
  echo "<EquipA>";
  echo "<IdEq>" . $row['IdEq'] . "</IdEq>" ;
  echo "</EquipA>";
 }
 echo "</Nest>";

mysqli_close($con);
?>